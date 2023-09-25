#include <iostream>
#include "mixr/base/String.hpp"

int main()
{
	const auto str = new mixr::base::String("Hello worlld\n");
	
	std::cout << str->getString();

	str->setStr("Goodbye world\n");

	std::cout << str->getString();

	str->unref();

	return 0;
}