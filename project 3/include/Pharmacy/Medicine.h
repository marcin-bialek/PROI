//  PROI project 3
//  Marcin Białek


#pragma once
#include <Identifiable.h>
#include <Json.h>

#include <map>
#include <string>



typedef uintmax_t MedicineId;



struct Medicine {
    std::string name;
    std::string group;
    double price;
    bool prescription;
};



class MedicineDatabase {
    std::map<std::string, std::string> groups;
    std::map<MedicineId, Medicine> medicines;
    
    void initGroups(Json &config);
    void initMedicines(Json &config);
    
    
public:
    MedicineDatabase(Json &config);
    
    auto getMedicineById(MedicineId id) const -> const Medicine*;
    auto getMedicineByName(std::string name) const -> const Medicine*;
    auto getAllMedicineIds() const -> std::vector<MedicineId>;
    auto getGroup(std::string) const -> const std::string*;
};

