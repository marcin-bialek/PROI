//  PROI project 3
//  Marcin Białek


#pragma once
#include <Json.h>
#include <Medicine.h>
#include <Person.h>
#include <Prescription.h>

//#include <condition_variable>
#include <future>
#include <map>
#include <mutex>
#include <queue>
#include <set>
#include <thread>
#include <vector>



class Window;



class Pharmacy {
    std::mutex mtx;
    
    Json &config;
    MedicineDatabase &medicineDatabase;
    int ticksFromLastDelivery = 0;
    int numberOfMedicinesToOrder;
    
    double money;
    double profitMargin;
    
    std::queue<std::unique_ptr<Customer>> line;
    std::vector<std::unique_ptr<Employee>> employees;
    std::vector<std::shared_ptr<Window>> windows;
    std::map<MedicineId, uintmax_t> availableMedicines;
    std::map<MedicineId, uintmax_t> medicinesToUnpack;
    std::set<MedicineId> medicinesToOrder;
    
    void initEmployees(Json &config);
    void initWindows(Json &config);
    void initMedicines(Json &config);
    
    auto getAvailableWindow() -> std::shared_ptr<Window>;
    void openWindow();
    void closeWindow();
    auto numberOfOpenedWindows() -> uintmax_t;
    void serveCustomer();
    bool checkPrescription(Prescription &prescription);
    auto takeMedicine(MedicineId id) -> const Medicine*;
    void delivery();
    void unpackMedicines();
    
    
public:
    Pharmacy(Json &config, MedicineDatabase &database);
    
    void newCustomer(std::unique_ptr<Customer> customer);
    void operator()();
    
    friend Window;
};
