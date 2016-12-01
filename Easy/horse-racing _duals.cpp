#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdlib>

int main() {
    int N;
    std::cin >> N;
    std::cin.ignore();
    std::vector<int> horses;
    for(int i = 0; i < N; i++) {
        int Pi;
        std::cin >> Pi;
        std::cin.ignore();
        horses.push_back(Pi);
    }
    std::sort(horses.begin(), horses.end());

    unsigned int min_diff = std::numeric_limits<unsigned int>::max();
    auto curr = horses.cbegin(), end = horses.cend();
    while(min_diff > 0 && curr != end) {
        auto diff = std::abs(*curr - *(curr - 1));
        if(diff < min_diff) {
            min_diff = diff;
        }
        ++curr;
    }

    std::cout << min_diff << std::endl;

    return EXIT_SUCCESS;
}
