#include <iostream>
#include <cstdlib>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <utility>

std::map<std::size_t, std::list<std::pair<std::size_t, std::size_t>>> bfs_path(std::map<std::size_t, std::set<std::size_t>> const & graph, std::size_t start);

int main() {
    std::size_t N; // the total number of nodes in the level, including the gateways
    std::size_t L; // the number of links
    std::size_t E; // the number of exit gateways
    std::cin >> N >> L >> E;
    std::cin.ignore();

    std::map<std::size_t, std::set<std::size_t>> graph;
    for(std::size_t i = 0; i < L; ++i) {
        std::size_t N1; // N1 and N2 defines a link between these nodes
        std::size_t N2;
        std::cin >> N1 >> N2;
        std::cin.ignore();

        graph[N1].emplace(N2);
        graph[N2].emplace(N1);
    }

    std::set<std::size_t> gateways;
    for(std::size_t i = 0; i < E; ++i) {
        std::size_t EI; // the index of a gateway node
        std::cin >> EI;
        std::cin.ignore();
        gateways.emplace(EI);
    }

    // game loop
    while(1) {
        std::size_t SI;
        std::cin >> SI;
        std::cin.ignore();

        auto paths = bfs_path(graph, SI);
        std::list<std::pair<std::size_t, std::size_t>> shortest_path(L);
        for(auto const & g : gateways) {
            auto path = paths.find(g);
            if(path != paths.cend() && path->second.size() < shortest_path.size()) {
                shortest_path = path->second;
            }
        }
        auto to_cut = shortest_path.back();
        graph.at(to_cut.first).erase(to_cut.second);
        graph.at(to_cut.second).erase(to_cut.first);
        std::cout << to_cut.first << ' ' << to_cut.second << std::endl;
    }

    return EXIT_SUCCESS;
}

std::map<std::size_t, std::list<std::pair<std::size_t, std::size_t>>> bfs_path(std::map<std::size_t, std::set<std::size_t>> const & graph, std::size_t start) {
    std::queue<std::size_t> q;
    std::map<std::size_t, std::list<std::pair<std::size_t, std::size_t>>> paths;
    std::map<std::size_t, bool> marked;

    q.push(start);
    paths[start] = {};
    marked[start] = true;

    while(!q.empty()) {
        auto v = q.front();
        q.pop();

        for(auto const & child : graph.at(v)) {
            if(marked[child] == false) {
                paths[child] = paths.at(v);
                paths.at(child).emplace_back(v, child);
                marked[child] = true;
                q.push(child);
            }
        }
    }

    return paths;
}
