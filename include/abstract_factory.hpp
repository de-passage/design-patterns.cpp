#ifndef GUARD_ABSTRACT_FACTORY_HPP__
#define GUARD_ABSTRACT_FACTORY_HPP__

#include <utility>
#include <stdexcept>

template<class Functor, class AbstractBase, class ...ConcreteClasses>
struct AbstractFactory {
	constexpr AbstractFactory(Functor);

	template<class ...Args>
	AbstractBase* operator()(Args&&...);

	private:
	template<class...Args>
	struct tuple {};
	Functor _func;

	template<class Current, class ...Args>
	inline AbstractBase* _instanciate(std::size_t, tuple<Current, Args...>);
	inline AbstractBase* _instanciate(std::size_t, tuple<>);
};

template<class Functor, class AbstractBase, class ...ConcreteClasses>
constexpr AbstractFactory<Functor, AbstractBase, ConcreteClasses...>::AbstractFactory(Functor f) : _func(f) { }

template<class Functor, class AbstractBase, class...ConcreteClasses>
template<class ...Args>
AbstractBase* AbstractFactory<Functor, AbstractBase, ConcreteClasses...>::operator()(Args&&... args) {
	return _instanciate(_func(std::forward<Args>(args)...), tuple<ConcreteClasses...>());
}

template<class Functor, class AbstractBase, class...ConcreteClasses>
template<class Current, class ...Args>
inline AbstractBase* AbstractFactory<Functor, AbstractBase, ConcreteClasses...>::_instanciate(std::size_t i, tuple<Current, Args...>) {
	return i == 0 ? new Current : _instanciate(i - 1, tuple<Args...>());
}

template<class Functor, class AbstractBase, class...ConcreteClasses>
inline AbstractBase* AbstractFactory<Functor, AbstractBase, ConcreteClasses...>::_instanciate(std::size_t, tuple<>) {
	throw std::out_of_range("Out of range exception: AbstractFactory() expects an integer strictly less than the number of concrete classes provided");
}

template<class...Args, class Functor>
AbstractFactory<Functor, Args...> make_abstract_factory(Functor f) {
	return AbstractFactory<Functor, Args...>(f);
}

#endif // GUARD_ABSTRACT_FACTORY_HPP__
