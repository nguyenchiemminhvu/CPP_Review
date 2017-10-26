#include "SampleProgram.h"
#include <assert.h>
#include <iostream>
#include <cstring>

using namespace std;


SampleProgram::SampleProgram()
{
}


SampleProgram::~SampleProgram()
{
}


//====================================================================
// All sample programs here

// overloading the parenthesis operator
void SampleProgram::testOverloadParenthesisOperator()
{
	class Matrix
	{
	public:

		Matrix()
		{
			// set all elements of the matrix to 0.0
			for (int row = 0; row < 4; row++)
			{
				for (int col = 0; col < 4; col++)
				{
					data[row][col] = 0.0;
				}
			}
		}

		double& Matrix::operator()(int row, int col)
		{
			assert(row >= 0 && row < 4);
			assert(col >= 0 && col < 4);

			return data[row][col];
		}

	private:

		double data[4][4];

	};

	Matrix mat4;
	for (int row = 0; row < 4; row++)
	{

		for (int col = 0; col < 4; col++)
		{
			mat4(row, col) = row * col;
			std::cout << mat4(row, col) << " ";
		}

		std::cout << std::endl;
	}

}


// copy constructor
void SampleProgram::testCopyContructor()
{
	class Number
	{
	public:

		Number(int v = 0)
		{
			this->value = v;
		}

		Number(const Number &other)
		{
			std::cout << "do copy constructor" << std::endl;
			this->value = other.value * 2;
		}

		int& Number::operator()()
		{
			return value;
		}

	private:

		int value;

	};

	Number n1(10);
	Number n2(n1);
	std::cout << n2() << std::endl;
}


// shadow copy and deep copy
void SampleProgram::testShadowCopyAndDeepCopy()
{
	class MyString
	{
	public:

		MyString()
		{
			data	= NULL;
			length	= 0;
		}

		MyString(const char *s)
		{
			std::cout << "Constructor with a C-style string param" << std::endl;
			assert(s != NULL);

			int s_length = strlen(s);
			length = s_length;

			data = new char[length];
			strcpy(data, s);
		}

		MyString(const MyString &other)
		{
			std::cout << "Copy constructor" << std::endl;
			assert(other.data != NULL);

			length = other.length;
			if (data != NULL)
			{
				data = new char[length];

				// do the deep copy
				strcpy(data, other.data);
			}
		}

		MyString& MyString::operator = (const MyString &other)
		{
			std::cout << "Assignment operator" << std::endl;
			if (this == &other)
				return *this;

			delete[] data;

			if (other.data == NULL)
			{
				length = 0;
				return *this;
			}

			length = other.length;
			data = new char[length];
			strcpy(data, other.data);
		}

		virtual ~MyString()
		{

		}

		const char *getString()
		{
			return this->data;
		}

	private:

		char	*data;
		int		length;

	};

	MyString s1("nguyen chiem minh vu");
	MyString s2(s1);
	MyString s3 = s2;
	std::cout << s1.getString() << std::endl;
	std::cout << s2.getString() << std::endl;
	std::cout << s3.getString() << std::endl;
}


// composition relationship
void SampleProgram::testCompositionRelationship()
{

}


// aggregation relationship
void SampleProgram::testAggregationRelationship()
{

}


// association relationship
void SampleProgram::testAssociationRelationship()
{

}


// dependencies relationship
void SampleProgram::testDependenciesRelationship()
{

}


// inheritance relationship basic
void SampleProgram::testInheritanceRelationship()
{

}


// multiple inheritance relationship
void SampleProgram::testMultipleInheritance()
{

}


// virtual functions
void SampleProgram::testVirtualFunctions()
{

}

//====================================================================