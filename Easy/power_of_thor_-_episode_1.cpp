#include <iostream>
#include <cstdlib>

int main() {
    int lightX; // the X position of the light of power
    int lightY; // the Y position of the light of power
    int initialTX; // Thor's starting X position
    int initialTY; // Thor's starting Y position
    std::cin >> lightX >> lightY >> initialTX >> initialTY;

    int deltaX = lightX - initialTX;
    int deltaY = lightY - initialTY;

    // game loop
    while(1) {
        int remainingTurns; // The remaining amount of turns Thor can move. Do not remove this line.
        std::cin >> remainingTurns;

        if(deltaX < 0) {
            if(deltaY < 0) {
                ++deltaX;
                ++deltaY;
                std::cout << "NW" << std::endl;
            } else {
                if(deltaY == 0) {
                    ++deltaX;
                    std::cout << "W" << std::endl;
                } else {
                    if(deltaY > 0) {
                        --deltaY;
                        std::cout << "SW" << std::endl;
                    }
                }
            }
        } else {
            if(deltaX == 0) {
                if(deltaY < 0) {
                    ++deltaY;
                    std::cout << "N" << std::endl;
                } else {
                    if(deltaY > 0) {
                        --deltaY;
                        std::cout << "S" << std::endl;
                    }
                }
            } else {
                if(deltaX > 0) {
                    if(deltaY < 0) {
                        --deltaX;
                        ++deltaY;
                        std::cout << "NE" << std::endl;
                    } else {
                        if(deltaY == 0) {
                            --deltaX;
                            std::cout << "E" << std::endl;
                        } else {
                            if(deltaY > 0) {
                                --deltaY;
                                std::cout << "SE" << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
