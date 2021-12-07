#include "include/Graph.hpp"

#include "include/Node.hpp"

#include <sstream>
#include <string>
#include <unordered_map>

#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <graphviz/types.h>

using namespace std::string_literals;

std::string Graph::str() const {
    std::stringstream result;
    for (auto& node : nodes) {
        result << node->str() << " -> ";
        for (auto& child : node->get_children()) {
            result << child->str() << ", ";
        }
        result << "\n";
    }
    return result.str();
}

void Graph::draw(std::string filename) const {
    std::unordered_map<Node*, Agnode_t*> node_map;
    Agraph_t* g;
    GVC_t* gvc;

    gvc = gvContext();

    g = agopen((char*)"g", Agdirected, nullptr);

    for (auto& node : nodes) {
        node_map[node] = agnode(g, const_cast<char*>((node->str()).c_str()), 1);
    }
    for (auto& node : nodes) {
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
