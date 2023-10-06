#include <iostream>
#include <string>
#include <stdexcept>

class InvalidDayException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid day entered.";
    }
};

class InvalidMonthException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid month entered.";
    }
};

int main() {
    int month, day, year;

    try {
        std::cout << "Enter a date of birth (M-D-YYYY): ";
        std::string input;
        std::cin >> input;

        size_t pos1 = input.find('-');
        size_t pos2 = input.rfind('-');

        if (pos1 == std::string::npos || pos2 == std::string::npos) {
            throw std::invalid_argument("Invalid date format");
        }

        month = std::stoi(input.substr(0, pos1));
        day = std::stoi(input.substr(pos1 + 1, pos2 - pos1 - 1));
        year = std::stoi(input.substr(pos2 + 1));

        if (month < 1 || month > 12) {
            throw InvalidMonthException();
        }

        if (day < 1 || day > 31) {
            throw InvalidDayException();
        }

        if (year < 0 || year > 2023) {
            throw std::invalid_argument("Invalid year entered.");
        }

        // leap year finder
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (month == 2 && day > 29) {
                throw InvalidDayException();
            }
        } else {
            if (month == 2 && day > 28) {
                throw InvalidDayException();
            }
        }

        std::string months[] = {"January", "February", "March", "April", "May", "June",
                                "July", "August", "September", "October", "November", "December"};

        std::cout << "Formatted date of birth: " << months[month - 1] << " " << day << ", " << year << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
