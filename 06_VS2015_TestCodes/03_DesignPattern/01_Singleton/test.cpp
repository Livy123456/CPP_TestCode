
#include <cstdio>
#include "Singleton.h"

namespace jj01
{
	class CPerson : public CSingleton<CPerson>
	{
		friend class CSingleton<CPerson>;	//< 因为要构建CPerson，但CPerson构造是私有的

		//! 私有
		CPerson(){ std::cout << "CPerson constructor\n"; }	
		~CPerson(){ std::cout << "CPerson destructor\n"; } //< 无法直接delete指针，需要通过单例析构
		CPerson(const CPerson& per);
		CPerson& operator=(const CPerson& per);

	public:
		void SayHello()
		{
			printf("Hello, I am a singleton person instance.\n");
		};
	};


	void Test01()
	{
		CPerson* p = CPerson::GetInstance();
		p->SayHello();
		std::cout << std::hex << (void*)p << std::endl;

		CPerson::ReleaseInstance();
	}
}


int main(void)
{
	jj01::Test01();

	getchar();
	return 0;
}