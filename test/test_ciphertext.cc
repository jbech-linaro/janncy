#include <algorithm>
#include <complex>
#include <vector>

#include <gtest/gtest.h>

#include "include/ciphertext.h"
#include "include/message.h"

namespace {

double epsilon = 10e-5;

void TestCloseEnough(janncy::Message::Vector v0, janncy::Message::Vector v1) {
  janncy::Message::Vector diff;
  diff.reserve(v0.size());
  std::transform(v0.begin(), v0.end(), v1.begin(), std::back_inserter(diff),
                 std::minus<janncy::Message::Scalar>());

  for (auto val : diff) {
    EXPECT_LT(std::norm(val), epsilon);
  }
}

}  // namespace

TEST(Ciphertext, AddCC) {
  auto in0 = janncy::Message::Vector{0, 1, 2, 3, 4, 5, 6, 7};
  auto in1 = in0;
  auto ct0 = janncy::Ciphertext::Encrypt(in0);
  auto ct1 = janncy::Ciphertext::Encrypt(in1);
  auto result = ct0.AddCC(ct1).Decrypt();
  janncy::Message::Vector expected;
  expected.reserve(in0.size());
  std::transform(in0.begin(), in0.end(), in1.begin(),
                 std::back_inserter(expected), std::plus<double>());
  TestCloseEnough(result, expected);
}

TEST(Ciphertext, MulCC) {
  auto in0 = janncy::Message::Vector{0, 1, 2, 3, 4, 5, 6, 7};
  auto in1 = in0;
  auto ct0 = janncy::Ciphertext::Encrypt(in0);
  auto ct1 = janncy::Ciphertext::Encrypt(in1);
  auto result = ct0.MulCC(ct1).Decrypt();
  janncy::Message::Vector expected;
  expected.reserve(in0.size());
  std::transform(in0.begin(), in0.end(), in1.begin(),
                 std::back_inserter(expected), std::multiplies<double>());
  TestCloseEnough(result, expected);
}

TEST(Ciphertext, MulCP) {
  auto in0 = janncy::Message::Vector{0, 1, 2, 3, 4, 5, 6, 7};
  auto in1 = in0;
  auto ct0 = janncy::Ciphertext::Encrypt(in0);
  auto pt_vec = in1;
  auto result = (ct0.MulCP(pt_vec)).Decrypt();
  janncy::Message::Vector expected;
  expected.reserve(in0.size());
  std::transform(in0.begin(), in0.end(), in1.begin(),
                 std::back_inserter(expected), std::multiplies<double>());
  TestCloseEnough(result, expected);
}

TEST(Ciphertext, AddCP) {
  auto in0 = janncy::Message::Vector{0, 1, 2, 3, 4, 5, 6, 7};
  auto in1 = in0;
  auto ct0 = janncy::Ciphertext::Encrypt(in0);
  auto pt_vec = in1;
  janncy::Message::Vector expected;
  expected.reserve(in0.size());
  std::transform(in0.begin(), in0.end(), in1.begin(),
                 std::back_inserter(expected), std::plus<double>());
  auto result = (ct0.AddCP(pt_vec)).Decrypt();
  TestCloseEnough(result, expected);
}

TEST(Ciphertext, RotateC) {
  auto in0 = janncy::Message::Vector{0, 1, 2, 3, 4, 5, 6, 7};
  auto ct = janncy::Ciphertext::Encrypt(in0);
  auto rotate_amount = 2;
  auto result = ct.RotateC(rotate_amount).Decrypt();
  auto expected = in0;
  std::rotate(expected.begin(), expected.begin() + rotate_amount,
              expected.end());
  TestCloseEnough(result, expected);
}

TEST(Ciphertext, Bootstrap) {
  auto in0 = janncy::Message::Vector{0, 1, 2, 3, 4, 5, 6, 7};
  auto ct = janncy::Ciphertext::Encrypt(in0);
  auto result = ct.Bootstrap().Decrypt();
  TestCloseEnough(result, in0);
}
