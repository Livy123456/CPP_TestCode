
#include <iostream>
#include <string>
#include "ObjectFactoryMacro.h"

namespace jj01
{
	class IPerson
	{
	public:
		IPerson() { std::cout << "Iperson constructor\n"; }
		virtual ~IPerson() { std::cout << "IPerson destructor\n"; }
		virtual void ShowInfo()
		{
			std::cout << "i am a IPerson\n";
		}
	};

	class Student : public IPerson
	{
	public:
		Student(const int nAge, const std::string& strName)
			:m_age(nAge)
			, m_strName(strName)
		{ 
			std::cout << "Student constructor\n"; 
		}
		~Student() { std::cout << "Student destructor\n"; }

		virtual void ShowInfo()
		{
			std::cout << "myname is " << m_strName << "	age is " << m_age << std::endl;
		}

	private:
		int m_age;
		std::string m_strName;
	};

	static IPerson* PersonObjCreator(const int nAge, const std::string& strName)
	{
		return new Student(nAge, strName);
	}

	//! 注册创建函数指针
	const bool bRegistered = CObjectFactory2<IPerson, std::string, const int, const std::string&>::GetInstance()->Register("studentCreator", PersonObjCreator);


	//! test
	void Test01()
	{
		//! 创建student对象指针
		IPerson* per = CObjectFactory2<IPerson, std::string, const int, const std::string&>::GetInstance()->CreateObject("studentCreator", 5, "livy");
		per->ShowInfo();

		//! 用完后释放
		delete per;
		per = nullptr;
	}
}


int main(void)
{
	jj01::Test01();

	getchar();
	return 0;
}