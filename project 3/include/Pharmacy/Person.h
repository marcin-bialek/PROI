//  PROI project 3
//  Marcin Białek


#pragma once
#include <Identifiable.h>
#include <Medicine.h>
#include <Prescription.h>

#include <vector>
#include <memory>
#include <string>



struct Person: public Identifiable {
    virtual ~Person() = default;
};



class Employee final: public Person {
public:
    Employee() {}
};



class Customer: public Person {
    std::unique_ptr<Prescription> prescription;
    std::vector<MedicineId> otcMedicines;
    
    
public:
    Customer(std::unique_ptr<Prescription> prescription, std::vector<MedicineId> otcMedicines): prescription(std::move(prescription)), otcMedicines(otcMedicines) {}
    
    auto getPrescription() -> std::unique_ptr<Prescription>;
    auto getOtcMedicines() -> const std::vector<MedicineId>&;
};



class BusinessCustomer: public Customer {
    std::string nip;
    
public:
    BusinessCustomer(std::string nip, std::unique_ptr<Prescription> prescription, std::vector<MedicineId> otcMedicines): Customer(std::move(prescription), otcMedicines), nip(nip) {}
    auto getNip() -> const std::string&;
};

