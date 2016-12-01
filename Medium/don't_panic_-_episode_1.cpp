#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>

int main() {
    std::size_t nbFloors; // number of floors
    std::size_t width; // width of the area
    std::size_t nbRounds; // maximum number of rounds
    std::size_t exitFloor; // floor on which the exit is found
    std::size_t exitPos; // position of the exit on its floor
    std::size_t nbTotalClones; // number of generated clones
    std::size_t nbAdditionalElevators; // ignore (always zero)
    std::size_t nbElevators; // number of elevators
    std::cin >> nbFloors >> width >> nbRounds >> exitFloor >> exitPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators;
    std::cin.ignore();

    std::map<std::size_t, std::size_t> elevators;
    for(std::size_t i = 0; i < nbElevators; i++) {
        std::size_t elevatorFloor; // floor on which this elevator is found
        std::size_t elevatorPos; // position of the elevator on its floor
        std::cin >> elevatorFloor >> elevatorPos;
        std::cin.ignore();
        elevators[elevatorFloor] = elevatorPos;
    }

    std::vector<bool> floor_blocked(nbFloors, false);
    while(1) {
        int cloneFloor; // floor of the leading clone
        int clonePos; // position of the leading clone on its floor
        std::string direction; // direction of the leading clone: LEFT or RIGHT
        std::cin >> cloneFloor >> clonePos >> direction;
        std::cin.ignore();

        if(cloneFloor != -1 && clonePos != -1 && direction != "NONE") {
            if(exitFloor == cloneFloor) {
                if(!floor_blocked.at(cloneFloor) && clonePos > exitPos && direction == "RIGHT") {
                    floor_blocked.at(cloneFloor) = true;
                    std::cout << "BLOCK" << std::endl;
                } else {
                    if(!floor_blocked.at(cloneFloor) && clonePos < exitPos && direction == "LEFT") {
                        floor_blocked.at(cloneFloor) = true;
                        std::cout << "BLOCK" << std::endl;
                    } else {
                        std::cout << "WAIT" << std::endl;
                    }
                }
            } else {
                if(!floor_blocked.at(cloneFloor) && clonePos > elevators.at(cloneFloor) && direction == "RIGHT") {
                    floor_blocked.at(cloneFloor) = true;
                    std::cout << "BLOCK" << std::endl;
                } else {
                    if(!floor_blocked.at(cloneFloor) && clonePos < elevators.at(cloneFloor) && direction == "LEFT") {
                        floor_blocked.at(cloneFloor) = true;
                        std::cout << "BLOCK" << std::endl;
                    } else {
                        std::cout << "WAIT" << std::endl;
                    }
                }
            }
        } else {
            std::cout << "WAIT" << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
