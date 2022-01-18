#ifndef JANNCY_CT_GRAPH_H_
#define JANNCY_CT_GRAPH_H_

#include <vector>

#include "include/ct_op.h"
#include "include/graph.h"

namespace janncy {

using CtGraph = Graph<CtOp>;

namespace ct_graph {

// TODO(alex): Move this evaluate directly to the visitor class?
std::vector<std::vector<double>> Evaluate(
    CtGraph& ct_graph, std::vector<std::vector<double>> init_values);

CtOp* CreateInput(CtGraph& ct_graph);
CtOp* CreateAdd(CtGraph& ct_graph, const CtOp* parent_1, const CtOp* parent_2);
CtOp* CreateMul(CtGraph& ct_graph, const CtOp* parent_1, const CtOp* parent_2);
CtOp* CreatePtAdd(CtGraph& ct_graph, const CtOp* parent);
CtOp* CreatePtMul(CtGraph& ct_graph, const CtOp* parent);
CtOp* CreateRotate(CtGraph& ct_graph, const CtOp* parent);

}  // namespace ct_graph

}  // namespace janncy

#endif  // JANNCY_CT_GRAPH_H_
