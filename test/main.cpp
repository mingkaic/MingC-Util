#include "../structures/header/maps.hpp"
#include "../structures/header/trees.hpp"
#include <gtest/gtest.h>
#include "readtest.cpp"
#include "listtest.cpp"
#include <cstdlib>

int main(int argc, char* argv[]) 
	{
	srand(0); // repeatable
	setenv("PYTHONPATH",".",1);
	readdir();
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	}