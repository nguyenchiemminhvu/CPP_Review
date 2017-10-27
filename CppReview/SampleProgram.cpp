#include "SampleProgram.h"
#include <assert.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

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
	// To qualify as a composition (strong relationship), an object and a part must have the following relationship:
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
	// To qualify as an aggregation (weaker relationship than composition), a whole object and its parts must have the following relationship:
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
	//////////////////////////////////////////////////////////////////////////
	// To qualify as an association (weak relationship), an object and another object must have the following relationship:
	// - The associated object (member) is otherwise unrelated to the object (class)
	// - The associated object (member) can belong to more than one object (class) at a time
	// - The associated object (member) does not have its existence managed by the object (class)
	// - The associated object (member) may or may not know about the existence of the object (class)
	//////////////////////////////////////////////////////////////////////////

	class Doctor;

	class Patient
	{
	public:

		friend class Doctor;

		Patient(const std::string &name) :
			name(name)
		{

		}

		std::string getName() const
		{
			return name;
		}

		void showListDoctor()
		{
			// pretend to show list of doctors
		}

	private:

		std::string name;
		std::vector<Doctor *> listDoctor;

		void addDoctor(Doctor *doc)
		{
			listDoctor.push_back(doc);
		}

	};

	class Doctor
	{
	public:

		Doctor(const std::string &name) :
			name(name)
		{

		}

		std::string getName() const
		{
			return name;
		}

		void addPatient(Patient *pat)
		{
			listPatient.push_back(pat);
			pat->addDoctor(this);
		}

		void showListPatient()
		{
			// pretend to show list of patients
		}

	private:

		std::string name;
		std::vector<Patient *> listPatient;

	};

	Patient *p1 = new Patient("minh vu");
	Patient *p2 = new Patient("hoang vi");
	Patient *p3 = new Patient("anh trung");

	Doctor *d1 = new Doctor("mother fucker 1");
	Doctor *d2 = new Doctor("mother fucker 2");

	d1->addPatient(p1);
	d2->addPatient(p1);
	d2->addPatient(p3);

	p1->showListDoctor();
	p2->showListDoctor();
	p3->showListDoctor();

	d1->showListPatient();
	d2->showListPatient();

	// just release memory
	delete p1;
	delete p2;
	delete p3;
	delete d1;
	delete d2;

	// -------------------------------------------------------
	// another example

	class Course
	{
	public:

		Course(const std::string &name, std::vector<Course *> pre = std::vector<Course *>())	:
			name(name), prerequisites(pre)
		{

		}

		void addPrerequisite(Course *course)
		{
			prerequisites.push_back(course);
		}

	private:

		std::string name;
		std::vector<Course *> prerequisites;

	};

	Course *computerScience = new Course("Computer science");
	
	Course *cpp = new Course("C++ programming language");
	cpp->addPrerequisite(computerScience);
	
	Course *java = new Course("Java programming language");
	java->addPrerequisite(computerScience);

	Course *oop = new Course("Object oriented programming");
	oop->addPrerequisite(computerScience);
	oop->addPrerequisite(cpp);
	oop->addPrerequisite(java);
}

//////////////////////////////////////////////////////////////////////////
//Property									Composition			Aggregation			Association
//Relationship type							Whole / part		Whole / part		Otherwise unrelated
//Members can belong to multiple classes	No					Yes					Yes
//Members existence managed by class		Yes					No					No
//Directionality							Unidirectional		Unidirectional		Unidirectional or bidirectional
//Relationship verb							Part - of			Has - a				Uses - a
//////////////////////////////////////////////////////////////////////////

// inheritance relationship basic
void SampleProgram::testInheritanceRelationship()
{
	// -------------------------------------------------
	// inheritance chains

	class A
	{
	public:

		A(int a)
		{
			std::cout << "A: " << a << std::endl;
		}

		~A()
		{
			std::cout << "~A()" << std::endl;
		}
	};

	class B : public A
	{
	public:

		B(int a, int b)	:
			A(a)
		{
			std::cout << "B: " << b << std::endl;
		}

		~B()
		{
			std::cout << "~B()" << std::endl;
		}
	};

	class C : public B
	{
	public:

		C(int a, int b, int c) :
			B(a, b)
		{
			std::cout << "C: " << c << std::endl;
		}

		~C()
		{
			std::cout << "~C()" << std::endl;
		}
	};

	// init parent class first
	C c(1, 2, 3);
}


// multiple inheritance relationship
void SampleProgram::testMultipleInheritance()
{
	class Person
	{
	private:
		std::string m_name;
		int m_age;

	public:
		Person(std::string name, int age)
			: m_name(name), m_age(age)
		{
		}

		std::string getName() { return m_name; }
		int getAge() { return m_age; }
	};

	class Employee
	{
	private:
		std::string m_employer;
		double m_wage;

	public:
		Employee(std::string employer, double wage)
			: m_employer(employer), m_wage(wage)
		{
		}

		std::string getEmployer() { return m_employer; }
		double getWage() { return m_wage; }
	};

	// Teacher publicly inherits Person and Employee
	class Teacher : public Person, public Employee
	{
	private:
		int m_teachesGrade;

	public:
		Teacher(std::string name, int age, std::string employer, double wage, int teachesGrade)
			: Person(name, age), Employee(employer, wage), m_teachesGrade(teachesGrade)
		{
		}
	};
}


// virtual functions
void SampleProgram::testVirtualFunctions()
{
	// -----------------------------------------------------------------
	// pointers and classes

	class Base
	{
	protected:
		int m_value;

	public:
		Base(int value)
			: m_value(value)
		{
		}

		const char* getName() { return "Base"; }
		int getValue() { return m_value; }
	};

	class Derived : public Base
	{
	public:
		Derived(int value)
			: Base(value)
		{
		}

		const char* getName() { return "Derived"; }
		int getValueDoubled() { return m_value * 2; }
	};

	Derived derived(5);
	std::cout << "derived is a " << derived.getName() << " and has value " << derived.getValue() << '\n';

	Derived &rDerived = derived;
	std::cout << "rDerived is a " << rDerived.getName() << " and has value " << rDerived.getValue() << '\n';

	Derived *pDerived = &derived;
	std::cout << "pDerived is a " << pDerived->getName() << " and has value " << pDerived->getValue() << '\n';

	// -----------------------------------------------------------------
	// pointers and classes 2

	class Animal
	{
	protected:
		std::string m_name;

		// We're making this constructor protected because
		// we don't want people creating Animal objects directly,
		// but we still want derived classes to be able to use it.
		Animal(std::string name)
			: m_name(name)
		{
		}

	public:
		virtual std::string getName() { return m_name; }
		virtual const char* speak() { return "???"; }
	};

	class Cat : public Animal
	{
	public:
		Cat(std::string name)
			: Animal(name)
		{
		}

		const char* speak() { return "Meow"; }
	};

	class Dog : public Animal
	{
	public:
		Dog(std::string name)
			: Animal(name)
		{
		}

		const char* speak() { return "Woof"; }
	};

	Cat cat("Fred");
	std::cout << "cat is named " << cat.getName() << ", and it says " << cat.speak() << '\n';

	Dog dog("Garbo");
	std::cout << "dog is named " << dog.getName() << ", and it says " << dog.speak() << '\n';

	Animal *pAnimal = &cat;
	std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

	pAnimal = &dog;
	std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

	std::vector<Animal *> animals;
	animals.push_back(new Dog("Fred"));
	animals.push_back(new Cat("Zack"));
	animals.push_back(new Dog("Jaycee"));
	animals.push_back(new Dog("Trundle"));
	animals.push_back(new Cat("Fortune"));

	for (int i = 0; i < animals.size(); i++)
	{
		std::cout << animals[i]->getName() << " says " << animals[i]->speak() << std::endl;
	}

	// -----------------------------------------------------------------------
	// virtual functions and polymorphisms

	class A
	{
	public:
		virtual const char* getName() { return "A"; }
	};

	class B : public A
	{
	public:
		virtual const char* getName() { return "B"; }
	};

	class C : public B
	{
	public:
		virtual const char* getName() { return "C"; }
	};

	class D : public C
	{
	public:
		virtual const char* getName() { return "D"; }
	};

	C c;
	A &rBase = c;
	std::cout << "rBase is a " << rBase.getName() << '\n';
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