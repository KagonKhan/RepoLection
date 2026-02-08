#pragma once
#include <iostream>

class IAmSingleAndReadyToMingle
{
public:
	static IAmSingleAndReadyToMingle& getStaticInstance()
	{
		static IAmSingleAndReadyToMingle single;
		return single;
	}

	static IAmSingleAndReadyToMingle& getHeapInstance()
	{
		if (instance == nullptr)
			instance = new IAmSingleAndReadyToMingle();

		return *instance;
	}

private:
	IAmSingleAndReadyToMingle()
	{
		
	}

	inline static IAmSingleAndReadyToMingle *instance { nullptr };
};


void PerformSingleton()
{
	//IAmSingle singler;
	for (size_t i = 0; i < 20; i++)
	{
		auto& singler = IAmSingleAndReadyToMingle::getStaticInstance();

	}

}