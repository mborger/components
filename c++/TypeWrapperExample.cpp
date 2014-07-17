#include <exception>
#include <iostream>
#include "TypeWrapper.hpp"

class DogId : public TypeWrapper<long>
{
    public:
    class InvalidDogId : public std::exception
    {
        const char* what() const
	#if __cplusplus > 199711L
		noexcept
	#else
		throw()
	#endif
        {
            return "Invalid DogId";
        }
    };

    DogId(const long id)
    {
        if( id % 2 != 0 ) {
            throw InvalidDogId();
        }
        value = id;
    }
};

#if __cplusplus > 199711L
namespace std {
    template<>
    class hash<DogId> : public hash<TypeWrapper<long>> {};
}
#endif

int main(int argc, char* argv[]) {
	TypeWrapper<long> tw(4);
	DogId di1(4);
	DogId di2(8);
	DogId di3(4);

	std::cerr << "tw  = " << tw << std::endl;
	std::cerr << "di1 = " << di1 << std::endl;
	std::cerr << "di2 = " << di2 << std::endl;
	std::cerr << "di3 = " << di3 << std::endl;

	std::cerr << std::boolalpha;
	std::cerr << "tw  == di1\t" << (tw == di1) << std::endl;
	std::cerr << "di1 == di2\t" << (di1 == di2) << std::endl;
	std::cerr << "di1 == di3\t" << (di1 == di3) << std::endl;

	std::cerr << "DogId(5) is invalid!" << std::endl;
	DogId di4(5);

	return 0;
}
