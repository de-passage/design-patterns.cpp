#include "abstract_factory.hpp"
#include <cassert>

struct AbstractFactoryTest {
	int value;
	virtual void do_something(int) = 0;
	AbstractFactoryTest();
	virtual ~AbstractFactoryTest() = default;
};

AbstractFactoryTest::AbstractFactoryTest() : value(0) {}

struct ABTChild1 : AbstractFactoryTest {
	void do_something(int i) override;
};

void ABTChild1::do_something(int i) {
	value = i;
}

struct ABTChild2 : AbstractFactoryTest {
	void do_something(int i) override;
};

void ABTChild2::do_something(int i) {
	value = i * 2;
}

int main() {

	auto builder = make_abstract_factory<AbstractFactoryTest, ABTChild1, ABTChild2>([](bool b) { return b ? 1 : 0; });
	AbstractFactoryTest* t1 = builder(true);
	AbstractFactoryTest* t2 = builder(false);
	t1->do_something(42);
	t2->do_something(42);

	assert(t1->value == 84);
	assert(t2->value == 42);

	delete t2;
	delete t1;

	return 0;

}

