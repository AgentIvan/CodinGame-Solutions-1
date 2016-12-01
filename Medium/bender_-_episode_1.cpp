#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unordered_set>
#include <utility>
#include <list>

using Map = std::vector<std::vector<char>>;
enum class Direction {SOUTH, EAST, NORTH, WEST};

class Bender {
    friend class std::hash<Bender>;

    public:
        Bender(Map const & map, std::size_t initial_x = 0, std::size_t initial_y = 0);

        void move();
        bool is_alive() const;
        bool is_looped() const;
        void set_looped(bool is_looped = true);
        std::string get_move() const;

        bool operator ==(Bender const & other) const;

    private:
        std::size_t _x;
        std::size_t _y;
        bool _is_in_braker_mode;
        bool _is_in_inverted_mode;
        bool _is_looped;
        bool _is_alive;
        Direction _dir;
        std::string _move;
        Map _map;

        bool try_move(Direction dir);
        void make_move(Direction dir);
        std::pair<std::size_t, std::size_t> find_tp(std::size_t curr_x, std::size_t curr_y);
};

namespace std {
    template<> struct hash<Bender> {
        using result_type = std::size_t;
        using argument_type = Bender;

        result_type operator ()(Bender const & b) const;
    };
}

int main() {
    std::size_t L;
    std::size_t C;
    std::cin >> L >> C;
    std::cin.ignore();

    Map map;
    map.reserve(L);
    for(std::size_t i = 0; i < L; ++i) {
        std::string row;
        getline(std::cin, row);
        map.emplace_back(row.cbegin(), row.cend());
    }

    std::size_t start_x = 0;
    std::size_t start_y = 0;
    for(std::size_t i = 0; i < L; ++i) {
        for(std::size_t j = 0; j < C; ++j) {
            if(map.at(i).at(j) == '@') {
                start_x = j;
                start_y = i;
            }
        }
    }

    Bender b(map, start_x, start_y);

    std::unordered_set<Bender> states;
    std::list<std::string> moves;
    while(b.is_alive() && !b.is_looped()) {
        b.move();
        moves.emplace_back(b.get_move());
        if(states.find(b) != states.cend()) {
            b.set_looped();
            states.emplace(b);
        } else {
            states.emplace(b);
        }
    }

    if(b.is_looped()) {
        std::cout << "LOOP" << std::endl;
    } else {
        for(auto const & m : moves) {
            std::cout << m << std::endl;
        }
    }

    return EXIT_SUCCESS;
}

Bender::Bender(Map const & map, std::size_t initial_x, std::size_t initial_y) : _map(map), _x(initial_x), _y(initial_y), _is_in_braker_mode(false), _is_in_inverted_mode(false), _is_looped(false), _is_alive(true), _dir(Direction::SOUTH) {
}

void Bender::move() {
    bool worked = try_move(_dir);

    if(!_is_in_inverted_mode) {
        if(!worked) {
            worked = try_move(Direction::SOUTH);
        }
        if(!worked) {
            worked = try_move(Direction::EAST);
        }
        if(!worked) {
            worked = try_move(Direction::NORTH);
        }
        if(!worked) {
            worked = try_move(Direction::WEST);
        }
    } else {
        if(!worked) {
            worked = try_move(Direction::WEST);
        }
        if(!worked) {
            worked = try_move(Direction::NORTH);
        }
        if(!worked) {
            worked = try_move(Direction::EAST);
        }
        if(!worked) {
            worked = try_move(Direction::SOUTH);
        }
    }
}

bool Bender::try_move(Direction dir) {
    switch(dir) {
        case Direction::SOUTH: {
            auto & new_tile = _map.at(_y + 1).at(_x);
            if(new_tile == '#') {
                return false;
            }
            if(new_tile == 'X') {
                if(_is_in_braker_mode) {
                    new_tile = ' ';
                    make_move(Direction::SOUTH);
                    return true;
                } else {
                    return false;
                }
            }
            if(new_tile == 'B') {
                _is_in_braker_mode = !_is_in_braker_mode;
                make_move(Direction::SOUTH);
                return true;
            }
            if(new_tile == 'I') {
                _is_in_inverted_mode = !_is_in_inverted_mode;
                make_move(Direction::SOUTH);
                return true;
            }
            if(new_tile == 'T') {
                auto tp = find_tp(_x, _y + 1);
                make_move(Direction::SOUTH);
                _x = tp.first;
                _y = tp.second;
                return true;
            }
            if(new_tile == 'S') {
                make_move(Direction::SOUTH);
                _dir = Direction::SOUTH;
                return true;
            }
            if(new_tile == 'E') {
                make_move(Direction::SOUTH);
                _dir = Direction::EAST;
                return true;
            }
            if(new_tile == 'N') {
                make_move(Direction::SOUTH);
                _dir = Direction::NORTH;
                return true;
            }
            if(new_tile == 'W') {
                make_move(Direction::SOUTH);
                _dir = Direction::WEST;
                return true;
            }
            if(new_tile == '$') {
                make_move(Direction::SOUTH);
                _is_alive = false;
                return true;
            }
            make_move(Direction::SOUTH);
            return true;
            break;
        }
        case Direction::EAST: {
            auto & new_tile = _map.at(_y).at(_x + 1);
            if(new_tile == '#') {
                return false;
            }
            if(new_tile == 'X') {
                if(_is_in_braker_mode) {
                    new_tile = ' ';
                    make_move(Direction::EAST);
                    return true;
                } else {
                    return false;
                }
            }
            if(new_tile == 'B') {
                _is_in_braker_mode = !_is_in_braker_mode;
                make_move(Direction::EAST);
                return true;
            }
            if(new_tile == 'I') {
                _is_in_inverted_mode = !_is_in_inverted_mode;
                make_move(Direction::EAST);
                return true;
            }
            if(new_tile == 'T') {
                auto tp = find_tp(_x + 1, _y);
                make_move(Direction::EAST);
                _x = tp.first;
                _y = tp.second;
                return true;
            }
            if(new_tile == 'S') {
                make_move(Direction::EAST);
                _dir = Direction::SOUTH;
                return true;
            }
            if(new_tile == 'E') {
                make_move(Direction::EAST);
                _dir = Direction::EAST;
                return true;
            }
            if(new_tile == 'N') {
                make_move(Direction::EAST);
                _dir = Direction::NORTH;
                return true;
            }
            if(new_tile == 'W') {
                make_move(Direction::EAST);
                _dir = Direction::WEST;
                return true;
            }
            if(new_tile == '$') {
                make_move(Direction::EAST);
                _is_alive = false;
                return true;
            }
            make_move(Direction::EAST);
            return true;
            break;
        }
        case Direction::NORTH: {
            auto & new_tile = _map.at(_y - 1).at(_x);
            if(new_tile == '#') {
                return false;
            }
            if(new_tile == 'X') {
                if(_is_in_braker_mode) {
                    new_tile = ' ';
                    make_move(Direction::NORTH);
                    return true;
                } else {
                    return false;
                }
            }
            if(new_tile == 'B') {
                _is_in_braker_mode = !_is_in_braker_mode;
                make_move(Direction::NORTH);
                return true;
            }
            if(new_tile == 'I') {
                _is_in_inverted_mode = !_is_in_inverted_mode;
                make_move(Direction::NORTH);
                return true;
            }
            if(new_tile == 'T') {
                auto tp = find_tp(_x, _y - 1);
                make_move(Direction::NORTH);
                _x = tp.first;
                _y = tp.second;
                return true;
            }
            if(new_tile == 'S') {
                make_move(Direction::NORTH);
                _dir = Direction::SOUTH;
                return true;
            }
            if(new_tile == 'E') {
                make_move(Direction::NORTH);
                _dir = Direction::EAST;
                return true;
            }
            if(new_tile == 'N') {
                make_move(Direction::NORTH);
                _dir = Direction::NORTH;
                return true;
            }
            if(new_tile == 'W') {
                make_move(Direction::NORTH);
                _dir = Direction::WEST;
                return true;
            }
            if(new_tile == '$') {
                make_move(Direction::NORTH);
                _is_alive = false;
                return true;
            }
            make_move(Direction::NORTH);
            return true;
            break;
        }
        case Direction::WEST: {
            auto & new_tile = _map.at(_y).at(_x - 1);
            if(new_tile == '#') {
                return false;
            }
            if(new_tile == 'X') {
                if(_is_in_braker_mode) {
                    new_tile = ' ';
                    make_move(Direction::WEST);
                    return true;
                } else {
                    return false;
                }
            }
            if(new_tile == 'B') {
                _is_in_braker_mode = !_is_in_braker_mode;
                make_move(Direction::WEST);
                return true;
            }
            if(new_tile == 'I') {
                _is_in_inverted_mode = !_is_in_inverted_mode;
                make_move(Direction::WEST);
                return true;
            }
            if(new_tile == 'T') {
                auto tp = find_tp(_x - 1, _y);
                make_move(Direction::WEST);
                _x = tp.first;
                _y = tp.second;
                return true;
            }
            if(new_tile == 'S') {
                make_move(Direction::WEST);
                _dir = Direction::SOUTH;
                return true;
            }
            if(new_tile == 'E') {
                make_move(Direction::WEST);
                _dir = Direction::EAST;
                return true;
            }
            if(new_tile == 'N') {
                make_move(Direction::WEST);
                _dir = Direction::NORTH;
                return true;
            }
            if(new_tile == 'W') {
                make_move(Direction::WEST);
                _dir = Direction::WEST;
                return true;
            }
            if(new_tile == '$') {
                make_move(Direction::WEST);
                _is_alive = false;
                return true;
            }
            make_move(Direction::WEST);
            return true;
            break;
        }
    }
}

void Bender::make_move(Direction dir) {
    switch(dir) {
        case Direction::SOUTH:
            _y += 1;
            _dir = Direction::SOUTH;
            _move = "SOUTH";
            break;
        case Direction::EAST:
            _x += 1;
            _dir = Direction::EAST;
            _move = "EAST";
            break;
        case Direction::NORTH:
            _y -= 1;
            _dir = Direction::NORTH;
            _move = "NORTH";
            break;
        case Direction::WEST:
            _x -= 1;
            _dir = Direction::WEST;
            _move = "WEST";
            break;
    }
}

bool Bender::is_alive() const {
    return _is_alive;
}

bool Bender::is_looped() const {
    return _is_looped;
}

void Bender::set_looped(bool is_looped) {
    _is_looped = is_looped;
}

std::string Bender::get_move() const {
    return _move;
}

std::pair<std::size_t, std::size_t> Bender::find_tp(std::size_t curr_x, std::size_t curr_y) {
    std::size_t another_x = 0;
    std::size_t another_y = 0;
    for(std::size_t i = 0; i < _map.size(); ++i) {
        for(std::size_t j = 0; j < _map.at(i).size(); ++j) {
            if(_map.at(i).at(j) == 'T' && !(i == curr_y && j == curr_x)) {
                another_x = j;
                another_y = i;
            }
        }
    }
    return std::make_pair(another_x, another_y);
}

bool Bender::operator ==(Bender const & other) const {
    return _map == other._map && _x == other._x && _y == other._y && _is_alive == other._is_alive && _is_looped == other._is_looped && _is_in_braker_mode == other._is_in_braker_mode && _is_in_inverted_mode == other._is_in_inverted_mode && _dir == other._dir;
}

typename std::hash<Bender>::result_type std::hash<Bender>::operator ()(Bender const & b) const {
    typename std::hash<Bender>::result_type res = 0;
    for(auto const & l : b._map) {
        for(auto const & c : l) {
            res ^= std::hash<char>()(c);
        }
    }
    return res ^ std::hash<unsigned int>()(b._x) ^ std::hash<unsigned int>()(b._y) ^ std::hash<bool>()(b._is_alive) ^ std::hash<bool>()(b._is_looped) ^ std::hash<bool>()(b._is_in_braker_mode) ^ std::hash<bool>()(b._is_in_inverted_mode) ^ std::hash<unsigned int>()(static_cast<unsigned int>(b._dir));
}
