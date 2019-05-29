//  PROI project 3
//  Marcin Białek


#pragma once
#include <Constants.h>
#include <Json.h>
#include <Person.h>
#include <Pharmacy.h>
#include <Prescription.h>

#include <array>



class EventEmmiter {
    Json &config;
    Pharmacy &pharmacy;
    MedicineDatabase &medicineDatabase;

    const int maxMedicinesPerCustomer;

    auto makeRandomNip() -> std::string;
    auto makeRandomCustomer() -> std::unique_ptr<Customer>;
    auto writePrescription(std::vector<MedicineId> rxMedicines) -> std::unique_ptr<Prescription>;


public:
    EventEmmiter(Json &config, Pharmacy &pharmacy, MedicineDatabase &database):
            config(config),
            pharmacy(pharmacy),
            medicineDatabase(database),
            maxMedicinesPerCustomer(config[CONFIG_MAX_MEDICINES_PER_CUSTOMER]) {}

    void operator ()();
};

