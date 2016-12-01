#include <iostream>
#include <string>
#include <cstdlib>
#include <list>

std::size_t score(std::string const & word);

int main() {
    std::size_t N;
    std::cin >> N;
    std::cin.ignore();

    std::list<std::string> dictionary;
    for(std::size_t i = 0; i < N; i++) {
        std::string W;
        std::getline(std::cin, W);
        dictionary.emplace_back(W.cbegin(), W.cend());
    }
    std::string LETTERS;
    std::getline(std::cin, LETTERS);

    std::size_t max_score = 0;
    std::string max_word = "";
    for(auto const & w : dictionary) {
        if(w.length() <= 7) {
            auto available_letters = LETTERS;

            bool can_be_composed = true;
            for(auto const & c : w) {
                auto c_pos = available_letters.find(c);

                if(c_pos != std::string::npos) {
                    available_letters.at(c_pos) = ' ';
                } else {
                    can_be_composed = false;
                    break;
                }
            }
            if(can_be_composed) {
                auto curr_score = score(w);
                if(curr_score > max_score) {
                    max_score = curr_score;
                    max_word = w;
                }
            }
        }
    }

    std::cout << max_word << std::endl;

    return EXIT_SUCCESS;
}

std::size_t score(std::string const & word) {
    std::size_t ret = 0;
    for(auto const & l : word) {
        if(l == 'e' || l == 'a' || l == 'i' || l == 'o' || l == 'n' || l ==  'r' || l == 'r' || l == 't' || l == 'l' || l == 's' || l == 'u') {
            ret += 1;
        }
        if(l == 'd' || l == 'g') {
            ret += 2;
        }
        if(l == 'b' || l == 'c' || l == 'm' || l == 'p') {
            ret += 3;
        }
        if(l == 'f' || l == 'h' || l == 'v' || l == 'w' || l == 'y') {
            ret += 4;
        }
        if(l == 'k') {
            ret += 5;
        }
        if(l == 'j' || l == 'x') {
            ret += 8;
        }
        if(l == 'q' || l == 'z') {
            ret += 10;
        }
    }

    return ret;
}
