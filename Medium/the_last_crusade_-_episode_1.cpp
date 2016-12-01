#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <utility>

int main() {
    std::size_t W; // number of columns.
    std::size_t H; // number of rows.
    std::cin >> W >> H;
    std::cin.ignore();
    std::map<std::pair<std::size_t, std::size_t>, std::size_t> grid;
    for(std::size_t i = 0; i < H; ++i) {
        for(std::size_t j = 0; j < W; ++j) {
            unsigned int type = 0;
            std::cin >> type;
            std::cin.ignore();

            grid[{i, j}] = type;
        }
    }
    std::size_t EX; // the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
    std::cin >> EX;
    std::cin.ignore();

    // game loop
    while(1) {
        std::size_t XI;
        std::size_t YI;
        std::string POS;
        std::cin >> XI >> YI >> POS;
        std::cin.ignore();

        switch(grid.at({YI, XI})) {
            case 0:
                std::cerr << "This should never happen" << std::endl;
                break;
            case 1:
            case 3:
            case 7:
            case 8:
            case 9:
            case 12:
            case 13:
                std::cout << XI << ' ' << YI + 1 << std::endl;
                break;
            case 2:
            case 6:
                if(POS == "LEFT") {
                    std::cout << XI + 1;
                } else {
                    if(POS == "RIGHT") {
                        std::cout << XI - 1;
                    }
                }
                std::cout << ' ' << YI << std::endl;
                break;
            case 4:
                if(POS == "TOP") {
                    std::cout << XI - 1 << ' ' << YI << std::endl;
                } else {
                    if(POS == "RIGHT") {
                        std::cout << XI << ' ' << YI + 1 << std::endl;
                    }
                }
                break;
            case 5:
                if(POS == "TOP") {
                    std::cout << XI + 1 << ' ' << YI << std::endl;
                } else {
                    if(POS == "LEFT") {
                        std::cout << XI << ' ' << YI + 1 << std::endl;
                    }
                }
                break;
            case 10:
                std::cout << XI - 1 << ' ' << YI << std::endl;
                break;
            case 11:
                std::cout << XI + 1 << ' ' << YI << std::endl;
                break;
            default:
                std::cerr << "Unknown type. This should never happen" << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
