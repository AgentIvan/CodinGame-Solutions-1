#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

int main() {
    int width; // the number of cells on the X axis
    std::cin >> width;
    std::cin.ignore();
    int height; // the number of cells on the Y axis
    std::cin >> height;
    std::cin.ignore();

    std::vector<std::vector<bool>> map(height, std::vector<bool>(width, false));

    for(int i = 0; i < height; ++i) {
        std::string line; // width characters, each either 0 or .
        std::getline(std::cin, line);

        for(int j = 0; j < width; ++j) {
            if(line.at(j) == '0') {
                map.at(i).at(j) = true;
            }
        }
    }

    for(int vindex = 0; vindex < height; ++vindex) {
        for(int hindex = 0; hindex < width; ++hindex) {
            if(map.at(vindex).at(hindex)) {
                std::cout << hindex << ' ' << vindex << ' ';

                int right_neighbor_x = -1;
                for(int right_index = hindex + 1; right_index < width; ++right_index) {
                    if(map.at(vindex).at(right_index)) {
                        right_neighbor_x = right_index;
                        break;
                    }
                }
                std::cout << right_neighbor_x << ' ' << ((right_neighbor_x == -1) ? -1 : vindex) << ' ';

                int bottom_neighbor_y = -1;
                for(int bottom_index = vindex + 1; bottom_index < height; ++bottom_index) {
                    if(map.at(bottom_index).at(hindex)) {
                        bottom_neighbor_y = bottom_index;
                        break;
                    }
                }
                std::cout << ((bottom_neighbor_y == -1) ? -1 : hindex) << ' ' << bottom_neighbor_y << std::endl;
            }
        }
    }

    return EXIT_SUCCESS;
}
