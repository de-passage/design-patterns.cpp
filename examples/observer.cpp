#include "observer.hpp"

#include <cassert>

struct Observer {
	int value1 = 0;
	int value2 = 0;

	void update(int, int);
};

void Observer::update(int i1, int i2) {
	value1 = i1;
	value2 = i2;
}

struct ObservableTest : Observable<void(int, int)> {
	void do_something(int i, int j) {
		notify(i, j);
	}
};

struct Observer2 {
	int value;
	void update(int, int);
	void update(int);
};

void Observer2::update(int i, int j) {
	value = i + j; 
}

void Observer2::update(int i) {
	value = i;
}

int main() {

	ObservableTest observable;

	Observer o1, o2;
	Observer2 o3;

	auto i1 = observable.attach(o1);
	observable.attach(o2);
	observable.attach(o3);

	observable.do_something(24, 42);

	assert(o1.value1 == 24);
	assert(o1.value2 == 42);
	assert(o2.value1 == 24);
	assert(o2.value2 == 42);
	assert(o3.value == 66);

	observable.detach(i1);

	observable.do_something(66, 44);

	assert(o1.value1 == 24);
	assert(o1.value2 == 42);
	assert(o2.value1 == 66);
	assert(o2.value2 == 44);
	assert(o3.value == 110);

	return 0;
}
