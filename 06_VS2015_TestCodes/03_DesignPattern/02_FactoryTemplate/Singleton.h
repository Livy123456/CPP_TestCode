#ifndef _SINGLETON_H
#define _SINGLETON_H

//#include "Types.h"

//#include <iostream>

template <typename T>
class CSingleton
{
protected:
	CSingleton() 
	{ 
		//std::cout << "singleton constructor\n"; 
	}
	CSingleton(const CSingleton& singleton);
	CSingleton& operator=(const CSingleton& singleton);
	~CSingleton() 
	{
		//std::cout << "singleton destructor\n"; 
	}

public:
	//! 获取单例实例指针
	static T* GetInstance()
	{
		if (nullptr == s_pInstance)
		{
			//Autolock
			if (nullptr == s_pInstance)
			{
				s_pInstance = new T();
			}
		}
		m_Deleter.do_nothing();
		return s_pInstance;
	}

	//! 尝试获取单例实例指针，在释放的时候，已经释放了就不要创建实例了
	//! return 单例实例指针
	static T* TryGetInstance()
	{
		return s_pInstance;
	}

	//! 删除单例实例
	static void ReleaseInstance()
	{
		if (nullptr != s_pInstance)
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}
	}

private:
	//! 负责单例的资源初始化和释放
	class CDeleter
	{
	public:
		CDeleter()	//< 不管有没有人用单例实例，都会先创建出来
		{
			CSingleton<T>::GetInstance();
		}
		~CDeleter()
		{
			CSingleton<T>::ReleaseInstance();
		}
		inline void do_nothing() const {};
	};

private:
	//! 单例实例指针
	static T* s_pInstance;
	//! 单例删除器
	static CDeleter m_Deleter;
};

template <typename T>
T* CSingleton<T>::s_pInstance = nullptr;

template <typename T>
typename CSingleton<T>::CDeleter CSingleton<T>::m_Deleter; //< 程序一运行就先调用自己的构造函数，对单例进行初始化

#endif	//< _SINGLETON_H