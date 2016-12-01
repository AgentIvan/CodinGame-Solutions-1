#include <iostream>
#include <cstdlib>
#include <map>
#include <set>
#include <stack>

std::size_t dfs_max_distance(std::map<std::size_t, std::set<std::size_t>> const & graph, std::size_t start);

int main() {
    std::size_t n; // the number of adjacency relations
    std::cin >> n;
    std::cin.ignore();

    std::map<std::size_t, std::set<std::size_t>> graph;
    for(std::size_t i = 0; i < n; i++) {
        std::size_t xi; // the ID of a person which is adjacent to yi
        std::size_t yi; // the ID of a person which is adjacent to xi
        std::cin >> xi >> yi;
        std::cin.ignore();
        graph[xi].emplace(yi);
        graph[yi].emplace(xi);
    }

    std::size_t leaf_node = 0;
    for(auto const & n : graph) {
        if(n.second.size() == 1) {
            leaf_node = n.first;
            break;
        }
    }
    // now we calculate the diameter of a tree (i.e. max distance between any two nodes)
    auto max_distance = dfs_max_distance(graph, leaf_node);
    // the radius (the thing we're looking for) of a undirected tree and its diameter are linked: 2 * R -1 <= D <= 2 * R
    std::cout << (max_distance + 1) / 2 << std::endl;

    return EXIT_SUCCESS;
}

std::size_t dfs_max_distance(std::map<std::size_t, std::set<std::size_t>> const & graph, std::size_t start) {
    std::map<std::size_t, bool> marked;
    std::stack<std::pair<std::size_t, std::size_t>> s;
    s.emplace(start, 0);
    marked[start] = true;

    std::size_t max_distance = 0;
    while(!s.empty()) {
        auto v = s.top().first;
        auto distance = s.top().second;
        s.pop();

        if(distance > max_distance) {
            max_distance = distance;
        }

        for(auto const & child : graph.at(v)) {
            if(!marked[child]) {
                s.emplace(child, distance + 1);
                marked[child] = true;
            }
        }
    }

    return max_distance;
}
