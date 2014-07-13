#pragma once
#include <typeinfo>
#include <ostream>

/**
 * @brief A class to give meaning to common data types.
 *
 * Often data types are shared for multiple purposes such as using longs
 * to represent ids for an object model. It can get confusing to be passing
 * around longs that might not represent an id for the model you're working with.
 * You can create a new type ModelId which extends a TypeWrapper<long> to
 * have more type safety over working with primitives.
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
	TypeWrapper(const T& t) :
		value(t)
	{}

	const T& getValue() const
	{
		return value;
	}

	/**
	 * The typeid is checked to prevent two differnet subclasses
	 * of the same templated TypeWrapper from being considered equivalent.
	 * For example if Foo is a TypeWrapper<int> and Bar is a TypeWrapper<int>,
	 * you probably don't want them to be equivalent even if the stored integer
	 * value is the same.
	 */
	virtual bool operator==(const TypeWrapper& rhs) const
	{
		return (typeid(*this)==typeid(rhs)) && (this->value==rhs.value);
	}

	friend std::ostream& operator<<(std::ostream &out, const TypeWrapper<T> &tw)
	{
		out << tw.value;
		return out;
	}

protected:
	T value;

	/**
	 * @brief Default constructor for validation
	 *
	 * This protected constructor exists so that a derived class may perform
	 * validation on the given value before initializing the stored
	 * value which may be a costly copy.
	 */
	TypeWrapper() {}
};

namespace std {

/**
 * @brief Standard hash function
 *
 * This hash function delegates to the standard
 * hash function of the wrapped type. I made it a class
 * instead of a struct so that derived classes of TypeWrapper
 * can just do the following:
 *
 * @code
 * namespace std {
 * 	template<>
 * 	class hash<Foo> : public hash<TypeWrapper<type>> {};
 * }
 * @endcode
 */
template<typename T>
class hash<TypeWrapper<T>> {
	public:
	std::size_t operator()(const TypeWrapper<T>& t) const
	{
		return std::hash<T>()(t.getValue());
	}
};

} //namespace std
