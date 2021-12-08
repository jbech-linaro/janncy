#ifndef NODE_HPP_
#define NODE_HPP_

#include "Panic.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

template <class T> class Graph;

/**
 * Uses the CRTP design pattern in order to disable mixing of different
 * node types within the same Graph
 * https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
 **/
template <class T> class Node {
  public:
    explicit Node(Graph<T>* graph);
    explicit Node(std::vector<T*> parents);
    void add_child(T* child) {
        if (!child) {
            panic("nullptr child!");
        }
        children_.push_back(child);
    }
    std::vector<T*> get_children() const { return children_; }
    virtual std::string str() const = 0;
    std::vector<T*> get_parents() const { return parents_; }

    Graph<T>* graph() const { return graph_; }

  private:
    Graph<T>* graph_;
    const std::vector<T*> parents_;
    std::vector<T*> children_;
};

#include "Graph.hpp"

template <class T> Graph<T>* get_graph(std::vector<T*> parents) {
    if (parents.size() == 0) {
        panic("Parents array has size zero!");
    }
    if (std::any_of(parents.begin(), parents.end(), [&](auto& x) {
            return static_cast<Node<T>*>(x)->graph() !=
                   static_cast<Node<T>*>(parents[0])->graph();
        })) {
        panic("Parent nodes do not all come from the same graph!");
    }
    return parents[0]->graph();
}

template <class T>
Node<T>::Node(std::vector<T*> parents)
    : graph_(get_graph(parents)), parents_(parents) {
    if (!graph_) {
        panic("nullptr graph!");
    }
    for (auto& parent : parents) {
        if (!parent) {
            panic("nulltpr parent!");
        }
        parent->add_child(static_cast<T*>(this));
    }
    graph_->add_node(static_cast<T*>(this));
}

template <class T>
Node<T>::Node(Graph<T>* graph) : graph_(graph), parents_({}) {
    if (!graph_) {
        panic("nullptr graph!");
    }
    graph_->add_node(static_cast<T*>(this));
}

#endif  // NODE_HPP_
