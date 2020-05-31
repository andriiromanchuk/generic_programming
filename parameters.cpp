#include <utils.h>

#include <array>

template <typename T, size_t Size>
class Array {
public:
	Array() {
		for (size_t i = 0; i < Size; i++) {
			mData[i] = T{};
		}
	}

	T& operator[](size_t i) {
		return mData[i];
	}

	constexpr size_t size() const {
		return Size;
	}

	void show() const;

private:
	T mData[Size];
};

template <typename T, size_t Size>
void Array<T, Size>::show() const {
	std::cout << "Elements: ";

	for (size_t i = 0; i < Size; i++) {
		std::cout << mData[i] << " ";
	}

	std::cout << std::endl;
}

template <size_t Amount = 8,
          typename T = std::string,
          template <typename, size_t> class Cont = Array>
struct SubjectList {
    Cont<T, Amount> mTable;
};

int main() {
    Array<int, 16> ints;

    PRI << ints.size();

    ints[7] = 3;

    ints.show();

    SubjectList list;
    SubjectList<12> list_1;
    SubjectList<16, int> list_2;
    SubjectList<20, int, std::array> list_3;

    static_cast<void>(list);
    static_cast<void>(list_1);
    static_cast<void>(list_2);
    static_cast<void>(list_3);

    return 0;
}
