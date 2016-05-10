#include <gtest/gtest.h>
#include <cstdlib>
#include "readtest.cpp"
#include "gtests/sptest.cpp"
#include "gtests/listtest.cpp"
#include "gtests/maptest.cpp"
#include "gtests/treetest.cpp"

int main(int argc, char* argv[]) 
	{
	#ifdef SPTEST
		SP_RTInit();
	#endif
	srand(0); // repeatable
	setenv("PYTHONPATH",".",1);
	pthread_t t1; 
	pthread_t t2;
	readdir(t1, t2);
	testing::InitGoogleTest(&argc, argv);
	int err = RUN_ALL_TESTS();

    char* a;
    char* b;
	pthread_join(t1, (void**) &a);
	pthread_join(t2, (void**) &b);
	return err;
	}