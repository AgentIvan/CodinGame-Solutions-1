#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>

struct Defib {
    int number;
    std::string name;
    std::string address;
    std::string phone;
    double longtitude;
    double latitude;
};

Defib to_Defib(std::string str);
double distance(double longtitudeA, double longtitudeB, double latitudeA, double latitudeB);

int main() {
    std::string LON;
    std::cin >> LON;
    std::cin.ignore();
    auto user_longtitude = std::stod(LON.replace(LON.find(','), 1, 1, '.'));
    std::string LAT;
    std::cin >> LAT;
    std::cin.ignore();
    auto user_latitude = std::stod(LAT.replace(LAT.find(','), 1, 1, '.'));
    int N;
    std::cin >> N;
    std::cin.ignore();
    std::vector<Defib> defibs;
    for (int i = 0; i < N; i++) {
        std::string DEFIB;
        std::getline(std::cin, DEFIB);
        defibs.push_back(to_Defib(DEFIB));
    }

    std::cout << std::min_element(defibs.cbegin(), defibs.cend(), [user_longtitude, user_latitude](Defib const & first, Defib const & second) {return distance(user_longtitude, user_latitude, first.longtitude, first.latitude) < distance(user_longtitude, user_latitude, second.longtitude, second.latitude);})->name << std::endl;

    return EXIT_SUCCESS;
}

Defib to_Defib(std::string str) {
    Defib ret;
    ret.number = stoi(str.substr(0, str.find(';')));
    str.erase(0, str.find(';') + 1);
    ret.name = str.substr(0, str.find(';'));
    str.erase(0, str.find(';') + 1);
    ret.address = str.substr(0, str.find(';'));
    str.erase(0, str.find(';') + 1);
    ret.phone = str.substr(0, str.find(';'));
    str.erase(0, str.find(';') + 1);
    auto longtitude_string = str.substr(0, str.find(';'));
    str.erase(0, str.find(';') + 1);
    ret.longtitude = std::stod(longtitude_string.replace(longtitude_string.find(','), 1, 1, '.'));
    ret.latitude = std::stod(str.replace(str.find(','), 1, 1, '.'));

    return ret;
}

double distance(double longtitudeA, double latitudeA, double longtitudeB, double latitudeB) {
    auto rad_lonA = longtitudeA * M_PI / 180;
    auto rad_lonB = longtitudeB * M_PI / 180;
    auto rad_latA = latitudeA * M_PI / 180;
    auto rad_latB = latitudeB * M_PI / 180;

    return std::sqrt((rad_lonB - rad_lonA) * std::cos((rad_latA + rad_latB) / 2) * (rad_lonB - rad_lonA) * std::cos((rad_latA + rad_latB) / 2) + (rad_latB - rad_latA) * (rad_latB - rad_latA)) * 6371;
}
