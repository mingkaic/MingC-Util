#include "../../structures/header/maps.hpp"
#include <string>

TEST(INIT, hashheap)
	{
	map::hashheap<std::string, size_t> 	inst;
	map::hashheap<std::string, size_t>* ptr = new map::hashheap<std::string, size_t>();
	EXPECT_TRUE(inst.isEmpty());
	EXPECT_TRUE(ptr->isEmpty());
	delete ptr;
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
	map::hashheap<std::string, double> table;

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
	map::hashheap<std::string, double> empty;
	map::hashheap<std::string, double> emptycopy(empty);
	map::hashheap<std::string, double> emptycopyassign;
	emptycopyassign = empty;

	ASSERT_TRUE(empty.isEmpty());
	EXPECT_TRUE(emptycopy.isEmpty());
	EXPECT_TRUE(emptycopyassign.isEmpty());

	map::hashheap<std::string, double> orig;
	map::hashheap<std::string, double> copyassign;
	map::hashheap<std::string, double> recopyassign;

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
	map::hashheap<std::string, double> copy(orig);
	copyassign = orig;
	recopyassign = orig;

	for (size_t i = 0; i < min; i++)
		{
		dcontain::wrapper<double> w1 = orig.remove(keyset[i]);
		dcontain::wrapper<double> w2 = copy.remove(keyset[i]);
		dcontain::wrapper<double> w3 = copyassign.remove(keyset[i]);
		dcontain::wrapper<double> w4 = recopyassign.remove(keyset[i]);
		EXPECT_EQ((double) w1, valueset[i]);
		EXPECT_TRUE((bool) w1);
		EXPECT_EQ((double) w2, valueset[i]);
		EXPECT_TRUE((bool) w2);
		EXPECT_EQ((double) w3, valueset[i]);
		EXPECT_TRUE((bool) w3);
		EXPECT_EQ((double) w4, valueset[i]);
		EXPECT_TRUE((bool) w4);
		}
	EXPECT_TRUE(orig.isEmpty());
	EXPECT_TRUE(copy.isEmpty());
	EXPECT_TRUE(copyassign.isEmpty());
	EXPECT_TRUE(recopyassign.isEmpty());
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
		EXPECT_EQ((double) w1, valueset[i]);
		EXPECT_TRUE((bool) w1);
		EXPECT_EQ((double) w2, valueset[i]);
		EXPECT_TRUE((bool) w2);
		EXPECT_EQ((double) w3, valueset[i]);
		EXPECT_TRUE((bool) w3);
		EXPECT_EQ((double) w4, valueset[i]);
		EXPECT_TRUE((bool) w4);
		}
	EXPECT_TRUE(orig.isEmpty());
	EXPECT_TRUE(copy.isEmpty());
	EXPECT_TRUE(copyassign.isEmpty());
	EXPECT_TRUE(recopyassign.isEmpty());
	}

TEST(SPECIAL, hashheap)
	{
	map::hashheap<size_t, double> theap;

	std::vector<size_t> numkeyset;
	std::vector<double> valueset;
	for (size_t key = getNumData();
		key > -1;
		key = getNumData()) 
		{
		numkeyset.push_back(key);
		}

	for (double value = getNumData();
		value >= 0;
		value = getNumData()) 
		{
		valueset.push_back(value);
		}

	size_t min = numkeyset.size();
	if (min > valueset.size())
		{
		min = valueset.size();
		}

	for (size_t i = 0; i < min; i++)
		{
		theap.put(numkeyset[i], valueset[i]);
		}

	std::sort(numkeyset.begin(), numkeyset.end());
	for (std::vector<size_t>::iterator it = numkeyset.begin(); 
		it != numkeyset.end(); 
		it++) 
		{
		map::pairptr<size_t, double> pv = theap.get();
		EXPECT_EQ(pv->getKey(), *it);
		pv = theap.remove();
		EXPECT_EQ(pv->getKey(), *it);
		}
	EXPECT_TRUE(theap.isEmpty());
	}