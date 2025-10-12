#pragma once

#include <string>
#include <chrono>

namespace et::domain {

struct Money {
    double amount;
    std::string currency;
};

struct Transaction {
    std::string id;
    std::chrono::system_clock::time_point date;
    Money amount;
    std::string description;
    std::string category;  // Optional, could be assigned later
};

struct Statement {
    std::string bankName;
    std::string accountNumber;
    std::chrono::system_clock::time_point startDate;
    std::chrono::system_clock::time_point endDate;
    Money openingBalance;
    Money closingBalance;
};

} // namespace et::domain
