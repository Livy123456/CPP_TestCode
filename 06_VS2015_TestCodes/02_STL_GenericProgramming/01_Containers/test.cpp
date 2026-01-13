// author : Hou Jie (侯捷)
// date : 2015/10/28 
// compiler : DevC++ 5.11 (MinGW with GNU 4.9.9.2)
//
// 說明：這是侯捷 E-learning video "C++標準庫" 的實例程式.
// 該課程的所有測試都出現在此.
// 每一個小測試單元都被放進一個 namespace 中, 
// 如此保持各單元間最大的獨立性.
// 每個 namespace 上方皆有該單元相應的 #include <...> 
// 因此有可能整個程式重複含入 (included) 某些 headers. 
// 這無所謂，因為每個 standard headers 都有自我防衛機制，不讓自己被 included 二次.
//
// 本文件用到若干 C++ 2.0 New Features，所以你必須在你的集成環境 (IDE) 上設定 "C++11 on". 
// 如果你的編譯器報錯，應是因為我用到 (測試) GNU 標準庫的獨特 (非標準) 組件 (特別是 allocators)，
// 將報錯語句改為註解 (comments) 即可通過編譯. 


//! 这里参考了侯捷的代码，但用的vs2022的IDE。这里对各种容器的效率做个简单测试，例如在大量的数据总查找某个数值的速度等。


using namespace std;

/*********************测试程序的辅助函数 begin()******************/

#include <cstdlib> //RAND_MAX
#include <string>	//< string 
#include <iostream>	//< cout cin

long get_a_target_long()
{
	long target = 0;

	cout << "target (0~" << RAND_MAX << "): ";
	cin >> target;
	return target;
}

string get_a_target_string()
{
	long target = 0;
	char buf[10];

	cout << "target (0~" << RAND_MAX << "): ";
	cin >> target;
	snprintf(buf, 10, "%d", target);
	return string(buf);
}

int compareLongs(const void* a, const void* b)
{
	return (*(long*)a - *(long*)b);
}

int compareStrings(const void* a, const void* b)
{
	if (*(string*)a > *(string*)b)
		return 1;
	else if (*(string*)a < *(string*)b)
		return -1;
	else
		return 0;
}
/*********************测试程序的辅助函数 end()******************/

/*********************1.测试std::array()|   begin ******************/
#include <array>
#include <iostream>
#include <ctime> 
#include <cstdlib> //qsort, bsearch, NULL


namespace jj01
{
	const long ASIZE = 200000L;

	//! 测试 std::array，该容器内存分配在栈上。进程默认栈大小一般为1MB~8MB不等，视操作系统和编译器而定。
	//!			如果数组过大，可能会导致栈溢出(stack overflow)。
	void test_array()
	{
		cout << "\ntest_array().......... \n";

		array<long, ASIZE> c;

		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i) 
		{
			c[i] = rand();
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;	//
		cout << "array.size()= " << c.size() << endl;
		cout << "array.front()= " << c.front() << endl;
		cout << "array.back()= " << c.back() << endl;
		cout << "array.data()= " << c.data() << endl;

		long target = get_a_target_long();

		timeStart = clock();
		::qsort(c.data(), ASIZE, sizeof(long), compareLongs);
		long* pItem = (long*)::bsearch(&target, (c.data()), ASIZE, sizeof(long), compareLongs);
		cout << "qsort()+bsearch(), milli-seconds : " << (clock() - timeStart) << endl;	//    
		if (pItem != NULL)
			cout << "found, " << *pItem << endl;
		else
			cout << "not found! " << endl;
	}
}
/*********************1.测试std::array()|   end ******************/


/*********************2.测试std::vector()|   begin ******************/
#include <vector>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
#include <algorithm> 	//sort()
namespace jj02
{
	void test_vector(long& value)
	{
		cout << "\ntest_vector().......... \n";

		vector<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try {
				snprintf(buf, 10, "%d", rand());
				c.push_back(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				//曾經最高 i=58389486 then std::bad_alloc
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "vector.max_size()= " << c.max_size() << endl;	//1073747823
		cout << "vector.size()= " << c.size() << endl;
		cout << "vector.front()= " << c.front() << endl;
		cout << "vector.back()= " << c.back() << endl;
		cout << "vector.data()= " << c.data() << endl;
		cout << "vector.capacity()= " << c.capacity() << endl << endl;

		//! 测试 std::find() 和 bsearch() 的效率差异
		string target = get_a_target_string();
		{
			timeStart = clock();
			auto pItem = find(c.begin(), c.end(), target);
			cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;

			if (pItem != c.end())
				cout << "found, " << *pItem << endl << endl;
			else
				cout << "not found! " << endl << endl;
		}

		{
			timeStart = clock();
			sort(c.begin(), c.end());
			cout << "sort(), milli-seconds : " << (clock() - timeStart) << endl;

			timeStart = clock();
			string* pItem = (string*)::bsearch(&target, (c.data()), //< bsearch是c语言查找算法接口
				c.size(), sizeof(string), compareStrings);
			cout << "bsearch(), milli-seconds : " << (clock() - timeStart) << endl;

			if (pItem != NULL)
				cout << "found, " << *pItem << endl << endl;
			else
				cout << "not found! " << endl << endl;
		}
	}
}
/*********************2.测试std::vector()|   end ******************/


/*********************3.测试std::list()|   begin ******************/
#include <list>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <algorithm> //find()
#include <iostream>
#include <ctime> 
namespace jj03
{
	void test_list(long& value)
	{
		cout << "\ntest_list().......... \n";

		list<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try {
				snprintf(buf, 10, "%d", rand());
				c.push_back(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "list.size()= " << c.size() << endl;
		cout << "list.max_size()= " << c.max_size() << endl;    //357913941
		cout << "list.front()= " << c.front() << endl;
		cout << "list.back()= " << c.back() << endl;

		string target = get_a_target_string();
		timeStart = clock();
		auto pItem = find(c.begin(), c.end(), target);
		cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;

		if (pItem != c.end())
			cout << "found, " << *pItem << endl;
		else
			cout << "not found! " << endl;

		timeStart = clock();
		c.sort();
		cout << "c.sort(), milli-seconds : " << (clock() - timeStart) << endl;
	}
}

/*********************3.测试std::list()|   end ******************/


/*********************4.测试std::forward_list()|   begin ******************/

#include <forward_list>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj04
{
	void test_forward_list(long& value)
	{
		cout << "\ntest_forward_list().......... \n";

		forward_list<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try 
			{
				snprintf(buf, 10, "%d", rand());
				c.push_front(string(buf));
			}
			catch (exception& p) 
			{
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "forward_list.max_size()= " << c.max_size() << endl;  //536870911
		cout << "forward_list.front()= " << c.front() << endl;


		string target = get_a_target_string();
		timeStart = clock();
		auto pItem = find(c.begin(), c.end(), target);
		cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;

		if (pItem != c.end())
			cout << "found, " << *pItem << endl;
		else
			cout << "not found! " << endl;

		timeStart = clock();
		c.sort();
		cout << "c.sort(), milli-seconds : " << (clock() - timeStart) << endl;

		c.clear();
	}
}


/*********************4.测试std::forward_list()|   end ******************/


/*********************5.测试std::deque()|   begin ******************/
#include <deque>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj05
{
	void test_deque(long& value)
	{
		cout << "\ntest_deque().......... \n";

		deque<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try {
				snprintf(buf, 10, "%d", rand());
				c.push_back(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "deque.size()= " << c.size() << endl;
		cout << "deque.front()= " << c.front() << endl;
		cout << "deque.back()= " << c.back() << endl;
		cout << "deque.max_size()= " << c.max_size() << endl;	//1073741821	

		string target = get_a_target_string();
		timeStart = clock();
		auto pItem = find(c.begin(), c.end(), target);
		cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;

		if (pItem != c.end())
			cout << "found, " << *pItem << endl;
		else
			cout << "not found! " << endl;

		timeStart = clock();
		sort(c.begin(), c.end());
		cout << "sort(), milli-seconds : " << (clock() - timeStart) << endl;

	}
}
/*********************5.测试std::deque()|   end ******************/


/*********************6.测试std::multiset()|   begin ******************/
#include <set>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj06
{
	void test_multiset(long& value)
	{
		cout << "\ntest_multiset().......... \n";

		multiset<string> c;
		char buf[10];
		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try {
				snprintf(buf, 10, "%d", rand());
				c.insert(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "multiset.size()= " << c.size() << endl;
		cout << "multiset.max_size()= " << c.max_size() << endl;	//214748364

		string target = get_a_target_string();
		{
			timeStart = clock();
			auto pItem = find(c.begin(), c.end(), target);	//比 c.find(...) 慢很多	
			cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;
			if (pItem != c.end())
				cout << "found, " << *pItem << endl;
			else
				cout << "not found! " << endl;
		}

		{
			timeStart = clock();
			auto pItem = c.find(target);		//比 std::find(...) 快很多							
			cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
			if (pItem != c.end())
				cout << "found, " << *pItem << endl;
			else
				cout << "not found! " << endl;
		}
	}
}
/*********************6.测试std::multiset()|   end ******************/


/*********************7.测试std::multimap()|   begin ******************/
#include <map>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj07
{
	void test_multimap(long& value)
	{
		cout << "\ntest_multimap().......... \n";

		multimap<long, string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try {
				snprintf(buf, 10, "%d", rand());
				//multimap 不可使用 [] 做 insertion 
				c.insert(pair<long, string>(i, buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "multimap.size()= " << c.size() << endl;
		cout << "multimap.max_size()= " << c.max_size() << endl;	//178956970	

		long target = get_a_target_long();
		{
			timeStart = clock();
			auto pItem = c.find(target);
			cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
			if (pItem != c.end())
				cout << "found, value=" << (*pItem).second << endl;
			else
				cout << "not found! " << endl;

			c.clear();
		}
	}
}
/*********************7.测试std::multimap()|   end ******************/


/*********************8.测试std::unordered_multiset()|   begin ******************/
#include <unordered_set>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj08
{
	void test_unordered_multiset(long& value)
	{
		cout << "\ntest_unordered_multiset().......... \n";

		unordered_multiset<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try {
				snprintf(buf, 10, "%d", rand());
				c.insert(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "unordered_multiset.size()= " << c.size() << endl;
		cout << "unordered_multiset.max_size()= " << c.max_size() << endl;	//357913941
		cout << "unordered_multiset.bucket_count()= " << c.bucket_count() << endl;
		cout << "unordered_multiset.load_factor()= " << c.load_factor() << endl;
		cout << "unordered_multiset.max_load_factor()= " << c.max_load_factor() << endl;
		cout << "unordered_multiset.max_bucket_count()= " << c.max_bucket_count() << endl;
		for (unsigned i = 0; i < 20; ++i) {
			cout << "bucket #" << i << " has " << c.bucket_size(i) << " elements.\n";
		}

		string target = get_a_target_string();
		{
			timeStart = clock();
			auto pItem = find(c.begin(), c.end(), target);	//比 c.find(...) 慢很多	
			cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;
			if (pItem != c.end())
				cout << "found, " << *pItem << endl;
			else
				cout << "not found! " << endl;
		}

		{
			timeStart = clock();
			auto pItem = c.find(target);		//比 std::find(...) 快很多							
			cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
			if (pItem != c.end())
				cout << "found, " << *pItem << endl;
			else
				cout << "not found! " << endl;
		}
	}
}
/*********************8.测试std::unordered_multiset()|   end ******************/


/*********************9.测试std::unordered_multimap()|   begin ******************/
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj09
{
	void test_unordered_multimap(long& value)
	{
		cout << "\ntest_unordered_multimap().......... \n";

		unordered_multimap<long, string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try {
				snprintf(buf, 10, "%d", rand());
				//multimap 不可使用 [] 進行 insertion 
				c.insert(pair<long, string>(i, buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "unordered_multimap.size()= " << c.size() << endl;
		cout << "unordered_multimap.max_size()= " << c.max_size() << endl;	//357913941	

		long target = get_a_target_long();
		timeStart = clock();
		auto pItem = c.find(target);
		cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
		if (pItem != c.end())
			cout << "found, value=" << (*pItem).second << endl;
		else
			cout << "not found! " << endl;
	}
}
/*********************9.测试std::unordered_multimap()|   end ******************/


//---------------------------------------------------
#include <set>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj13
{
	void test_set(long& value)
	{
		cout << "\ntest_set().......... \n";

		set<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try {
				snprintf(buf, 10, "%d", rand());
				c.insert(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "set.size()= " << c.size() << endl;
		cout << "set.max_size()= " << c.max_size() << endl;	   //214748364

		string target = get_a_target_string();
		{
			timeStart = clock();
			auto pItem = find(c.begin(), c.end(), target);	//比 c.find(...) 慢很多	
			cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;
			if (pItem != c.end())
				cout << "found, " << *pItem << endl;
			else
				cout << "not found! " << endl;
		}

		{
			timeStart = clock();
			auto pItem = c.find(target);		//比 std::find(...) 快很多							
			cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
			if (pItem != c.end())
				cout << "found, " << *pItem << endl;
			else
				cout << "not found! " << endl;
		}
	}
}
//---------------------------------------------------
#include <map>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj14
{
	void test_map(long& value)
	{
		cout << "\ntest_map().......... \n";

		map<long, string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try {
				snprintf(buf, 10, "%d", rand());
				c[i] = string(buf);
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "map.size()= " << c.size() << endl;
		cout << "map.max_size()= " << c.max_size() << endl;		//178956970

		long target = get_a_target_long();
		timeStart = clock();
		auto pItem = c.find(target);
		cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
		if (pItem != c.end())
			cout << "found, value=" << (*pItem).second << endl;
		else
			cout << "not found! " << endl;

		c.clear();
	}
}
//---------------------------------------------------
#include <unordered_set>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj15
{
	void test_unordered_set(long& value)
	{
		cout << "\ntest_unordered_set().......... \n";

		unordered_set<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try {
				snprintf(buf, 10, "%d", rand());
				c.insert(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "unordered_set.size()= " << c.size() << endl;
		cout << "unordered_set.max_size()= " << c.max_size() << endl;  //357913941
		cout << "unordered_set.bucket_count()= " << c.bucket_count() << endl;
		cout << "unordered_set.load_factor()= " << c.load_factor() << endl;
		cout << "unordered_set.max_load_factor()= " << c.max_load_factor() << endl;
		cout << "unordered_set.max_bucket_count()= " << c.max_bucket_count() << endl;
		for (unsigned i = 0; i < 20; ++i) {
			cout << "bucket #" << i << " has " << c.bucket_size(i) << " elements.\n";
		}

		string target = get_a_target_string();
		{
			timeStart = clock();
			auto pItem = find(c.begin(), c.end(), target);	//比 c.find(...) 慢很多	
			cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;
			if (pItem != c.end())
				cout << "found, " << *pItem << endl;
			else
				cout << "not found! " << endl;
		}

		{
			timeStart = clock();
			auto pItem = c.find(target);		//比 std::find(...) 快很多							
			cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
			if (pItem != c.end())
				cout << "found, " << *pItem << endl;
			else
				cout << "not found! " << endl;
		}
	}
}
//---------------------------------------------------
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj16
{
	void test_unordered_map(long& value)
	{
		cout << "\ntest_unordered_map().......... \n";

		unordered_map<long, string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try {
				snprintf(buf, 10, "%d", rand());
				c[i] = string(buf);
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "unordered_map.size()= " << c.size() << endl;	//357913941
		cout << "unordered_map.max_size()= " << c.max_size() << endl;

		long target = get_a_target_long();
		timeStart = clock();
		//! auto pItem = find(c.begin(), c.end(), target);	//map 不適用 std::find() 			
		auto pItem = c.find(target);

		cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
		if (pItem != c.end())
			cout << "found, value=" << (*pItem).second << endl;
		else
			cout << "not found! " << endl;
	}
}
//---------------------------------------------------
#include <stack>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj17
{
	void test_stack(long& value)
	{
		cout << "\ntest_stack().......... \n";

		stack<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try {
				snprintf(buf, 10, "%d", rand());
				c.push(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "stack.size()= " << c.size() << endl;
		cout << "stack.top()= " << c.top() << endl;
		c.pop();
		cout << "stack.size()= " << c.size() << endl;
		cout << "stack.top()= " << c.top() << endl;


		{
			stack<string, list<string>> c;		//以 list 為底層 
			for (long i = 0; i < 10; ++i) {
				snprintf(buf, 10, "%d", rand());
				c.push(string(buf));
			}
			cout << "stack.size()= " << c.size() << endl;
			cout << "stack.top()= " << c.top() << endl;
			c.pop();
			cout << "stack.size()= " << c.size() << endl;
			cout << "stack.top()= " << c.top() << endl;
		}

		{
			stack<string, vector<string>> c;	//以 vector 為底層 
			for (long i = 0; i < 10; ++i) {
				snprintf(buf, 10, "%d", rand());
				c.push(string(buf));
			}
			cout << "stack.size()= " << c.size() << endl;
			cout << "stack.top()= " << c.top() << endl;
			c.pop();
			cout << "stack.size()= " << c.size() << endl;
			cout << "stack.top()= " << c.top() << endl;
		}

		{
			stack<string, set<string>> c;	//以 set 為底層 
			/*!
				for(long i=0; i< 10; ++i) {
						snprintf(buf, 10, "%d", rand());
						c.push(string(buf));
				}
				cout << "stack.size()= " << c.size() << endl;
				cout << "stack.top()= " << c.top() << endl;
				c.pop();
				cout << "stack.size()= " << c.size() << endl;
				cout << "stack.top()= " << c.top() << endl;

			//[Error] 'class std::set<std::basic_string<char> >' has no member named 'push_back'
			//[Error] 'class std::set<std::basic_string<char> >' has no member named 'back'
			//[Error] 'class std::set<std::basic_string<char> >' has no member named 'pop_back'
			*/
		}

		//!stack<string, map(string>> c5;	////以 map 為底層, [Error] template argument 2 is invalid
		//!stack<string>::iterator ite1;  	//[Error] 'iterator' is not a member of 'std::stack<std::basic_string<char> >'

	}
}
//---------------------------------------------------
#include <queue>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj18
{
	void test_queue(long& value)
	{
		cout << "\ntest_queue().......... \n";

		queue<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < value; ++i)
		{
			try {
				snprintf(buf, 10, "%d", rand());
				c.push(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "queue.size()= " << c.size() << endl;
		cout << "queue.front()= " << c.front() << endl;
		cout << "queue.back()= " << c.back() << endl;
		c.pop();
		cout << "queue.size()= " << c.size() << endl;
		cout << "queue.front()= " << c.front() << endl;
		cout << "queue.back()= " << c.back() << endl;


		{
			queue<string, list<string>> c;		//以 list 為底層 
			for (long i = 0; i < 10; ++i) {
				snprintf(buf, 10, "%d", rand());
				c.push(string(buf));
			}
			cout << "queue.size()= " << c.size() << endl;
			cout << "queue.front()= " << c.front() << endl;
			cout << "queue.back()= " << c.back() << endl;
			c.pop();
			cout << "queue.size()= " << c.size() << endl;
			cout << "queue.front()= " << c.front() << endl;
			cout << "queue.back()= " << c.back() << endl;
		}

		{
			queue<string, vector<string>> c;	//以 vector 為底層 
			for (long i = 0; i < 10; ++i) {
				snprintf(buf, 10, "%d", rand());
				c.push(string(buf));
			}
			cout << "queue.size()= " << c.size() << endl;
			cout << "queue.front()= " << c.front() << endl;
			cout << "queue.back()= " << c.back() << endl;
			//!c.pop();  //[Error] 'class std::vector<std::basic_string<char> >' has no member named 'pop_front'
			cout << "queue.size()= " << c.size() << endl;
			cout << "queue.front()= " << c.front() << endl;
			cout << "queue.back()= " << c.back() << endl;
		}

		{
			queue<string, set<string>> c;		//以 set 為底層 
			/*!
				for(long i=0; i< 10; ++i) {
						snprintf(buf, 10, "%d", rand());
						c.push(string(buf));
				}
				cout << "queue.size()= " << c.size() << endl;
				cout << "queue.front()= " << c.front() << endl;
				cout << "queue.back()= " << c.back() << endl;
				c.pop();
				cout << "queue.size()= " << c.size() << endl;
				cout << "queue.front()= " << c.front() << endl;
				cout << "queue.back()= " << c.back() << endl;
			//[Error] 'class std::set<std::basic_string<char> >' has no member named 'push_back'
			//[Error] 'class std::set<std::basic_string<char> >' has no member named 'front'
			//[Error] 'class std::set<std::basic_string<char> >' has no member named 'pop_front'
			*/
		}

		//! queue<string, map<string>> c5;	//以 map 為底層, [Error] template argument 2 is invalid
		//! queue<string>::iterator ite1;  	//[Error] 'iterator' is not a member of 'std::queue<std::basic_string<char> >'	
	}
}




/*********************	测试各种容器|   begin ******************/
#include <cstdlib> //rand() and RAND_MAX
namespace jjxx
{
	void test_containers()
	{
		int choice;
		long value;

		srand(time(NULL));

		cout << "\n\ntest_containers()......... \n";
		cout << "select: \n";
		cout << "       (1)array (2)vector (3)list (4)forward_list (5)deque (6)multiset \n";
		cout << "       (7)multimap (8)unordered_multiset (9)unordered_multimap (10)slist \n";
		cout << "       (11)hash_multiset (12)hash_multimap (13)set (14)map (15)unordered_set \n";
		cout << "       (16)unordered_map (17)stack (18)queue \n";
		cout << " (2),(3),(5),(6),(8) will test also moveable elements. \n";
		cin >> choice;
		if (choice != 1) { 	//1 ==> array, use ASIZE
			cout << "how many elements: ";
			cin >> value;
		}

		switch (choice)
		{
		case 1: 	jj01::test_array();
			break;
		case 2: 	jj02::test_vector(value);
			break;
		case 3: 	jj03::test_list(value);
			break;
		case 4: 	jj04::test_forward_list(value);
			break;
		case 5: 	jj05::test_deque(value);
			break;
		case 6: 	jj06::test_multiset(value);
			break;
		case 7: 	jj07::test_multimap(value);
			break;
		case 8: 	jj08::test_unordered_multiset(value);
			break;
		case 9: 	jj09::test_unordered_multimap(value);
			break;
		//case 10: 	jj10::test_slist(value);
		//	break;
		//case 11: 	jj11::test_hash_multiset(value);
		//	break;
		//case 12: 	jj12::test_hash_multimap(value);
		//	break;
		case 13: 	jj13::test_set(value);
			break;
		case 14: 	jj14::test_map(value);
			break;
		case 15: 	jj15::test_unordered_set(value);
			break;
		case 16: 	jj16::test_unordered_map(value);
			break;
		case 17: 	jj17::test_stack(value);
			break;
		case 18: 	jj18::test_queue(value);
			break;
		default:
			break;
		}
	}
}

/*********************	测试各种容器|   end ******************/

int main(void)
{
	//! 测试各种容器
	jjxx::test_containers();

	system("pause");
	return 0;
}