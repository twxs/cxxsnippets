#include <gtest/gtest.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

template<class Range, class T>
bool contains(const Range &range, const T &value) {
	typedef decltype(*begin(range)) value_type; 
	return any_of(begin(range), end(range), [&value] (const value_type &i) { return value == i;} );
}

TEST(algorithm, stringcontains) {
  string str("hello");
  ASSERT_TRUE(contains(str, 'o'));
  ASSERT_FALSE(contains(str, 'O'));
}

TEST(algorithm, vectorcontains) {
  vector<int> v {0, 1, 2, 3};
  ASSERT_TRUE(contains(v, 0));
  ASSERT_FALSE(contains(v, 4));
}


TEST(algorithm, vectorcontain) {
  vector<int> v {0, 1, 2, 3};
  ASSERT_TRUE(contains(v, 0));
  ASSERT_FALSE(contains(v, 4));
}

