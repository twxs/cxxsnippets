#include <gtest/gtest.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

template <class Range, class T>
bool contains(const Range &range, const T &value) {
  typedef decltype(*begin(range)) value_type;
  return any_of(begin(range), end(range),
                [&value](const value_type &i) { return value == i; });
}

TEST(algorithm, stringcontains) {
  string str("hello");
  ASSERT_TRUE(contains(str, 'o'));
  ASSERT_FALSE(contains(str, 'O'));
}

TEST(algorithm, vectorcontains) {
  vector<int> v{0, 1, 2, 3};
  ASSERT_TRUE(contains(v, 0));
  ASSERT_FALSE(contains(v, 4));
}

TEST(algorithm, vectorcontain) {
  vector<int> v{0, 1, 2, 3};
  ASSERT_TRUE(contains(v, 0));
  ASSERT_FALSE(contains(v, 4));
}

// given a rage of values {0, 1, 2, 3} and a value
// return the enclosing values i.e 0.5 -> {0, 1}; 5 -> {3, 3}
template <class Range, class T>
auto find_range(const Range &rge, const T &value)
    -> decltype(std::make_pair(*std::begin(rge), *std::begin(rge))) {

	auto begin = std::rbegin(rge);
	auto end = std::rend(rge);
	assert(std::distance(begin, end) >= 2);

	auto lower = std::upper_bound(begin, end, value, [](const auto & l, const auto & r) {return l >= r; });

	auto upper = lower;

	if (lower == end) { // v < range
		lower = upper = std::next(begin, std::distance(begin, end)-1);
	}
	else { // v ∈ rge, v > rge
		upper = (lower != begin) ? std::prev(lower) : lower;
	}
	return std::make_pair(*lower, *upper);
}

TEST(algorithm, find_range) {
	vector<int> values{ 0, 2, 3 };

	
	for (const auto & v : { 
		std::make_pair(-1, std::make_pair(0, 0)),
		std::make_pair( 0, std::make_pair(0, 2)),
		std::make_pair( 1, std::make_pair(0, 2)),
		std::make_pair(2, std::make_pair(2, 3)),
		std::make_pair(3, std::make_pair(3, 3)),
		std::make_pair( 4, std::make_pair(3, 3)),
	}) {
		//std::cout << v << " € [" << find_range(values, v).first << ", " << find_range(values, v).second << "]\n";
		ASSERT_EQ(v.second, find_range(values, v.first));

	}
}
