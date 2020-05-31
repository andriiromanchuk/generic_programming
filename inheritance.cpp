#include <utils.h>

// Example 1
struct NonCopyable {
    NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

template <typename T>
struct Shape {
    virtual ~Shape() = default;

    virtual void evaluate() = 0;

    T value;
};

template <typename T>
struct Circle : NonCopyable, Shape<T> {
    void evaluate() final {
        std::cout << "Circle evaluation\n";

        //value = 5; // error
        this->value = 5;
        Shape<T>::value = 5;
    }

    template <typename U>
    /*virtual*/ void dump() {}
};

// Example 2
struct Animal {
    virtual ~Animal() = default;

    virtual void smile() = 0;
};

struct Panda : public Animal {
    void smile() final {
        std::cout << "Panda is smiling\n";
    }
};

struct Pangolin : public Animal {
    void smile() final {
        std::cout << "Pangolin is smiling\n";
    }
};

template <typename T>
class SmartPointer {
public:
    SmartPointer() : SmartPointer{nullptr} {}

    explicit SmartPointer(T* p) : mPtr{p} {}

    T* operator->() {
        return mPtr;
    }

    operator bool() {
        return mPtr != nullptr;
    }

    /*template <typename U>
    operator SmartPointer<U>() {
        return SmartPointer<U>{mPtr};
    }*/

private:
    T* mPtr;
};

// Example 3
struct Widget
{};

struct Move {
    void operator()(Widget&) {
        std::cout << "\tmove\n";
    }
};

struct Update {
    void operator()(Widget&) {
        std::cout << "\tupdate\n";
    }
};

struct Draw {
    void operator()(Widget&) {
        std::cout << "\tdraw\n";
    }
};

template <typename... Ts>
class Sequence : public Ts... {
public:
    void operator()(Widget& w) {
        call<Ts...>(w);

        std::cout << std::endl;
    }

private:
    template <typename T, typename U, typename... Us>
    void call(Widget& w) {
        call<T>(w);
        call<U, Us...>(w);
    }

    template <typename T>
    void call(Widget& w) {
        T::operator()(w);
    }
};

int main() {
    constexpr size_t ArrSize = 3;

    // Instantiation inheritance
    Circle<int>* derived = new Circle<int>{};
    Shape<int>* base = derived;

    base->evaluate();

    // Relation between instantiated classes
    SmartPointer<Animal> animals[ArrSize]{};

    SmartPointer<Animal> animal{new Panda{}};
    SmartPointer<Panda> panda{new Panda{}};
    SmartPointer<Pangolin> pangolin{new Pangolin{}};

    animals[0] = animal;
    //animals[1] = panda;
    //animals[2] = pangolin;

    for (SmartPointer<Animal>& ptr : animals) {
        if (ptr) {
            ptr->smile();
        }
    }

    Widget arr[ArrSize]{};

    using moveUpdateOp = Sequence<Move, Update>;
    using MoveUpdateDrawOp = Sequence<Move, Update, Draw>;
    using moveUpdateThenMoveUpdateDrawOp = Sequence<moveUpdateOp, MoveUpdateDrawOp>;

    using Op = moveUpdateThenMoveUpdateDrawOp;
    Op opSequence{};

    for (size_t i = 0; i < ArrSize; i++) {
        std::cout << "#" << i << ":\n";
        opSequence(arr[i]);
    }

    return 0;
}
