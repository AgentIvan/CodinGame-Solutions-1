#include <iostream>
#include <string>
#include <cstdlib>

int main() {
    // game loop
    while(1) {
        std::string enemy1; // name of enemy 1
        std::cin >> enemy1;
        int dist1; // distance to enemy 1
        std::cin >> dist1;
        std::string enemy2; // name of enemy 2
        std::cin >> enemy2;
        int dist2; // distance to enemy 2
        std::cin >> dist2;

        if(dist1 < dist2) {
            std::cout << enemy1 << std::endl;
        } else {
            std::cout << enemy2 << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
