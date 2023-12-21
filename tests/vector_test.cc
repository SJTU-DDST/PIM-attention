#include <gtest/gtest.h>
#include "../attention/vector.hpp"
#include "../attention/token.hpp"

TEST(Vector, vector) {
    vector<int32_t> v(2);
    vector<int32_t> &v_c = v;
    std::cout<<v<<v_c;
}