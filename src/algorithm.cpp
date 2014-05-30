#include <gtest/gtest.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

template<class Range, class T>
bool contains(const Range &range, const T &value) {
	typedef decltype(*cbegin(range)) value_type; 
	return any_of(cbegin(range), cend(range), [&value] (const value_type &i) { return value == i;} );
}

TEST(algorithm, contains) {
  string str("hello");
  ASSERT_TRUE(contains(str, 'o'));
}

