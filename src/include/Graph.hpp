#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <vector>
#include <string>

class Node;

class Graph {
public:
    void add_node(Node* node) {
        nodes.push_back(node);
    }

    std::string str() const;

    void draw() const;

private:
    std::vector<Node*> nodes;
};

#endif  // GRAPH_HPP_
