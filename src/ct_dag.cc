#include "include/ct_dag.h"

#include <memory>
#include <vector>

#include "include/cleartext_evaluator.h"
#include "include/ct_add.h"
#include "include/ct_input.h"
#include "include/ct_mul.h"
#include "include/ct_pt_add.h"
#include "include/ct_pt_mul.h"
#include "include/ct_rotate.h"

namespace janncy {

namespace ct_graph {

const CtOp& CreateInput(CtGraph& ct_graph) {
  return ct_graph.AddNode(std::make_unique<CtInput>(), {});
}

const CtOp& CreateAdd(CtGraph& ct_graph, const CtOp& parent_1,
                      const CtOp& parent_2) {
  return ct_graph.AddNode(std::make_unique<CtAdd>(), {&parent_1, &parent_2});
}

const CtOp& CreateMul(CtGraph& ct_graph, const CtOp& parent_1,
                      const CtOp& parent_2) {
  return ct_graph.AddNode(std::make_unique<CtMul>(), {&parent_1, &parent_2});
}

const CtOp& CreatePtAdd(CtGraph& ct_graph, const CtOp& parent) {
  return ct_graph.AddNode(std::make_unique<CtPtAdd>(), {&parent});
}

const CtOp& CreatePtMul(CtGraph& ct_graph, const CtOp& parent) {
  return ct_graph.AddNode(std::make_unique<CtPtMul>(), {&parent});
}

const CtOp& CreateRotate(CtGraph& ct_graph, const CtOp& parent) {
  return ct_graph.AddNode(std::make_unique<CtRotate>(), {&parent});
}

}  // namespace ct_graph

}  // namespace janncy
