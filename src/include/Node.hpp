#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>
#include <vector>

class Node {
public:
    void add_child(Node* child);
    std::vector<Node*> get_children() const;
    virtual std::string str() const = 0;

private:
    std::vector<Node*> children;
};

#endif  // NODE_HPP_
