#include "maybe.hpp"

#include <cassert>

struct TestMaybe {

	int to_int() { return 42; }
};

Maybe<int> foo(int i) {
	return i > 30 ? Maybe<int>(i) : Maybe<int>();
}

Maybe<TestMaybe> bar(int i) {
	return i > 30 ? Maybe<TestMaybe>(new TestMaybe()) : Maybe<TestMaybe>();
}

int main() {

	Maybe<int> mb1 = foo(0);
	Maybe<int> mb2 = foo(42);

	assert(!mb1);
	assert(mb2);

	bool exception_thrown = false;

	try {
		*mb1;
	} catch (const std::runtime_error& e) {
		exception_thrown = true;
	}

	assert(exception_thrown);

	assert(*mb2 == 42);

	Maybe<TestMaybe> mb3 = bar(0);
	Maybe<TestMaybe> mb4 = bar(31);

	assert(!mb3);
	assert(mb4);

	exception_thrown = false;

	try {
		mb3->to_int();
	} catch (const std::runtime_error& e) {
		exception_thrown = true;
	}

	assert(exception_thrown);

	assert(mb4->to_int() == 42);

	return 0;

}

