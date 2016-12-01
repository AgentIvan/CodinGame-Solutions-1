#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstdlib>

std::string mayan(unsigned long int dec, std::vector<std::string> const & digits);
unsigned long int decimal(std::string const & mayan, std::size_t width, std::size_t height, std::vector<std::string> const & digits);
void print_mayan(std::string const & mayan, std::size_t width, std::size_t height, std::ostream & os = std::cout);

int main() {
    std::size_t L;
    std::size_t H;
    std::cin >> L >> H;
    std::cin.ignore();

    std::vector<std::string> digits(20);
    for(std::size_t i = 0; i < H; i++) {
        std::string numeral;
        std::cin >> numeral;
        std::cin.ignore();

        for(std::size_t digit = 0; digit < 20; ++digit) {
            digits.at(digit).append(numeral.substr(L * digit, L));
        }
    }

    std::size_t S1;
    std::cin >> S1;
    std::cin.ignore();
    std::string num1;
    for(std::size_t i = 0; i < S1; i++) {
        std::string num1Line;
        std::cin >> num1Line;
        std::cin.ignore();
        num1.append(num1Line);
    }

    std::size_t S2;
    std::cin >> S2;
    std::cin.ignore();
    std::string num2;
    for(std::size_t i = 0; i < S2; i++) {
        std::string num2Line;
        std::cin >> num2Line;
        std::cin.ignore();
        num2.append(num2Line);
    }

    char operation;
    std::cin >> operation;
    std::cin.ignore();

    auto num1_dec = decimal(num1, L, H, digits);
    auto num2_dec = decimal(num2, L, H, digits);
    unsigned long int result = 0;

    switch(operation) {
        case '*':
            result = num1_dec * num2_dec;
            break;
        case '/':
            result = num1_dec / num2_dec;
            break;
        case '+':
            result = num1_dec + num2_dec;
            break;
        case '-':
            result = num1_dec - num2_dec;
            break;
        default:
            std::cerr << "Illegal operation" << std::endl;
            break;
    }

    print_mayan(mayan(result, digits), L, H);

    return EXIT_SUCCESS;
}

unsigned long int decimal(std::string const & mayan, std::size_t width, std::size_t height, std::vector<std::string> const & digits) {
    unsigned long int ret = 0;
    for(std::size_t position = 0; position < mayan.length() / (width * height); ++position) {
        auto curr_digit = std::distance(digits.cbegin(), std::find(digits.cbegin(), digits.cend(), mayan.substr(mayan.length() - width * height * (position + 1), width * height)));

        unsigned long int acc = 1;
        for(std::size_t power = 0; power < position; ++power) {
            acc *= 20;
        }

        ret += curr_digit * acc;
    }

    return ret;
}

std::string mayan(unsigned long int dec, std::vector<std::string> const & digits) {
    std::string ret;

    std::stack<unsigned long int> s;
    s.push(dec);
    while(dec > 20) {
        s.pop();
        s.push(dec % 20);
        s.push(dec / 20);
        dec /= 20;
    }

    while(!s.empty()) {
        ret.append(digits.at(s.top()));
        s.pop();
    }

    return ret;
}

void print_mayan(std::string const & mayan, std::size_t width, std::size_t height, std::ostream & os) {
    for(std::size_t index = 0; index < mayan.length(); index += width) {
        os << mayan.substr(index, width) << std::endl;
    }
}
