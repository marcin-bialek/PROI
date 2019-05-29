//  PROI project 3
//  Marcin Białek


#include <Constants.h>
#include <Logger.h>
#include <Medicine.h>



MedicineDatabase::MedicineDatabase(Json &config) {
    initGroups(config);
    initMedicines(config);
}



void MedicineDatabase::initGroups(Json &config) {
    config[CONFIG_MEDICINE_GROUPS].forEach([this](std::string key, Json::Value &value) {
        groups[key] = static_cast<std::string>(value);
    });
}



void MedicineDatabase::initMedicines(Json &config) {
    const uintmax_t length = config[CONFIG_MEDICINES].length();
    
    for(uintmax_t i = 0; i < length; i++) {
        medicines[i] = {
            config[CONFIG_MEDICINE_NAME(i)],
            config[CONFIG_MEDICINE_GROUP(i)],
            config[CONFIG_MEDICINE_PRICE(i)],
            config[CONFIG_MEDICINE_PRESCRIPTION(i)]
        };
    }
}



auto MedicineDatabase::getAllMedicineIds() const -> std::vector<MedicineId> {
    std::vector<MedicineId> ids;
    
    for(auto i = medicines.begin(); i != medicines.end(); i++) {
        ids.push_back(i->first);
    }
    
    return ids;
}



auto MedicineDatabase::getGroup(std::string group) const -> const std::string* {
    if(groups.find(group) == groups.end())
        return nullptr;
        
    return &groups.at(group);
}



auto MedicineDatabase::getMedicineById(MedicineId id) const -> const Medicine* {
    if(medicines.find(id) == medicines.end())
        return nullptr;
        
    return &medicines.at(id);
}



auto MedicineDatabase::getMedicineByName(std::string name) const -> const Medicine* {
    for(auto i = medicines.begin(); i != medicines.end(); i++) {
        if(i->second.name == name) {
            return &i->second;
        }
    }
    
    return nullptr;
}
