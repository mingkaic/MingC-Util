#include "../../structures/header/maps.hpp"
#include <string>

TEST(INIT, hashheap)
	{/*
	hashheap<size_t> 	inst;
	hashheap<size_t>* 	ptr = new hashheap<size_t>();
	EXPECT_EQ(inst.numInserted(), 0);
	EXPECT_EQ(ptr->numInserted(), 0);
	delete ptr;*/
	}

TEST(INIT, hashmap)
	{
	map::hashmap<std::string, size_t> 	inst;
	map::hashmap<std::string, size_t>* 	ptr = new map::hashmap<std::string, size_t>();
	EXPECT_TRUE(inst.isEmpty());
	EXPECT_TRUE(ptr->isEmpty());
	delete ptr;
	}

// ------------ DATA ENTRY ----------------- //
TEST(ENTER_SEARCH, hashheap)
	{
	
	}

TEST(ENTER_SEARCH, hashmap)
	{
	map::hashmap<std::string, double> table;

	std::vector<std::string> keyset;
	std::vector<std::string> extraset;
	std::vector<double> valueset;

	for (std::string key = getStrData();
		key.size() > 0;
		key = getStrData()) 
		{
		extraset.push_back(key);
		}

	for (std::string key = getStrData();
		key.size() > 0;
		key = getStrData()) 
		{
		std::vector<std::string>::iterator it = find(extraset.begin(), extraset.end(), key);
		if (extraset.end() != it) 
			{
			extraset.erase(it);
			}
		keyset.push_back(key);
		}

	for (double value = getNumData();
		value >= 0;
		value = getNumData()) 
		{
		valueset.push_back(value);
		}

	size_t min = keyset.size();
	if (min > valueset.size())
		{
		min = valueset.size();
		}

	for (size_t i = 0; i < min; i++)
		{
		table.put(keyset[i], valueset[i]);
		}

	for (size_t i = 0; i < min; i++)
		{
		double value = table.get(keyset[i]);
		EXPECT_EQ(value, valueset[i]);
		}

	for (std::vector<std::string>::iterator it = extraset.begin(); 
		it != extraset.end(); 
		it++) 
		{
		bool value = table.get(*it);
		EXPECT_FALSE(value);
		}

	for (std::vector<std::string>::iterator it = extraset.begin(); 
		it != extraset.end(); 
		it++) 
		{
		bool value = table.remove(*it);
		EXPECT_FALSE(value);
		}

	for (size_t i = 0; i < min; i++)
		{
		dcontain::wrapper<double> w = table.remove(keyset[i]);
		double value = w;
		bool good = w;
		EXPECT_EQ(value, valueset[i]);
		EXPECT_TRUE(good);
		}
	EXPECT_TRUE(table.isEmpty());
	}

// ------------ COPY STRUCTURES ----------------- //
TEST(COPY, hashheap)
	{
	}

TEST(COPY, hashmap)
	{
	map::hashmap<std::string, double> empty;
	map::hashmap<std::string, double> emptycopy(empty);
	map::hashmap<std::string, double> emptycopyassign;
	emptycopyassign = empty;

	ASSERT_TRUE(empty.isEmpty());
	EXPECT_TRUE(emptycopy.isEmpty());
	EXPECT_TRUE(emptycopyassign.isEmpty());

	map::hashmap<std::string, double> orig;
	map::hashmap<std::string, double> copyassign;
	map::hashmap<std::string, double> recopyassign;

	std::vector<std::string> keyset;
	std::vector<double> valueset;
	for (std::string key = getStrData();
		key.size() > 0;
		key = getStrData()) 
		{
		keyset.push_back(key);
		}

	for (double value = getNumData();
		value >= 0;
		value = getNumData()) 
		{
		valueset.push_back(value);
		}

	size_t min = keyset.size();
	if (min > valueset.size())
		{
		min = valueset.size();
		}

	for (size_t i = 0; i < min; i++)
		{
		orig.put(keyset[i], valueset[i]);
		}
	map::hashmap<std::string, double> copy(orig);
	copyassign = orig;
	recopyassign = orig;

	for (size_t i = 0; i < min; i++)
		{
		dcontain::wrapper<double> w1 = orig.remove(keyset[i]);
		dcontain::wrapper<double> w2 = copy.remove(keyset[i]);
		dcontain::wrapper<double> w3 = copyassign.remove(keyset[i]);
		dcontain::wrapper<double> w4 = recopyassign.remove(keyset[i]);
		double value = w1;
		bool good = w1;
		EXPECT_EQ(value, valueset[i]);
		EXPECT_TRUE(good);
		value = w2;
		good = w2;
		EXPECT_EQ(value, valueset[i]);
		EXPECT_TRUE(good);
		value = w3;
		good = w3;
		EXPECT_EQ(value, valueset[i]);
		EXPECT_TRUE(good);
		value = w4;
		good = w4;
		EXPECT_EQ(value, valueset[i]);
		EXPECT_TRUE(good);
		}
	EXPECT_TRUE(orig.isEmpty());
	EXPECT_TRUE(copy.isEmpty());
	EXPECT_TRUE(copyassign.isEmpty());
	EXPECT_TRUE(recopyassign.isEmpty());
	}