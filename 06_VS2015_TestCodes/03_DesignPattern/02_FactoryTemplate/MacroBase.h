#ifndef __MACRO_BASE_H__
#define __MACRO_BASE_H__

#define __string_join( X, Y ) __string_do_join( X, Y )
#define __string_do_join( X, Y ) __string_do_join2( X, Y )
#define __string_do_join2( X, Y ) X##Y

//! 模板参相关宏
#define __typename_templatetype_pre_comma__(n), typename T##n
#define __typename_templatetype_comma__(n) typename T##n,
#define __typename_templatetype__(n) typename T##n

#define __templatetype_comma__(n) T##n,
#define __templatetype__(n) T##n

#define __functype_comma__(n) T##n,
#define __functype__(n) T##n

#define __template_funcin_param_comma__(n) ,T##n param##n
#define __template_funcin_param_back_comma__(n) T##n param##n,
#define __template_funcin_param__(n) T##n param##n

#define __funcin_param_variant_comma__(n) param##n,
#define __funcin_param_variant__(n)param##n

#endif//__MACRO_BASE_H_