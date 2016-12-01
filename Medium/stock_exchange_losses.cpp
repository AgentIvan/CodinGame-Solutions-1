#include <iostream>
#include <vector>
#include <cstdlib>

int main() {
    std::size_t n;
    std::cin >> n;
    std::cin.ignore();

    std::vector<int> values;
    values.reserve(n);
    for(std::size_t i = 0; i < n; ++i) {
        std::size_t v;
        std::cin >> v;
        std::cin.ignore();
        values.push_back(v);
    }

    int max_loss = 0;
    auto peak = values.cbegin();
    for(auto curr = values.cbegin(), end = values.cend(); curr != end; ++curr) {
        int loss = *curr - *peak;

        if(loss < 0 && loss < max_loss) {
            max_loss = loss;
        } else {
            if(loss > 0) {
                peak = curr;
            }
        }
    }

    std::cout << max_loss << std::endl;

    return EXIT_SUCCESS;
}
