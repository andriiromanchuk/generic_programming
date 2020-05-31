#include <utils.h>

#include <iostream>
#include <cassert>
#include <cstddef>

static constexpr bool Counting = false;

template <typename T>
class Array {
public:
	explicit Array(size_t size)
		: mData{new T[size]},
		  mSize{size} {
		for (size_t i = 0; i < size; i++) {
			mData[i] = T{};
		}

		if constexpr (Counting) {
			Counter++;
			PRI << "constr: " << Counter;
		}
	}

	Array(const Array& other)
		: mData{new T[other.size()]},
		  mSize{other.size()} {
		copy(other);

		if constexpr (Counting) {
			Counter++;
			PRI << "copy constr: " << Counter;
		}
	}

	~Array() {
		if constexpr (Counting) {
			PRI << "destr: " << Counter;
			Counter--;
		}

		delete[] mData;
	}

	Array& operator=(const Array& other) {
		if (this != &other) {
			copy(other);
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

	// Computed assignments
	Array& operator+=(const Array<T>& other) {
		for (size_t i = 0; i< size(); i++) {
			mData[i] += other.mData[i];
		}

		return *this;
	}

	Array& operator*=(const Array<T>& other) {
		for (size_t i = 0; i< size(); i++) {
			mData[i] *= other.mData[i];
		}

		return *this;
	}

	Array& operator*=(const T& s) {
		for (size_t i = 0; i< size(); i++) {
			mData[i] *= s;
		}

		return *this;
	}

protected:
	void copy(const Array<T>& other) {
		for (size_t i = 0; i < size(); i++) {
			mData[i] = other.mData[i];
		}
	}

private:
	T* mData;
	size_t mSize;

	inline static size_t Counter;
};

template <typename T>
Array<T> operator+(const Array<T>& a, const Array<T>& b) {
	Array<T> result{a.size()};

	for (size_t i = 0; i < a.size(); i++) {
		result[i] = a[i] + b[i];
	}

	return result;
}

template <typename T>
Array<T> operator*(const Array<T>& a, const Array<T>& b) {
	Array<T> result{a.size()};

	for (size_t i = 0; i < a.size(); i++) {
		result[i] = a[i] * b[i];
	}

	return result;
}

template <typename T>
Array<T> operator*(const Array<T>& a, const T& s) {
	Array<T> result{a.size()};

	for (size_t i = 0; i < a.size(); i++) {
		result[i] = a[i] * s;
	}

	return result;
}

template <typename T>
Array<T> operator*(const T& s, const Array<T>& a) {
	return a * s;
}

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
        // Ideal
        for (size_t i = 0; i < ArrSize; i++) {
            x[i] = k * x[i] + x[i] * y[i];
        }
    } else if constexpr (option == 1) {
        x = k * x + x * y;
    } else if constexpr (option == 2) {
        Array<double> tmp1 = k * x;
        Array<double> tmp2 = x * y;
        Array<double> tmp3 = std::move(tmp1) + std::move(tmp2);

        x = std::move(tmp3);
    } else if constexpr(option == 3) {
        Array<double> tmp{x};

        x *= k;
        tmp *= y;
        x += tmp;
    }

    print(x);

    return 0;
}
