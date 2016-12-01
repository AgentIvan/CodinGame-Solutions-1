#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

int main() {
    std::string MESSAGE;
    std::getline(std::cin, MESSAGE);

    std::vector<bool> bits;
    for(auto const & chr : MESSAGE) {
        for(std::size_t bit_index = 7; bit_index > 0; --bit_index) {
            bits.push_back((chr >> (bit_index - 1)) & 1);
        }
    }

    auto curr = bits.cbegin(), end = bits.cend();
    while(curr != end) {
        std::cout << (*curr ? "0 " : "00 ") << '0';
        while(std::distance(curr, end) > 1 && *(curr + 1) == *curr) {
            std::cout << '0';
            ++curr;
        }
        if(std::distance(curr, end) > 1) {
            std::cout << ' ';
        }
        ++curr;
    }

    return EXIT_SUCCESS;
}
