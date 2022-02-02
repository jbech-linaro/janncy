#ifndef JANNCY_CHUNK_LAYOUT_H_
#define JANNCY_CHUNK_LAYOUT_H_

#include <bitset>
#include <optional>
#include <vector>

namespace janncy {

const int kChunkIndexBits = 32;
using ChunkMask = std::bitset<kChunkIndexBits>;

class ChunkLayout {
 public:
  std::vector<std::optional<int>> DimensionIndices(int dimension) const;
  std::vector<std::optional<int>> DimensionIndices(int dimension,
                                                   int offset) const;

 private:
  int chunk_size_;
};

}  // namespace janncy

#endif  // JANNCY_CHUNK_LAYOUT_H_
