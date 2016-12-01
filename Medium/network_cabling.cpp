#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <limits>

int main() {
    std::size_t N;
    std::cin >> N;
    std::cin.ignore();

    int xmax = std::numeric_limits<int>::min(), xmin = std::numeric_limits<int>::max();
    std::vector<std::pair<int, int>> houses;
    houses.reserve(N);
    for(std::size_t i = 0; i < N; ++i) {
        int X;
        int Y;
        std::cin >> X >> Y;
        std::cin.ignore();

        if(X > xmax) {
            xmax = X;
        }

        if(X < xmin) {
            xmin = X;
        }

        houses.emplace_back(X, Y);
    }

    // we're looking for a median, so sort first
    std::sort(houses.begin(), houses.end(), [](std::pair<int, int> const & one, std::pair<int, int> const & another) {return one.second < another.second;});
    // now the median
    auto y0 = (houses.cbegin() + houses.size() / 2)->second;

    std::cout << std::accumulate(houses.cbegin(), houses.cend(), static_cast<long int>(xmax - xmin), [y0](long int acc, std::pair<int, int> const & another) {return acc + std::abs(another.second - y0);}) << std::endl;

    return EXIT_SUCCESS;
}
