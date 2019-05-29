//  PROI project 3
//  Marcin Białek


#include <Exception.h>
#include <Logger.h>

#include <iostream>



std::mutex Logger::mtx;
std::fstream Logger::file;
std::condition_variable Logger::var;
std::queue<std::string> Logger::logsToSave;
std::thread Logger::saverThread;
bool Logger::running = false;



void Logger::init(std::string logFilePath) {
    file.open(logFilePath, std::ios::trunc | std::ios::out);
    
    if(!file.good())
        throw Exception("Error opening log file.");
    
    saverThread = std::thread(saverLoop);
    running = true;
}



void Logger::join() {
    ::end = true;
    
    if(running) {
        file.close();
        saverThread.join();
    }
}



void Logger::end() {
    file.close();
    var.notify_one();
}



void Logger::pushLogIntoQueue(std::string message) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        logsToSave.push(message);
    }
    
    var.notify_one();
}



void Logger::saverLoop() {
    while(!::end) {
        std::unique_lock<std::mutex> lock(mtx);

        var.wait(lock, [&] {
            return !logsToSave.empty() || ::end;
        });

        while(!logsToSave.empty()) {
            file << logsToSave.front() << std::endl;
            logsToSave.pop();
        }
    }
}



void Logger::info(std::string message) {
    std::cout << message << std::endl;
    pushLogIntoQueue(message);
}



void Logger::warning(std::string message) {
    message = "[WARNING] " + message;
    
    std::cout << message << std::endl;
    pushLogIntoQueue(message);
}



void Logger::error(std::string message) {
    message = "[ERROR] " + message;
    
    std::cout << message << std::endl;
    pushLogIntoQueue(message);
}



