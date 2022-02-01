#ifndef JANNCY_CT_DAG_H_
#define JANNCY_CT_DAG_H_

#include <vector>

#include "include/ct_op.h"
#include "include/dag.h"

namespace janncy {

using CtDag = Dag<CtOp>;

namespace ct_dag {

const CtOp& CreateInput(CtDag& ct_graph);

const CtOp& CreateMulCC(CtDag& ct_graph, const CtOp& parent_1,
                        const CtOp& parent_2);
const CtOp& CreateMulCP(CtDag& ct_graph, const CtOp& parent);
const CtOp& CreateMulCS(CtDag& ct_graph, const CtOp& parent);

const CtOp& CreateAddCC(CtDag& ct_graph, const CtOp& parent_1,
                        const CtOp& parent_2);
const CtOp& CreateAddCP(CtDag& ct_graph, const CtOp& parent);
const CtOp& CreateAddCS(CtDag& ct_graph, const CtOp& parent);

const CtOp& CreateRotateC(CtDag& ct_graph, const CtOp& parent);

}  // namespace ct_dag

}  // namespace janncy

#endif  // JANNCY_CT_DAG_H_
