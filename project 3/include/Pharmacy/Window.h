//  PROI project 3
//  Marcin Białek


#pragma once
#include <Bill.h>
#include <Identifiable.h>
#include <Person.h>
#include <Pharmacy.h>

#include <future>
#include <memory>



class Window: public Identifiable {
    Pharmacy &pharmacy;
    std::unique_ptr<Employee> employee;
    std::unique_ptr<Customer> customer;
    std::future<void> task;
    
    void sellMedicines(std::vector<MedicineId> medicines);
    auto writeReceipt(const std::vector<MedicineId> &medicines) -> std::unique_ptr<Receipt>;
    auto writeInvoice(const std::string &nip, const std::vector<MedicineId> &medicines) -> std::unique_ptr<Invoice>;
    
    
public:
    Window(Pharmacy &pharmacy): pharmacy(pharmacy) {}
    
    void open(std::unique_ptr<Employee> employee);
    auto close() -> std::unique_ptr<Employee>;
    void serve(std::unique_ptr<Customer> customer);
    bool isOpen() const;
    bool isBusy() const;
};
