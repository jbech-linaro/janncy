#ifndef JANNCY_DAG_H_
#define JANNCY_DAG_H_

#include <algorithm>
#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace janncy {

template <class T>
class Dag {
 public:
  // Transfers ownership of `new_node` to the Graph object
  const T& AddNode(std::unique_ptr<T> new_node,
                   const std::vector<const T*>& parents) {
    const T* raw_new_node = new_node.get();
    nodes_.emplace_back(std::move(new_node));

    child_map_[raw_new_node] = {};
    parent_map_[raw_new_node] = {};

    for (const T* parent : parents) {
      assert(child_map_.count(parent) == 1);
      child_map_[parent].push_back(raw_new_node);
      parent_map_[raw_new_node].push_back(parent);
    }

    return *raw_new_node;
  }

  const std::vector<const T*>& parents(const T& node) const {
    return parent_map_.at(&node);
  }
  const std::vector<const T*>& children(const T& node) const {
    return child_map_.at(&node);
  }
  std::vector<const T*> nodes() const {
    std::vector<const T*> result(nodes_.size());
    std::transform(nodes_.begin(), nodes_.end(), result.begin(),
                   [](const auto& ptr) { return ptr.get(); });
    return result;
  }
  bool Contains(const T& node) const { return child_map_.count(node) == 1; }

 private:
  std::vector<std::unique_ptr<T>> nodes_;
  std::unordered_map<const T*, std::vector<const T*>> child_map_;
  std::unordered_map<const T*, std::vector<const T*>> parent_map_;
};

template <class T>
std::ostream& operator<<(std::ostream& stream, const Dag<T>& dag) {
  stream << "DAG{\n";
  for (const T* node : dag.nodes()) {
    stream << "  " << *node << " -> " << dag.children(node) << "\n";
  }
  return stream << "}";
}

}  // namespace janncy

#endif  //  JANNCY_DAG_H_
