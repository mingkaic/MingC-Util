#include "../structures/header/lists.hpp"
#include <algorithm>

TEST(INIT, deque)
	{
	deque<size_t> 	inst;
	deque<size_t>* 	ptr = new deque<size_t>();
	EXPECT_TRUE(inst.isEmpty());
	EXPECT_TRUE(ptr->isEmpty());
	delete ptr;
	}

TEST(INIT, dynamicarr)
	{
	dynamicarr<size_t> 		inst;
	dynamicarr<size_t>* 	ptr = new dynamicarr<size_t>();
	EXPECT_EQ(0, inst[0]);
	EXPECT_EQ(0, (*ptr)[0]);
	delete ptr;
	}

TEST(INIT, queue)
	{
	queue<size_t> 	inst;
	queue<size_t>* 	ptr = new queue<size_t>();
	EXPECT_TRUE(inst.isEmpty());
	EXPECT_TRUE(ptr->isEmpty());
	delete ptr;
	}

TEST(INIT, searchlist)
	{
	searchlist<size_t> 		inst;
	searchlist<size_t>* 	ptr = new searchlist<size_t>();
	EXPECT_EQ(0, inst.size());
	EXPECT_EQ(0, ptr->size());
	delete ptr;
	}

TEST(INIT, skiplist)
	{
	skiplist<size_t> 	inst;
	skiplist<size_t>* 	ptr = new skiplist<size_t>();
	EXPECT_TRUE(inst.isEmpty());
	EXPECT_TRUE(ptr->isEmpty());
	delete ptr;
	}

TEST(INIT, stack)
	{
	stack<size_t> 	inst;
	stack<size_t>* 	ptr = new stack<size_t>();
	EXPECT_TRUE(inst.isEmpty());
	EXPECT_TRUE(ptr->isEmpty());
	delete ptr;
	}

// data entry
TEST(DATA_ENTRY, deque)
	{
	deque<double> 		back2back;
	deque<double> 		front2front;
	deque<double> 		front2back;
	deque<double> 		back2front;
	std::vector<double> store;

	for (double data = getTestData();
		data >= 0;
		data = getTestData()) 
		{
		back2back.push_back(data);
		front2front.push_front(data);
		front2back.push_front(data);
		back2front.push_back(data);
		store.push_back(data);
		}

	double f2bpeek, f2bpop, b2fpeek, b2fpop;
	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		f2bpeek = front2back.peek_back();
		EXPECT_EQ(f2bpeek, *it);
		f2bpop = front2back.pop_back();
		EXPECT_EQ(f2bpop, *it);
		b2fpeek = back2front.peek_front();
		EXPECT_EQ(b2fpeek, *it);
		b2fpop = back2front.pop_front();
		EXPECT_EQ(b2fpop, *it);
		}

	double b2bpeek, b2bpop, f2fpeek, f2fpop;
	std::reverse(store.begin(), store.end());
	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		b2bpeek = back2back.peek_back();
		EXPECT_EQ(b2bpeek, *it);
		b2bpop = back2back.pop_back();
		EXPECT_EQ(b2bpop, *it);
		f2fpeek = front2front.peek_front();
		EXPECT_EQ(f2fpeek, *it);
		f2fpop = front2front.pop_front();
		EXPECT_EQ(f2fpop, *it);
		}

	EXPECT_TRUE(front2back.isEmpty());
	EXPECT_TRUE(back2front.isEmpty());
	}

TEST(DATA_ENTRY, dynamicarr)
	{
	dynamicarr<double>  arr;
	dynamicarr<bool>	arr2;
	std::vector<double> store;
	bool verifier[101] = {false};
	size_t index = 0;
	size_t testindex;

	for (double data = getTestData();
		data >= 0;
		data = getTestData()) 
		{
		arr[index++] = data;
		testindex = ((size_t) data) % 101;
		arr2[testindex] = true;
		verifier[testindex] = true;
		store.push_back(data);
		}
	index = 0;
	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		EXPECT_EQ(arr[index++], *it);
		}
	for (size_t i = 0; i < 101; i++) 
		{
		if (verifier[i])
			EXPECT_TRUE(arr2[i]);
		else
			EXPECT_FALSE(arr2[i]);
		}
	}

TEST(DATA_ENTRY, queue)
	{
	queue<double> 		q;
	std::vector<double> store;

	for (double data = getTestData();
		data >= 0;
		data = getTestData()) 
		{
		q.push_front(data);
		store.push_back(data);
		}

	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		EXPECT_EQ(q.peek_back(), *it);
		EXPECT_EQ(q.pop_back(), *it);
		}

	EXPECT_TRUE(q.isEmpty());
	}

TEST(DATA_ENTRY, searchlist)
	{
	searchlist<double> 	list;
	std::vector<double> store;
	size_t index = 0;

	for (double data = getTestData();
		data >= 0;
		data = getTestData()) 
		{
		list.nInsert(data, index++);
		store.push_back(data);
		}

	size_t chosen = rand() % list.size();
	double elem = rand();
	double old = list.nPeek(chosen);
	EXPECT_EQ(old, list.nReplace(elem, chosen));
	replace(store.begin()+chosen, store.end()+chosen+1, old, elem);

	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		EXPECT_EQ(list.nRemove(0), *it);
		}

	EXPECT_EQ(0, list.size());
	}

TEST(DATA_ENTRY, skiplist)
	{
	skiplist<double> 	list;
	std::vector<double> store;

	for (double data = getTestData();
		data >= 0;
		data = getTestData()) 
		{
		if (true == list.insert(data))
			{
			store.push_back(data);
			//std::cout << list;
			}
		}

	// tests Sortedness
	double last = -1;
	size_t end = list.size();
	double value;
	for (size_t i = 0; i < end; i++)
		{
		value = list[i];
		EXPECT_GT(value, last);
		last = value;
		}

	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		//std::cout << *it << ">>> \n";
		EXPECT_TRUE(list.remove(*it));
		//std::cout << list;
		}

	EXPECT_TRUE(list.isEmpty());
	}

TEST(DATA_ENTRY, stack)
	{
	stack<double> 		s;
	std::vector<double> store;

	for (double data = getTestData();
		data >= 0;
		data = getTestData()) 
		{
		s.push(data);
		store.push_back(data);
		}
	std::reverse(store.begin(), store.end());
	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		EXPECT_EQ(s.peek(), *it);
		EXPECT_EQ(s.pop(), *it);
		}

	EXPECT_TRUE(s.isEmpty());
	}

TEST(SEARCH, searchlist)
	{
	searchlist<double> 	list;
	std::vector<double> store;
	std::vector<double> antistore;
	std::vector<double> uniques;
	size_t index = 0;

	for (double data = getTestData();
		data >= 0; data = getTestData())
		{
		antistore.push_back(data);
		}

	for (double data = getTestData();
		data >= 0;
		data = getTestData()) 
		{
		std::vector<double>::iterator it = find(antistore.begin(), antistore.end(), data);
		if (it != antistore.end())
			{
			antistore.erase(it);
			}
		list.nInsert(data, index++);
		store.push_back(data);
		}

	index = 0;
	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		if (uniques.end() == find(uniques.begin(), uniques.end(), *it)) 
			{
			EXPECT_EQ(list.search(*it), index);
			uniques.push_back(*it);
			}
		EXPECT_EQ(list.nPeek(index++), *it);
		}

	std::random_shuffle(store.begin(), store.end());

	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		EXPECT_GE(list.search(*it), 0);
		}

	for (std::vector<double>::iterator it = antistore.begin(); 
		it != antistore.end(); 
		it++) 
		{
		EXPECT_LT(list.search(*it), 0);
		}
	}

TEST(SEARCH, skiplist)
	{
	skiplist<double> 	list;
	std::vector<double> antistore;
	std::vector<double> store;

	for (double data = getTestData();
		data >= 0; data = getTestData())
		{
		antistore.push_back(data);
		}

	for (double data = getTestData();
		data >= 0;
		data = getTestData()) 
		{
		std::vector<double>::iterator it = find(antistore.begin(), antistore.end(), data);
		if (it != antistore.end())
			{
			antistore.erase(it);
			}
		if (true == list.insert(data))
			{
			store.push_back(data);
			}
		}
	
	std::random_shuffle(store.begin(), store.end());

	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		EXPECT_TRUE(list.search(*it));
		}

	for (std::vector<double>::iterator it = antistore.begin(); 
		it != antistore.end(); 
		it++) 
		{
		EXPECT_FALSE(list.search(*it));
		}
	}