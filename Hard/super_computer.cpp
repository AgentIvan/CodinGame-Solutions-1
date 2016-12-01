#include <iostream>
#include <set>
#include <cstdlib>

int main() {
    std::set<std::pair<std::size_t, std::size_t>> tasks;

    std::size_t N;
    std::cin >> N;
    std::cin.ignore();
    for(std::size_t i = 0; i < N; ++i) {
        std::size_t J;
        std::size_t D;
        std::cin >> J >> D;
        std::cin.ignore();

        tasks.emplace(J, D);
    }

    std::size_t n_tasks = 0;
    std::size_t curr_end = 0;
    for(auto const & task : tasks) {
        if (task.first >= curr_end) {
            ++n_tasks;
            curr_end = task.first + task.second;
        } else {
            if(task.first + task.second < curr_end) {
                curr_end = task.first + task.second;
            }
        }
    }

    std::cout << n_tasks << std::endl;

    return EXIT_SUCCESS;
}
