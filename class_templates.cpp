#include <utils.h>

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

struct Book {
	std::string title = "Alphabet";
	int price = 7;
};

/*std::ostream& operator<<(std::ostream& os, const Book& obj) {
	return os << obj.title << " " << obj.price << "|";
}*/

int main() {
    // Template instantiation point 1
    Array<int> ints{4};

    ints[3] = 9;

    PRI << "ints size in bytes: " << sizeof(ints);

    ints.show();

    // Template instantiation point 2
    Array<Book> books{2};

    // unused member-functions are not instantiated
    //books.show();

    return 0;
}
