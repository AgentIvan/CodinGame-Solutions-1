#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

int main() {
    std::size_t N;
    std::cin >> N;
    std::cin.ignore();

    std::vector<std::string> subseqs;
    subseqs.reserve(N);

    for(std::size_t i = 0; i < N; ++i) {
        std::string subseq;
        std::cin >> subseq;
        std::cin.ignore();

        subseqs.emplace_back(subseq.cbegin(), subseq.cend());
    }

    std::sort(subseqs.begin(), subseqs.end());

    std::string shortest_seq;
    do {
        std::string curr_seq = subseqs.front();
        for(std::size_t i = 1; i < subseqs.size(); ++i) {
            bool match = false;

            auto const & next = subseqs.at(i);
            for(std::size_t j = 0; j < curr_seq.size(); ++j) {
                if(next.size() >= curr_seq.size() - j) {
                    if(match = equal(curr_seq.cbegin() + j, curr_seq.cend(), next.cbegin())) {
                        curr_seq.append(next.substr(curr_seq.size() - j));
                        break;
                    }
                } else {
                    if(match = equal(curr_seq.cbegin() + j, curr_seq.cbegin() + j + next.size(), next.cbegin())) {
                        break;
                    }
                }
            }

            if(!match) {
                curr_seq.append(subseqs.at(i));
            }
        }

        if(shortest_seq.empty() || (curr_seq.size() < shortest_seq.size())) {
            shortest_seq = curr_seq;
        }
    } while(std::next_permutation(subseqs.begin(), subseqs.end()));

    std::cout << shortest_seq.size() << std::endl;

    return EXIT_SUCCESS;
}
