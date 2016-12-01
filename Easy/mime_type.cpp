#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cstdlib>

int main() {
    int N; // Number of elements which make up the association table.
    std::cin >> N;
    std::cin.ignore();
    int Q; // Number Q of file names to be analyzed.
    std::cin >> Q;
    std::cin.ignore();

    std::unordered_map<std::string, std::string> type_map;
    for (int i = 0; i < N; i++) {
        std::string EXT; // file extension
        std::string MT; // MIME type.
        std::cin >> EXT >> MT;
        std::cin.ignore();
        std::transform(EXT.begin(), EXT.end(), EXT.begin(), static_cast<int (*)(int)>(std::tolower));
        type_map[EXT] = MT;
    }
    for (int i = 0; i < Q; i++) {
        std::string FNAME; // One file name per line.
        std::getline(std::cin, FNAME);
        auto file_ext = (FNAME.find_last_of('.') != -1) ? FNAME.substr(FNAME.find_last_of('.') + 1) : "";
        std::transform(file_ext.begin(), file_ext.end(), file_ext.begin(), static_cast<int (*)(int)>(std::tolower));
        std::cout << (type_map.find(file_ext) != type_map.cend() ? type_map.at(file_ext) : "UNKNOWN") << std::endl;
    }

    return EXIT_SUCCESS;
}
