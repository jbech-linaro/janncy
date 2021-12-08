#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>
#include <vector>

/**
 * Uses the CRTP design pattern in order to disable mixing of different
 * node types within the same Graph
 * https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
 **/
template <class T> class Node {
  public:
    explicit Node(std::vector<T*> parents) : parents_(parents) {
        for (auto& parent : parents) {
            parent->add_child(static_cast<T*>(this));
        }
    }
    void add_child(T* child) { children_.push_back(child); }
    std::vector<T*> get_children() const { return children_; }
    virtual std::string str() const = 0;

    std::vector<T*> get_parents() const { return parents_; }

  protected:
    std::vector<T*> parents_;

  private:
    std::vector<T*> children_;
};

#endif  // NODE_HPP_
