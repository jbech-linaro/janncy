#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include "CtOp.hpp"
#include "FlowNode.hpp"
#include "Node.hpp"

#include <algorithm>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <graphviz/types.h>

using namespace std::string_literals;

#include <string>
#include <unordered_set>

template <class T> class Node;

template <class T> class Graph {
  public:
    void add_node(T* node) { nodes_.insert(node); }

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

    void reload() {
        std::set<T*> new_nodes;
        std::set<T*> nodes;
        for (auto& node : nodes_) {
            nodes.insert(node);
            new_nodes.insert(node);
        }
        while (!new_nodes.empty()) {
            for (auto& val : new_nodes) {
                nodes.insert(val);
            }
            new_nodes.clear();
            for (auto& node : nodes) {
                auto children = node->get_children();
                for (auto& child : children) {
                    if (!nodes.count(child)) {
                        new_nodes.insert(child);
                    }
                }
            }
        }
        for (auto& node : nodes) {
            nodes_.insert(node);
        }
    }

    void draw(std::string filename) {
        reload();
        std::unordered_map<T*, Agnode_t*> node_map;
        Agraph_t* g;
        GVC_t* gvc;

        gvc = gvContext();

        g = agopen((char*)"g", Agdirected, nullptr);

        for (auto& node : nodes_) {
            node_map[node] =
                agnode(g, const_cast<char*>((node->str()).c_str()), 1);
        }
        for (auto& node : nodes_) {
            for (auto& child : node->get_children()) {
                agedge(g, node_map[node], node_map[child], 0, 1);
            }
        }
        // agsafeset(n, (char*)"color", (char*)"red", (char*)"");
        std::string filepath =
            "-o/data/sanchez/users/nsamar/janncy/"s + filename + ".pdf"s;
        char* args[] = {(char*)"dot", (char*)"-Tpdf", (char*)filepath.c_str()};
        gvParseArgs(gvc, sizeof(args) / sizeof(char*), args);

        gvLayout(gvc, g, "dot");
        gvRenderJobs(gvc, g);
        gvFreeLayout(gvc, g);
        agclose(g);
        gvFreeContext(gvc);
    }

  protected:
    std::unordered_set<T*> nodes_;
};

#endif  // GRAPH_HPP_
