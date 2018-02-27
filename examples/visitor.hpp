#include "visitor.hpp"

#include <string>
#include <cassert>

struct VisitorExample : Visitable<VisitorExample> {

	template<class Visitor>
	void accept(const Visitor& visitor) {
		visitor(42, "Hello World!");
	}

};


struct Visitor {

	int count;

	void operator()(int i) {
		assert(i == 42);
		count++;
	}

	void operator()(const std::string& s) {
		assert(s == "Hello World!");
		count++;
	}

};

struct Visitor2 {
	std::string string;
	int integer;

	void operator()(int i) {
		integer = i;
	}

	void operator()(const std::string& str) {
		string = str;
	}
};

int main() {
	Visitor visitor{0};
	Visitor2 visitor2;

	VisitorExample visitable;

	visitable.visit(visitor);
	visitable.visit(visitor2);

	assert(visitor.count == 2);
	assert(visitor2.string == "Hello World!");
	assert(visitor2.integer == 42);

    return 0;
}

