#ifndef JANNCY_GRAPH_H_
#define JANNCY_GRAPH_H_

#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <graphviz/types.h>

#include <algorithm>
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

  std::string str() const {
    std::stringstream result;
    for (auto& node : nodes_) {
      result << node->str() << " -> ";
      for (auto& child : node->get_children()) {
        result << child->str() << ", ";
      }
      result << "\n";
    }
    return result.str();
  }

  const std::vector<const T*>& parents(const T* node) const {
    return parent_map_.at(node);
  }
  const std::vector<T*>& parents(const T* node) { return parent_map_.at(node); }

  const std::vector<const T*>& children(const T* node) const {
    return child_map_.at(node);
  }
  const std::vector<T*>& children(const T* node) { return child_map_.at(node); }

  std::vector<const T*> nodes() const { return GetRawNodePointers(); }
  std::vector<T*> nodes() { return GetRawNodePointers(); }

  bool Contains(const T* node) const { return child_map_.count(node) == 1; }

 private:
  std::vector<std::unique_ptr<T>> nodes_;
  std::unordered_map<const T*, std::vector<T*>> child_map_;
  std::unordered_map<const T*, std::vector<T*>> parent_map_;

  std::vector<T*> GetRawNodePointers() const {
    std::vector<T*> result(nodes_.size());
    std::transform(nodes_.begin(), nodes_.end(), result.begin(),
                   [](const auto& ptr) { return ptr.get(); });
    return result;
  }
};

template <class T>
void Draw(Graph<T>& graph, const std::string& filename) {
  std::unordered_map<const T*, Agnode_t*> node_map;
  Agraph_t* g;
  GVC_t* gvc;

  gvc = gvContext();

  g = agopen((char*)"g", Agdirected, nullptr);

  for (auto& node : graph.nodes()) {
    node_map[node] = agnode(g, const_cast<char*>((node->str()).c_str()), 1);
    for (auto& child : graph.children(node)) {
      node_map[child] = agnode(g, const_cast<char*>((child->str()).c_str()), 1);
      agedge(g, node_map.at(node), node_map.at(child), 0, 1);
    }
  }
  std::string filepath =
      "-o/data/sanchez/users/nsamar/janncy/" + filename + ".pdf";
  char* args[] = {(char*)"dot", (char*)"-Tpdf", (char*)filepath.c_str()};
  gvParseArgs(gvc, sizeof(args) / sizeof(char*), args);

  gvLayout(gvc, g, "dot");
  gvRenderJobs(gvc, g);
  gvFreeLayout(gvc, g);
  agclose(g);
  gvFreeContext(gvc);
}

}  // namespace janncy

#endif  //  JANNCY_GRAPH_H_
