#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <map>
#include <set>
#include <utility>
#include <queue>

std::queue<std::pair<int, int>> find_path(int start_x, int start_y, int goal_x, int goal_y, std::map<std::pair<int, int>, std::set<std::pair<int, int>>> const & edges);

int main() {
    int R; // number of rows.
    int C; // number of columns.
    int A; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
    std::cin >> R >> C >> A;
    std::cin.ignore();

    bool all_scanned = false;
    std::queue<std::pair<int, int>> Cpath, Tpath;

    // game loop
    while(1) {
        int KR; // row where Kirk is located.
        int KC; // column where Kirk is located.
        std::cin >> KR >> KC;
        std::cin.ignore();

        int TR = -1, TC = -1;
        int CR = -1, CC = -1;

        std::vector<std::vector<char>> map;
        for(int i = 0; i < R; i++) {
            std::string ROW; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
            std::cin >> ROW;
            std::cin.ignore();

            auto Tj = ROW.find('T');
            if(Tj != std::string::npos) {
                TR = i;
                TC = Tj;
            }
            auto Cj = ROW.find('C');
            if(Cj != std::string::npos) {
                CR = i;
                CC = Cj;
            }

            map.emplace_back(ROW.cbegin(), ROW.cend());
        }

        if(!all_scanned) {
            std::map<std::pair<int, int>, std::set<std::pair<int, int>>> graph;
            for(std::size_t i = 0; i < map.size(); ++i) {
                for(std::size_t j = 0; j < map.at(i).size(); ++j) {
                    if(map.at(i).at(j) == '.' || map.at(i).at(j) == 'T') {
                        if(i > 0 && (map.at(i - 1).at(j) == '.' || map.at(i - 1).at(j) == 'T' || map.at(i - 1).at(j) == '?')) {
                            graph[{j, i}].emplace(j, i - 1);
                        }
                        if(j < map.at(i).size() - 1 && (map.at(i).at(j + 1) == '.' || map.at(i).at(j + 1) == 'T' || map.at(i).at(j + 1) == '?')) {
                            graph[{j, i}].emplace(j + 1, i);
                        }
                        if(i < map.size() - 1 && (map.at(i + 1).at(j) == '.' || map.at(i + 1).at(j) == 'T' || map.at(i + 1).at(j) == '?')) {
                            graph[{j, i}].emplace(j, i + 1);
                        }
                        if(j > 0 && (map.at(i).at(j - 1) == '.' || map.at(i).at(j - 1) == 'T' || map.at(i).at(j - 1) == '?')) {
                            graph[{j, i}].emplace(j - 1, i);
                        }
                    }
                }
            }

            // BFS for the first not scanned cell
            std::pair<int, int> goto_node{-1, -1};

            std::queue<std::pair<int, int>> q;
            std::map<std::pair<int, int>, std::queue<std::pair<int, int>>> path;
            std::map<std::pair<int, int>, bool> marked;

            q.push({KC, KR});
            path[{KC, KR}] = std::queue<std::pair<int, int>>{};
            marked[{KC, KR}] = true;

            while(!q.empty() && goto_node == std::make_pair<>(-1, -1)) {
                auto v = q.front();
                q.pop();

                for(auto const & child : graph.at(v)) {
                    if(marked[child] == false) {
                        path[child] = path.at(v);
                        path.at(child).push(child);
                        marked[child] = true;
                        q.push(child);
                    }

                    if(map.at(child.second).at(child.first) == '?') {
                        goto_node = path.at(child).front();
                        break;
                    }
                }
            }

            // if there are cells to discover
            if(goto_node != std::make_pair<>(-1, -1)) {
                if(goto_node.first < KC) {
                    std::cout << "LEFT" << std::endl;
                }
                if(goto_node.first > KC) {
                    std::cout << "RIGHT" << std::endl;
                }
                if(goto_node.second < KR) {
                    std::cout << "UP" << std::endl;
                }
                if(goto_node.second > KR) {
                    std::cout << "DOWN" << std::endl;
                }
            } else {
                all_scanned = true;
                if(CR == -1 && CC == -1) {
                    return EXIT_FAILURE;
                } else {
                    // Allow entering control room
                    if(CR > 0 && map.at(CR - 1).at(CC) != '#' && map.at(CR - 1).at(CC) != '?') {
                        graph[{CC, CR}].emplace(CC, CR - 1);
                        graph[{CC, CR - 1}].emplace(CC, CR);
                    }
                    if(CC < map.at(CR).size() - 1 && map.at(CR).at(CC + 1) != '#' && map.at(CR).at(CC + 1) != '?') {
                        graph[{CC, CR}].emplace(CC + 1, CR);
                        graph[{CC + 1, CR}].emplace(CC, CR);
                    }
                    if(CR < map.size() - 1 && map.at(CR + 1).at(CC) != '#' && map.at(CR + 1).at(CC) != '?') {
                        graph[{CC, CR}].emplace(CC, CR + 1);
                        graph[{CC, CR + 1}].emplace(CC, CR);
                    }
                    if(CC > 0 && map.at(CR).at(CC - 1) != '#' && map.at(CR).at(CC - 1) != '?') {
                        graph[{CC, CR}].emplace(CC - 1, CR);
                        graph[{CC - 1, CR}].emplace(CC, CR);
                    }

                    // Finding paths...
                    Cpath = find_path(KC, KR, CC, CR, graph);
                    Tpath = find_path(CC, CR, TC, TR, graph);

                    // ... and making a first step
                    if(Cpath.front().first < KC) {
                        std::cout << "LEFT" << std::endl;
                    }
                    if(Cpath.front().first > KC) {
                        std::cout << "RIGHT" << std::endl;
                    }
                    if(Cpath.front().second < KR) {
                        std::cout << "UP" << std::endl;
                    }
                    if(Cpath.front().second > KR) {
                        std::cout << "DOWN" << std::endl;
                    }
                    Cpath.pop();
                }
            }
        } else {
            // continue moving
            std::pair<int, int> goto_node;
            if(!Cpath.empty()) {
                goto_node = Cpath.front();
                Cpath.pop();
            } else {
                goto_node = Tpath.front();
                Tpath.pop();
            }
            if(goto_node.first < KC) {
                std::cout << "LEFT" << std::endl;
            }
            if(goto_node.first > KC) {
                std::cout << "RIGHT" << std::endl;
            }
            if(goto_node.second < KR) {
                std::cout << "UP" << std::endl;
            }
            if(goto_node.second > KR) {
                std::cout << "DOWN" << std::endl;
            }
        }
    }

    return EXIT_SUCCESS;
}

std::queue<std::pair<int, int>> find_path(int start_x, int start_y, int goal_x, int goal_y, std::map<std::pair<int, int>, std::set<std::pair<int, int>>> const & edges) {
    std::map<std::pair<int, int>, std::queue<std::pair<int, int>>> path;
    std::set<std::pair<int, int>> open_set;
    std::set<std::pair<int, int>> closed_set;
    std::map<std::pair<int, int>, std::pair<int, int>> node_costs;
    open_set.emplace(start_x, start_y);
    node_costs[{start_x, start_y}] = {0, 0};
    path[{start_x, start_y}] = std::queue<std::pair<int, int>>{};

    bool goal_found = false;
    while(!goal_found && !open_set.empty()) {
        auto q = *std::min_element(open_set.begin(), open_set.end(), [&node_costs](std::pair<int, int> const & p1, std::pair<int, int> const & p2) {return node_costs.at(p1).first + node_costs.at(p1).second < node_costs.at(p2).first + node_costs.at(p2).second;});
        open_set.erase(q);

        for(auto const & child : edges.at(q)) {
            if(child == std::make_pair(goal_x, goal_y)) {
                goal_found = true;
                path[child] = path.at(q);
                path.at(child).push(child);
                break;
            } else {
                auto g_cost = node_costs.at(q).first + 1;
                auto h_cost = std::abs(goal_x - child.first) + std::abs(goal_y - child.second);

                auto open_itr = open_set.find(child);
                auto closed_itr = closed_set.find(child);
                if(!(open_itr != open_set.cend() && node_costs.at(*open_itr).first + node_costs.at(*open_itr).second < g_cost + h_cost) && !(closed_itr != closed_set.cend() && node_costs.at(*closed_itr).first + node_costs.at(*closed_itr).second < g_cost + h_cost)) {
                    open_set.emplace(child);
                    node_costs[child] = {g_cost, h_cost};
                    path[child] = path.at(q);
                    path.at(child).push(child);
                }
            }
        }

        closed_set.emplace(q);
    }

    if(goal_found) {
        return path.at({goal_x, goal_y});
    } else {
        return std::queue<std::pair<int, int>>{};
    }
}
