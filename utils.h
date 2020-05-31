#ifndef UTILS_H
#define UTILS_H

#include <iostream>

#define LOG \
    std::cout << __LINE__ << "|" << __PRETTY_FUNCTION__ << "|"; \
    detail::Endler{}()

#define PRI \
    detail::Endler{}()

namespace detail {
struct Endler {
    ~Endler() {
        std::cout << std::endl;
    }

    std::ostream& operator()() {
        return std::cout;
    }
};
}

#endif // UTILS_H
