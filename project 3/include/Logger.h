//  PROI project 3
//  Marcin Białek


#pragma once
#include <fstream>
#include <string>
#include <thread>
#include <queue>



class Logger {
    static std::mutex mtx;
    static std::condition_variable var;
    static std::thread saverThread;
    static std::fstream file;
    static std::queue<std::string> logsToSave;
    static bool running;
    
    static void pushLogIntoQueue(std::string message);
    static void saverLoop();
    
    
public:
    static void init(std::string logFilePath);
    static void join();
    static void end();
    
    static void info(std::string message);
    static void warning(std::string message);
    static void error(std::string message);
};

