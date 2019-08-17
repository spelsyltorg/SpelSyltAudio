#pragma once
#include <new>

namespace CL
{
	//------------------------------------------------------------

	template<typename T>
	class TContainerAllocatorBase;

	template<typename T>
	class TContainerAllocatorIterator
	{
	public:
		TContainerAllocatorIterator(TContainerAllocatorBase<T>& InContainer, bool IsEnd);

		void operator=(TContainerAllocatorIterator& InIT);

		T& operator*();
		bool operator!=(const TContainerAllocatorIterator<T>& InOther) const;
		void operator++();
	private:
		TContainerAllocatorBase<T>* Container;
		unsigned int CurrentIndex;
		unsigned int EndIndex;
	};

	//------------------------------------------------------------

	template <typename T>
	class TContainerAllocatorBase
	{
	public:
		TContainerAllocatorBase();
		~TContainerAllocatorBase();

		virtual void Allocate(unsigned int InSize);
		virtual void ShrinkToMin();

		virtual void Clear();

		virtual void Remove(unsigned int InAtIndex);
		virtual void RemoveReplace(unsigned int InAtIndex);

		virtual unsigned int GetSize() const;
		virtual unsigned int GetMaxSize() const;
		virtual T& GetLast();

		virtual T& operator[](unsigned int InIndex);
		virtual const T& operator[](unsigned int InIndex) const;

		TContainerAllocatorIterator<T> CreateBeginIT() { return TContainerAllocatorIterator<T>(*this, false); };
		TContainerAllocatorIterator<T> CreateEndIT() { return TContainerAllocatorIterator<T>(*this, true); };

	protected:
		virtual void Resize(unsigned int InNewSize);
		virtual void FreeAllMemory();

		T* Data;
		unsigned int CurrentSize;
		unsigned int MaxSize;
	};
}

//------------------------------------------------------------

template<typename T>
inline CL::TContainerAllocatorBase<T>::TContainerAllocatorBase()
	: Data(nullptr)
	, CurrentSize(0)
	, MaxSize(0)
{
}

//------------------------------------------------------------

template<typename T>
inline CL::TContainerAllocatorBase<T>::~TContainerAllocatorBase()
{
	if (Data != nullptr)
	{
		FreeAllMemory();
	}
}

//------------------------------------------------------------

template<typename T>
inline void CL::TContainerAllocatorBase<T>::Allocate(unsigned int InSize)
{
	if (Data != nullptr)
	{
		return;
	}

	Data = new T[InSize];
	MaxSize = InSize;
}

//------------------------------------------------------------

template<typename T>
inline void CL::TContainerAllocatorBase<T>::ShrinkToMin()
{
	Resize(CurrentSize);
}

//------------------------------------------------------------

template<typename T>
inline void CL::TContainerAllocatorBase<T>::Clear()
{
	CurrentSize = 0;
}

//------------------------------------------------------------

template<typename T>
inline void CL::TContainerAllocatorBase<T>::Remove(unsigned int InAtIndex)
{
	const unsigned int SizeToEnd = sizeof(T) * (MaxSize - InAtIndex);
	memcpy_s(&Data[InAtIndex], SizeToEnd, &Data[InAtIndex + 1], SizeToEnd - sizeof(T));
	CurrentSize--;
}

//------------------------------------------------------------

template<typename T>
inline void CL::TContainerAllocatorBase<T>::RemoveReplace(unsigned int InAtIndex)
{
	const unsigned int IndexOfLastElement = CurrentSize - 1;
	memcpy_s(&Data[InAtIndex], sizeof(T), &Data[IndexOfLastElement], sizeof(T));
	CurrentSize--;
}

//------------------------------------------------------------

template<typename T>
inline unsigned int CL::TContainerAllocatorBase<T>::GetSize() const
{
	return CurrentSize;
}

//------------------------------------------------------------

template<typename T>
inline unsigned int CL::TContainerAllocatorBase<T>::GetMaxSize() const
{
	return MaxSize;
}

//------------------------------------------------------------

template<typename T>
inline T& CL::TContainerAllocatorBase<T>::GetLast()
{
	return Data[CurrentSize - 1];
}

//------------------------------------------------------------

template<typename T>
inline T& CL::TContainerAllocatorBase<T>::operator[](unsigned int InIndex)
{
	return Data[InIndex];
}

//------------------------------------------------------------

template<typename T>
inline const T& CL::TContainerAllocatorBase<T>::operator[](unsigned int InIndex) const
{
	return Data[InIndex];
}

//------------------------------------------------------------

template<typename T>
inline void CL::TContainerAllocatorBase<T>::Resize(unsigned int InNewSize)
{
	T* NewLocation = new T[InNewSize];
	memcpy_s(NewLocation, sizeof(T) * InNewSize, Data, sizeof(T) * MaxSize);
	const unsigned int OldSize = CurrentSize;

	FreeAllMemory();
	Data = NewLocation;
	CurrentSize = OldSize;
	MaxSize = InNewSize;
}

//------------------------------------------------------------

template<typename T>
inline void CL::TContainerAllocatorBase<T>::FreeAllMemory()
{
	delete[MaxSize] Data;
	Data = nullptr;
	MaxSize = 0;
	CurrentSize = 0;
}

//------------------------------------------------------------

//BEGIN ITERATOR

//------------------------------------------------------------

template<typename T>
inline CL::TContainerAllocatorIterator<T>::TContainerAllocatorIterator(TContainerAllocatorBase<T>& InContainer, bool IsEnd)
	: Container(&InContainer)
	, CurrentIndex(IsEnd ? InContainer.GetSize() - 1 : 0)
	, EndIndex(InContainer.GetSize() - 1)
{
}

//------------------------------------------------------------

template<typename T>
inline void CL::TContainerAllocatorIterator<T>::operator=(TContainerAllocatorIterator<T>& InIT)
{
	Container = InIT.Container;
	CurrentIndex = InIT.CurrentIndex;
	EndIndex = InIT.EndIndex;
}

//------------------------------------------------------------

template<typename T>
inline T& CL::TContainerAllocatorIterator<T>::operator*()
{
	return Container->operator[](CurrentIndex);
}

//------------------------------------------------------------

template<typename T>
inline bool CL::TContainerAllocatorIterator<T>::operator!=(const TContainerAllocatorIterator<T>& InOther) const
{
	return CurrentIndex != InOther.CurrentIndex;
}

//------------------------------------------------------------

template<typename T>
inline void CL::TContainerAllocatorIterator<T>::operator++()
{
	CurrentIndex++;
}

//------------------------------------------------------------