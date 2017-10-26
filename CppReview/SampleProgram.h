#pragma once
class SampleProgram
{
public:

	SampleProgram();
	virtual ~SampleProgram();

	//====================================================================
	// All sample programs here

	// overloading the parenthesis operator
	void testOverloadParenthesisOperator();

	// copy constructor
	void testCopyContructor();

	// shadow copy and deep copy
	void testShadowCopyAndDeepCopy();

	// composition relationship
	void testCompositionRelationship();

	// aggregation relationship
	void testAggregationRelationship();

	// association relationship
	void testAssociationRelationship();

	// dependencies relationship
	void testDependenciesRelationship();

	// inheritance relationship basic
	void testInheritanceRelationship();

	// multiple inheritance relationship
	void testMultipleInheritance();

	// virtual functions
	void testVirtualFunctions();

	//====================================================================
};

