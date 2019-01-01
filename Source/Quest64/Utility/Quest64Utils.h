// Start 28/12/2018 - Niall Maple & Dane Maple

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Containers/Map.h"

/**
 * 
 */
static class QUEST64_API Quest64Utils
{
public:

	template <typename T1, typename T2>
	struct TCustomPair
	{
		TCustomPair()
		{

		}

		TCustomPair(T1 a, T2 b)
		{
			m_first = a;
			m_second = b;
		}

		T1 m_first;
		T2 m_second;
	};

	template <typename T1, typename T2>
	struct FSeekHelper
	{
		FSeekHelper()
		{

		}

		FSeekHelper(T1 a, T2 b)
		{
			m_pair = TCustomPair<T1, T2>(a, b);
			m_value = a;
		}

		TCustomPair<T1, T2> m_pair;
		T1					m_value;
	};


	template <typename T>
	static FORCEINLINE void Seek(float amount, float dt, FSeekHelper<T, T>& seekPair)
	{
		amount *= dt;
		amount = amount - 1 >= 0 ? 1 : amount;
		seekPair.m_value = seekPair.m_pair.m_first + (seekPair.m_pair.m_second - seekPair.m_pair.m_first) * amount;
	}

	template <typename First, typename... Rest> 
	static FORCEINLINE void Seek(float amount, float dt, FSeekHelper<First, First>& seekPair, FSeekHelper<Rest, Rest>&... rest)
	{
		Seek<First>(amount, dt, seekPair);
		Seek<Rest...>(amount, dt, rest...);
	}
};
