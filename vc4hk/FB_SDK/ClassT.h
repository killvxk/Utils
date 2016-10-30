#ifndef _CLASST_H
#define _CLASST_H

namespace eastl
{
	class allocator
	{
	public:
		__forceinline allocator()
		{
		}

		__forceinline allocator(eastl::allocator *__formal)
		{
		}

		__forceinline void set_name(const char *__formal)
		{
		}

		__forceinline const char* get_name()
		{
			return "EASTL";
		}

		__forceinline void* allocate(unsigned int n, int flags)
		{
			return malloc(n);
		}

		__forceinline void deallocate(void *p, unsigned int __formal)
		{
			free(p);
		}
	};

	template <class T>
	class vector
	{
	private:
		T* m_firstElement;
		T* m_lastElement;
		T* m_arrayBound;
		void* vftable;
	public:
		size_t size()
		{
			return (((intptr_t)m_lastElement - (intptr_t)m_firstElement) / sizeof(void*));
		}

		T at(int nIndex)
		{
			return *(T*)((intptr_t)m_firstElement + (nIndex * sizeof(T)));
		}
		T operator [](int index)
		{
			return At(index);
		}
	};

	template <class T, INT Count, INT PadSize>
	class fixed_vector
	{
	private:
		T* m_firstElement;
		T* m_lastElement;
		T* m_arrayBound;
		//LPVOID m_pad[PadSize];
		T m_data[Count];

	public:
		fixed_vector() {
			m_firstElement = (T *)m_data;
			m_lastElement = (T *)m_data;
			m_arrayBound = (T *)&m_data[Count];
		}

		void push_back(T *const value) {
			if (m_lastElement > m_arrayBound) {

				return;
			}
			*m_lastElement = *value;
			m_lastElement = m_lastElement + 1;
		};

		void clear() {
			m_firstElement = m_data;
			m_lastElement = m_data;
		}

		UINT Size() {
			return m_lastElement - m_firstElement;
		}

		T At(INT nIndex) {
			return m_firstElement[nIndex];
		}

		T operator [](INT index) { return At(index); }
	};
}
namespace fb
{
	template <typename T>
	class WeakPtr
	{
	private:
		T** m_ptr;

	public:
		T* GetData()
		{
			if (m_ptr == NULL)
				return NULL;

			if (*m_ptr == NULL)
				return NULL;

			return (T*)((intptr_t)(*m_ptr) - sizeof(intptr_t));
		}
	};


	template <class T>
	class Array
	{
	private:
		T* m_firstElement;

	public:
		T At(INT nIndex)
		{
			if (m_firstElement == NULL)
				return NULL;

			return *(T*)((intptr_t)m_firstElement + (nIndex * sizeof(T)));
		};

		T operator [](INT index) { return At(index); }
	};




};

#endif