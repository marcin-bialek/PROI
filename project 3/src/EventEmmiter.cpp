//  PROI project 3
//  Marcin Białek


#include <Constants.h>
#include <EventEmmiter.h>
#include <Logger.h>
#include <Random.h>

#include <memory>
#include <string>
#include <thread>



void EventEmmiter::operator()() {
    try {
        int ticksPerSecond = config[CONFIG_TICKS_PER_SECOND];
        int simulationTime = config[CONFIG_SIMULATION_TIME];
        double probabilityOfNewCustomer = config[CONFIG_PROBABILITY_OF_NEW_CUSTOMER];

        while(simulationTime-- && !end) {
            if(Random::trueWithProbabilityOf(probabilityOfNewCustomer)) {
                pharmacy.newCustomer(makeRandomCustomer());
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / ticksPerSecond));
        }
    }
    catch (Exception e) {
        Logger::error(e.getMessage());
    }
    
     end = true;
}



auto EventEmmiter::makeRandomNip() -> std::string {
    std::string nip = "";
    
    for(int i = 0; i < 10; i++) {
        nip += Random::numberFromRange(0, 9) + '0';
    }
    
    return nip;
}



auto EventEmmiter::makeRandomCustomer() -> std::unique_ptr<Customer> {
    std::vector<MedicineId> rxMedicines, otcMedicines;
    auto medicineIds = medicineDatabase.getAllMedicineIds();

    for(uintmax_t i = 0; i < Random::numberFromRange(0, maxMedicinesPerCustomer); i++) {
        uintmax_t index = Random::numberFromRange(0, medicineIds.size() - 1);
        MedicineId id = medicineIds[index];
        auto medicine = medicineDatabase.getMedicineById(id);

        if(medicine->prescription) {
            rxMedicines.push_back(id);
        }
        else {
            otcMedicines.push_back(id);
        }
    }
    
    if(Random::trueWithProbabilityOf(0.2)) {
        auto customer = new BusinessCustomer(makeRandomNip(), writePrescription(rxMedicines), otcMedicines);
        return std::unique_ptr<Customer>(customer);
    }

    auto customer = new Customer(writePrescription(rxMedicines), otcMedicines);
    return std::unique_ptr<Customer>(customer);
}



auto EventEmmiter::writePrescription(std::vector<MedicineId> rxMedicines) -> std::unique_ptr<Prescription> {
    if(rxMedicines.empty()) {
        return std::unique_ptr<Prescription>(nullptr);
    }

    return std::unique_ptr<Prescription>(new Prescription(rxMedicines, PRESCRIPTION_VALID_SIGNATURE));
}
