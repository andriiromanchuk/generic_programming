#include <utils.h>

#include <array>
#include <cassert>

static constexpr bool Counting = false;

template <typename T>
struct is_expr_or_array {
    static constexpr bool value = false;
};

template <typename F, typename T, typename U>
class Expr {
public:
    Expr(F f, const T& a, const U& b)
        : func{f}, a{a}, b{b} {
        if constexpr (Counting) {
            PRI << "Expr constr";
        }
    }

    ~Expr() {
        if constexpr (Counting) {
            PRI << "Expr destr";
        }
    }

    auto operator[](size_t i) const {
        //return func(a[i], a[i]);
        return func(subscript(a, i), subscript(b, i));
    }

private:
    template <typename V>
    auto subscript(const V& arg, size_t i) const {
        if constexpr (is_expr_or_array<V>::value) {
            return arg[i];
        } else {
            static_cast<void>(i);

            return arg;
        }
    }

    F func;

    const T& a;
    const U& b;
};

// Functors
struct Mult {
    template <typename T, typename U>
    auto operator()(const T& a, const U& b) const {
        return a * b;
    }
};

struct Add {
    template <typename T, typename U>
    auto operator()(const T& a, const U& b) const {
        return a + b;
    }
};

// Overloaded operators
template <typename T, typename U>
auto operator*(const T& a, const U& b) {
    return Expr{Mult{}, a, b};
}

template <typename T, typename U>
auto operator+(const T& a, const U& b) {
    return Expr{Add{}, a, b};
}

template <typename T>
class Array {
public:
    Array(size_t size)
        : mData{new T[size]},
          mSize{size} {
        if constexpr (Counting) {
            Counter++;
            PRI << "Array constr: " << Counter;
        }
    }

    ~Array() {
        if constexpr (Counting) {
            PRI << "Array destr: " << Counter;
            Counter--;
        }

        delete[] mData;
    }

    template <typename U>
    Array& operator=(const U& other) {
        for (size_t i = 0; i < size(); i++) {
            mData[i] = other[i];
        }

        return *this;
    }

    size_t size() const {
        return mSize;
    }

    T& operator[](size_t i) {
        return mData[i];
    }

    const T& operator[](size_t i) const {
        return mData[i];
    }

private:
    T* mData;
    size_t mSize;

    inline static size_t Counter;
};

template <typename... Ts>
struct is_expr_or_array<Expr<Ts...>> {
    static constexpr bool value = true;
};

template <typename T>
struct is_expr_or_array<Array<T>> {
    static constexpr bool value = true;
};

static_assert (!is_expr_or_array<double>::value, "");
static_assert (is_expr_or_array<Expr<Mult, double, Array<double>>>::value, "");
static_assert (is_expr_or_array<Array<double>>::value, "");

template <typename T>
void initialize(T& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = i;
    }
}

template <typename T>
void print(const T& arr) {
    std::cout << "arr:";

    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << " " << arr[i];
    }

    std::cout << std::endl;
}

static constexpr size_t option = 0;

int main() {
    constexpr size_t ArrSize = 10;

    constexpr double k = 2.;
    Array<double> x{ArrSize};
    Array<double> y{ArrSize};

    assert(x.size() == y.size());

    initialize(x);
    initialize(y);

    if constexpr (option == 0) {
        x = k * x + x * y;
    } else {
        Expr<Mult, double, Array<double>> tmp1  = k * x;
        Expr<Mult, Array<double>, Array<double>> tmp2 = x * y;
        Expr<Add,
             Expr<Mult, double, Array<double>>,
             Expr<Mult, Array<double>, Array<double>>
            > tmp3 = std::move(tmp1) + std::move(tmp2);

        x = std::move(tmp3);
    }

    print(x);

    return 0;
}
