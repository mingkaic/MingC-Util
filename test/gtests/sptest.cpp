#include "../../structures/header/lists.hpp"
#include "../../utils/memory.hpp"

class tclass;

static list::skiplist<tclass*>* allocs = NULL;
static const size_t obvious_password = 1234567890;

class tclass
	{
	public:
		tclass()
			{
			allocs->insert(this);
			}
		~tclass()
			{
			allocs->remove(this);
			}
		size_t testFunction()
			{
			return obvious_password;
			}
	};

bool tpointerEq(tclass* ptr1, tclass* ptr2)
	{
	return ptr2 == ptr1;
	}

signed tpointerCmp(tclass* ptr1, tclass* ptr2)
	{
	return ptr2 - ptr1;
	}

#ifndef SPTEST
#define SPTEST

void SP_RTInit()
	{
	allocs = new list::skiplist<tclass*>;
	allocs->setCompare(tpointerCmp);
	allocs->setEquals(tpointerEq);
	}

#endif

TEST(SMARTPOINTER, reset)
	{
	ASSERT_TRUE(allocs->isEmpty());
	spointer<tclass> ref(new tclass);
	EXPECT_FALSE(allocs->isEmpty());
    ref.reset();
	EXPECT_TRUE(allocs->isEmpty());
	}

TEST(SMARTPOINTER, function_call)
	{
	ASSERT_TRUE(allocs->isEmpty());
	spointer<tclass> ref(new tclass);
	EXPECT_EQ(ref->testFunction(), obvious_password);
	EXPECT_FALSE(allocs->isEmpty());
	}

TEST(SMARTPOINTER, scopes)
	{
	ASSERT_TRUE(allocs->isEmpty());
		{
		spointer<tclass> ref(new tclass);
		EXPECT_FALSE(allocs->isEmpty());
		}
	EXPECT_TRUE(allocs->isEmpty());
	tclass* ptr = new tclass;
		{
		spointer<tclass> ref(ptr);
		EXPECT_FALSE(allocs->isEmpty());
		}
	EXPECT_TRUE(allocs->isEmpty());
	}

TEST(SMARTPOINTER, copy)
	{
	double remember = 15.2;
	spointer<double> empty;
		{
		double* test = new double[1];
		test[0] = remember;
		spointer<double> fresh(test);
		EXPECT_EQ(fresh.use_count(), 1);
		empty = fresh;
		EXPECT_EQ(fresh.use_count(), 2);
		}
	EXPECT_EQ(*empty, remember);
	}

TEST(SMARTPOINTER, simplestorage)
	{
	double remember = 15.2;
		{
		double* test = new double[1];
		test[0] = remember;
		spointer<double> dptr(test);
		EXPECT_EQ(dptr.use_count(), 1);
		dcontain::binode<spointer<double> > holder(dptr);
		EXPECT_EQ(dptr.use_count(), 2);
		}
	}

TEST(SMARTPOINTER, complexstorage)
	{
	double remember = 15.2;
	list::queue<spointer<double> > q;
		{
		double* test = new double[1];
		test[0] = remember;
		spointer<double> dptr(test);
		q.push_front(dptr);
		}
	spointer<double> nptr = q.pop_back();
	EXPECT_EQ(*nptr, remember);
	}