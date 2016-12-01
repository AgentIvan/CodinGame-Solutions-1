#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <queue>
#include <cstdlib>

int main() {
    std::size_t L;
    std::cin >> L;
    std::cin.ignore();
    std::size_t H;
    std::cin >> H;
    std::cin.ignore();

    std::vector<std::vector<char>> map;
    map.reserve(H);
    for(std::size_t i = 0; i < H; ++i) {
        std::string row;
        std::getline(std::cin, row);
        map.emplace_back(row.cbegin(), row.cend());
    }

    std::size_t N;
    std::cin >> N;
    std::cin.ignore();

    for(std::size_t i = 0; i < N; ++i) {
        std::size_t X;
        std::size_t Y;
        std::cin >> X >> Y;
        std::cin.ignore();
        auto cell = std::make_pair(X, Y);

        if(map.at(Y).at(X) == '#') {
            std::cout << 0 << std::endl;
        } else {
            std::size_t area = 0;
            std::queue<std::pair<std::size_t, std::size_t>> q;
            std::vector<std::vector<bool>> painted(H, std::vector<bool>(L, false));
            q.emplace(X, Y);
            while(!q.empty()) {
                auto n = q.front();
                q.pop();
                if(!painted.at(n.second).at(n.first)) {
                    auto w = n.first, e = n.first;
                    while(w > 0 && map.at(n.second).at(w - 1) != '#') {
                        --w;
                    }
                    while(e < map.at(n.second).size() - 1 && map.at(n.second).at(e + 1) != '#') {
                        ++e;
                    }
                    for(auto index = w; index <= e; ++index) {
                        ++area;
                        painted.at(n.second).at(index) = true;
                        if(n.second > 0 && map.at(n.second - 1).at(index) != '#' && !painted.at(n.second - 1).at(index)) {
                            q.emplace(index, n.second - 1);
                        }
                        if(n.second < map.size() - 1 && map.at(n.second + 1).at(index) != '#' && !painted.at(n.second + 1).at(index)) {
                            q.emplace(index, n.second + 1);
                        }
                    }
                }
            }
            std::cout << area << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
