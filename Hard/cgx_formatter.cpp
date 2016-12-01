#include <iostream>
#include <string>
#include <cstdlib>

int main() {
    std::size_t N;
    std::cin >> N;
    std::cin.ignore();

    std::size_t n_spaces = 0;
    bool new_line = true;
    for(std::size_t i = 0; i < N; ++i) {
        std::string CGXLine;
        std::getline(std::cin, CGXLine);

        bool raw_string = false;
        for(auto const & c : CGXLine) {
            if(raw_string) {
                if(new_line) {
                    for(std::size_t i = 0; i < n_spaces; ++i) {
                        std::cout << ' ';
                    }
                    new_line = false;
                }

                std::cout << c;

                if(c == '\'') {
                    raw_string = false;
                }
            } else {
                switch (c) {
                    case ' ':
                    case '\t':
                        break;
                    case '(':
                        if(!new_line) {
                            std::cout << std::endl;
                        }
                        for(std::size_t i = 0; i < n_spaces; ++i) {
                            std::cout << ' ';
                        }
                        std::cout << '(';
                        std::cout << std::endl;
                        new_line = true;
                        n_spaces += 4;
                        break;
                    case ')':
                        n_spaces -= 4;
                        if(!new_line) {
                            std::cout << std::endl;
                        }
                        for(std::size_t i = 0; i < n_spaces; ++i) {
                            std::cout << ' ';
                        }
                        new_line = false;
                        std::cout << ')';
                        break;
                    case '\'':
                        raw_string = !raw_string;
                        if(new_line) {
                            for(std::size_t i = 0; i < n_spaces; ++i) {
                                std::cout << ' ';
                            }
                            new_line = false;
                        }
                        std::cout << '\'';
                        break;
                    case ';':
                        if(new_line) {
                            for(std::size_t i = 0; i < n_spaces; ++i) {
                                std::cout << ' ';
                            }
                        }
                        std::cout << ';' << std::endl;
                        new_line = true;
                        break;
                    default:
                        if(new_line) {
                            for(std::size_t i = 0; i < n_spaces; ++i) {
                                std::cout << ' ';
                            }
                            new_line = false;
                        }
                        std::cout << c;
                        break;
                };
            }
        }
    }

    return EXIT_SUCCESS;
}
