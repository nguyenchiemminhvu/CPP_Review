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

	// inheritance relationship basic
	void testInheritanceRelationship();

	// multiple inheritance relationship
	void testMultipleInheritance();

	// virtual functions
	void testVirtualFunctions();

	// dynamic casting
	void testDynamicCasting();

	// template functions
	void testTemplateFunction();

	// template class
	void testTemplateClass();

	// template function specialization
	void testTemplateFunctionSpecialization();

	// template class specialization
	void testTemplateClassSpecialization();

	// exception
	void testException();

	// STL container
	void testStlContainer();

	// STL Iterator
	void testStlIterator();

	// STL algorithm
	void testStlAlgorithm();

	// smart pointer basic review
	void testSmartPointerBasic();

	// unique pointer (smart pointer review)
	void testUniquePointer();

	// shared pointer (smart pointer review)
	void testSharedPointer();

	// Circular dependency issues (smart pointer review)
	void testCircularDependencyIssues();

	// C++11 standard
	void testCpp11Features();

	//====================================================================
};

