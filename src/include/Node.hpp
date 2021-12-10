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
    Node(const Node& other);
    Node(Graph<T>* graph, std::vector<T*> parents)
        : graph_(graph), parents_(parents) {}
    void add_child(T* child) {
        if (!child) {
            panic("nullptr child!");
        }
        children_.push_back(child);
    }
    std::vector<T*> get_children() const { return children_; }
    virtual std::string str() const { return "Anonymous"; }
    std::vector<T*> get_parents() const { return parents_; }
    void register_with_graph();

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
            return x->graph() != parents[0]->graph();
        })) {
        panic("Parent nodes do not all come from the same graph!");
    }
    return parents[0]->graph();
}

template <class T> void Node<T>::register_with_graph() {
    for (auto& parent : parents_) {
        if (!parent) {
            panic("nullptr parent!");
        }
        /**
         * nsamar: These static_cast()'s are concerning, but I see no cleaner
         * way to do this. If there is a better way, please reach out to me!
         *
         * The problem here is not only that static_cast is used, but that this
         * is undefined behavior. This is because `this' cannot be cast to a T,
         * as a T is not yet constructed; that is, T is in the process of being
         * constructed and is currently in its base class constructor.
         *
         * This undefined behavior seems to work in practice tho.
         *
         * A solution would be to have another function that will be guaranteed
         * to be called after the construction of the entire object is complete.
         * Then we could add children and register with the graph using dynamic
         * cast instead of this unsafe static_cast.
         **/
        parent->add_child(static_cast<T*>(this));
    }
    if (!graph_) {
        panic("nullptr graph!");
    }
    graph_->add_node(static_cast<T*>(this));
}

template <class T>
Node<T>::Node(std::vector<T*> parents)
    : graph_(get_graph(parents)), parents_(parents) {
    register_with_graph();
}

template <class T>
Node<T>::Node(Graph<T>* graph) : graph_(graph), parents_{graph->sentinel()} {
    assert(graph->sentinel() && "Graph sentinel must not be nullptr");
    if (!graph_) {
        panic("nullptr graph!");
    }
    graph_->add_node(static_cast<T*>(this));
}

template <class T>
Node<T>::Node(const Node& other)
    : graph_(other.graph_), parents_{other.parents_} {
    if (graph_->sentinel() == parents_[0]) {
        graph_->add_node(static_cast<T*>(this));
    } else {
        register_with_graph();
    }
}

#endif  // NODE_HPP_
