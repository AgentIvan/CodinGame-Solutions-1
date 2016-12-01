#include <iostream>
#include <string>
#include <cstdlib>

int main() {
    std::size_t W; // width of the building.
    std::size_t H; // height of the building.
    std::cin >> W >> H;
    std::cin.ignore();
    std::size_t N; // maximum number of turns before game over.
    std::cin >> N;
    std::cin.ignore();
    std::size_t X0;
    std::size_t Y0;
    std::cin >> X0 >> Y0;
    std::cin.ignore();

    std::size_t l = 0, r = W, t = 0, b = H;
    std::size_t x = X0, y = Y0;

    // game loop
    while (1) {
        std::string bombDir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        std::cin >> bombDir;
        std::cin.ignore();

        if(bombDir == "U") {
            l = x;
            r = x + 1;
            b = y;
        }
        if(bombDir == "UR") {
            l = x + 1;
            b = y;
        }
        if(bombDir == "R") {
            l = x + 1;
            t = y;
            b = y + 1;
        }
        if(bombDir == "DR") {
            l = x + 1;
            t = y + 1;
        }
        if(bombDir == "D") {
            l = x;
            r = x + 1;
            t = y + 1;
        }
        if(bombDir == "DL") {
            r = x;
            t = y + 1;
        }
        if(bombDir == "L") {
            r = x;
            t = y;
            b = y + 1;
        }
        if(bombDir == "UL") {
            r = x;
            b = y;
        }

        x = l + (r - l) / 2;
        y = t + (b - t) / 2;

        std::cout << x << ' ' << y << std::endl;
    }

    return EXIT_SUCCESS;
}
