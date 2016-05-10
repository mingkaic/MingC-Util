//
//  spointer.hpp
//  memory
//
//  description: smart pointer based on std::spointer
//
//  Created by Mingkai Chen on 2015-05-10.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __WICKD_SMAUT__H
#define __WICKD_SMAUT__H

class ref_count
	{
	private:
    	long*   rc;
	public:
        // constructs NULL counter pointer
        // @remark default constructor
	    ref_count (void) : rc(NULL) {}

        // constructs counter pointing to other's counter
        // @remark copy constructor
	    ref_count (const ref_count& other) : rc(other.rc) {}

        // copy assignment operator (for safe measure)
        // @param[in]   other     reference to ref_count object to copy from
        // @return      reference to this after copy assignment
	    ref_count& operator = (const ref_count& other)
	    	{
			if (this != &other)
				{
	    		rc = other.rc;
		    	}
		    return *this;
	    	}

        // swap contents with another ref_count
        // @param[out]   other    ref_count to swap with
        // @return void
	    void swap (ref_count& other)
	    	{
	    	long holder = *rc;
	    	*rc = *(other.rc);
	    	*(other.rc) = holder;
	    	}

        // get the count value
        // @param[]   void
        // @return long count value
	    long use_count (void) const
	    	{
	        long count = 0;
	        if (NULL != rc)
	        	{
	            count = *rc;
	        	}
	        return count;
	    	}

        // initiate or increment reference counter 
	    // if the input pointer is valid
        // @param[in]   p 	pointer to a T typed object
        // @return void
	    template<class T>
	    void acquire (T* p) 
	    	{
	        if (NULL != p)
	        	{
	            if (NULL == rc)
	            	{
	                try
	                	{
	                    rc = new long(1);
	                	}
	                catch (std::bad_alloc&)
	                	{
	                    delete p;
	                    throw; // rethrow
	                	}
	            	}
	            else
	            	{
	                ++(*rc);
	            	}
	        	}
	    	}

        // delete or decrement reference counter and input
	    // then nullifies this counter
        // @param[in]   p 	pointer to a T typed object
        // @return void
	    template<class T>
	    void release (T* p)
	    	{
	        if (NULL != rc)
	        	{
	            --(*rc);
	            if (0 == *rc)
	            	{
	                delete p;
	                delete rc;
	            	}
	            rc = NULL;
	        	}
	    	}
	};

// actual smart pointer
template <class T>
class spointer
	{
	private:
		// used by this for quick reference increment
		inline void acquire (T* optr)
		    {
	        reference.acquire(optr);
	        ptr = optr;
	    	}

		// used by this for quick reference decrement
	    inline void release (void)
		    {
	        reference.release(ptr);
	        ptr = NULL;
		    }

	    // share with spointers of other types
	    template<class OTHERTYPE>
	    friend class spointer;

		T* ptr;
    	ref_count	reference;
	public:
	    // constructs null raw pointer 
	    // and initialize reference
	    // @remark default constructor
		spointer (void) : ptr(NULL), reference()
			{
			}
	    // constructs points raw pointer 
		// to input and initialize reference
	    // @remark constructor
		explicit spointer (T* pValue) : reference()
			{
			acquire(pValue);
			}

        // destroys self content, then copy sptr content to self
        // @remark copy constructor
		spointer (const spointer<T>& sptr) : reference(sptr.reference)
			{
			acquire(sptr.ptr);
			}

        // destroys self content, then copy 
		// sptr content OF ANOTHER TYPE to self
        // @remark copy constructor for other types
	    template <class U>
	    spointer (const spointer<U>& sptr) : reference(sptr.reference)
	    	{
	    	acquire(static_cast<T*>(sptr.ptr));
	    	}

        // destroys self content, then copy 
		// sptr reference OF ANOTHER TYPE to self
	    // and input raw pointer to this pointer content
        // @remark copy constructor for other types
		template <class U>
	    spointer (const spointer<U>& sptr, T* rawptr) : reference(sptr.reference)
	    	{
	       	acquire(rawptr);
	    	}

        // destructor
        // @remark destructor
		virtual ~spointer (void)
			{
			release();
			}

        // copy assignment operator
        // @param[in]   sptr     reference to spointer object to copy from
        // @return      reference to this after copy assignment
		spointer<T>& operator = (const spointer<T>& sptr)
			{
			if (this != &sptr)
				{
				release();
				reference = sptr.reference;
				acquire(sptr.ptr);
				}
			return *this;
			}

        // unleash this raw pointer and reference
        // @param[]   void 
        // @return void
		inline void reset (void) throw()
			{
		    release();
			}

        // unleash this raw pointer and reference
		// then reference input raw pointer
        // @param[in]   ptrnew	pointer to T typed data
        // @return void
		void reset (T* ptrnew)
			{
			release();
        	acquire(ptrnew);
			}

        // swap contents between this and other
        // @param[in]   other 	reference of spointer 
        // @return void
		void swap (spointer<T>& other)
			{
			reference.swap(other.reference);
			T* ptrbuffer = other.ptr;
			other.ptr = ptr;
			ptr = ptrbuffer;
			}

        // get raw pointer
        // @param[]		void
        // @return raw pointer
		T* get (void) const { return ptr; }

        // override dereference
        // @param[]		void
        // @return dereferenced raw pointer
		T& operator * () const { return *ptr; }

        // override pointer member access
        // @param[]		void
        // @return raw pointer
		T* operator -> () const { return ptr; }

        // determines if there is only a single reference
        // @param[]		void
        // @return true if there's only a single reference, false otherwise
		bool unique (void) const { return 1 == reference.use_count(); }

        // get reference count
        // @param[]		void
        // @return long reference count
		long use_count (void) const { return reference.use_count(); }

        // boolean conversion if raw pointer is non-null and reference count is available
        // @param[]		void
        // @return true if raw pointer is non-null and reference count is available, false otherwise
		explicit operator bool() const 
			{ 
			return NULL != ptr && 0 < reference.use_count();
			}
	};

	// comparaison operators
	template<class T, class U> 
	inline bool operator==(const spointer<T>& l, const spointer<U>& r)
		{
	    return (l.get() == r.get());
		}
	template<class T, class U> 
	inline bool operator!=(const spointer<T>& l, const spointer<U>& r)
		{
	    return (l.get() != r.get());
		}
	template<class T, class U> 
	inline bool operator<=(const spointer<T>& l, const spointer<U>& r)
		{
	    return (l.get() <= r.get());
		}
	template<class T, class U> 
	inline bool operator<(const spointer<T>& l, const spointer<U>& r)
		{
	    return (l.get() < r.get());
		}
	template<class T, class U> 
	inline bool operator>=(const spointer<T>& l, const spointer<U>& r)
		{
	    return (l.get() >= r.get());
		}
	template<class T, class U> 
	inline bool operator>(const spointer<T>& l, const spointer<U>& r)
		{
	    return (l.get() > r.get());
		}

#endif /*__WICKD_SMAUT__H  */