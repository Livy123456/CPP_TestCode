
#include "Singleton.h"
#include "MacroBase.h"

#include <vector>
#include <map>

//! （1）预处理阶段，针对构建对象的参数个数分别展开，形成一套单独模板工厂，CObjectFactory0、CObjectFactoryl等
//! （2）编译阶段，根据实际调用情况，以及调用所涉及的参数个数，再实例化具体的模板。例如下，是CObjectFactory2有两个参数，则实例化2个参数那个模板对象工厂
//! const bool bRegistered = CObjectFactory2<IPerson, std::string, const int, const std::string&>::GetInstance()->Register("studentCreator", PersonObjCreator);

//! CObjectFactory0
#define FACTORY_NUMBER 0
#define FACTORY_CLASS_TYPES
#define FACTORY_TYPES_COMMA
#define FACTORY_TYPES_PRE_COMMA
#define FACTORY_TYPES_ARGS
#define FACTORY_ARGS
#include "ObjectFactoryTemplate.h"	
#undef FACTORY_NUMBER
#undef FACTORY_CLASS_TYPES
#undef FACTORY_TYPES_COMMA
#undef FACTORY_TYPES_PRE_COMMA
#undef FACTORY_TYPES_ARGS
#undef FACTORY_ARGS


//CObjectFactoryl
#define FACTORY_NUMBER 1
#define FACTORY_CLASS_TYPES typename T1,
#define FACTORY_TYPES_COMMA T1
#define FACTORY_TYPES_PRE_COMMA , T1
#define FACTORY_TYPES_ARGS , T1 al
#define FACTORY_ARGS a1
#include "ObjectFactoryTemplate.h"
#undef FACTORY_NUMBER
#undef FACTORY_CLASS_TYPES
#undef FACTORY_TYPES_COMMA
#undef FACTORY_TYPES_PRE_COMMA
#undef FACTORY_TYPES_ARGS
#undef FACTORY_ARGS
#undef FACTORY_SINGLETON	//< 取消头文件ObjectFactoryTemplate定义的宏

//CObjectFactory2
#define FACTORY_NUMBER 2
#define FACTORY_CLASS_TYPES typename T1, typename T2,
#define FACTORY_TYPES_COMMA T1,T2
#define FACTORY_TYPES_PRE_COMMA ,T1,T2
#define FACTORY_TYPES_ARGS ,T1 al,T2 a2
#define FACTORY_ARGS al,a2
#include "ObjectFactoryTemplate.h"
#undef FACTORY_NUMBER
#undef FACTORY_CLASS_TYPES
#undef FACTORY_TYPES_COMMA
#undef FACTORY_TYPES_PRE_COMMA
#undef FACTORY_TYPES_ARGS
#undef FACTORY_ARGS
#undef FACTORY_SINGLETON


//CObjectFactory3
#define FACTORY_NUMBER 3
#define FACTORY_CLASS_TYPES typename T1, typename T2, typename T3,
#define FACTORY_TYPES_COMMA T1,T2,T3
#define FACTORY_TYPES_PRE_COMMA ,T1,T2,T3
#define FACTORY_TYPES_ARGS ,T1 al,T2 a2,T3 a3
#define FACTORY_ARGS al,a2,a3
#include "ObjectFactoryTemplate.h"
#undef FACTORY_NUMBER
#undef FACTORY_CLASS_TYPES
#undef FACTORY_TYPES_COMMA
#undef FACTORY_TYPES_PRE_COMMA
#undef FACTORY_TYPES_ARGS
#undef FACTORY_ARGS
#undef FACTORY_SINGLETON

//CObjectFactory4
#define FACTORY_NUMBER 4
#define FACTORY_CLASS_TYPES typename T1,typename T2,typename T3, typename T4,
#define FACTORY_TYPES_COMMA T1,T2,T3,T4
#define FACTORY_TYPES_PRE_COMMA ,T1,T2,T3,T4
#define FACTORY_TYPES_ARGS ,T1 a1,T2 a2,T3 a3,T4 a4
#define FACTORY_ARGS a1,a2,a3,a4
#include "ObjectFactoryTemplate.h"
#undef FACTORY_NUMBER
#undef FACTORY_CLASS_TYPES
#undef FACTORY_TYPES_COMMA
#undef FACTORY_TYPES_PRE_COMMA
#undef FACTORY_TYPES_ARGS
#undef FACTORY_ARGS
#undef FACTORY_SINGLETON


//CObjectFactory5
#define FACTORY_NUMBER 5
#define FACTORY_CLASS_TYPES typename T1, typename T2, typename T3, typename T4, typename T5,
#define FACTORY_TYPES_COMMA T1,T2,T3,T4,T5
#define FACTORY_TYPES_PRE_COMMA ,T1,T2,T3,T4,T5
#define FACTORY_TYPES_ARGS ,T1 al,T2 a2,T3 a3,T4 a4,T5 a5
#define FACTORY_ARGS al,a2,a3,a4,a5
#include "ObjectFactoryTemplate.h"
#undef FACTORY_NUMBER
#undef FACTORY_CLASS_TYPES
#undef FACTORY_TYPES_COMMA
#undef FACTORY_TYPES_PRE_COMMA
#undef FACTORY_TYPES_ARGS
#undef FACTORY_ARGS
#undef FACTORY_SINGLETON


//CObjectFactory6
#define FACTORY_NUMBER 6
#define FACTORY_CLASS_TYPES typename T1,typename T2, typename T3, typename T4, typename T5, typename T6,
#define FACTORY_TYPES_COMMA T1,T2,T3,T4,T5,T6
#define FACTORY_TYPES_PRE_COMMA ,T1,T2,T3,T4,T5,T6
#define FACTORY_TYPES_ARGS ,T1 al,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6
#define FACTORY_ARGS al,a2,a3,a4,a5,a6
#include "ObjectFactoryTemplate.h"
#undef FACTORY_NUMBER
#undef FACTORY_CLASS_TYPES
#undef FACTORY_TYPES_COMMA
#undef FACTORY_TYPES_PRE_COMMA
#undef FACTORY_TYPES_ARGS
#undef FACTORY_ARGS
#undef FACTORY_SINGLETON