#pragma once
#include <iostream>



namespace State
{
	struct super {
		super(std::string mes) {
			std::cout << mes << "\n";
		}
	};

	struct sub{
		inline static const std::string message{ "TESTING " };

		auto some_function_name(int x, int y, int z) -> int;
	};



}

void performState()
{
	using namespace State;
	sub s;

	std::cout << s.some_function_name(5,4,3);
}