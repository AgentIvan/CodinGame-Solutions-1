#include <iostream>
#include <string>
#include <set>
#include <memory>
#include <cstdlib>

struct Node {
    char value;
    std::set<std::shared_ptr<Node>> children;
};

void add_phone(std::shared_ptr<Node> root, std::string phone);
std::size_t count(std::shared_ptr<Node> root);
void print(std::shared_ptr<Node> root, std::ostream & os = std::cerr);

int main() {
    std::size_t N;
    std::cin >> N;
    std::cin.ignore();

    std::shared_ptr<Node> root = std::make_shared<Node>();
    root->value = '\0';
    for(std::size_t i = 0; i < N; i++) {
        std::string telephone;
        std::cin >> telephone;
        std::cin.ignore();

        add_phone(root, telephone);
    }

    std::cout << count(root) - 1 << std::endl; // minus root node
    return EXIT_SUCCESS;
}

void add_phone(std::shared_ptr<Node> root, std::string phone) {
    if(!phone.empty()) {
        for(auto & child : root->children) {
            if(child->value == phone.front()) {
                add_phone(child, phone.substr(1));
                return;
            }
        }

        std::shared_ptr<Node> child = std::make_shared<Node>();
        child->value = phone.front();
        add_phone(child, phone.substr(1));
        root->children.emplace(child);
    }
}

std::size_t count(std::shared_ptr<Node> root) {
    std::size_t ret = 1;
    for(auto const & child : root->children) {
        ret += count(child);
    }

    return ret;
}
