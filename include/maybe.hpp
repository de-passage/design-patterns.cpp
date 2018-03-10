#ifndef GUARD_MAYBE_HPP__
#define GUARD_MAYBE_HPP__

#include <utility>

#include <stdexcept>

template<class Type>
struct Maybe {
	// Constructs an empty object (no value)
	constexpr Maybe();

	// Construct an object based on the argument
	Maybe(const Type&);
	Maybe(Type&&);

	// Take ownership of the given pointer
	constexpr Maybe(Type*);

	// Copy ctor
	Maybe(Maybe&&);
	Maybe(const Maybe&);

	// Dtor
	~Maybe();

	//Assignment operator
	Maybe& operator=(const Maybe&);
	Maybe& operator=(Maybe&&);

	// Return true if a value is present, false otherwise
	constexpr operator bool() const;

	// Access the contained value. Throw std::runtime_error if there is no value
	Type& operator*();
	const Type& operator*() const;
	Type* operator->();
	const Type* operator->() const;

	private:
	Type* _pointer;

	void _check_validity() const;
};

template<class Type>
constexpr Maybe<Type>::Maybe() : _pointer(nullptr) {}

template<class Type>
Maybe<Type>::Maybe(const Type& obj) : _pointer(new Type(obj)) {}

template<class Type>
Maybe<Type>::Maybe(Type&& obj) : _pointer(new Type(std::forward<Type>(obj))) {}

template<class Type>
constexpr Maybe<Type>::Maybe(Type* p) : _pointer(p) {}

template<class Type>
Maybe<Type>::Maybe(const Maybe& obj) : _pointer(obj ? new Type(*obj) : nullptr) {}

template<class Type>
Maybe<Type>::Maybe(Maybe&& obj) : _pointer(nullptr) {
	std::swap(_pointer, obj._pointer);
}

template<class Type>
Maybe<Type>::~Maybe() {
	if(_pointer) delete _pointer;
}

template<class Type>
constexpr Maybe<Type>::operator bool() const {
	return _pointer;
}

template<class Type>
Type& Maybe<Type>::operator*() {
	_check_validity();
	return *_pointer;
}

template<class Type>
Maybe<Type>& Maybe<Type>::operator=(const Maybe& mb) {
	if(_pointer) delete _pointer;
	_pointer = mb ? new Type(*mb) : nullptr;
	return *this;
}

template<class Type>
Maybe<Type>& Maybe<Type>::operator=(Maybe&& mb) {
	std::swap(_pointer, mb._pointer);
	return *this;
}

template<class Type>
const Type& Maybe<Type>::operator*() const {
	return const_cast<Maybe<Type>*>(this)->operator*();
}

template<class Type>
Type* Maybe<Type>::operator->() {
	_check_validity();
	return _pointer;
}

template<class Type>
const Type* Maybe<Type>::operator->() const {
	return const_cast<Maybe<Type>*>(this)->operator->();
}

template<class Type>
void Maybe<Type>::_check_validity() const {
	if(!_pointer)
		throw std::runtime_error("Maybe: trying to access a non-existent value");
}



#endif// GUARD_MAYBE_HPP__
