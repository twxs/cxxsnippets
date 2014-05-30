#include <gtest/gtest.h>


TEST(sementic_move, simple) {

	struct A {
		~A() { }
		A() { }
		A(A&&) { }
		A(const A&) { }
		A& operator=(A&&) { }
		A& operator=(const A&) { }
	};

	A a1;

  ASSERT_TRUE(true);

}