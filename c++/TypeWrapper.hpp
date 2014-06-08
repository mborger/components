#pragma once
#include <typeinfo>

/**
 * @brief A class to give meaning to common data types.
 *
 * Often data types are shared for multiple purposes such as using longs
 * to represent ids for an object model. It can get confusing to be passing
 * around longs that might not represent an id for the model you're working with.
 * The constructor can also be overriden to provide some validation.
 * The stored value is designed to be immutable.
 */
template<typename T>
class TypeWrapper
{
public:
	/**
	 * @brief Value initializing constructor
	 */
	TypeWrapper(const T& t) : value(t) {}

	const T& getValue() const { return value; }

	/**
	 * The typeid is checked to prevent two differnet subclasses
	 * of the same templated TypeWrapper from being considered equivalent.
	 * For example if Foo is a TypeWrapper<int> and Bar is a TypeWrapper<int>,
	 * you probably don't want them to be equivalent even if the stored integer
	 * value is the same.
	 */
	virtual bool operator==(const TypeWrapper& rhs) const {
		return (typeid(*this)==typeid(rhs)) && (this->value==rhs.value);
	}

protected:
	T value;

	/**
	 * @brief Default constructor for validation
	 *
	 * This protected constructor exists so that a subclass may perform
	 * validation on the given value before initializing the stored
	 * value which may be an expensive copy.
	 */
	TypeWrapper() {}
};
