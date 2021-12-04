#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>
#include <vector>

class Node {
public:
    explicit Node(std::vector<Node*> parents) : parents_(parents) {};
    void add_child(Node* child);
    std::vector<Node*> get_children() const;
    virtual std::string str() const = 0;

    std::vector<Node*> get_parents() const { return parents_; }

protected:
    std::vector<Node*> parents_;

private:
    std::vector<Node*> children;
};

#endif  // NODE_HPP_
