//  PROI project 3
//  Marcin Białek


#pragma once
#include <Identifiable.h>
#include <Medicine.h>

#include <string>
#include <vector>



struct Prescription: public Identifiable {
    const std::vector<MedicineId> medicines;
    const std::string signature;
    
    Prescription(std::vector<MedicineId> medicines, std::string signature): medicines(medicines), signature(signature) {}
};
