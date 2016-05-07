#pragma once

template <class T>
class spointer
	{
	private:
		T* ptr;
		size_t reference;

		void ref() {reference++;}
		size_t unref() {return --reference;}
	public:
		spointer() : spointer(NULL) 
			{
			}
		spointer(T* pValue) : ptr(pValue), reference(1)
			{
			}
		spointer(const spointer<T>& sptr) : ptr(sptr.ptr), 
			reference(sptr.reference+1)
			{
			}
		~spointer()
			{
			if (0 == unref())
				{
				delete ptr;
				}
			}
		spointer<T>& operator = (const spointer<T>& sptr)
			{
			if (this != &sptr)
				{
				if(unref() == 0)
					{
					delete ptr;
					}

				ptr = sptr.ptr;
				reference = sptr.reference+1;
				}
			return *this;
			}
		void reset(T* ptrnew = NULL)
			{
			delete ptr;
			ptr = ptrnew;
			reference = 1;
			}
		void swap(spointer<T>& other)
			{
			size_t refbuffer = other.reference;
			T* ptrbuffer = other.ptr;
			other.reference = reference;
			other.ptr = ptr;
			reference = refbuffer;
			ptr = ptrbuffer;
			}

		T* get() const { return ptr; }
		T& operator * () const { return *ptr; }
		T* operator -> () const { return ptr; }
		bool unique() 
			{
			if (1 == reference) return true; 
			return false;
			}
		explicit operator bool() const { return NULL != ptr; }
		size_t use_count() const { return reference; }
	};