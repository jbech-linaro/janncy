#ifndef JANNCY_CT_GRAPH_H_
#define JANNCY_CT_GRAPH_H_

#include <vector>

#include "include/ct_op.h"
#include "include/dag.h"

namespace janncy {

using CtGraph = Graph<CtOp>;

namespace ct_graph {

const CtOp& CreateInput(CtGraph& ct_graph);
const CtOp& CreateAdd(CtGraph& ct_graph, const CtOp& parent_1,
                      const CtOp& parent_2);
const CtOp& CreateMul(CtGraph& ct_graph, const CtOp& parent_1,
                      const CtOp& parent_2);
const CtOp& CreatePtAdd(CtGraph& ct_graph, const CtOp& parent);
const CtOp& CreatePtMul(CtGraph& ct_graph, const CtOp& parent);
const CtOp& CreateRotate(CtGraph& ct_graph, const CtOp& parent);

}  // namespace ct_graph

}  // namespace janncy

#endif  // JANNCY_CT_GRAPH_H_
