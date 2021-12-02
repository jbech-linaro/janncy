#ifndef FLOW_HPP_
#define FLOW_HPP_

#include <unordered_map>
#include <vector>

class Flow {
public:
    void add_child(FlowNode* parent, FlowNode* child);
private:
    std::unordered_map<FlowNode*, std::vector<FlowNode*>> children;
}

#endif  // FLOWNODE_HPP_
