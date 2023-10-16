#pragma once
#include <iostream>

#ifdef DEBUG_MODE
	#define Log(x) std::cout << x << std::endl;
#else
	#define Log(x)
#endif