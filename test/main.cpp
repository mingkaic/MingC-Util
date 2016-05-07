#include "../structures/header/trees.hpp"
#include <gtest/gtest.h>
#include <cstdlib>
#include "readtest.cpp"
#include "listtest.cpp"
//#include "maptest.cpp"
//#include "sptest.cpp"

int main(int argc, char* argv[]) 
	{
	srand(0); // repeatable
	setenv("PYTHONPATH",".",1);
	readdir();
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	}