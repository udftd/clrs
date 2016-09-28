#ifndef _FY_VECTOR_HPP_
#define _FY_VECTOR_HPP_

#include "exceptions.hpp"

#include <utility>
#include <algorithm>

template <typename T>
class Vector
{
	public:
		Vector(std::size_t initSize = 0)
			: theSize{ initSize },
			theCapacity{ initSize + SPARE_CAPACITY }
		{
			data = new T[theCapacity];
		}
		~Vector() { delete [] data; }

		Vector(const Vector& rhs)
			: theSize{ rhs.theSize },
			theCapacity{ rhs.theCapacity },
			data{ nullptr }
		{
			data = new T[rhs.theCapacity];
			for (std::size_t i = 0; i < theSize; ++i)
				data[i] = rhs.data[i];
		}
		Vector(Vector&& rhs)
			: theSize{ rhs.theSize },
			theCapacity{ rhs.theCapacity },
			data{ rhs.data }
		{
			rhs.theSize = 0;
			rhs.theCapacity = 0;
			rhs.data = nullptr;
		}

		Vector& operator = (const Vector& rhs)
		{
			Vector tmp = rhs;
			std::swap(*this, tmp);
			return *this;
		}
		Vector& operator = (const Vector&& rhs)
		{
			std::swap(theSize, rhs.theSize);
			std::swap(theCapacity, rhs.theCapacity);
			std::swap(data, rhs.data);
			return *this;
		}

		static const int SPARE_CAPACITY = 1;

	public:

		std::size_t size()const { return theSize; }
		std::size_t capacity()const { return theCapacity; }
		bool empty()const { return theSize == 0; }

		void resize(std::size_t newSize)
		{
			if (newSize > theCapacity)
				reserve(newSize * 2);
			theSize = newSize;
		}
		void reserve(std::size_t newCapacity)
		{
			if (newCapacity < theCapacity)
				return;

			T* newData = new T[theCapacity];
			for (std::size_t i = 0; i < theSize; ++i)
				newData = std::move(data[i]);
			theCapacity = newCapacity;
			std::swap(data, newData);
			delete [] newData;
		}

		const T& operator [] (std::size_t position)const 
		{
			if (position < 0 || position >= theSize) {
				throw ArrayOutOfBound{};
			}
			if (position >= 0 && position < theSize)
				return data[position];
		}
		T& operator [] (std::size_t position)
		{
			return const_cast<T&>(
					static_cast<const Vector&>(*this)[position]
						);
		}

	public:
		void push_back(const T& x)
		{
			if (theSize == theCapacity)
				reserve(2 * theCapacity + 1);
			data[theSize++] = x;
		}
		void push_back(const T&& x)
		{
			if (theSize == theCapacity)
				reserve(2 * theCapacity + 1);
			data[theSize++] = std::move(x);
		}
		void pop_back()
		{
			if (empty())
				return;
			--theSize;
		}
		const T& back()const
		{
			if (empty())
				throw Underflow{};
			return data[theSize - 1];
		}

	public:

		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin() { return &data[0]; }
		const_iterator begin()const { return &data[0]; }
		iterator end() { return &data[theSize]; }
		const_iterator end()const {return &data[theSize]; }


	private:
		std::size_t theSize;
		std::size_t theCapacity;

		T* data;
};


#endif









