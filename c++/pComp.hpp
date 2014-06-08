#pragma once
#include <functional>

/**
 * @brief Pointer comparator
 *
 * This is a comparator function that works with containers of pointers.
 * It wraps any of the standard comparators and applies their comparison
 * logic to dereferenced objects.
 *
 * @tparam Type
 * 		The object to compare.
 * @tparam Compare
 * 		The non-pointer comparator to use.
 * 		Defaults to std::less.
 */
template<typename Type, typename Compare = std::less<Type> >
struct pComp : public std::binary_function<Type *, Type *, bool> {
    bool operator()(const Type *x, const Type *y) const
        { return Compare()(*x, *y); }
};
