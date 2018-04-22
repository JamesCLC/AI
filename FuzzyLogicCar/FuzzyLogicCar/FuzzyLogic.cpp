#include "FuzzyLogic.h"



FuzzyLogic::FuzzyLogic()
{
	m_Engine = nullptr;
	m_Velocity = nullptr;
	m_Displacement = nullptr;
	m_Output = nullptr;
}


FuzzyLogic::~FuzzyLogic()
{

}

void FuzzyLogic::Init()
{
	// Set up the Engine
	m_Engine = new Engine;
	m_Engine->setName("FuzzyCar");
	m_Engine->setDescription("Driving a car using Fuzzy Logic");

	// Set up the Velocity Input Variable
	m_Velocity = new InputVariable;
	m_Velocity->setName("Velocity");
	m_Velocity->setDescription("The Car's Velocity relative to the Racing Line.");
	m_Velocity->setEnabled(true);
	m_Velocity->setRange(-0.6, 0.6);
	m_Velocity->setLockValueInRange(true);
	m_Velocity->addTerm(new Gaussian("left", -0.6, 0.3));
	m_Velocity->addTerm(new Gaussian("straight", 0, 0.1));
	m_Velocity->addTerm(new Gaussian("right", 0.6, 0.3));

	// Add the Velocity to the Engine
	m_Engine->addInputVariable(m_Velocity);

	// Set up the Displacement Input Variable
	m_Displacement = new InputVariable;
	m_Displacement->setName("Displacement");
	m_Displacement->setDescription("The Distance of the car from the Racing Line.");
	m_Displacement->setEnabled(true);
	m_Displacement->setRange(-720, 720);
	m_Displacement->setLockValueInRange(true);
	m_Displacement->addTerm(new Gaussian("left", -640, 400));
	m_Displacement->addTerm(new Gaussian("centre", 0, 50));
	m_Displacement->addTerm(new Gaussian("right", 640, 400));

	// Add the Displacement to the Engine
	m_Engine->addInputVariable(m_Displacement);

	// Set up the Output of the Fuzzy Inference System
	m_Output = new OutputVariable;
	m_Output->setName("Output");
	m_Output->setDescription("The Output of the FIS. Used to modify the car's velocity.");
	m_Output->setEnabled(true);
	m_Output->setRange(-1, 1);
	m_Output->setLockValueInRange(true);
	m_Output->setAggregation(new Maximum);
	m_Output->setDefuzzifier(new Centroid(100));
	//m_Output->setDefuzzifier(new Bisector(100));
	m_Output->setDefaultValue(fl::nan);
	m_Output->setLockPreviousValue(false);
	m_Output->addTerm(new Gaussian("hardRight", -1, 0.3));
	m_Output->addTerm(new Gaussian("softRight", -0.5, 0.4));
	m_Output->addTerm(new Gaussian("noChange", 0, 0.2));
	m_Output->addTerm(new Gaussian("softLeft", 0.5, 0.4));
	m_Output->addTerm(new Gaussian("hardLeft", 1, 0.3));

	// Add the Output to the Engine
	m_Engine->addOutputVariable(m_Output);

	// Set up the Rule Block
	m_RuleBlock = new RuleBlock;
	m_RuleBlock->setName("RuleBlock");
	m_RuleBlock->setDescription("A Memdani Rule block to determine the output of the FIS.");
	m_RuleBlock->setEnabled(true);
	m_RuleBlock->setConjunction(new Minimum);
	m_RuleBlock->setDisjunction(fl::null);
	m_RuleBlock->setImplication(new AlgebraicProduct);
	m_RuleBlock->setActivation(new General);

	// Add the Rules
	m_RuleBlock->addRule(Rule::parse("if Displacement is left and Velocity is left then Output is hardRight", m_Engine));
	m_RuleBlock->addRule(Rule::parse("if Displacement is left and Velocity is straight then Output is softRight", m_Engine));
	m_RuleBlock->addRule(Rule::parse("if Displacement is left and Velocity is right then Output is noChange", m_Engine));

	m_RuleBlock->addRule(Rule::parse("if Displacement is centre and Velocity is left then Output is softRight", m_Engine));
	m_RuleBlock->addRule(Rule::parse("if Displacement is centre and Velocity is straight then Output is noChange", m_Engine));
	m_RuleBlock->addRule(Rule::parse("if Displacement is centre and Velocity is right then Output is softLeft", m_Engine));

	m_RuleBlock->addRule(Rule::parse("if Displacement is right and Velocity is left then Output is noChange", m_Engine));
	m_RuleBlock->addRule(Rule::parse("if Displacement is right and Velocity is straight then Output is softLeft", m_Engine));
	m_RuleBlock->addRule(Rule::parse("if Displacement is right and Velocity is right then Output is hardLeft", m_Engine));

	m_Engine->addRuleBlock(m_RuleBlock);

	// Test to make suire the Engine has been set up correctly.
	std::string status;
	if (not m_Engine->isReady(&status))
		throw Exception("[engine error] engine is not ready:n" + status, FL_AT);

}

float FuzzyLogic::Update(float velocity, float displacement)
{
	// Put the Car's values into the FIS.
	m_Velocity->setValue(velocity);
	m_Displacement->setValue(displacement);

	// Process the information.
	m_Engine->process();

	return m_Output->getValue();
}
