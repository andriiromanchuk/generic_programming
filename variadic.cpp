#include <utils.h>

// Example 1
template <typename T, typename U>
auto sum(T a, U b) {
    return a + b;
}

template <typename T, typename U, typename... Ts>
auto sum(T a, U b, Ts... vs) {
    return sum(sum(a, b), vs...);
}

// Example 2
struct Book {
    Book() = default;

    Book(const std::string& title) : title{title}
    {}

    Book(double wearout, int price)
        : wearout{wearout}, price{price}
    {}

    std::string title = "default";
    double wearout = 0.;
    int price = 0;
};

std::ostream& operator<<(std::ostream& os, const Book& obj) {
    return os << obj.title << " " << obj.wearout << " " << obj.price << "|";
}

template <typename T>
class Container {
public:
    Container(size_t cap)
        : mData{new T[cap]},
          mSize{0},
          mCapacity{cap}
    {}

    ~Container() {
        delete[] mData;
    }

    template <typename... Ts>
    void emplace(Ts&&... vs) {
        if (mSize >= mCapacity) {
            throw std::logic_error{"Container is already filled!"};
        }

        PRI << "Using " << sizeof... (vs) << "-argument(s) constructor";

        mData[mSize++] = T{std::forward<Ts>(vs)...};
    }

    T& operator[](size_t ix) {
        return mData[ix];
    }

    size_t size() const {
        return mSize;
    }

private:
    T* mData;
    size_t mSize;
    size_t mCapacity;
};

int main() {
    PRI << sum(1, 2.2);
    PRI << sum(1, 2LL, 3.3f, 4.4, 5L);

    Container<Book> cont{3};

    cont.emplace();
    cont.emplace("philips");
    cont.emplace(4.4, 5);

    try {
        cont.emplace();
    } catch (std::exception& e) {
        PRI << "Caught exception: " << e.what();
    }

    for (size_t i = 0; i < cont.size(); i++) {
        PRI << cont[i];
    }

    return 0;
}
