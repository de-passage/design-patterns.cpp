#ifndef GUARD_STRATEGY_HPP__
#define GUARD_STRATEGY_HPP__

#include <functional>
#include <type_traits>


template<typename Signature>
struct Strategy {

  void set_strategy(const std::function<Signature>&);
  bool has_strategy() const;

  protected:
    std::function<Signature> strategy;


};

template<typename Signature>
void Strategy<Signature>::set_strategy(const std::function<Signature>& f) {
  strategy = f;
}
template<typename Signature>
bool Strategy<Signature>::has_strategy() const {
  return strategy;
}

#endif // GUARD_STRATEGY_HPP__
