#include "include/fully_connected.h"

#include <string>
#include <vector>

#include "include/flow_visitor.h"

namespace janncy {

FullyConnected::FullyConnected(int input_size, int output_size)
    : input_size_(input_size), output_size_(output_size) {}

void FullyConnected::Accept(FlowVisitor& visitor) { visitor.Visit(*this); }
std::string FullyConnected::op_type() const { return "FullyConnected"; }
std::vector<int> FullyConnected::shape() const { return {output_size()}; }

int FullyConnected::input_size() const { return input_size_; }
int FullyConnected::output_size() const { return output_size_; }

}  // namespace janncy
