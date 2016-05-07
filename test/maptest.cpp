#include "../structures/header/maps.hpp"

TEST(INIT, hashheap)
	{
	hashheap<size_t> 	inst;
	hashheap<size_t>* 	ptr = new hashheap<size_t>();
	EXPECT_EQ(inst.numInserted(), 0);
	EXPECT_EQ(ptr->numInserted(), 0);
	delete ptr;
	}

TEST(INIT, hashtable)
	{
	hashtable<size_t> 	inst;
	hashtable<size_t>* 	ptr = new hashtable<size_t>();
	EXPECT_EQ(inst.numInserted(), 0);
	EXPECT_EQ(ptr->numInserted(), 0);
	delete ptr;
	}

TEST(DATA_ENTRY, hashheap)
	{
	
	}

TEST(DATA_ENTRY, hashtable)
	{
	
	}

TEST(SEARCH, hashheap)
	{
	
	}

TEST(SEARCH, hashtable)
	{
	
	}