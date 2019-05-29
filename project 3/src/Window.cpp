//  PROI project 3
//  Marcin Białek


#include <Bill.h>
#include <Constants.h>
#include <Exception.h>
#include <Logger.h>
#include <Random.h>
#include <Window.h>

#include <iomanip>
#include <future>
#include <sstream>



void Window::open(std::unique_ptr<Employee> employee) {
    this->employee = std::move(employee);
    Logger::info(LOGGER_MSG_2(this->employee->getId(), getId()));
}



auto Window::close() -> std::unique_ptr<Employee> {
    Logger::info(LOGGER_MSG_9(getId()));
    return std::move(employee);
}



bool Window::isOpen() const {
    return employee != nullptr;
}



bool Window::isBusy() const {
    return customer != nullptr;
}



void Window::serve(std::unique_ptr<Customer> customer) {
    this->customer = std::move(customer);
    
    task = std::async(std::launch::async, [&] {
        std::this_thread::sleep_for(std::chrono::seconds(Random::numberFromRange(4, 8)));
        if(end) {
            return;
        }
        
        auto medicines = this->customer->getOtcMedicines();
        
        if(auto prescription = this->customer->getPrescription()) {
            if(!pharmacy.checkPrescription(*prescription.get())) {
                Logger::warning(LOGGER_MSG_11(this->customer->getId()));
                return;
            }
            
            medicines.insert(medicines.begin(), prescription->medicines.begin(), prescription->medicines.end());
        }

        if(!medicines.empty()) {
            sellMedicines(medicines);
        }

        Logger::info(LOGGER_MSG_4(this->customer->getId()));
        this->customer.reset();
    });
    
    Logger::info(LOGGER_MSG_3(this->customer->getId(), getId()));
}



void Window::sellMedicines(std::vector<MedicineId> medicines) {
    if(auto customer = dynamic_cast<BusinessCustomer*>(this->customer.get())) {
        std::unique_ptr<Bill> bill = writeInvoice(customer->getNip(), medicines);
        Logger::info(LOGGER_MSG_17(this->customer->getId(), bill->toString()));
    }
    else {
        std::unique_ptr<Bill> bill = writeReceipt(medicines);
        Logger::info(LOGGER_MSG_16(this->customer->getId(), bill->toString()));
    }
}



auto Window::writeReceipt(const std::vector<MedicineId> &medicines) -> std::unique_ptr<Receipt> {
    std::unique_ptr<Receipt> receipt(new Receipt);
    
    for(auto id : medicines) {
        if(auto medicine = pharmacy.takeMedicine(id)) {
            receipt->addProduct(medicine->name, medicine->price);
        }
    }
    
    return receipt;
}



auto Window::writeInvoice(const std::string &nip, const std::vector<MedicineId> &medicines) -> std::unique_ptr<Invoice> {
    std::unique_ptr<Invoice> invoice(new Invoice);
    invoice->nip = nip;
    
    for(auto id : medicines) {
        if(auto medicine = pharmacy.takeMedicine(id)) {
            if(auto group = pharmacy.medicineDatabase.getGroup(medicine->group)) {
                invoice->addProduct(medicine->name, *group, medicine->price, pharmacy.profitMargin);
            }
        }
    }
    
    return invoice;
}
