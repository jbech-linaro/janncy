#include "include/Node.hpp"

void Node::add_child(Node* child) {
    children.push_back(child);
}

std::vector<Node*> Node::get_children() const {
    return children;
}

