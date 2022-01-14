#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <algorithm>
#include <sstream>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <graphviz/types.h>

namespace janncy {

template <class T> class Graph {
  public:
    // Transfers ownership of `new_node` to the Graph object
    T* add_node(T* new_node, const std::vector<const T*>& parents) {
        nodes_.emplace_back(new_node);

        child_map_[new_node] = {};
        parent_map_[new_node] = {};

        for (const T* parent : parents) {
            assert(child_map_.count(parent) == 1);
            child_map_[parent].push_back(new_node);

            // alex: This is safe because the assert guarantees that `parent`
            //       points to an object owned by this object and has been
            //       allocated as non-const.
            //       It looks a bit dodgy, but is neccessary to achieve const
            //       correctness if using pointers as indices.
            parent_map_[new_node].push_back(const_cast<T*>(parent));
        }

        return new_node;
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

    void draw(const std::string& filename) const {
        /*
        std::unordered_map<const T*, Agnode_t*> node_map;
        Agraph_t* g;
        GVC_t* gvc;

        gvc = gvContext();

        g = agopen((char*)"g", Agdirected, nullptr);

        for (auto& node : nodes_) {
            node_map[node] =
                agnode(g, const_cast<char*>((node->str()).c_str()), 1);
            for (auto& child : children(node)) {
                node_map[child] =
                    agnode(g, const_cast<char*>((child->str()).c_str()), 1);
                agedge(g, node_map.at(node), node_map.at(child), 0, 1);
            }
        }
        // agsafeset(n, (char*)"color", (char*)"red", (char*)"");
        std::string filepath =
            "-o/data/sanchez/users/nsamar/janncy/" + filename + ".pdf";
        char* args[] = {(char*)"dot", (char*)"-Tpdf", (char*)filepath.c_str()};
        gvParseArgs(gvc, sizeof(args) / sizeof(char*), args);

        gvLayout(gvc, g, "dot");
        gvRenderJobs(gvc, g);
        gvFreeLayout(gvc, g);
        agclose(g);
        gvFreeContext(gvc);
        */
    }

    const std::vector<const T*>& parents(const T* node) const {
        return parent_map_.at(node);
    }
    const std::vector<T*>& parents(const T* node) {
        return parent_map_.at(node);
    }

    const std::vector<const T*>& children(const T* node) const {
        return child_map_.at(node);
    }
    const std::vector<T*>& children(const T* node) {
        return child_map_.at(node);
    }

    std::vector<const T*> nodes() const {
        return get_raw_node_pointers();
    }
    std::vector<T*> nodes() {
        return get_raw_node_pointers();
    }

    bool contains(const T* node) const {
        return child_map_.count(node) == 1;
    }

  private:
    std::vector<std::unique_ptr<T>> nodes_;
    std::unordered_map<const T*, std::vector<T*> > child_map_;
    std::unordered_map<const T*, std::vector<T*> > parent_map_;

    std::vector<T*> get_raw_node_pointers() const {
        std::vector<T*> result(nodes_.size());
        std::transform(nodes_.begin(), nodes_.end(), result.begin(),
                [](const auto& ptr) { return ptr.get(); }
        );
        return result;
    }
};

}  // namespace janncy

#endif  // GRAPH_HPP_
