#pragma once
#include "SingletonBase.h"
class RandomFunction:public SingletonBase<RandomFunction>
{
public:
	RandomFunction() { srand(GetTickCount()); } ~RandomFunction() { }
	HRESULT init() { return S_OK; }

	inline int getInt(int num) { return rand() % num; }
	inline int getFromInt(int from, int num) { return rand() % (num - from + 1) + from; }
	float getFloat(void) { return (float)rand() / (float)RAND_MAX; }
	float getFloat(float num) { return (float)rand() / (float)RAND_MAX *num; }
	float getFromFloat(float from, float num) { return ((getFloat()) * (num - from) + from); }
};