#include <iostream>
#include <string>
#include <cstdlib>

int main() {
    int L;
    std::cin >> L;
    int H;
    std::cin >> H;
    std::string T;
    std::cin.ignore();
    std::getline(std::cin, T);
    for(int i = 0; i < H; ++i) {
        std::string ROW;
        std::getline(std::cin, ROW);
        for(auto chr : T) {
            auto upper_chr = std::toupper(chr);
            if(upper_chr >= 'A' && upper_chr <= 'Z') {
                std::cout << ROW.substr((upper_chr - 'A') * L, L);
            } else {
                std::cout << ROW.substr(26 * L, L);
            }
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}
