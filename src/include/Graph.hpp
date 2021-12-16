#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include "Node.hpp"
#include "Panic.hpp"

#include <algorithm>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>

#include "graphviz/cgraph.h"
#include "graphviz/gvc.h"
#include "graphviz/types.h"

#include <string>
#include <unordered_set>

template <class T> class Graph {
  public:
    void add_node(T* node) {
        if (!node) {
            panic("Cannot insert nullptr node!");
        }
        nodes_.push_back(node);
    }

    T* sentinel() {
        if (!sentinel_) {
            /*
             * nsamar: This is undefined behavior cuz node<T> is not a T
             * It works, but is a hack. dynamic_cast would generate a nullptr.
             */
            sentinel_ = static_cast<T*>(new Node<T>(this, {}));
        }
        return sentinel_;
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
            for (auto& child : node->get_children()) {
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

  protected:
    std::vector<T*> nodes_;
    T* sentinel_ = nullptr;
};

#endif  // GRAPH_HPP_
