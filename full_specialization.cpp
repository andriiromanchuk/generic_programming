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

// Full specialization
template <>
class Array<char> {
public:
	Array(const std::string& s) : mString{s} {
		//LOG;
	}

	char& operator[](size_t i) {
		return mString[i];
	}

	operator std::string() const {
		return mString;
	}

private:
	std::string mString;
};

Array<char> operator+(const Array<char>& a, const Array<char>& b) {
	return std::string{a} + std::string{b};
}

struct Book {
	std::string title = "Alphabet";
	int price = 7;
};

std::ostream& operator<<(std::ostream& os, const Book& obj) {
	return os << obj.title << " " << obj.price << "|";
}

// Member-function specialization
template <>
void Array<Book*>::show() const {
	std::cout << "Elements: ";

	for (size_t i = 0; i < mSize; i++) {
		std::cout << *mData[i] << " ";
	}

	std::cout << std::endl;
}

int main() {
    // Example 1
    Array<char> chars{"Boom"};

    PRI << "chars: " << std::string{chars};

    Array<char> concatenation = chars + std::string{"!!!"};

    PRI << std::string{concatenation};

    //chars.show();

    // Example 2
    Book x{"LOTR", 9}, y{"Hunt", 8};
    Array<Book*> pointers{2};

    pointers[0] = &x;
    pointers[1] = &y;

    pointers.show();

    return 0;
}

