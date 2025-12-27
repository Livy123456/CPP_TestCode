#include <iostream>
#include <vector>

using namespace std;

namespace jj01
{
	void Print() {}

	template <typename T, typename... Types>
	void Print(const T& firstArg, const Types&... args)
	{
		//! firstArg是第一个参数， args是剩下的参数包
		//! 所以每次重复调用Print的时候，传入参数包，firstArg又重新接受了第一个参数，
		//! args接受剩下的参数包，直到参数包为空，调用第一个Print无参的重载结束
		cout << firstArg << endl;
		Print(args...);
	}

	/************************************************************************/
	//! ranged-base for(since C++11)
	void Test01()
	{
		for (int i : {1, 2, 3, 4, 5, 6})
		{
			cout << i << endl;
		}
	}

	void Test02()
	{
		vector<int> vec = { 1,2,3,4,5,6 };
		for (auto& i : vec)
		{
			i += 5;
		}

		for (auto i : vec)
		{
			cout << i << endl;
		}

	}
}

int main(void)
{
	//jj01::Print(1, 2.5, "Hello Variadic Templates", 'A');
	jj01::Test02();


	getchar();
	return 0;
}