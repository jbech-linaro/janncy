#ifndef JANNCY_CT_DAG_H_
#define JANNCY_CT_DAG_H_

#include <vector>

#include "include/ct_op.h"
#include "include/dag.h"

namespace janncy {

using CtDag = Dag<CtOp>;

namespace ct_dag {

const CtOp& CreateInput(CtDag& ct_graph);
const CtOp& CreateAdd(CtDag& ct_graph, const CtOp& parent_1,
                      const CtOp& parent_2);
const CtOp& CreateMul(CtDag& ct_graph, const CtOp& parent_1,
                      const CtOp& parent_2);
const CtOp& CreatePtAdd(CtDag& ct_graph, const CtOp& parent);
const CtOp& CreatePtMul(CtDag& ct_graph, const CtOp& parent);
const CtOp& CreateRotate(CtDag& ct_graph, const CtOp& parent);

}  // namespace ct_dag

}  // namespace janncy

#endif  // JANNCY_CT_DAG_H_
