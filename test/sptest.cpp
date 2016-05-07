#include "../structures/header/lists.hpp"
#include "../utils/spointer.hpp"

static skiplist<void*> allocs;
static const size_t obvious_password = 1234567890;

class tclass
	{
	public:
		tclass()
			{
			allocs.insert(this);
			}
		~tclass()
			{
			allocs.remove(this);
			}
		size_t testFunction()
			{
			return obvious_password;
			}
	};

TEST(SMARTPOINTER, reset)
	{
	ASSERT_TRUE(allocs.isEmpty());
	spointer<tclass> ref(new tclass);
	EXPECT_FALSE(allocs.isEmpty());
    ref.reset();
	EXPECT_TRUE(allocs.isEmpty());
	}

TEST(SMARTPOINTER, function_call)
	{
	ASSERT_TRUE(allocs.isEmpty());
	spointer<tclass> ref(new tclass);
	EXPECT_EQ(ref->testFunction(), obvious_password);
	EXPECT_FALSE(allocs.isEmpty());
	}

TEST(SMARTPOINTER, scopes)
	{
	ASSERT_TRUE(allocs.isEmpty());
		{
		spointer<tclass> ref(new tclass);
		EXPECT_FALSE(allocs.isEmpty());
		}
	EXPECT_TRUE(allocs.isEmpty());
	tclass* ptr = new tclass;
		{
		spointer<tclass> ref(ptr);
		EXPECT_FALSE(allocs.isEmpty());
		}
	EXPECT_TRUE(allocs.isEmpty());
	}