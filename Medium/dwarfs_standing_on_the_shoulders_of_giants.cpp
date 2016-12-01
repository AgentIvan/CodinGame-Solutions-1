#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <cstdlib>

std::size_t count(std::size_t node, std::map<std::size_t, std::set<std::size_t>> const & edges);

int main() {
    std::set<std::size_t> roots;
    std::map<std::size_t, std::set<std::size_t>> edges;

    std::size_t n; // the number of relationships of influence
    std::cin >> n;
    std::cin.ignore();
    for(std::size_t i = 0; i < n; ++i) {
        std::size_t x; // a relationship of influence between two people (x influences y)
        std::size_t y;
        std::cin >> x >> y;
        std::cin.ignore();

        // Add the relationship to the list
        edges[x].emplace(y);
        roots.emplace(x);
    }

    // Find all the roots
    for(auto const & e : edges) {
        for(auto const & v : e.second) {
            roots.erase(v);
        }
    }

    // Start from all roots and count their influences
    std::size_t max_count = 0;
    for(auto const & v : roots) {
        auto curr_count = count(v, edges);
        if(curr_count > max_count) {
            max_count = curr_count;
        }
    }

    std::cout << max_count << std::endl;

    return EXIT_SUCCESS;
}

std::size_t count(std::size_t node, std::map<std::size_t, std::set<std::size_t>> const & edges) {
    if(edges.find(node) != edges.cend() && !edges.at(node).empty()) {
        std::size_t max_count = 1;
        for(auto const & v : edges.at(node)) {
            auto curr_count = count(v, edges);
            if(curr_count > max_count) {
                max_count = curr_count;
            }
        }

        return max_count + 1;
    } else {
        return 1;
    }
}
