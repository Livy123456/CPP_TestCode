# const在类成员函数右侧

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/45f6454de50e4f7582ee286ad1e42e8a.png)
上图来自侯捷的面相对象高级开发视频课程：

勾选意思是可以调用对应的成员函数。
当成员函数的const版本和non-const版本同时存在，则const object只能调用const版本，non-const object只能调用non-const版本。



- 该函数不会修改被隐式的访问的对象

```cpp
#include <iostream>
using namespace std;

class Person
{
public:
	void Show() const		//<	const成员函数，不会修改被隐式的访问的对象的数据
	{
		//m_a = 10;		//<	错误，无法被修改
		cout << m_a << endl;
	}

private:
	int m_a;
};

int main(void)
{

	cin.get();
	return 0;
}
```
## 1. const调用限制

1. 相同成员函数的const和non-const版本同时存在，const object只会（只能）调用const版本，non-const object只会（只能）调用non-const版本。
2. non-const成员函数可调用const成员函数，反之则不行，会引发：error C2662:cannot convert 'this' pointer from 'const class X' to 'class X&'. Conversion loses quali
3. const对象只能调用const成员函数，不能调用non-const成员函数。non-const对象则两种成员函数都能调用

## 2. const成员函数返回*this

返回的是常量对象，不能改变对象内部数据

## 3. const是作为函数的签名

const关键字：如果两个函数同名、参数也相同，只是一个又const，一个没有，这是属于两个函数，没有歧义。const也算作签名的一部分。

# 类成员声明为const数据成员
> 注：
> 1. c++11之前，类的数据成员为非静态const时，需通过初始化列表初始化；
> 2. c++11 支持类的数据成员为非静态const时，可以直接在声明的时候初始化，例如const int m_a = 20;
```cpp
#include <iostream>
using namespace std;

class CPerson
{
public:
	CPerson(int a)
		:m_a(a)		//<	非静态const数据成员：必须在执行到构造函数体之前，即创建对象时进行初始化。这里只能使用初始化列表
	{
		//m_a = a;	//<	非静态const数据成员不能直接赋值来初始化
	}

	int GetCount() const
	{
		return m_a;
	}

private:
	const int m_a;	//<	非静态const变量
};

int main(void)		//< c++中形参void和空着等效
{
	CPerson per(5);
	cout << per.GetCount();

	std::cin.get();
	return 0;
}
```



> 参考书籍：C++ Primer Plus（第六版）——12.7.1队列类 ——3. 类方法


# Const声明迭代器
STL迭代器系以指针为根据塑模出来，所以迭代器的作用就像个T*

```cpp
//! 1. 声明迭代器为const就想声明指针为const一样(即声明一个T* const指针)
	std::vector<int> vec;
	const std::vector<int>::iterator iter = vec.begin();	//< iter的作用像个T* const
	*iter = 10;		//< 正确，改变iter所指内容
	//++iter;		//<	错误，iter是const

	std::vector<int>::const_iterator cIter = vec.begin();	//< cIter的作用像个const T*
	//*cIter = 10;		//< 错误！*cIter是const
	++cIter;			//< 没问题，改变cIter。
```

> 参考——effective c++（第三版）—— 条款3 尽可能使用const

# 成员函数相互调用，避免代码重复
```cpp
class MyString
{
public:
	MyString(const std::string& str)
		:m_str(str){}

	//! 当const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本可避免代码重复。
	const char& operator[](std::size_t nPos) const
	{
		return m_str[nPos];
	}

	//! 只能使用operator[] 调用 const operator[]，因为从逻辑上const operator[]是不会修改对象内部数据的；
	//! 如果相反调用，则违背了const成员函数不能修改对象内部数据的逻辑，
	//! 所以只能operator[] 调用 const operator[]
	char& operator[](std::size_t nPos)
	{
		return (const_cast<char&>(static_cast<const MyString&>(*this)[nPos]));
	}

private:
	std::string m_str;
};

void Test02()
{
	MyString mystr("hello");
	cout << mystr[0] << endl;
}
```
# bitwise constness 和 logical constness
> 参考effective c++ 条款3 尽可能使用const （第三版）

bitwise(又称physical constness) 和 logical constness一直是个哲学思辨，历来两方拥护者都有争议

- bitwise：
成员函数只有在不更改对象之任何成员变量(static除外)时才可以说是const。也就是说它不更改对象内的任何一个bit。这种论点的好处是很容易侦测违反点：编译器只需寻找成员变量的赋值动作即可。bitwise constness正是c++对常量性(constness)的定义，因此const成员函数不可以更改对象内任何non-static成员变量。
- logical：
但有些具备const性质的成员函数却能通过bitwise测试。具体如下：
成员变量维护一个指针，成员函数声明为const，但返回一个引用指向对象内部，成员函数实现代码并不更改指针。编译器则正常通过编译。

```cpp
class CTextBlock
{
public:
	char& operator[](std::size_t pos) const	//< bitwise const 声明，但其实不适当
	{return pText[pos];}
private:
	char* pText;
}

//! 语法上没有错，但你终究改变了成员变量所指向的值。
const CTextBlock cctb("Hello");	//< 声明一个常量对象。
char* pc = &cctb[0];			//< 调用const operator[]取得一个指针，指向cctb的数据
*pc = 'J';					//< cctb现在有了"Jello"这样的内容
```

这种情况导出所谓的logical constness。
> 总结logical constness观点：一个const成员函数可以修改它所处理的对象内的某些bits，但只有在客户端侦测不出的情况下才得如此。

前面的那个示例客户端是可以修改，也就是可以侦测出的，所以不允许，但下面这个就是客户端是侦测不出的。

```cpp
class CTextBlock
{
public:
	std::size_t length() const;
private:
	char pText;
	mutable std::size_t textLength;		//< 这些成员变量可能总是会被更改，即使在
	mutable bool lengthIsValid;			//<	const 成员函数内。
};
std::size_t CTextBlock::length() const
{
	if(!lengthIsValid)
	{
		//! 正确，因为加了关键字mutable，可释放non-static成员变量的bitwise constness约束。
		textLength = std::strlen(pText);	
		lengthIsValid = true;
	}
	return textLength;
}
```


# const引用传递替代值传递

## 1. 不适用情况

- 内置类型
因为引用本质也是用指针实现的，对于内置类型值传递比引用传递效率高

- STL迭代器和函数对象
因为习惯上它们都被设计为值传递。迭代器和函数对象的实践者有责任看看它们是否高效且不受切割问题的影响


> effective c++ 条款20 尽量以pass-by-reference-to-const替代pass-by-value