#pragma once
#include <SpelSyltCommonLibrary/Container/Public/ContainerAllocatorGrowing.h>
#include <SpelSyltCommonLibrary/Container/Public/ContainerAllocatorStatic.h>

#include <cassert>
#include <type_traits>

namespace CL
{
	template<typename T, typename Allocator = TContainerAllocatorStatic<T>>
	class TArray
	{
		//static_assert(std::is_base_of(TContainerAllocatorBase<T>, Allocator).value(), "Allocator must be of Allocator type!");

	public:
		TArray();
		TArray(unsigned int InSize);

		void Allocate(unsigned int InSize);
		void Clear();

		bool IsEmpty() const;
		unsigned int GetSize() const;
		unsigned int GetMaxSize() const;
		
		T& operator[](unsigned int InIndex);
		const T& operator[](unsigned int InIndex) const;
		
		template<typename ...TArgs>
		T& EmplaceBack(TArgs... InArgs);
		T& AddBack(const T& InElement);

		TContainerAllocatorIterator<T> begin() { return Alloc.CreateBeginIT(); };
		TContainerAllocatorIterator<T> end() { return Alloc.CreateEndIT(); };

	private:
		Allocator Alloc;
	};
}

//------------------------------------------------------------

template<typename T, typename Allocator>
inline CL::TArray<T, Allocator>::TArray()
	: Alloc()
{
}

//------------------------------------------------------------

template<typename T, typename Allocator>
inline CL::TArray<T, Allocator>::TArray(unsigned int InSize)
	: Alloc()
{
	Alloc.Allocate(InSize);
}

//------------------------------------------------------------

template<typename T, typename Allocator>
inline void CL::TArray<T, Allocator>::Allocate(unsigned int InSize)
{
	Alloc.Allocate(InSize);
}

//------------------------------------------------------------

template<typename T, typename Allocator>
inline void CL::TArray<T, Allocator>::Clear()
{
	Alloc.Clear();
}

//------------------------------------------------------------

template<typename T, typename Allocator>
inline bool CL::TArray<T, Allocator>::IsEmpty() const
{
	return Alloc.GetSize() == 0;
}

//------------------------------------------------------------

template<typename T, typename Allocator>
inline unsigned int CL::TArray<T, Allocator>::GetSize() const
{
	return Alloc.GetSize();
}

//------------------------------------------------------------

template<typename T, typename Allocator>
inline unsigned int CL::TArray<T, Allocator>::GetMaxSize() const
{
	return Alloc.GetMaxSize();
}

//------------------------------------------------------------

template<typename T, typename Allocator>
inline T& CL::TArray<T, Allocator>::operator[](unsigned int InIndex)
{
	return Alloc[InIndex];
}

//------------------------------------------------------------

template<typename T, typename Allocator>
inline const T& CL::TArray<T, Allocator>::operator[](unsigned int InIndex) const
{
	return Alloc[InIndex];
}

//------------------------------------------------------------

template<typename T, typename Allocator>
template<typename ...TArgs>
inline T& CL::TArray<T, Allocator>::EmplaceBack(TArgs ...InArgs)
{
	const bool Result = Alloc.EmplaceBack(InArgs...);
	assert(Result && "Could not emplace? Are you using a static allocator with no space?");
	return Alloc.GetLast();
}

//------------------------------------------------------------

template<typename T, typename Allocator>
inline T& CL::TArray<T, Allocator>::AddBack(const T& InElement)
{
	const bool Result = Alloc.AddBack(InElement);
	assert(Result && "Could not add? Are you using a static allocator with no space?");
	return Alloc.GetLast();
}

//------------------------------------------------------------