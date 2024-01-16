/*
File:			DynArray.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:	Brenna Pavlinchak

Purpose:		A dynamically-allocated resizeable array (similar to std::vector)
Notes:			Property of Full Sail University 2401
*/

// Header protection
#pragma once

/***********/
/* Defines */
/***********/

/*
How to use:

	When working on a lab, turn that lab's #define from 0 to 1

		Example:	#define LAB_1	1

	When working on an individual unit test, turn that #define from 0 to 1

		Example:	#define DYNARRAY_DEFAULT_CTOR	1

NOTE: If the unit test is not on, that code will not be compiled!
*/

// Main toggle
#define LAB_1	1

// Individual unit test toggles
#define LAB1_DEFAULT_CONSTRUCTOR_NO_ARGS			0
#define LAB1_DEFAULT_CONSTRUCTOR_WITH_ARGS			0
#define LAB1_BRACKET_OPERATOR						0
#define LAB1_SIZE_ACCESSOR							0
#define LAB1_CAPACITY_ACCESSOR						0
#define LAB1_RESERVE_EMPTY							0
#define LAB1_RESERVE_DOUBLE_CAPACITY				0
#define LAB1_RESERVE_LARGER_CAPACITY				1
#define LAB1_RESERVE_SMALLER_CAPACITY				1
#define LAB1_APPEND_NO_RESIZE						1
#define LAB1_APPEND_RESIZE							1
#define LAB1_CLEAR									1
#define LAB1_DESTRUCTOR								1
#define LAB1_ASSIGNMENT_OPERATOR					1
#define LAB1_COPY_CONSTRUCTOR						0

// Our implementation of a vector (simplified)
template<typename Type>
class DynArray {

	// Gives access to test code
	friend class UnitTests_Lab1;

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Type* mArray = reinterpret_cast<Type*>(-1);
	size_t mSize = -1;
	size_t mCapacity = -1;

public:

	DynArray(size_t _startingCap = 0):mArray(nullptr), mSize(0), mCapacity(0) //Default Constructor 
	{
		// TODO: Implement this method
		if (_startingCap > 0)
		{
			mCapacity = _startingCap;
			mArray = new Type[_startingCap];
		}
	};

	~DynArray() //Default Constructor no args
	{
		// TODO: Implement this method
		delete[] mArray;
	}

	DynArray(const DynArray& _copy) : mArray(nullptr), mSize(_copy.mSize), mCapacity(_copy.mCapacity) //Copy Constructor
	{
		// TODO: Implement this method
		for(size_t i = 0; i < mSize; i++) 
		{
			mArray[i] = _copy.mArray[i];
		}
	}

	DynArray& operator=(const DynArray& _assign) //[] Operator 
	{
		// TODO: Implement this method
		if (this != &_assign) 
		{
			Clear();
			mSize = _assign.mSize;
			mCapacity = _assign.mCapacity;
			mArray = new Type[mCapacity];

			for(size_t i = 0; i < mSize; i++) 
			{
				mArray[i] = _assign.mArray[i];
			}
		}
		return *this;
	}

	void Clear() //Clear
	{
		// TODO: Implement this method
		delete[] mArray;
		mArray = nullptr;
		mSize = 0;
		mCapacity = 0;
	}

	Type& operator[](size_t _index) //[] Operator 
	{
		// TODO: Implement this method
		return mArray[_index];
	}

	size_t Size() const //Size
	{
		// TODO: Implement this method
		return mSize;
	}

	size_t Capacity() const //Capacity
	{
		// TODO: Implement this method
		return mCapacity;
	}

	void Append(const Type& _data) //Append
	{
		// TODO: Implement this method
		if(mSize >= mCapacity) 
		{
			size_t newCapacity = (mCapacity == 0) ? 1 : mCapacity * 2;
			Reserve(newCapacity);
		}
		mArray[mSize] = _data;
		mSize++;
	}

	void Reserve(size_t _newCapacity = 0) //Reserve 
	{
		// TODO: Implement this method
		if (_newCapacity == 0 && mCapacity == 0) //Reserve from empty 
		{
			_newCapacity = 1;
		}

		if (_newCapacity < mCapacity * 2) //Reserve with default 
		{
			_newCapacity = mCapacity * 2;
		}

		Type* newArray = new Type[_newCapacity];

		if (_newCapacity <= mCapacity)
		{
			for (size_t i = 0; i < mSize; i++) //Reserve with larger 
			{
				newArray[i] = mArray[i];
			}
		}

		if (_newCapacity <= mCapacity) //Reserve with smaller 
		{
			return;
		}
	
		delete[] mArray;
		mArray = newArray;
		mCapacity = _newCapacity;
	}
};