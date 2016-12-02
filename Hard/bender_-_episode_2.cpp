#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <cstdlib>

int main() {
    std::map<std::size_t, std::set<std::size_t>> grid;
    std::map<std::size_t, std::size_t> money;
    std::size_t N;
    std::cin >> N;
    std::cin.ignore();
    for(std::size_t i = 0; i < N; ++i) {
        std::size_t room, room_money;
        std::string door1, door2;
        std::cin >> room >> room_money >> door1 >> door2;
        std::cin.ignore();

        money[room] = room_money;
        grid[room] = {};

        if(door1 != "E") {
            grid[room].emplace(stoull(door1));
        }

        if(door2 != "E") {
            grid[room].emplace(stoull(door2));
        }
    }

    std::map<std::size_t, std::size_t> amounts;
    for(auto const & r : grid) {
        amounts[r.first] = 0;
    }
    amounts.at(0) = money.at(0);

    std::queue<std::size_t> q;
    q.emplace(0);

    while(!q.empty()) {
        auto curr_room = q.front();
        q.pop();

        for(auto const & neighbor : grid.at(curr_room)) {
            auto alt = amounts.at(curr_room) + money.at(neighbor);
            if(alt > amounts.at(neighbor)) {
                amounts.at(neighbor) = alt;
                q.emplace(neighbor);
            }
        }
    }

    std::cout << std::max_element(amounts.cbegin(), amounts.cend(), [](std::pair<std::size_t, std::size_t> const & p1, std::pair<std::size_t, std::size_t> const & p2) {return p1.second < p2.second;})->second << std::endl;

    return EXIT_SUCCESS;
}
