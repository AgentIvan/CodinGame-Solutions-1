#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <limits>
#include <list>

struct Stop {
    std::string id;
    std::string name;
    std::string description;
    double latitude;
    double longtitude;
    std::string zone_id;
    std::string url;
    std::string type;
    std::string mother;

    bool operator ==(Stop const & other) const;
    bool operator <(Stop const & other) const;
};

Stop make_stop(std::string const & s);
double radians(double deg);
double distance(double latitude_a, double longtitude_a, double latitude_b, double longtitude_b);
std::map<std::string, std::list<std::pair<std::string, std::string>>> dijkstra_paths(std::string const & start, std::map<std::string, std::set<std::string>> const & edges, std::map<std::string, Stop> const & stops);

int main() {
    std::string start_point;
    std::cin >> start_point;
    std::cin.ignore();
    std::string end_point;
    std::cin >> end_point;
    std::cin.ignore();

    std::size_t N;
    std::cin >> N;
    std::cin.ignore();
    std::map<std::string, Stop> stops;
    std::map<std::string, std::set<std::string>> grid;
    for(std::size_t i = 0; i < N; ++i) {
        std::string stop_name;
        std::getline(std::cin, stop_name);
        auto stop = make_stop(stop_name);
        stops[stop.id] = stop;
        grid[stop.id] = {};
    }

    std::size_t M;
    std::cin >> M;
    std::cin.ignore();
    for(std::size_t i = 0; i < M; ++i) {
        std::string route_start, route_end;
        std::cin >> route_start >> route_end;
        std::cin.ignore();

        grid[route_start].emplace(route_end);
    }

    auto paths = dijkstra_paths(start_point, grid, stops);
    if(paths.find(end_point) != paths.cend()) {
        std::cout << stops.at(start_point).name << std::endl;
        for(auto const & route : paths.at(end_point)) {
            std::cout << stops.at(route.second).name << std::endl;
        }
    } else {
        std::cout << "IMPOSSIBLE" << std::endl;
    }

    return EXIT_SUCCESS;
}

bool Stop::operator ==(Stop const & other) const {
    return id == other.id;
}

bool Stop::operator <(Stop const & other) const {
    return id < other.id;
}

Stop make_stop(std::string const & s) {
    std::size_t start = 0;
    auto end = s.find(',', start);

    auto id = s.substr(start, end - start);
    start = end + 1;
    end = s.find(',', start);

    auto name = s.substr(start + 1, end - start - 2); // to get rid of quotes
    start = end + 1;
    end = s.find(',', start);

    auto description = s.substr(start, end - start);
    start = end + 1;
    end = s.find(',', start);

    auto latitude = std::stod(s.substr(start, end - start));
    start = end + 1;
    end = s.find(',', start);

    auto longtitude = std::stod(s.substr(start, end - start));
    start = end + 1;
    end = s.find(',', start);

    auto zone_id = s.substr(start, end - start);
    start = end + 1;
    end = s.find(',', start);

    auto url = s.substr(start, end - start);
    start = end + 1;
    end = s.find(',', start);

    auto type = s.substr(start, end - start);
    start = end + 1;
    end = s.find(',', start);

    auto mother = s.substr(start);

    return Stop{id, name, description, latitude, longtitude, zone_id, url, type, mother};
}

double radians(double deg) {
    return deg * M_PI / 180;
}

double distance(double latitude_a, double longtitude_a, double latitude_b, double longtitude_b) {
    auto x = radians(longtitude_b - longtitude_a) * std::cos(radians(latitude_a + latitude_b) / 2);
    auto y = radians(latitude_b - latitude_a);

    return 6371 * std::sqrt(x * x + y * y);
}

std::map<std::string, std::list<std::pair<std::string, std::string>>> dijkstra_paths(std::string const & start, std::map<std::string, std::set<std::string>> const & edges, std::map<std::string, Stop> const & stops) {
    std::set<std::string> q;
    std::map<std::string, double> distances;
    std::map<std::string, std::list<std::pair<std::string, std::string>>> paths;

    for(auto const & node : edges) {
        distances[node.first] = std::numeric_limits<std::size_t>::max();
        q.emplace(node.first);
    }

    distances.at(start) = 0;
    paths[start] = {};
    while(!q.empty()) {
        auto u = *std::min_element(q.cbegin(), q.cend(), [&distances](std::string const & s1, std::string const & s2) {return distances.at(s1) < distances.at(s2);});
        q.erase(u);

        for(auto const & v : edges.at(u)) {
            if(q.find(v) != q.cend()) {
                auto alt = distances.at(u) + distance(stops.at(u).latitude, stops.at(u).longtitude, stops.at(v).latitude, stops.at(v).longtitude);
                if(alt < distances.at(v)) {
                    distances.at(v) = alt;
                    paths[v] = paths.at(u);
                    paths.at(v).emplace_back(u, v);
                }
            }
        }
    }

    return paths;
}
