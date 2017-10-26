#include "SampleProgram.h"
#include <assert.h>
#include <iostream>
#include <string>
#include <map>

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
	//////////////////////////////////////////////////////////////////////////
	// To qualify as a composition, an object and a part must have the following relationship:
	// - The part(member) is part of the object(class)
	// - The part(member) can only belong to one object(class) at a time
	// - The part(member) has its existence managed by the object(class)
	// - The part(member) does not know about the existence of the object(class)
	//////////////////////////////////////////////////////////////////////////

	class Point2D
	{
	public:

		Point2D() :
			x(0), y(0)
		{

		}

		Point2D(int x, int y) :
			x(x), y(y)
		{

		}

		void setPoint(int x, int y)
		{
			this->x = x;
			this->y = y;
		}

		int getPosX()
		{
			return this->x;
		}
		
		int getPosY()
		{
			return this->y;
		}

	private:

		int x;
		int y;

	};

	class GameObject
	{
	public:

		GameObject(const std::string &name, const Point2D &pos) :
			name(name), pos(pos)
		{

		}

		void moveTo(int x, int y)
		{
			std::cout << name << " move from (" << pos.getPosX() << " , " << pos.getPosY() << ") to (" << x << " , " << y << ")" << std::endl;
			pos.setPoint(x, y);
		}

	private:

		std::string		name;
		Point2D			pos;

	};

	GameObject mc("MC", Point2D(5, 5));
	GameObject enemy("Enemy", Point2D(0, 0));

	mc.moveTo(10, 10);
	enemy.moveTo(5, 5);
}


// aggregation relationship
void SampleProgram::testAggregationRelationship()
{
	//////////////////////////////////////////////////////////////////////////
	// To qualify as an aggregation, a whole object and its parts must have the following relationship:
	// - The part (member) is part of the object (class)
	// - The part (member) can belong to more than one object (class) at a time
	// - The part (member) does not have its existence managed by the object (class)
	// - The part (member) does not know about the existence of the object (class)
	//////////////////////////////////////////////////////////////////////////

	class Person
	{
	public:

		Person(int peronalID, const std::string &name) :
			peronalID(peronalID), 
			name(name)
		{

		}

		int getPersonalID()
		{
			return peronalID;
		}

		std::string getName()
		{
			return name;
		}

	private:

		int				peronalID;
		std::string		name;

	};

	class University
	{
	public:

		University(const std::string &name)	:
			name(name)
		{

		}

		void hire(Person *person)
		{
			assert(person != NULL);

			std::cout << name << " hire " << person->getName() << std::endl;
			numberOfTeacher++;
			listTeacher.insert(std::pair<int, Person*>(numberOfTeacher, person));
		}

		void cancelContract(int personalID)
		{
			for (std::map<int, Person*>::iterator iter = listTeacher.begin(); iter != listTeacher.end(); iter++)
			{
				if (((Person *)(*iter).second)->getPersonalID() == personalID)
				{
					std::cout << name << " cancel contract to " << ((Person*)(*iter).second)->getName() << std::endl;
					listTeacher.erase(iter);
					return;
				}
			}
		}

		void showTeachersInfo()
		{
			std::cout << std::endl;
			std::cout << "=================================================" << std::endl;
			std::cout << " " << name << " " << std::endl;
			for (std::map<int, Person *>::iterator iter = listTeacher.begin(); iter != listTeacher.end(); iter++)
			{
				std::cout << ((Person*)(*iter).second)->getPersonalID() << " " << ((Person*)(*iter).second)->getName() << std::endl;
			}
			std::cout << "=================================================" << std::endl;
			std::cout << std::endl;
		}

	private:

		std::string					name;

		int							numberOfTeacher;
		std::map<int, Person*>		listTeacher;

	};

	class Company
	{
	public:

		Company(const std::string &name)	:
			name(name)
		{

		}

		void hire(Person *person)
		{
			assert(person != NULL);

			std::cout << name << " hire " << person->getName() << std::endl;
			numberOfEmployee++;
			listEmployee.insert(std::pair<int, Person*>(numberOfEmployee, person));
		}

		void cancelContract(int personalID)
		{
			for (std::map<int, Person*>::iterator iter = listEmployee.begin(); iter != listEmployee.end(); iter++)
			{
				if (((Person *)(*iter).second)->getPersonalID() == personalID)
				{
					std::cout << name << " cancel contract to " << ((Person*)(*iter).second)->getName() << std::endl;
					listEmployee.erase(iter);
					return;
				}
			}
		}

		void showEmployeesInfo()
		{
			std::cout << std::endl;
			std::cout << "=================================================" << std::endl;
			std::cout << " " << name << " " << std::endl;
			for (std::map<int, Person *>::iterator iter = listEmployee.begin(); iter != listEmployee.end(); iter++)
			{
				std::cout << ((Person*)(*iter).second)->getPersonalID() << " " << ((Person*)(*iter).second)->getName() << std::endl;
			}
			std::cout << "=================================================" << std::endl;
			std::cout << std::endl;
		}

	private:

		std::string					name;

		int							numberOfEmployee;
		std::map<int, Person*>		listEmployee;
	};

	University	DuyTan("Duy Tan University");
	Company		Gameloft("Gameloft company");

	Person *minhvu	= new Person(123, "NCMV");
	Person *trieu	= new Person(456, "Trieu");
	Person *vi		= new Person(789, "Hoang Vi");

	DuyTan.hire(minhvu);
	Gameloft.hire(vi);
	Gameloft.hire(trieu);
	DuyTan.hire(trieu);

	DuyTan.showTeachersInfo();
	Gameloft.showEmployeesInfo();

	Gameloft.cancelContract(trieu->getPersonalID());

	DuyTan.showTeachersInfo();
	Gameloft.showEmployeesInfo();

	Gameloft.hire(trieu);

	DuyTan.showTeachersInfo();
	Gameloft.showEmployeesInfo();

	// just release memory
	delete minhvu;
	delete trieu;
	delete vi;
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


// dynamic casting
void SampleProgram::testDynamicCasting()
{

}


// template class
void SampleProgram::testTemplateClass()
{

}


// template class specialization
void SampleProgram::testTemplateClassSpecialization()
{

}


// exception
void SampleProgram::testException()
{

}


// STL container
void SampleProgram::testStlContainer()
{

}


// STL Iterator
void SampleProgram::testStlIterator()
{

}


// STL algorithm
void SampleProgram::testStlAlgorithm()
{

}


// smart pointer basic review
void SampleProgram::testSmartPointerBasic()
{

}

// unique pointer (smart pointer review)
void SampleProgram::testUniquePointer()
{

}


// shared pointer (smart pointer review)
void SampleProgram::testSharedPointer()
{

}


// Circular dependency issues (smart pointer review)
void SampleProgram::testCircularDependencyIssues()
{

}


// C++11 standard
void SampleProgram::testCpp11Features()
{

}

//====================================================================