#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include "Panic.hpp"

#include <algorithm>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <graphviz/types.h>

namespace janncy {

template <class T> class Graph {
  public:
    void add_node(T* node, const std::vector<T*>& parents) {
        if (!node) {
            panic("Cannot insert nullptr node!");
        }
        nodes_.push_back(node);
        child_map_.insert(std::make_pair(node, std::vector<T*>{}));
        parent_map_.insert(std::make_pair(node, std::vector<T*>{}));
        for (auto parent : parents) {
            child_map_.at(parent).push_back(node);
            parent_map_.at(node).push_back(parent);
        }
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
        std::unordered_map<T*, Agnode_t*> node_map;
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
    }

    const std::vector<T*>& parents(T* node) const {
        return parent_map_.at(node);
    }

    const std::vector<T*>& children(T* node) const {
        return child_map_.at(node);
    }

    const std::vector<T*>& nodes() const { return nodes_; }

  private:
    std::vector<T*> nodes_;
    std::unordered_map<T*, std::vector<T*> > child_map_;
    std::unordered_map<T*, std::vector<T*> > parent_map_;
};

}  // namespace janncy

#endif  // GRAPH_HPP_
