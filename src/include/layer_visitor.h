#ifndef JANNCY_LAYER_VISITOR_H_
#define JANNCY_LAYER_VISITOR_H_

namespace janncy {

class Layer;
class ConvLayer;
class FullyConnectedLayer;
class AveragePoolLayer;
class BatchNormalizationLayer;
class AddLayer;
class InputLayer;
class ReluLayer;
class MaxPoolLayer;
class FlattenLayer;

class LayerVisitor {
 public:
  LayerVisitor() = default;
  LayerVisitor(LayerVisitor&&) = default;
  virtual ~LayerVisitor() {}
  LayerVisitor(const LayerVisitor&) = delete;
  LayerVisitor& operator=(const LayerVisitor&) = delete;
  LayerVisitor& operator=(const LayerVisitor&&) = default;

  virtual void Visit(const ConvLayer& node) = 0;
  virtual void Visit(const FullyConnectedLayer& node) = 0;
  virtual void Visit(const AveragePoolLayer& node) = 0;
  virtual void Visit(const BatchNormalizationLayer& node) = 0;
  virtual void Visit(const AddLayer& node) = 0;
  virtual void Visit(const InputLayer& node) = 0;
  virtual void Visit(const ReluLayer& node) = 0;
  virtual void Visit(const MaxPoolLayer& node) = 0;
  virtual void Visit(const FlattenLayer& node) = 0;
};

}  // namespace janncy

#endif  // JANNCY_LAYER_VISITOR_H_
