#include <iostream>
#include <vector>
#include <cstdlib>

int main() {
    std::size_t L;
    std::size_t C;
    std::size_t N;
    std::cin >> L >> C >> N;
    std::cin.ignore();

    std::vector<int> q;
    q.reserve(N);
    for(std::size_t i = 0; i < N; ++i) {
        std::size_t Pi;
        std::cin >> Pi;
        std::cin.ignore();
        q.push_back(Pi);
    }

    // caches
    std::vector<std::size_t> earnings(N); // earnings if the given group is first in the queue
    std::vector<std::size_t> next_group(N); // next group indices

	for(std::size_t i = 0; i < N; ++i) {
	    std::size_t index = i;
	    bool circle = false;
	    while(earnings.at(i) + q.at(index) <= L && !circle) {
	        earnings.at(i) += q.at(index);

	        ++index;
	        if(index == N) { // go to the beginning
	            index = 0;
	        }

	        if(index == i) { // we've looped
	            circle = true;
	        }
	    }
	    next_group.at(i) = index;
	}

	std::size_t total_earnings = 0;
	std::size_t index = 0;
	for(std::size_t ride = 0; ride < C; ++ride) {
	    total_earnings += earnings.at(index);
	    index = next_group.at(index);
	}

    std::cout << total_earnings << std::endl;

    return EXIT_SUCCESS;
}
