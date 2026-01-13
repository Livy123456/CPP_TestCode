



//---------------------------------------------------
//! 1. accumulateÀ„∑®
#include <iostream>     // std::cout
#include <functional>   // std::minus
#include <numeric>      // std::accumulate

using namespace std;

namespace jj00
{
	int myfunc(int x, int y) { return x + 2 * y; }

	struct myclass {
		int operator()(int x, int y) { return x + 3 * y; }
	} myobj;

	void test_accumulate()
	{
		cout << "\ntest_accumulate().......... \n";
		int init = 100;
		int nums[] = { 10,20,30 };

		cout << "using default accumulate: ";
		cout << accumulate(nums, nums + 3, init);  //160
		cout << '\n';

		cout << "using functional's minus: ";
		cout << accumulate(nums, nums + 3, init, minus<int>()); //40
		cout << '\n';

		cout << "using custom function: ";
		cout << accumulate(nums, nums + 3, init, myfunc);	//220
		cout << '\n';

		cout << "using custom object: ";
		cout << accumulate(nums, nums + 3, init, myobj);	//280
		cout << '\n';
	}
}


//---------------------------------------------------
//! ≤‚ ‘for_eachÀ„∑®
#include <iostream>     // std::cout
#include <algorithm>    // std::for_each
#include <vector>       // std::vector
namespace jj01
{
	void myfunc(int i) 
	{
		cout << ' ' << i;
	}

	struct myclass 
	{
		void operator() (int i) { cout << ' ' << i; }
	} myobj;

	void test_for_each()
	{
		cout << "\ntest_for_each().......... \n";

		vector<int> myvec;
		myvec.push_back(10);
		myvec.push_back(20);
		myvec.push_back(30);

		for_each(myvec.begin(), myvec.end(), myfunc);
		cout << endl;		//output: 10 20 30

		for_each(myvec.begin(), myvec.end(), myobj);
		cout << endl;		//output: 10 20 30

							//since C++11, range-based for- statement
		for (auto& elem : myvec)
			elem += 5;

		for (auto elem : myvec)
			cout << ' ' << elem; 	//output: 15 25 35
	}
}

//---------------------------------------------------
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
namespace jj02
{
	bool myfunc(int i, int j) { return (i < j); }

	struct myclass 
	{
		bool operator() (int i, int j) { return (i < j); }
	} myobj;

	bool test_sort()
	{
		cout << "\ntest_sort().......... \n";

		int myints[] = { 32,71,12,45,26,80,53,33 };
		vector<int> myvec(myints, myints + 8);          // 32 71 12 45 26 80 53 33

														// using default comparison (operator <):
		sort(myvec.begin(), myvec.begin() + 4);         //(12 32 45 71)26 80 53 33

														// using function as comp
		sort(myvec.begin() + 4, myvec.end(), myfunc); 	// 12 32 45 71(26 33 53 80)

														// using object as comp
		sort(myvec.begin(), myvec.end(), myobj);      //(12 26 32 33 45 53 71 80)

													  // print out content:
		cout << "\nmyvec contains:";
		for (auto elem : myvec)		//C++11 range-based for statement
			cout << ' ' << elem; 	//output: 12 26 32 33 45 53 71 80

									// using reverse iterators and default comparison (operator <):
		sort(myvec.rbegin(), myvec.rend());

		// print out content:
		cout << "\nmyvec contains:";
		for (auto elem : myvec)		//C++11 range-based for statement
			cout << ' ' << elem; 	//output: 80 71 53 45 33 32 26 12    

									// using explicitly default comparison (operator <):
		sort(myvec.begin(), myvec.end(), less<int>());

		// print out content:
		cout << "\nmyvec contains:";
		for (auto elem : myvec)		//C++11 range-based for statement
			cout << ' ' << elem; 	//output: 12 26 32 33 45 53 71 80   

									// using another comparision criteria (operator >):
		sort(myvec.begin(), myvec.end(), greater<int>());

		// print out content:
		cout << "\nmyvec contains:";
		for (auto elem : myvec)		//C++11 range-based for statement
			cout << ' ' << elem; 	//output: 80 71 53 45 33 32 26 12 	     

		return true;
	}
}

int main(void)
{
	//jj00::test_accumulate();
	//jj01::test_for_each();
	jj02::test_sort();

	getchar();
	return 0;
}