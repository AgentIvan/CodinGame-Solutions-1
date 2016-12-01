#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>

int main() {
    std::size_t R;
    std::cin >> R;
    std::cin.ignore();
    std::size_t L;
    std::cin >> L;
    std::cin.ignore();

    std::vector<std::size_t> curr_sequence{R};
    std::vector<std::size_t> next_sequence;

    for(std::size_t i = 1; i < L; ++i) {
        auto curr_it = curr_sequence.cbegin(), end_it = curr_sequence.cend();
        while(curr_it != end_it) {
            auto curr = *curr_it;
            std::size_t count = 1;

            while(curr_it + 1 != end_it && *(curr_it + 1) == curr) {
                ++count;
                ++curr_it;
            }
            ++curr_it;

            next_sequence.push_back(count);
            next_sequence.push_back(curr);
        }

        curr_sequence = next_sequence;
        next_sequence.clear();
    }
    for(auto it = curr_sequence.cbegin(), end_it = curr_sequence.cend(); it != end_it; ++it) {
        std::cout << *it << ((it == end_it - 1) ? "" : " ");
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
