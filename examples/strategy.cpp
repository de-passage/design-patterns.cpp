#include "strategy.hpp"

#include <cassert>

struct StrategyTest : Strategy<int(int)> {
	int do_something(int i) {
		return strategy(i);
	}
};

int main() {
	StrategyTest st;

	st.set_strategy( [](int i) { return i; } );
	assert(st.do_something(42) == 42);

	st.set_strategy( [](int i) { return i * 2; } );
	assert(st.do_something(42) == 84);

	st.set_strategy( [](int i) { return i + 1; } );
	assert(st.do_something(42) == 43);
	return 0;
}

