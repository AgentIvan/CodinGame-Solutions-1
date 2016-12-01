#include <iostream>
#include <cstdlib>
#include <map>
#include <set>
#include <utility>
#include <list>
#include <limits>
#include <algorithm>

std::pair<std::map<size_t, std::size_t>, std::map<size_t, std::list<std::pair<size_t, size_t>>>> dijkstra(size_t start, std::map<size_t, std::set<size_t>> const & edges, std::set<size_t> const & gateways);

int main() {
    size_t N; // the total number of nodes in the level, including the gateways
    size_t L; // the number of links
    size_t E; // the number of exit gateways
    std::cin >> N >> L >> E;
    std::cin.ignore();

    std::map<size_t, std::set<size_t>> graph;
    for(size_t i = 0; i < L; i++) {
        size_t N1; // N1 and N2 defines a link between these nodes
        size_t N2;
        std::cin >> N1 >> N2;
        std::cin.ignore();

        graph[N1].emplace(N2);
        graph[N2].emplace(N1);
    }

    std::set<size_t> gateways;
    for(size_t i = 0; i < E; i++) {
        size_t EI; // the index of a gateway node
        std::cin >> EI;
        std::cin.ignore();

        gateways.emplace(EI);
    }

    // game loop
    while(1) {
        size_t SI; // The index of the node on which the Skynet agent is positioned this turn
        std::cin >> SI;
        std::cin.ignore();

        auto result = dijkstra(SI, graph, gateways);
        auto distances = result.first;
        auto paths = result.second;

        std::map<size_t, std::size_t> node_ranks;
        for(auto const & node : graph) {
            node_ranks[node.first] = 0;
            for(auto const & neighbor : node.second) {
                if(gateways.find(neighbor) != gateways.cend()) {
                    ++node_ranks.at(node.first);
                }
            }
        }

        auto shortest_distance = std::numeric_limits<size_t>::max();
        std::list<std::pair<size_t, size_t>> shortest_path;
        for(auto const & g : gateways) {
            if(paths.find(g) != paths.cend() && distances.at(g) < shortest_distance) {
                shortest_path = paths.at(g);
                shortest_distance = distances.at(g);
            }
        }

        std::pair<size_t, size_t> to_cut_link; // link to cut
        if(shortest_distance == 1) { // if we're in imediate danger...
            to_cut_link = shortest_path.back(); // obviously cut the link to the gateway
        } else { // else cut a link between a node connected to multiple gateways (a "dangerous" node) and its gateway
            std::size_t max_exit_edges = 0;
            std::set<size_t> dangerous_nodes;

            for(auto const & node : graph) {
                std::size_t n_exit_edges = 0;
                for(auto const & child : node.second) {
                    if(gateways.find(child) != gateways.cend()) {
                        ++n_exit_edges;
                    }
                }
                if(n_exit_edges > max_exit_edges) {
                    max_exit_edges = n_exit_edges;
                    dangerous_nodes = {node.first};
                } else {
                    if(n_exit_edges == max_exit_edges) {
                        dangerous_nodes.emplace(node.first);
                    }
                }
            }

            // now it's time to pick which of dangerous nodes to cut. it appears that the virus always heads to a node with the maximum value of sum of node ranks along the path minus path length
            auto max_rank = std::numeric_limits<int>::min();
            std::set<size_t> max_rank_nodes;
            for(auto const & node : dangerous_nodes) {
                int curr_rank = 0;
                for(auto const & link : paths.at(node)) {
                    curr_rank += node_ranks.at(link.second) - 1;
                }
                if(curr_rank > max_rank) {
                    max_rank = curr_rank;
                    max_rank_nodes = {node};
                } else {
                    if(curr_rank == max_rank) {
                        max_rank_nodes.emplace(node);
                    }
                }
            }
            // now we select the closets among equally dangerous nodes
            auto to_cut_node = *std::min_element(max_rank_nodes.cbegin(), max_rank_nodes.cend(), [&distances](size_t n1, size_t n2) {return distances.at(n1) < distances.at(n2);});
            // and pick the closest of its gateway
            size_t to_cut_exit = 0;
            std::size_t to_cut_exit_distance = std::numeric_limits<std::size_t>::max();
            for(auto const & child : graph.at(to_cut_node)) {
                if(gateways.find(child) != gateways.cend() && distances.at(child) < to_cut_exit_distance) {
                    to_cut_exit_distance = distances.at(child);
                    to_cut_exit = child;
                }
            }
            to_cut_link = std::make_pair(to_cut_node, to_cut_exit);
        }
        // remove the cut link
        graph.at(to_cut_link.first).erase(to_cut_link.second);
        graph.at(to_cut_link.second).erase(to_cut_link.first);
        std::cout << to_cut_link.first << ' ' << to_cut_link.second << std::endl;
    }

    return EXIT_SUCCESS;
}

std::pair<std::map<size_t, std::size_t>, std::map<size_t, std::list<std::pair<size_t, size_t>>>> dijkstra(size_t start, std::map<size_t, std::set<size_t>> const & edges, std::set<size_t> const & gateways) {
    std::set<size_t> q;
    std::map<size_t, std::size_t> distances;
    std::map<size_t, std::list<std::pair<size_t, size_t>>> paths;

    for(auto const & node : edges) {
        distances[node.first] = std::numeric_limits<std::size_t>::max();
        q.emplace(node.first);
    }

    distances.at(start) = 0;
    paths[start] = {};
    while(!q.empty()) {
        auto u = *std::min_element(q.cbegin(), q.cend(), [&distances](int n1, int n2) {return distances.at(n1) < distances.at(n2);});
        // we cannot go through gateways
        if(gateways.find(u) == gateways.cend()) {
            for(auto const & v : edges.at(u)) {
                if(q.find(v) != q.cend()) {
                    auto alt = distances.at(u) + 1;
                    if(alt < distances.at(v)) {
                        distances.at(v) = alt;
                        paths[v] = paths.at(u);
                        paths.at(v).emplace_back(u, v);
                    }
                }
            }
        }
        q.erase(u);
    }

    return std::make_pair(distances, paths);
}
