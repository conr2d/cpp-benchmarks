#include "catch2/catch_all.hpp"
#include "te.hpp"
#include <iostream>
#include <variant>

// direct call
struct Direct {
  int _value = 0;
  int value() const {
    return _value;
  }
  void add() {
    _value += 1;
  }
};

// virtual function
struct Virtual {
  virtual ~Virtual() = default;
  virtual int value() const = 0;
  virtual void add() = 0;
};

struct VirtualImpl : public Virtual {
  int _value = 0;
  int value() const override {
    return _value;
  }
  void add() override {
    _value += 1;
  }
};

// type erasure
namespace te = boost::te;
struct TypeErased : public te::poly<TypeErased> {
  int value() const {
    return te::call<int>([](const auto& self) { return self.value(); }, *this);
  }
  void add() {
    te::call([](auto& self) { self.add(); }, *this);
  }
};

// variant + visit
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct VariantImpl {
  int _value = 0;
  int value() const {
    return _value;
  }
  void add() {
    _value += 1;
  }
};

struct Variant {
  std::variant<Direct, VariantImpl> _data = VariantImpl{};
  int value() const {
    return std::visit(overloaded{
      [](const auto& self) { return self.value(); },
    }, _data);
  }
  void add() {
    return std::visit(overloaded{
      [](auto& self) { self.add(); },
    }, _data);
  }
};

// CRTP
template<typename Derived>
struct CRTPBase {
  int value() const {
    return static_cast<Derived*>(this)->value();
  }
  void add() {
    static_cast<Derived*>(this)->add();
  }
};

struct CRTP : public CRTPBase<CRTP> {
  int _value = 0;
  int value() const {
    return _value;
  }
  void add() {
    _value += 1;
  }
};

constexpr auto iterations = 100000;

TEST_CASE("function call", "[test]") {
  BENCHMARK("direct call") {
    Direct v;
    for (int i = 0; i < iterations; ++i) {
      v.add();
    }
    return v.value();
  };

  BENCHMARK("virtual function") {
    Virtual* v = new VirtualImpl();
    for (int i = 0; i < iterations; ++i) {
      v->add();
    }
    return v->value();
  };

#if defined(__clang__) || defined(NDEBUG)
  BENCHMARK("type erasure") {
    TypeErased v = {Direct()};
    for (int i = 0; i < iterations; ++i) {
      v.add();
    }
    return v.value();
  };
#endif

  BENCHMARK("variant + visit") {
    Variant v{};
    for (int i = 0; i < iterations; ++i) {
      v.add();
    }
    return v.value();
  };

  BENCHMARK("CRTP") {
    CRTP v{};
    for (int i = 0; i < iterations; ++i) {
      v.add();
    }
    return v.value();
  };
}
