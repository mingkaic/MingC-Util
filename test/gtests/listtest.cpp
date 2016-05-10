#include "../../structures/header/lists.hpp"
#include <algorithm>

// ------------ CHECK INITIAL STATES ----------------- //
TEST(INIT, deque)
	{
	list::deque<size_t> 	inst;
	list::deque<size_t>* 	ptr = new list::deque<size_t>();
	EXPECT_TRUE(inst.isEmpty());
	EXPECT_TRUE(ptr->isEmpty());
	delete ptr;
	}

TEST(INIT, dynamicarr)
	{
	list::dynamicarr<size_t> 	inst;
	list::dynamicarr<size_t>* 	ptr = new list::dynamicarr<size_t>();
	EXPECT_EQ(0, inst[0]);
	EXPECT_EQ(0, (*ptr)[0]);
	delete ptr;
	}

TEST(INIT, queue)
	{
	list::queue<size_t> 	inst;
	list::queue<size_t>* 	ptr = new list::queue<size_t>();
	EXPECT_TRUE(inst.isEmpty());
	EXPECT_TRUE(ptr->isEmpty());
	delete ptr;
	}

TEST(INIT, searchlist)
	{
	list::searchlist<size_t> 	inst;
	list::searchlist<size_t>* 	ptr = new list::searchlist<size_t>();
	EXPECT_EQ(0, inst.size());
	EXPECT_EQ(0, ptr->size());
	delete ptr;
	}

TEST(INIT, skiplist)
	{
	list::skiplist<size_t> 	inst;
	list::skiplist<size_t>* ptr = new list::skiplist<size_t>();
	EXPECT_TRUE(inst.isEmpty());
	EXPECT_TRUE(ptr->isEmpty());
	delete ptr;
	}

TEST(INIT, stack)
	{
	list::stack<size_t> 	inst;
	list::stack<size_t>* 	ptr = new list::stack<size_t>();
	EXPECT_TRUE(inst.isEmpty());
	EXPECT_TRUE(ptr->isEmpty());
	delete ptr;
	}

// ------------ DATA ENTRY ----------------- //
TEST(DATA_ENTRY, deque)
	{
	list::deque<double> 		back2back;
	list::deque<double> 		front2front;
	list::deque<double> 		front2back;
	list::deque<double> 		back2front;
	std::vector<double> store;

	for (double data = getNumData();
		data >= 0;
		data = getNumData()) 
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
	list::dynamicarr<double>  arr;
	list::dynamicarr<bool>	arr2;
	std::vector<double> store;
	bool verifier[101] = {false};
	size_t index = 0;
	size_t testindex;

	for (double data = getNumData();
		data >= 0;
		data = getNumData()) 
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
	list::queue<double> 		q;
	std::vector<double> store;

	for (double data = getNumData();
		data >= 0;
		data = getNumData()) 
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
	list::searchlist<double> 	list;
	std::vector<double> store;
	size_t index = 0;

	for (double data = getNumData();
		data >= 0;
		data = getNumData()) 
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
	list::skiplist<double> 	list;
	std::vector<double> store;

	for (double data = getNumData();
		data >= 0;
		data = getNumData()) 
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
	list::stack<double> 		s;
	std::vector<double> store;

	for (double data = getNumData();
		data >= 0;
		data = getNumData()) 
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

// ------------ COPY STRUCTURES ----------------- //
TEST(COPY, deque)
	{
	list::deque<double> 		empty;
	list::deque<double> 		emptycopy(empty);
	list::deque<double> 		emptycopyassign;
	emptycopyassign = empty;

	ASSERT_TRUE(empty.isEmpty());
	EXPECT_TRUE(emptycopy.isEmpty());
	EXPECT_TRUE(emptycopyassign.isEmpty());

	list::deque<double> 		orig;
	list::deque<double> 		copyassign;
	list::deque<double> 		recopyassign;
	std::vector<double> store;

	for (double data = getNumData();
		data >= 0;
		data = getNumData()) 
		{
		orig.push_back(data);
		recopyassign.push_front(data); // different data order
		store.push_back(data);
		}

	list::deque<double> 		copy(orig);
	copyassign = orig;
	recopyassign = orig;

	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		ASSERT_EQ(orig.peek_front(), *it);
		ASSERT_EQ(orig.pop_front(), *it);
		EXPECT_EQ(copy.peek_front(), *it);
		EXPECT_EQ(copy.pop_front(), *it);
		EXPECT_EQ(copyassign.peek_front(), *it);
		EXPECT_EQ(copyassign.pop_front(), *it);
		EXPECT_EQ(recopyassign.peek_front(), *it);
		EXPECT_EQ(recopyassign.pop_front(), *it);
		}

	ASSERT_TRUE(orig.isEmpty());
	EXPECT_TRUE(copy.isEmpty());
	EXPECT_TRUE(copyassign.isEmpty());
	EXPECT_TRUE(recopyassign.isEmpty());
	}

TEST(COPY, dynamicarr)
	{
	list::dynamicarr<double>  empty;
	list::dynamicarr<double>  emptycopy(empty);
	list::dynamicarr<double>  emptycopyassign;
	emptycopyassign = empty;

	ASSERT_EQ(empty[0], 0);
	EXPECT_EQ(emptycopy[0], 0);
	EXPECT_EQ(emptycopyassign[0], 0);

	list::dynamicarr<double> 		orig;
	list::dynamicarr<double> 		copyassign;
	list::dynamicarr<double> 		recopyassign;
	std::vector<double> store;
	size_t index = 0;

	for (double data = getNumData();
		data >= 0;
		data = getNumData()) 
		{
		orig[index] = data;
		recopyassign[index] = data;
		store.push_back(data);
		index++;
		}

	list::dynamicarr<double> 		copy(orig);
	copyassign = orig;
	recopyassign = orig;

	index = 0;
	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		ASSERT_EQ(orig[index], *it);
		EXPECT_EQ(copy[index], *it);
		EXPECT_EQ(copyassign[index], *it);
		EXPECT_EQ(recopyassign[index], *it);
		index++;
		}
	}

TEST(COPY, queue)
	{
	list::queue<double>  empty;
	list::queue<double>  emptycopy(empty);
	list::queue<double>  emptycopyassign;
	emptycopyassign = empty;

	ASSERT_TRUE(empty.isEmpty());
	EXPECT_TRUE(emptycopy.isEmpty());
	EXPECT_TRUE(emptycopyassign.isEmpty());

	list::queue<double> 		orig;
	list::queue<double> 		copyassign;
	list::queue<double> 		recopyassign;
	std::vector<double> store;

	for (double data = getNumData();
		data >= 0;
		data = getNumData()) 
		{
		orig.push_front(data);
		recopyassign.push_front(data);
		store.push_back(data);
		}

	list::queue<double> 		copy(orig);
	copyassign = orig;
	recopyassign = orig;
	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		ASSERT_EQ(orig.peek_back(), *it);
		EXPECT_EQ(copy.peek_back(), *it);
		EXPECT_EQ(copyassign.peek_back(), *it);
		EXPECT_EQ(recopyassign.peek_back(), *it);

		ASSERT_EQ(orig.pop_back(), *it);
		EXPECT_EQ(copy.pop_back(), *it);
		EXPECT_EQ(copyassign.pop_back(), *it);
		EXPECT_EQ(recopyassign.pop_back(), *it);
		}

	ASSERT_TRUE(orig.isEmpty());
	EXPECT_TRUE(copy.isEmpty());
	EXPECT_TRUE(copyassign.isEmpty());
	EXPECT_TRUE(recopyassign.isEmpty());
	}

TEST(COPY, searchlist)
	{
	list::searchlist<double>  empty;
	list::searchlist<double>  emptycopy(empty);
	list::searchlist<double>  emptycopyassign;
	emptycopyassign = empty;

	ASSERT_EQ(empty.size(), 0);
	EXPECT_EQ(emptycopy.size(), 0);
	EXPECT_EQ(emptycopyassign.size(), 0);

	list::searchlist<double> 	orig;
	list::searchlist<double> 		copyassign;
	list::searchlist<double> 		recopyassign;
	std::vector<double> store;
	size_t index = 0;

	for (double data = getNumData();
		data >= 0;
		data = getNumData()) 
		{
		orig.nInsert(data, index);
		recopyassign.nInsert(data, index);
		store.push_back(data);
		index++;
		}

	list::searchlist<double> 		copy(orig);
	copyassign = orig;
	recopyassign = orig;

	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		ASSERT_EQ(orig.nRemove(0), *it);
		EXPECT_EQ(copy.nRemove(0), *it);
		EXPECT_EQ(copyassign.nRemove(0), *it);
		EXPECT_EQ(recopyassign.nRemove(0), *it);
		}

	ASSERT_EQ(orig.size(), 0);
	EXPECT_EQ(copy.size(), 0);
	EXPECT_EQ(copyassign.size(), 0);
	EXPECT_EQ(recopyassign.size(), 0);
	}

TEST(COPY, skiplist)
	{
	list::skiplist<double>  empty;
	list::skiplist<double>  emptycopy(empty);
	list::skiplist<double>  emptycopyassign;
	emptycopyassign = empty;

	ASSERT_TRUE(empty.isEmpty());
	EXPECT_TRUE(emptycopy.isEmpty());
	EXPECT_TRUE(emptycopyassign.isEmpty());

	list::skiplist<double> 	orig;
	list::skiplist<double> 	copyassign;
	list::skiplist<double> 	recopyassign;
	std::vector<double> store;

	for (double data = getNumData();
		data >= 0;
		data = getNumData()) 
		{
		if (true == orig.insert(data))
			{
			recopyassign.insert(data);
			store.push_back(data);
			}
		}

	list::skiplist<double> 		copy(orig);
	copyassign = orig;
	recopyassign = orig;

	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		ASSERT_TRUE(orig.remove(*it));
		EXPECT_TRUE(copy.remove(*it));
		EXPECT_TRUE(copyassign.remove(*it));
		EXPECT_TRUE(recopyassign.remove(*it));
		}
	ASSERT_TRUE(orig.isEmpty());
	EXPECT_TRUE(copy.isEmpty());
	EXPECT_TRUE(copyassign.isEmpty());
	EXPECT_TRUE(recopyassign.isEmpty());
	}

TEST(COPY, stack)
	{
	list::stack<double>  empty;
	list::stack<double>  emptycopy(empty);
	list::stack<double>  emptycopyassign;
	emptycopyassign = empty;

	ASSERT_TRUE(empty.isEmpty());
	EXPECT_TRUE(emptycopy.isEmpty());
	EXPECT_TRUE(emptycopyassign.isEmpty());

	list::stack<double> 	orig;
	list::stack<double> 	copyassign;
	list::stack<double> 	recopyassign;
	std::vector<double> store;

	for (double data = getNumData();
		data >= 0;
		data = getNumData()) 
		{
		orig.push(data);
		recopyassign.push(data);
		store.push_back(data);
		}

	list::stack<double> 		copy(orig);
	copyassign = orig;
	recopyassign = orig;
	std::reverse(store.begin(), store.end());

	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		ASSERT_EQ(orig.peek(), *it);
		EXPECT_EQ(copy.peek(), *it);
		EXPECT_EQ(copyassign.peek(), *it);
		EXPECT_EQ(recopyassign.peek(), *it);

		ASSERT_EQ(orig.pop(), *it);
		EXPECT_EQ(copy.pop(), *it);
		EXPECT_EQ(copyassign.pop(), *it);
		EXPECT_EQ(recopyassign.pop(), *it);
		}

	ASSERT_TRUE(orig.isEmpty());
	EXPECT_TRUE(copy.isEmpty());
	EXPECT_TRUE(copyassign.isEmpty());
	EXPECT_TRUE(recopyassign.isEmpty());
	}

// ------------ SEARCH FUNCTIONS ----------------- //
TEST(SEARCH, dynamicarr)
	{
	list::dynamicarr<double> 	arr;
	std::vector<double> store;
	std::vector<double> uniques;
	size_t index = 0;

	for (double data = getNumData();
		data >= 0;
		data = getNumData()) 
		{
		arr[index] = data;
		store.push_back(data);
		index++;
		}

	index = 0;
	for (std::vector<double>::iterator it = store.begin(); 
		it != store.end(); 
		it++) 
		{
		if (uniques.end() == find(uniques.begin(), uniques.end(), *it)) 
			{
			EXPECT_EQ(arr.indexOf(*it), index);
			uniques.push_back(*it);
			}
		index++;
		}
	}

TEST(SEARCH, searchlist)
	{
	list::searchlist<double> 	list;
	std::vector<double> store;
	std::vector<double> antistore;
	std::vector<double> uniques;
	size_t index = 0;

	for (double data = getNumData();
		data >= 0; data = getNumData())
		{
		antistore.push_back(data);
		}

	for (double data = getNumData();
		data >= 0;
		data = getNumData()) 
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
	list::skiplist<double> 	list;
	std::vector<double> antistore;
	std::vector<double> store;

	for (double data = getNumData();
		data >= 0; data = getNumData())
		{
		antistore.push_back(data);
		}

	for (double data = getNumData();
		data >= 0;
		data = getNumData()) 
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