#include "../../structures/header/trees.hpp"
#include <algorithm>

TEST(INIT, bstree)
	{
	tree::bstree<size_t> 	inst;
	tree::bstree<size_t>* 	ptr = new tree::bstree<size_t>();
	EXPECT_TRUE(inst.isEmpty());
	EXPECT_TRUE(ptr->isEmpty());
	EXPECT_EQ(inst.size(), 0);
	EXPECT_EQ(ptr->size(), 0);
	delete ptr;
	}

TEST(INIT, heap)
	{
	tree::heap<size_t> 	inst;
	tree::heap<size_t>* 	ptr = new tree::heap<size_t>();
	EXPECT_TRUE(inst.isEmpty());
	EXPECT_TRUE(ptr->isEmpty());
	delete ptr;
	}

TEST(INIT, rbtree)
	{
	tree::rbtree<size_t> 	inst;
	tree::rbtree<size_t>* 	ptr = new tree::rbtree<size_t>();
	EXPECT_TRUE(inst.isEmpty());
	EXPECT_TRUE(ptr->isEmpty());
	EXPECT_EQ(inst.size(), 0);
	EXPECT_EQ(ptr->size(), 0);
	delete ptr;
	}

TEST(INIT, treap)
	{
	tree::treap<size_t> 	inst;
	tree::treap<size_t>* 	ptr = new tree::treap<size_t>();
	EXPECT_TRUE(inst.isEmpty());
	EXPECT_TRUE(ptr->isEmpty());
	EXPECT_EQ(inst.size(), 0);
	EXPECT_EQ(ptr->size(), 0);
	delete ptr;
	}

TEST(ENTER_SEARCH, bstree)
	{
	tree::bstree<double> 	tr;
	std::vector<double> set;

	for (double value = getNumData();
		value > -1;
		value = getNumData())
		{
		tr.put(value);
		set.push_back(value);
		}
	for (std::vector<double>::iterator it = set.begin();
		it != set.end();
		it++)
		{
		EXPECT_TRUE(tr.get(*it));
		}
	for (std::vector<double>::iterator it = set.begin();
		it != set.end();
		it++)
		{
		EXPECT_TRUE(tr.remove(*it));
		}
	EXPECT_TRUE(tr.isEmpty());
	EXPECT_EQ(tr.size(), 0);
	}

TEST(ENTER_SEARCH, heap)
	{
	tree::heap<double> 	tr;
	tree::heap<double> 	tr2;
	std::vector<double> set;

	for (double value = getNumData();
		value > -1;
		value = getNumData())
		{
		tr.put(value);
		tr2.put(value);
		set.push_back(value);
		}
	for (std::vector<double>::iterator it = set.begin();
		it != set.end();
		it++)
		{
		bool found = tr.get(*it);
		EXPECT_TRUE(found);
		found = tr.remove(*it);
		EXPECT_TRUE(found);
		}
	EXPECT_TRUE(tr.isEmpty());
	
	std::sort(set.begin(), set.end());
	for (std::vector<double>::iterator it = set.begin();
		it != set.end();
		it++)
		{
		double value = tr2.get();
		EXPECT_EQ(value, *it);
		value = tr2.remove();
		EXPECT_EQ(value, *it);
		}
	EXPECT_TRUE(tr2.isEmpty());
	}

TEST(ENTER_SEARCH, rbtree)
	{
	tree::rbtree<double> 	tr;
	std::vector<double> set;

	for (double value = getNumData();
		value > -1;
		value = getNumData())
		{
		tr.put(value);
		set.push_back(value);
		}
	for (std::vector<double>::iterator it = set.begin();
		it != set.end();
		it++)
		{
		EXPECT_TRUE(tr.get(*it));
		}
	for (std::vector<double>::iterator it = set.begin();
		it != set.end();
		it++)
		{
		EXPECT_TRUE(tr.remove(*it));
		}
	EXPECT_TRUE(tr.isEmpty());
	EXPECT_EQ(tr.size(), 0);
	}

TEST(ENTER_SEARCH, treap)
	{
	tree::treap<double> 	tr;
	std::vector<double> set;
	for (double value = getNumData();
		value > -1;
		value = getNumData())
		{
		tr.put(value);
		set.push_back(value);
		}
	for (std::vector<double>::iterator it = set.begin();
		it != set.end();
		it++)
		{
		EXPECT_TRUE(tr.get(*it));
		}
	for (std::vector<double>::iterator it = set.begin();
		it != set.end();
		it++)
		{
		EXPECT_TRUE(tr.remove(*it));
		}
	EXPECT_TRUE(tr.isEmpty());
	EXPECT_EQ(tr.size(), 0);
	}

TEST(COPY, bstree)
	{
	tree::bstree<double> empty;
	tree::bstree<double> emptycopy(empty);
	tree::bstree<double> emptycopyassign;
	emptycopyassign = empty;

	ASSERT_TRUE(empty.isEmpty());
	EXPECT_TRUE(emptycopy.isEmpty());
	EXPECT_TRUE(emptycopyassign.isEmpty());

	tree::bstree<double> orig;
	tree::bstree<double> copyassign;
	tree::bstree<double> recopyassign;
	
	std::vector<double> set;

	for (double value = getNumData();
		value > -1;
		value = getNumData()) 
		{
		orig.put(value);
		set.push_back(value);
		}

	tree::bstree<double> copy(orig);
	copyassign = orig;
	recopyassign = orig;

	for (std::vector<double>::iterator it = set.begin();
		it != set.end();
		it++)
		{
		EXPECT_TRUE(orig.remove(*it));
		EXPECT_TRUE(copy.remove(*it));
		EXPECT_TRUE(copyassign.remove(*it));
		EXPECT_TRUE(recopyassign.remove(*it));
		}

	EXPECT_TRUE(orig.isEmpty());
	EXPECT_TRUE(copy.isEmpty());
	EXPECT_TRUE(copyassign.isEmpty());
	EXPECT_TRUE(recopyassign.isEmpty());
	}

TEST(COPY, heap)
	{
	tree::heap<double> empty;
	tree::heap<double> emptycopy(empty);
	tree::heap<double> emptycopyassign;
	emptycopyassign = empty;

	ASSERT_TRUE(empty.isEmpty());
	EXPECT_TRUE(emptycopy.isEmpty());
	EXPECT_TRUE(emptycopyassign.isEmpty());

	tree::heap<double> orig;
	tree::heap<double> copyassign;
	tree::heap<double> recopyassign;
	
	std::vector<double> set;

	for (double value = getNumData();
		value > -1;
		value = getNumData()) 
		{
		orig.put(value);
		set.push_back(value);
		}

	tree::heap<double> copy(orig);
	copyassign = orig;
	recopyassign = orig;

	for (std::vector<double>::iterator it = set.begin();
		it != set.end();
		it++)
		{
		EXPECT_TRUE(orig.remove(*it));
		EXPECT_TRUE(copy.remove(*it));
		EXPECT_TRUE(copyassign.remove(*it));
		EXPECT_TRUE(recopyassign.remove(*it));
		}

	EXPECT_TRUE(orig.isEmpty());
	EXPECT_TRUE(copy.isEmpty());
	EXPECT_TRUE(copyassign.isEmpty());
	EXPECT_TRUE(recopyassign.isEmpty());
	}

TEST(COPY, rbtree)
	{
	tree::rbtree<double> empty;
	tree::rbtree<double> emptycopy(empty);
	tree::rbtree<double> emptycopyassign;
	emptycopyassign = empty;

	ASSERT_TRUE(empty.isEmpty());
	EXPECT_TRUE(emptycopy.isEmpty());
	EXPECT_TRUE(emptycopyassign.isEmpty());

	tree::rbtree<double> orig;
	tree::rbtree<double> copyassign;
	tree::rbtree<double> recopyassign;
	
	std::vector<double> set;

	for (double value = getNumData();
		value > -1;
		value = getNumData()) 
		{
		orig.put(value);
		set.push_back(value);
		}

	tree::rbtree<double> copy(orig);
	copyassign = orig;
	recopyassign = orig;

	for (std::vector<double>::iterator it = set.begin();
		it != set.end();
		it++)
		{
		EXPECT_TRUE(orig.remove(*it));
		EXPECT_TRUE(copy.remove(*it));
		EXPECT_TRUE(copyassign.remove(*it));
		EXPECT_TRUE(recopyassign.remove(*it));
		}

	EXPECT_TRUE(orig.isEmpty());
	EXPECT_TRUE(copy.isEmpty());
	EXPECT_TRUE(copyassign.isEmpty());
	EXPECT_TRUE(recopyassign.isEmpty());
	}

TEST(COPY, treap)
	{
	tree::treap<double> empty;
	tree::treap<double> emptycopy(empty);
	tree::treap<double> emptycopyassign;
	emptycopyassign = empty;

	ASSERT_TRUE(empty.isEmpty());
	EXPECT_TRUE(emptycopy.isEmpty());
	EXPECT_TRUE(emptycopyassign.isEmpty());

	tree::treap<double> orig;
	tree::treap<double> copyassign;
	tree::treap<double> recopyassign;
	
	std::vector<double> set;

	for (double value = getNumData();
		value > -1;
		value = getNumData()) 
		{
		orig.put(value);
		set.push_back(value);
		}

	tree::treap<double> copy(orig);
	copyassign = orig;
	recopyassign = orig;

	for (std::vector<double>::iterator it = set.begin();
		it != set.end();
		it++)
		{
		EXPECT_TRUE(orig.remove(*it));
		EXPECT_TRUE(copy.remove(*it));
		EXPECT_TRUE(copyassign.remove(*it));
		EXPECT_TRUE(recopyassign.remove(*it));
		}

	EXPECT_TRUE(orig.isEmpty());
	EXPECT_TRUE(copy.isEmpty());
	EXPECT_TRUE(copyassign.isEmpty());
	EXPECT_TRUE(recopyassign.isEmpty());
	}

TEST(SPECIAL, bstree)
	{
	tree::bstree<double> 	tr;
	std::vector<double> 	set;

	for (double value = getNumData();
		value > -1;
		value = getNumData())
		{
		tr.put(value);
		set.push_back(value);
		}
	std::vector<double> v = tr.getList();
	size_t s = tr.size();
	EXPECT_EQ(s, set.size());
	std::sort(set.begin(), set.end());
	for (size_t i = 0; i < s; i++)
		{
		EXPECT_EQ(v[i], set[i]);
		}
	}