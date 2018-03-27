#pragma once

//////////////////////////////////////////////
// [https://www.fuzzylite.com/cpp/#example] //
//////////////////////////////////////////////

#include "fl/Headers.h"

using namespace fl;

class FuzzyLogic
{
public:
	FuzzyLogic();
	~FuzzyLogic();

	void Init();
	float Update(float velocity, float displacement);

private:
	Engine* m_Engine;
	InputVariable* m_Velocity;
	InputVariable* m_Displacement;
	OutputVariable* m_Output;
	RuleBlock* m_RuleBlock;
};


