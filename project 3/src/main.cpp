//  PROI project 3
//  Marcin Białek


#include <Constants.h>
#include <EventEmmiter.h>
#include <Exception.h>
#include <Json.h>
#include <Logger.h>
#include <Medicine.h>
#include <Pharmacy.h>
#include <Random.h>


#include <iostream>
#include <thread>


volatile bool end = false;


int main() {
    using namespace std;
    
    Json config;
    
    try {
        Logger::init(LOGS_FILE_PATH);
        
        config.loadFromFile(CONFIG_FILE_PATH);
        
        MedicineDatabase database(config);
        Pharmacy pharmacy(config, database);
        EventEmmiter emmiter(config, pharmacy, database);
        
        thread pharmacyThread(ref(pharmacy));
        thread eventEmmiterThread(ref(emmiter));
        eventEmmiterThread.join();
        pharmacyThread.join();
    }
    catch(Exception e) {
        cout << e.getMessage() << endl;
    }
    
    Logger::end();
    Logger::join();
}
