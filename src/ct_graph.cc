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

CtOp* CtGraph::CreateInput() { return AddNode(new CtInput(), {}); }
CtOp* CtGraph::CreateAdd(const CtOp* parent_1, const CtOp* parent_2) {
  return AddNode(new CtAdd(), {parent_1, parent_2});
}
CtOp* CtGraph::CreateMul(const CtOp* parent_1, const CtOp* parent_2) {
  return AddNode(new CtMul(), {parent_1, parent_2});
}
CtOp* CtGraph::CreatePtAdd(const CtOp* parent) {
  return AddNode(new CtPtAdd(), {parent});
}
CtOp* CtGraph::CreatePtMul(const CtOp* parent) {
  return AddNode(new CtPtMul(), {parent});
}
CtOp* CtGraph::CreateRotate(const CtOp* parent) {
  return AddNode(new CtRotate(), {parent});
}

}  // namespace janncy
