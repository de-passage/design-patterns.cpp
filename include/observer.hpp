#ifndef GUARD_OBSERVER_HPP__
#define GUARD_OBSERVER_HPP__

#include <list>
#include <functional>
#include <tuple>


namespace details {
	template<int I> struct placeholder {};
}

namespace std {
	template<int I>
		struct is_placeholder<::details::placeholder<I>> : std::integral_constant<int, I>{};
}

template<typename Signature>
struct Observable {

	typedef std::list<std::function<Signature>> ContainerType;
	typedef typename ContainerType::iterator ObserverID;

	template<class ...Args>
		void notify(Args&&...) const;

	template<class Observer>
		ObserverID attach(Observer&);

	template<class Observer>
		ObserverID attach(const Observer&);

	void detach(const ObserverID&);

	private:
	ContainerType observers;

};

namespace details {
	template<class Obs, class R, class ...Args>
		decltype(auto) build_function(R (std::remove_reference_t<Obs>::*f)(Args...), Obs&& o, const Observable<R(Args...)>*) {
			return [f, &o](Args&&... args) { return (o.*f)(std::forward<Args>(args)...); };
		}
}

template<class Signature>
template<class Observer>
typename Observable<Signature>::ObserverID Observable<Signature>::attach(const Observer& obs) {
	std::function<Signature> func(details::build_function(&Observer::update, obs, this));
	observers.push_front(func);
	return observers.front();
}

template<class Signature>
template<class Observer>
typename Observable<Signature>::ObserverID Observable<Signature>::attach(Observer& obs) {
	std::function<Signature> func(details::build_function(&Observer::update, obs, this));
	observers.push_front(func);
	return observers.begin();
}

template<class Signature>
void Observable<Signature>::detach(const ObserverID& id) {
	observers.erase(id);
}

template<class Signature>
template<class ...Args>
void Observable<Signature>::notify(Args&&... args) const {
	for(auto it = observers.begin(); it != observers.end(); ++it) {
		(*it)(std::forward<Args>(args)...);
	}
}
#endif// GUARD_OBSERVER_HPP__
