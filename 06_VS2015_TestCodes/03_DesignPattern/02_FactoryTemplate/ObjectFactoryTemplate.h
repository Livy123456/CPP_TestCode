#define FACTORY_FACTORY __string_join(CObjectFactory,FACTORY_NUMBER)
#define FACTORY_SINGLETON CSingleton< FACTORY_FACTORY<AbstractProduct,IdentifierType FACTORY_TYPES_PRE_COMMA,ComFunc,ProductCreator> >

//! 注：该工厂创建出来的对象后需要自己释放
/// \class CObjectFactory
///\brief对象工厂模板
template
<
	class AbstractProduct,
		typename IdentifierType,
		FACTORY_CLASS_TYPES
		typename ComFunc = std::less <IdentifierType>,
		typename ProductCreator = AbstractProduct* (*)(FACTORY_TYPES_COMMA)
>
class FACTORY_FACTORY:public FACTORY_SINGLETON
{
	friend class FACTORY_SINGLETON;	//< 因为基类单例类会创建子类对象，所以需要访问子类的私有构造

	/// 创建器map类型
	typedef std::map< IdentifierType, ProductCreator, ComFunc > IdToProductMap;

private:
	FACTORY_FACTORY()
	{
	}

public:
	~FACTORY_FACTORY()
	{
		m_creatorMap.clear();
	}
public:
	//! 注册一个创建对象的工厂方法
	//! param[in] id		创建器标示符
	//! param[in] creator	创建器
	//! return true			注册成功
	//!	return false		注册失败
	bool Register(const IdentifierType& id, ProductCreator creator)
	{
		typename IdToProductMap::iterator iter = m_creatorMap.find(id);

			//!	insert会传递回来一个pair，其中包含一个适代器和一个boo1
		if(iter != m_creatorMap.end())
		{
			m_creatorMap.erase(iter);
		}
		return m_creatorMap.insert((typename IdToProductMap::value_type(id, creator))).second;

	}
	//! 主销一个创建对象的工厂方法
	//! param[in] id	创建器ID
	//! return true		注销成功
	//! return false	注销失败
	bool Unregister(const IdentifierType& id)
	{
		return (1 == m_creatorMap.erase(id));
	}

	//! 使用制定创建器创建一个对象
	//! param[in] id	创建器ID
	//! return NULL		创建失败
	//! return 对象指针	创建成功
	AbstractProduct* CreateObject(const IdentifierType& id FACTORY_TYPES_ARGS)
	{
		typename IdToProductMap::const_iterator iter = m_creatorMap.find(id);
		if(iter != m_creatorMap.end())
		{
			return (iter->second) (FACTORY_ARGS);
		}
		return 0;
	}

private:

	//! 对象创建器
	IdToProductMap m_creatorMap;
};
