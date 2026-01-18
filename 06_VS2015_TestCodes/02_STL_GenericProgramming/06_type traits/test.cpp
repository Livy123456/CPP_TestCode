


#include <iostream>
#include <list>
using namespace std;

//! 1. 测试type traits
namespace jj01
{
	template <typename T>
	void type_traits_output(const T& x)
	{
		cout << "\ntype traits for type: " << typeid(T).name() << endl;
		
		cout << "is_void\t" << is_void<T>::value << endl;
		cout << "is_integral\t" << is_integral<T>::value << endl;
		cout << "is_floating_point\t" << is_floating_point<T>::value << endl;
		cout << "is_arithmetic\t" << is_arithmetic<T>::value << endl;
		cout << "is_signed\t" << is_signed<T>::value << endl;
		cout << "is_unsigned\t" << is_unsigned<T>::value << endl;
		cout << "is_const\t" << is_const<T>::value << endl;
		cout << "is_volatile\t" << is_volatile<T>::value << endl;
		cout << "is_class\t" << is_class<T>::value << endl;
		cout << "is_function\t" << is_function<T>::value << endl;
		cout << "is_reference\t" << is_reference<T>::value << endl;
		cout << "is_lvalue_reference\t" << is_lvalue_reference<T>::value << endl;
		cout << "is_rvalue_reference\t" << is_rvalue_reference<T>::value << endl;
		cout << "is_pointer\t" << is_pointer<T>::value << endl;
		cout << "is_member_pointer\t" << is_member_pointer<T>::value << endl;
		cout << "is_member_object_pointer\t" << is_member_object_pointer<T>::value << endl;
		cout << "is_member_function_pointer\t" << is_member_function_pointer<T>::value << endl;
		cout << "is_fundamental\t" << is_fundamental<T>::value << endl;
		cout << "is_scalar\t" << is_scalar<T>::value << endl;
		cout << "is_object\t" << is_object<T>::value << endl;
		cout << "is_compound\t" << is_compound<T>::value << endl;
		cout << "has_virtual_destructor\t" << has_virtual_destructor<T>::value << endl;
		cout << "is_polymorphic\t" << is_polymorphic<T>::value << endl;

	}

	//! 测试string
	void Test01()
	{
		type_traits_output(std::string("hello"));
	}

	//! 测试自定义类
	class Foo
	{
	private:
		int d1, d2;
	};
	void Test02()
	{
		type_traits_output(Foo());
	}

	class Goo
	{
	public:
		virtual ~Goo() {}
	private:
		int d1, d2;
	};
	void Test03()
	{
		type_traits_output(Goo());
	}

	class Zoo
	{
	public:
		Zoo(int i1, int i2) :d1(i1), d2(i2) {}
		Zoo(const Zoo&) = delete;
		Zoo(Zoo&&) = default;
		Zoo& operator=(const Zoo&) = default;
		Zoo& operator=(const Zoo&&) = delete;
		virtual ~Zoo(){}

	private:
		int d1, d2;
	};
	void Test04()
	{
		type_traits_output(Zoo(1, 2));
		type_traits_output(list<int>());
	}
}



int main(void)
{
	//jj01::Test02();
	//jj01::Test03();
	jj01::Test04();

	getchar();
	return 0;
}