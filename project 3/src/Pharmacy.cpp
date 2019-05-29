//  PROI project 3
//  Marcin Białek


#include <Bill.h>
#include <Constants.h>
#include <Exception.h>
#include <Logger.h>
#include <Pharmacy.h>
#include <Random.h>
#include <Window.h>

#include <iomanip>
#include <sstream>



Pharmacy::Pharmacy(Json &config, MedicineDatabase &database): config(config), medicineDatabase(database) {
    numberOfMedicinesToOrder = config[CONFIG_NUMBER_OF_MEDICINES_TO_ORDER];
    profitMargin = config[CONFIG_PROFIT_MARGIN];
    money = config[CONFIG_MONEY];
    
    initEmployees(config);
    initWindows(config);
    initMedicines(config);
}



void Pharmacy::initEmployees(Json &config) {
    int numberOfEmployees = config[CONFIG_NUMBER_OF_EMPLOYEES];
    
    if(numberOfEmployees <= 0) {
        throw Exception("There must be at least 1 employee in the pharmacy.");
    }
    
    while(numberOfEmployees--) {
        employees.push_back(std::unique_ptr<Employee>(new Employee()));
    }
}



void Pharmacy::initWindows(Json &config) {
    int numberOfWindows = config[CONFIG_NUMBER_OF_WINDOWS];
    
    if(numberOfWindows <= 0) {
        throw Exception("There must be at least 1 window in the pharmacy.");
    }
    
    while(numberOfWindows--) {
        windows.push_back(std::make_shared<Window>(*this));
    }
}



void Pharmacy::initMedicines(Json &config) {
    auto ids = medicineDatabase.getAllMedicineIds();
    int numberOfMedicines = config[CONFIG_NUMBER_OF_EACH_MEDICINE_AT_START];
    
    for(auto &id : ids) {
        availableMedicines[id] = numberOfMedicines;
    }
}



auto Pharmacy::getAvailableWindow() -> std::shared_ptr<Window> {
    for(auto window : windows) {
        if(window->isOpen() && !window->isBusy())
            return window;
    }
    
    return nullptr;
}



void Pharmacy::openWindow() {
    if(employees.empty()) return;
    
    for(auto window : windows) {
        if(!window->isOpen()) {
            window->open(std::move(employees.back()));
            employees.pop_back();
            return;
        }
    }
}



void Pharmacy::closeWindow() {
    for(auto window : windows) {
        if(window->isOpen() && !window->isBusy()) {
            employees.push_back(window->close());
            return;
        }
    }
}



auto Pharmacy::numberOfOpenedWindows() -> uintmax_t {
    uintmax_t opened = 0;
    
    for(auto window : windows) {
        if(window->isOpen())
            opened++;
    }
    
    return opened;
}



void Pharmacy::operator()() {
    try {
        int ticksPerSecond = config[CONFIG_TICKS_PER_SECOND];
        int simulationTime = config[CONFIG_SIMULATION_TIME];
        int deliveryInterval = config[CONFIG_DELIVERY_INTERVAL];
        int queueSizeToOpenNewWindow = config[CONFIG_QUEUE_SIZE];
        
        while(simulationTime-- && !end) {
            if(ticksFromLastDelivery++ == deliveryInterval && medicinesToUnpack.empty()) {
                if(!medicinesToOrder.empty()) {
                    delivery();
                }
                
                ticksFromLastDelivery = 0;
            }
            
            if(line.empty()) {
                closeWindow();
            }
            else if(!line.empty() && getAvailableWindow() != nullptr) {
                serveCustomer();
            }
            else if((!line.empty() && numberOfOpenedWindows() == 0) || (int)line.size() >= queueSizeToOpenNewWindow) {
                openWindow();
            }

            if(!medicinesToUnpack.empty() && !employees.empty()) {
                unpackMedicines();
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / ticksPerSecond));
        }
    }
    catch (Exception e) {
        Logger::error(e.getMessage());
    }
    
    end = true;
}



void Pharmacy::newCustomer(std::unique_ptr<Customer> customer) {
    Logger::info(LOGGER_MSG_1(customer->getId()));
    
    {
        std::lock_guard<std::mutex> lock(mtx);
        line.push(std::move(customer));
    }
}



void Pharmacy::serveCustomer() {
    if(auto window = getAvailableWindow()) {
        std::unique_ptr<Customer> customer;
        
        {
            std::lock_guard<std::mutex> lock(mtx);
            customer = std::move(line.front());
            line.pop();
        }
        
        window->serve(std::move(customer));
    }
}



bool Pharmacy::checkPrescription(Prescription &prescription) {
    if(prescription.signature == PRESCRIPTION_VALID_SIGNATURE)
        return true;
    
    return false;
}



auto Pharmacy::takeMedicine(MedicineId id) -> const Medicine* {
    if(availableMedicines.find(id) == availableMedicines.end()) {
        Logger::warning(LOGGER_MSG_12(id));
        return nullptr;
    }

    if(availableMedicines.at(id) == 0) {
        Logger::warning(LOGGER_MSG_13(id));
        return nullptr;
    }
    
    std::lock_guard<std::mutex> lock(mtx);
    availableMedicines[id] = availableMedicines.at(id) - 1;
    
    if(availableMedicines.at(id) == 0) {
        medicinesToOrder.insert(id);
        Logger::info(LOGGER_MSG_5(id));
    }
    
    if(auto medicine = medicineDatabase.getMedicineById(id)) {
        return medicine;
    }
    
    Logger::warning(LOGGER_MSG_14(id));
    return nullptr;
}



void Pharmacy::delivery() {
    Invoice invoice;
    invoice.nip = "1234567890";
    
    {
        std::lock_guard<std::mutex> lock(mtx);
        
        for(auto id : medicinesToOrder) {
            medicinesToUnpack[id] = numberOfMedicinesToOrder;
            
            if(auto medicine = medicineDatabase.getMedicineById(id)) {
                if(auto group = medicineDatabase.getGroup(medicine->group)) {
                    for(int i = 0; i < numberOfMedicinesToOrder; i++) {
                        invoice.addProduct(medicine->name, *group, medicine->price, profitMargin);
                    }
                }
            }
            else {
                Logger::warning(LOGGER_MSG_15(id));
            }
        }
        
        medicinesToOrder.clear();
        money = money - invoice.sum();
    }
    
    Logger::info(LOGGER_MSG_6(invoice.toString()));
}



void Pharmacy::unpackMedicines() {
    static std::vector<std::future<void>> tasks;
    
    if(employees.empty())
        return;
    
    auto task = std::async(std::launch::async, [&](std::unique_ptr<Employee> employee) {
        Logger::info(LOGGER_MSG_7(employee->getId()));
        
        mtx.lock();
        
        while(!medicinesToUnpack.empty()) {
            auto i = medicinesToUnpack.begin();
            auto id = i->first;
            auto howMany = i->second;
            medicinesToUnpack.erase(i);
            mtx.unlock();
            
            std::this_thread::sleep_for(std::chrono::seconds(Random::numberFromRange(1, 2)));
            if(end) {
                return;
            }
            
            mtx.lock();
            availableMedicines[id] = availableMedicines.at(id) + howMany;
        }
        
        uintmax_t id = employee->getId();
        employees.push_back(std::move(employee));
        mtx.unlock();
        
        Logger::info(LOGGER_MSG_8(id));
    }, std::move(employees.back()));
    
    employees.pop_back();
    tasks.push_back(std::move(task));
}

