#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

int main() {
    std::size_t N;
    std::cin >> N;
    std::cin.ignore();
    std::size_t C;
    std::cin >> C;
    std::cin.ignore();

    std::vector<int> budget;
    budget.reserve(N);
    for(std::size_t i = 0; i < N; i++) {
        std::size_t B;
        std::cin >> B;
        std::cin.ignore();
        budget.push_back(B);
    }

    if(std::accumulate(budget.cbegin(), budget.cend(), 0) < C) {
        std::cout << "IMPOSSIBLE" << std::endl;
    } else {
        int sum = 0;
        std::vector<int> contribution(N, 0);
        while(sum < C) {
            for(std::size_t i = 0; i < N && sum < C; ++i) {
                if(contribution.at(i) < budget.at(i)) {
                    ++contribution.at(i);
                    ++sum;
                }
            }
        }

        std::sort(contribution.begin(), contribution.end());

        for(auto c : contribution) {
            std::cout << c << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
