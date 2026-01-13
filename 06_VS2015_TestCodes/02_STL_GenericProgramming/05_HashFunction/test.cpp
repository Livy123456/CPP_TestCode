

//! 一个万用的Hash Function
//! 从侯捷的STL标准库和泛型编程里面参考的代码
#include <iostream>
#include <unordered_set>
using namespace std;

//! fraom boost (functional/hash):
template <typename T>
inline void hash_combine(size_t& seed, const T& val)
{
	seed ^= hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}


//! auxiliary generic functions to create a hash value using a seed
template <typename T>
inline void hash_val(size_t& seed, const T& val)
{
	hash_combine(seed, val);
}

template <typename T, typename... Types>
inline void hash_val(size_t& seed, const T& val, const Types&... args)
{
	hash_combine(seed, val);
	hash_val(seed, args...);
}

//! auxiliary generic function
template <typename... Types>
inline size_t hash_val(const Types&... args)
{
	size_t seed = 0;
	hash_val(seed, args...);
	return seed;
}

class Customer
{
public:
	Customer(const std::string& strFirstName,
		const std::string& strLastName,
		const int number)
		:fname(strFirstName)
		, lname(strLastName)
		, no(number)
	{}

	bool operator==(const Customer& c) const
	{
		return (c.fname == this->fname &&
			c.lname == this->lname &&
			c.no == this->no);
	}

	std::string fname;
	std::string lname;
	int no;
};



class CustomerHash
{
public:
	size_t operator()(const Customer& c) const
	{
		return hash_val(c.fname, c.lname, c.no);	//< 调用万用的hash函数
	}	
};


int main(void)
{
	unordered_set<Customer, CustomerHash> set3;
	set3.insert(Customer("Ace", "Hou", 1L));
	set3.insert(Customer("Sabri", "Hou", 2L));
	set3.insert(Customer("Stacy", "Chen", 3L));
	set3.insert(Customer("Mike", "Tseng", 4L));
	set3.insert(Customer("Paili", "Chen", 5L));
	set3.insert(Customer("Light", "Shiau", 6L));
	set3.insert(Customer("Shally", "Hwung", 7L));
	cout << "set3 current bucket_count: " << set3.bucket_count() << endl; // 8


	//! 打印下hash函数算出来的值，是个很大的值，分别再除以篮子个数，取余数，来看看落在哪个篮子
	CustomerHash hh;
	cout << "bucket position of Ace = " << hh(Customer("Ace", "Hou", 1L)) % 8 << endl;	//4
	cout << "bucket position of Sabri = " << hh(Customer("Sabri", "Hou", 2L)) % 8 << endl;	//4
	cout << "bucket position of Stacy = " << hh(Customer("Stacy", "Chen", 3L)) % 8 << endl;	//1
	cout << "bucket position of Mike = " << hh(Customer("Mike", "Tseng", 4L)) % 8 << endl;	//2
	cout << "bucket position of Paili = " << hh(Customer("Paili", "Chen", 5L)) % 8 << endl;	//6
	cout << "bucket position of Light = " << hh(Customer("Light", "Shiau", 6L)) % 8 << endl;	//1
	cout << "bucket position of Shally = " << hh(Customer("Shally", "Hwung", 7L)) % 8 << endl;	//1



	//bucket #0 has 0 elements.
	//	bucket #1 has 3 elements.
	//	bucket #2 has 1 elements.
	//	bucket #3 has 0 elements.
	//	bucket #4 has 2 elements.
	//	bucket #5 has 0 elements.
	//	bucket #6 has 1 elements.
	//	bucket #7 has 0 elements.
	for (unsigned i = 0; i < set3.bucket_count(); ++i)
	{
		cout << "bucket #" << i << " has " << set3.bucket_size(i) << " elements.\n";
	}


	getchar();
	return 0;
}