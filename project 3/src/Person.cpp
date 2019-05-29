//  PROI project 3
//  Marcin Białek


#include <Person.h>



auto Customer::getPrescription() -> std::unique_ptr<Prescription> {
    return std::move(prescription);
}



auto Customer::getOtcMedicines() -> const std::vector<MedicineId>& {
    return otcMedicines;
}



auto BusinessCustomer::getNip() -> const std::string& {
    return nip;
}
