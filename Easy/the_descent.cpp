#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // game loop
    while(1) {
        std::vector<int> heights;
        heights.reserve(8);

        for(int i = 0; i < 8; i++) {
            int mountainH; // represents the height of one mountain.
            std::cin >> mountainH;
            heights.push_back(mountainH);
        }

        std::cout << std::distance(heights.cbegin(), std::max_element(heights.cbegin(), heights.cend())) << std::endl; // The index of the mountain to fire on.
    }

    return EXIT_SUCCESS;
}
