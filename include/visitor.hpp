#ifndef GUARD_VISITOR_HPP__
#define GUARD_VISITOR_HPP__

#include <utility>

template<class Base>
struct Visitable {

  template<class Visitor>
    void visit(const Visitor&);

  template<class Visitor>
    void visit(const Visitor&) const;

  template<class Visitor>
    void visit(Visitor&&);

  template<class Visitor>
    void visit(Visitor&&) const;
};

template<class Visitor>
struct VisitorFunctor {
  constexpr VisitorFunctor(Visitor& visitor);
  template<class T, class...Args>
    void operator()(T&&, Args&&...);

  template<class T, class...Args>
    void operator()(T&&, Args&&...) const;

  template<class T>
    void operator()(T&&);

  template<class T>
    void operator()(T&&) const;

  Visitor& visitor;
};


template<class Base>
template<class Visitor>
void Visitable<Base>::visit(const Visitor& visitor) {
  static_cast<Base*>(this)->accept(VisitorFunctor<const Visitor>(visitor));
}

template<class Base>
template<class Visitor>
void Visitable<Base>::visit(const Visitor& visitor) const {
  static_cast<const Base*>(this)->accept(VisitorFunctor<const Visitor>(visitor));
}


template<class Base>
template<class Visitor>
void Visitable<Base>::visit(Visitor&& visitor) {
  static_cast<Base*>(this)->accept(VisitorFunctor<Visitor>(std::forward<Visitor>(visitor)));
}

template<class Base>
template<class Visitor>
void Visitable<Base>::visit(Visitor&& visitor) const {
  static_cast<const Base*>(this)->accept(VisitorFunctor<Visitor>(visitor));
}
template<class Visitor>
constexpr VisitorFunctor<Visitor>::VisitorFunctor(Visitor& visitor) : visitor(visitor) {}

template<class Visitor>
template<class T, class ...Args>
void VisitorFunctor<Visitor>::operator()(T&& t, Args&&... args) {
  visitor(t);
  operator()(args...);
}

template<class Visitor>
template<class T, class ...Args>
void VisitorFunctor<Visitor>::operator()(T&& t, Args&&... args) const {
  visitor(t);
  operator()(args...);
}


template<class Visitor>
template<class T>
void VisitorFunctor<Visitor>::operator()(T&& t) {
  visitor(t);
}

template<class Visitor>
template<class T>
void VisitorFunctor<Visitor>::operator()(T&& t) const {
  visitor(t);
}
#endif// GUARD_VISITOR_HPP__
