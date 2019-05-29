//  PROI project 3
//  Marcin Białek


#pragma once


#define LOGS_FILE_PATH      "./pharmacy.log"
#define CONFIG_FILE_PATH    "./pharmacy.json"


#define CONFIG_TICKS_PER_SECOND             "simulation/ticks per second"
#define CONFIG_SIMULATION_TIME              "simulation/time"
#define CONFIG_PROBABILITY_OF_NEW_CUSTOMER  "simulation/probability of new client per tick"
#define CONFIG_MAX_MEDICINES_PER_CUSTOMER   "simulation/max medicines per customer"
#define CONFIG_DELIVERY_INTERVAL            "simulation/delivery interval"


#define CONFIG_MEDICINE_GROUPS              "medicine groups"
#define CONFIG_MEDICINES                    "medicines"
#define CONFIG_MEDICINE_NAME(id)            "medicines/" + std::to_string(id) + "/name"
#define CONFIG_MEDICINE_GROUP(id)           "medicines/" + std::to_string(id) + "/group"
#define CONFIG_MEDICINE_PRICE(id)           "medicines/" + std::to_string(id) + "/price"
#define CONFIG_MEDICINE_PRESCRIPTION(id)    "medicines/" + std::to_string(id) + "/prescription"


#define CONFIG_NUMBER_OF_EMPLOYEES              "pharmacy/number of employees"
#define CONFIG_NUMBER_OF_WINDOWS                "pharmacy/number of windows"
#define CONFIG_NUMBER_OF_EACH_MEDICINE_AT_START "pharmacy/number of each medicine at start"
#define CONFIG_NUMBER_OF_MEDICINES_TO_ORDER     "pharmacy/number of medicines to order"
#define CONFIG_MONEY                            "pharmacy/money at start"
#define CONFIG_PROFIT_MARGIN                    "pharmacy/profit margin"
#define CONFIG_QUEUE_SIZE                       "pharmacy/queue size to open new window"
#define PRESCRIPTION_VALID_SIGNATURE            "xyz"


#define LOGGER_MSG_1(id) "Nowy klient (" + std::to_string(id) + ")."
#define LOGGER_MSG_2(id1, id2) "Pracownik (" + std::to_string(id1) + ") otworzył okienko (" + std::to_string(id2) + ")."
#define LOGGER_MSG_3(id1, id2) "Klient (" + std::to_string(id1) + ") jest obsługiwany przy okienku (" + std::to_string(id2) + ")."
#define LOGGER_MSG_4(id) "Klient (" + std::to_string(id) + ") został obsłużony."
#define LOGGER_MSG_5(id) "Lek (" + std::to_string(id) + ") został wyprzedany."
#define LOGGER_MSG_6(c) "\nNowa dostawa:\n" + c
#define LOGGER_MSG_7(id) "Pracownik (" + std::to_string(id) + ") poszedł odpakowywać leki."
#define LOGGER_MSG_8(id) "Pracownik (" + std::to_string(id) + ") skończył odpakowywać leki."
#define LOGGER_MSG_9(id) "Okienko (" + std::to_string(id) + ") zostało zamknięte."
#define LOGGER_MSG_11(id) "Klient (" + std::to_string(id) + ") ma niepoprawną receptę."
#define LOGGER_MSG_12(id) "Klient chce kupić lek (" + std::to_string(id) + "), który nie istnieje."
#define LOGGER_MSG_13(id) "Klient chce kupić lek (" + std::to_string(id) + "), który się skończył."
#define LOGGER_MSG_14(id) "Lek (" + std::to_string(id) + ") nie istnieje w bazie."
#define LOGGER_MSG_15(id) "Zamówiony lek (" + std::to_string(id) + ") nie istnieje w bazie."
#define LOGGER_MSG_16(id, b) "\nKlient (" + std::to_string(id) + ") otrzymał paragon:\n" + b
#define LOGGER_MSG_17(id, b) "\nKlient (" + std::to_string(id) + ") otrzymał fakturę:\n" + b


#define RECEIPT_FORMAT_A(n, c, p) std::setw(4) << "" << std::left << std::setw(27) << (n + " × " + std::to_string(c)) << std::right << std::setw(7) << std::fixed << std::setprecision(2) << p << " PLN" << std::endl
#define RECEIPT_FORMAT_B(p) std::setw(4) << "" << std::left << std::setw(26) << "SUMA:" << std::right << std::setw(7) << std::fixed << std::setprecision(2) << p << " PLN" << std::endl


#define INVOICE_FORMAT_A(n) std::setw(4) << "" << std::left << "NIP: " << n << std::endl
#define INVOICE_FORMAT_B std::setw(4) << "" << std::left << std::setw(19) << "NAZWA" << std::right << std::setw(4) << "LICZBA" << std::setw(11) << "VAT" << std::setw(13) << "NETTO" << std::setw(13) << "BRUTTO" << std::setw(18) << "KATEGORIA LEKU" << std::endl
#define INVOICE_FORMAT_C(n, c, t, a, b, g) std::setw(4) << "" << std::left << std::setw(23) << n << std::right << std::setw(2) << std::to_string(c) << std::setw(9) << std::fixed << std::setprecision(2) << t << " %" << std::setw(9) << std::fixed << std::setprecision(2) << a << " PLN" << std::setw(9) << std::fixed << std::setprecision(2) << b << " PLN    " << g << std::endl
#define INVOICE_FORMAT_D(c, a, b) std::setw(4) << "" << std::left << std::setw(23) << "SUMA:" << std::right << std::setw(2) << c << std::setw(20) << std::fixed << std::setprecision(2) << a << " PLN" << std::setw(9) << std::fixed << std::setprecision(2) << b << " PLN" << std::endl
