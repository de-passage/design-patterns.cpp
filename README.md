# Design patterns

A collection of common design patterns in C++. Rather than using arbitrary examples I tried to take advantage of the generic programming capability of C++ to implement context-free classes. However this also means that I had to take some liberties with the design.

## Strategy

The Strategy pattern answers to the need to extract an algoritm from a class, allowing both the class and the algorithm to change independently and to replace the algoritm as needed by the program. For example a class implementing a sort() function can benefit from the Strategy pattern since it allows it to change the actual sort algorithm depending on the needs of the user.  
In C++11, implementing the Strategy pattern is trivial as std::function provides all the needed functionalities.

## Abstract factory

The Abstract Factory pattern is an interface to instanciate classes inheriting from a common ancestor without the need to specify the actual class to use. This allows the creation of objects with different behaviors based on runtime information.  
The implementation provided here is completely independant from the target hierarchy. The user creates an AbstractFactory by calling the make_abstract_factory function together with the base type of which the returned pointers will be, the different subclasses that can be instanciated and a function or functor as the only non template parameter. This function will be used to decide which class is actually instanciated when the factory is called. It is expected to return the index (starting from 0) of the class to instanciate in the list of subclasses the abstract factory has been created with.

Note that in this case the target class can only be instanciated through a constructor without arguments, but the class could easily be extended to accept arbitrary constructors.

## Visitor

The Visitor pattern is a solution to the problem of applying new algorithms to an existing structure, without modifying it. It is usually implemented by creating a hierarchy of visitor classes inheriting from a common interface defining the various overloads of a visit() function. Each subclass then implements the various algorithms that the represent.  
In C++ however, templates make the use of inheritance completely unnecessary. A visitor can be defined as any functor or function providing an overload for each of the types the visited class contains. This visited class can then trivially be implemented as follow (non constant variations omitted for brevity):
```c++
struct Visited {
	template<typename Visitor>
	void visit(const Visitor& visitor) const {
		visitor(member1);
		visitor(member2);
		...
	}

	private:
		int member1;
		std::string member2;
		...
};
```
The implementation we propose is thus simply a convenience class that can be inherited to transforms a single-parameter visitor function into a variadic function applying the original visitor to each of its arguments (unrelated note: the implementation is actually a variation of the Template Method pattern). 

## Observer

The observer pattern, also called publish/subscribe is a common solution to the problem of notifying external objects of an internal state change. The classic implementation uses two hierarchies, one of observable objects, implementing an interface to attach observers, and the observers implementing an update() function processing the data sent by the observed object. However this approach itself inflexible to the extent that it requires the observers to inherit from an arbitrary interface. This disqualifies a wide number of objects, notably standard library ones, and forces the user to write wrappers around them to be able to make them observers.  
Consider an hypothetic array of data recording the state of an object as it changes. In the C++ STL, std::vector doesn't inherit from any Observer hierarchy and cannot be used as is in the classic Observer implementation, we would then need to create a new class containing a reference to our vector when in this case the only operation we actualy need to do is a `my_vector.push_back(data)`.  
For additional flexibility it is therefore reasonable to consider any function with an appropriate signature to be an observer. We then only need to store a list of std::functions and call them with the data when needed. In the previous example all we need is then to write a lambda or call std::bind to create a function with the desired signature and behavior. (in the present implementation we also allow objects with an update() member function to be given as is. The Observable::attach() function converts them automatically to the desired std::function)
