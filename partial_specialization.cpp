#include <utils.h>

// Primary template
template <typename T>
class Array {
public:
	explicit Array(size_t size)
		: mData{new T[size]},
		  mSize{size} {
		for (size_t i = 0; i < size; i++) {
			mData[i] = T{};
		}

		PRI << "Primary: arr[" << size << "]: "
			<< mSize * sizeof(T);
	}

	~Array() {
		delete[] mData;
	}

	T& operator[](size_t i) {
		return mData[i];
	}

	void show() const;

private:
	T* mData;
	size_t mSize;
};

template <typename T>
void Array<T>::show() const {
	std::cout << "Elements: ";

	for (size_t i = 0; i < mSize; i++) {
		std::cout << mData[i] << " ";
	}

	std::cout << std::endl;
}

// Example 1
template <typename T, typename U>
struct is_same {
	static constexpr bool value = false;
};

template <typename T>
struct is_same<T, T> {
	static constexpr bool value = true;
};

static_assert(!is_same<double, int>::value, "");
static_assert(is_same<char, char>::value, "");

// Example 2
template <typename T, typename U
          //, bool = std::is_same<T, U>::value
          >
struct Pair {
    using FirstType = T;
    using SecondType = U;

    T first;
    U second;
};

/*template <typename T, typename U>
class Array<Pair<T, U, false>> {
public:
    Array(size_t size)
        : mFirstData{new T[size]},
          mSecondData{new U[size]},
          mSize{size} {
        PRI << "Partial specialization: arr["
            << size << "]: "
            << mSize * sizeof(T) << ", "
            << mSize * sizeof(U);
    }

    ~Array() {
        delete[] mSecondData;
        delete[] mFirstData;
    }

private:
    T* mFirstData;
    U* mSecondData;
    size_t mSize;
};*/

template <typename T>
void printSize() {
    PRI << "size: " << sizeof(T)
        << ", first " << sizeof(typename T::FirstType)
        << ", second " << sizeof(typename T::SecondType);
}

int main() {
    using SameTypePair = Pair<double, double>;
    using DiffTypePair = Pair<char, int>;

    printSize<SameTypePair>();
    printSize<DiffTypePair>();

    Array<SameTypePair> arr2{10};
    Array<DiffTypePair> arr1{10};

    return 0;
}
