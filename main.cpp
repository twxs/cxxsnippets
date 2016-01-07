#include <gtest/gtest.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

template<class Range, class Value>
bool contains(const Range &range, const Value &value) {
	typedef decltype(*cbegin(range)) value_type; 
	return any_of(cbegin(range), cend(range), [&](const value_type &i) { return value == i;} );
}

TEST(any_of, contains) {
  string str("hello");
  ASSERT_TRUE(contains(str, 'o'));
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    auto ret = RUN_ALL_TESTS();
    return ret;
}
