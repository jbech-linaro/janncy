#ifndef DRAW_GRAPH_H
#define DRAW_GRAPH_H

#include <cstdlib>
#include <experimental/filesystem>
#include <iostream>
#include <string>

#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <graphviz/types.h>

#include "graph.h"
#include "utils.h"

namespace janncy {

template <class T>
void DrawGraph(const Graph<T>& graph, const std::string& filename) {
  Agraph_t* g = agopen((char*)"g", Agdirected, nullptr);

  for (const T* node : graph.nodes()) {
    // Use the pointer for node id, as string representation may not be unique.
    Agnode_t* g_node = agnode(g, ToString(node).data(), 1);
    agsafeset(g_node, (char*)"label", ToString(*node).data(), (char*)"");

    for (const T* child : graph.children(*node)) {
      Agnode_t* g_child = agnode(g, ToString(child).data(), 1);
      agedge(g, g_node, g_child, 0, 1);
    }
  }
  std::string output_dir = "../janncy_graphs";
  std::experimental::filesystem::create_directories(output_dir);
  std::string filepath_arg = "-o" + output_dir + "/" + filename + ".pdf";

  char* args[] = {(char*)"dot", (char*)"-Tpdf", filepath_arg.data()};

  GVC_t* gvc = gvContext();
  gvParseArgs(gvc, sizeof(args) / sizeof(char*), args);

  gvLayout(gvc, g, "dot");
  gvRenderJobs(gvc, g);
  gvFreeLayout(gvc, g);
  agclose(g);
  gvFreeContext(gvc);
}

}  // namespace janncy
#endif  // DRAW_GRAPH_H
