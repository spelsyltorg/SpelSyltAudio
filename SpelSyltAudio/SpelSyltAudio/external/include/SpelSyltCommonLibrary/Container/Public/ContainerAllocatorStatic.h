#pragma once
#include <SpelSyltCommonLibrary/Container/Public/ContainerAllocatorBase.h>

namespace CL
{
	template <typename T>
	class TContainerAllocatorStatic final
		: public TContainerAllocatorBase<T>
	{
	public:
		bool AddBack(const T& InT);

		template<typename ...TArgs>
		bool EmplaceBack(TArgs... InArgs);
	};
}

//------------------------------------------------------------

template<typename T>
inline bool CL::TContainerAllocatorStatic<T>::AddBack(const T& InT)
{
	if (CurrentSize + 1 == MaxSize)
	{
		return false;
	}

	Data[CurrentSize] = InT;
	CurrentSize++;

	return true;
}

//-----------------------------------------------------------

template<typename T>
template<typename ...TArgs>
inline bool CL::TContainerAllocatorStatic<T>::EmplaceBack(TArgs ...InArgs)
{
	if (CurrentSize + 1 == MaxSize)
	{
		return false;
	}

	new(&Data[CurrentSize]) T(InArgs...);
	CurrentSize++;

	return true;
}

//-----------------------------------------------------------
