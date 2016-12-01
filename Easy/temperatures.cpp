#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <cstdlib>

int main() {
    int n; // the number of temperatures to analyse
    std::cin >> n;
    std::cin.ignore();
    std::string temps; // the n temperatures expressed as integers ranging from -273 to 5526
    std::getline(std::cin, temps);

    std::istringstream temps_stream(temps);
    std::vector<int> temp_values;

    std::copy(std::istream_iterator<int>(temps_stream), std::istream_iterator<int>(), std::back_inserter(temp_values));

    std::cout << (temp_values.empty() ? 0 : *(std::min_element(temp_values.cbegin(), temp_values.cend(), [](int t1, int t2) {if(std::abs(t1) == std::abs(t2)) {return t1 > t2;} else {return std::abs(t1) < std::abs(t2);}}))) << std::endl;

    return EXIT_SUCCESS;
}
