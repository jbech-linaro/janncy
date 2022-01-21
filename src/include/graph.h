#ifndef JANNCY_GRAPH_H_
#define JANNCY_GRAPH_H_

#include <algorithm>
#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace janncy {

template <class T>
class Graph {
 public:
  // Transfers ownership of `new_node` to the Graph object
  T* AddNode(std::unique_ptr<T> new_node,
             const std::vector<const T*>& parents) {
    T* raw_new_node = new_node.get();
    nodes_.emplace_back(std::move(new_node));

    child_map_[raw_new_node] = {};
    parent_map_[raw_new_node] = {};

    for (const T* parent : parents) {
      assert(child_map_.count(parent) == 1);
      child_map_[parent].push_back(raw_new_node);

      // alex: This is safe because the assert guarantees that `parent`
      //       points to an object owned by this object and has been
      //       allocated as non-const.
      //       It looks a bit dodgy, but is neccessary to achieve const
      //       correctness if using pointers as indices.
      parent_map_[raw_new_node].push_back(const_cast<T*>(parent));
    }

    return raw_new_node;
  }

  std::vector<const T*> parents(const T* node) const {
    auto& ref = parent_map_.at(node);
    return std::vector<const T*>(ref.begin(), ref.end());
  }
  const std::vector<T*>& parents(const T* node) { return parent_map_.at(node); }

  std::vector<const T*> children(const T* node) const {
    auto& ref = child_map_.at(node);
    return std::vector<const T*>(ref.begin(), ref.end());
  }
  const std::vector<T*>& children(const T* node) { return child_map_.at(node); }

  std::vector<const T*> nodes() const {
    std::vector<const T*> result(nodes_.size());
    std::transform(nodes_.begin(), nodes_.end(), result.begin(),
                   [](const auto& ptr) { return ptr.get(); });
    return result;
  }
  std::vector<T*> nodes() {
    std::vector<T*> result(nodes_.size());
    std::transform(nodes_.begin(), nodes_.end(), result.begin(),
                   [](const auto& ptr) { return ptr.get(); });
    return result;
  }

  bool Contains(const T* node) const { return child_map_.count(node) == 1; }

 private:
  std::vector<std::unique_ptr<T>> nodes_;
  std::unordered_map<const T*, std::vector<T*>> child_map_;
  std::unordered_map<const T*, std::vector<T*>> parent_map_;
};

template <class T>
std::ostream& operator<<(std::ostream& stream, const Graph<T>& graph) {
  stream << "Graph{\n";
  for (const T* node : graph.nodes()) {
    stream << "  " << *node << " -> " << graph.children(node) << "\n";
  }
  return stream << "}";
}

}  // namespace janncy

#endif  //  JANNCY_GRAPH_H_
