#include "include/ct_graph.h"

#include <vector>

#include "include/cleartext_evaluator.h"
#include "include/ct_add.h"
#include "include/ct_input.h"
#include "include/ct_mul.h"
#include "include/ct_pt_add.h"
#include "include/ct_pt_mul.h"
#include "include/ct_rotate.h"

namespace janncy {

CtOp* ct_graph::CreateInput(CtGraph& ct_graph) {
  return ct_graph.AddNode(new CtInput(), {});
}

CtOp* ct_graph::CreateAdd(CtGraph& ct_graph, const CtOp* parent_1,
                          const CtOp* parent_2) {
  return ct_graph.AddNode(new CtAdd(), {parent_1, parent_2});
}

CtOp* ct_graph::CreateMul(CtGraph& ct_graph, const CtOp* parent_1,
                          const CtOp* parent_2) {
  return ct_graph.AddNode(new CtMul(), {parent_1, parent_2});
}

CtOp* ct_graph::CreatePtAdd(CtGraph& ct_graph, const CtOp* parent) {
  return ct_graph.AddNode(new CtPtAdd(), {parent});
}

CtOp* ct_graph::CreatePtMul(CtGraph& ct_graph, const CtOp* parent) {
  return ct_graph.AddNode(new CtPtMul(), {parent});
}

CtOp* ct_graph::CreateRotate(CtGraph& ct_graph, const CtOp* parent) {
  return ct_graph.AddNode(new CtRotate(), {parent});
}

}  // namespace janncy
