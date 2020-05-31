#include <utils.h>

#include <array>

template <size_t V>
struct Fact {
    static constexpr size_t value = V * Fact<V - 1>::value;
};

template <>
struct Fact<0> {
    static constexpr size_t value = 1;
};

// Functor policies
template <typename T>
struct Mult {
    constexpr auto operator()(const T& a, const T& b) const {
        return a * b;
    }

    static constexpr T initial_value = 1;
};

template <typename T>
struct Add {
    constexpr auto operator()(const T& a, const T& b) const {
        return a + b;
    }

    static constexpr T initial_value = 0;
};

// C++17
template <template <typename> class Policy, typename T, size_t Size>
constexpr T accumulate(const std::array<T, Size>& arr) {
    Policy<T> policy;
    auto res = Policy<T>::initial_value;

    for (const T& x : arr) {
        res = policy(res, x);
    }

    return res;
}

static_assert(accumulate<Mult>(std::array<int, 4>{1, 2, 3, 4}) == 24, "");
static_assert(accumulate<Add>(std::array<int, 4>{1, 2, 3, 4}) == 10, "");

int main() {
    PRI << "fact(0): " << Fact<0>::value;
    PRI << "fact(1): " << Fact<1>::value;
    PRI << "fact(2): " << Fact<2>::value;
    PRI << "fact(3): " << Fact<3>::value;
    PRI << "fact(4): " << Fact<4>::value;

    return 0;
}
