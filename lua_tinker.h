// lua_tinker.h
//
// LuaTinker - Simple and light C++ wrapper for Lua.
//
// Copyright (c) 2005-2007 Kwon-il Lee (zupet@hitel.net)
//
// please check Licence.txt file for licence and legal issues.

#if !defined(_LUA_TINKER_H_)
#define _LUA_TINKER_H_


#if (defined(WIN64) || defined(_WIN64))
#define ZCE_WIN64 1
#endif //

#if (defined(WIN32) || defined(_WIN32)) && !(defined(WIN64) || defined(_WIN64))
#define ZCE_WIN32 1
#endif


#if defined ZCE_WIN32
// vc71(2003):
#if defined(_MSC_VER) && (_MSC_VER == 1310)
#  define ZCE_PLATFORM_TOOLSET "win32-v71"
// vc80(2005):
#elif defined(_MSC_VER) && (_MSC_VER == 1400)
#  define ZCE_PLATFORM_TOOLSET "win32-v80"
// vc90(VS2008):
#elif defined(_MSC_VER) && (_MSC_VER == 1500)
#  define ZCE_PLATFORM_TOOLSET "win32-v90"
// vc10(VS2010):
#elif defined(_MSC_VER) && (_MSC_VER == 1600)
#  define ZCE_PLATFORM_TOOLSET "win32-v100"
// vc11(VS2012):
#elif defined(_MSC_VER) && (_MSC_VER == 1700)
#  define ZCE_PLATFORM_TOOLSET "win32-v110"
#elif defined(_MSC_VER) && (_MSC_VER == 1800)
#  define ZCE_PLATFORM_TOOLSET "win32-v120"
#endif
#elif defined ZCE_WIN64
// vc71(2003):
#if defined(_MSC_VER) && (_MSC_VER == 1310)
#  define ZCE_PLATFORM_TOOLSET "x64-v71"
// vc80(2005):
#elif defined(_MSC_VER) && (_MSC_VER == 1400)
#  define ZCE_PLATFORM_TOOLSET "x64-v80"
// vc90(VS2008):
#elif defined(_MSC_VER) && (_MSC_VER == 1500)
#  define ZCE_PLATFORM_TOOLSET "x64-v90"
// vc10(VS2010):
#elif defined(_MSC_VER) && (_MSC_VER == 1600)
#  define ZCE_PLATFORM_TOOLSET "x64-v100"
// vc11(VS2012):
#elif defined(_MSC_VER) && (_MSC_VER == 1700)
#  define ZCE_PLATFORM_TOOLSET "x64-v110"
#elif defined(_MSC_VER) && (_MSC_VER == 1800)
#  define ZCE_PLATFORM_TOOLSET "x64-v120"
#endif
#endif

//�����ڲ�����ͳһʹ��ZCE_PLAT_TOOLSET_CONF����꣬�򻯴�ҵı��빤������
#if defined _DEBUG || defined DEBUG
#  define ZCE_PLAT_TOOLSET_CONF ZCE_PLATFORM_TOOLSET"-Debug"
#else
#  define ZCE_PLAT_TOOLSET_CONF ZCE_PLATFORM_TOOLSET"-Release"
#endif


#if !defined LUA_LIB_LIBARY_NAME
#define LUA_LIB_LIBARY_NAME   "lualib.lib"
#endif


#pragma comment(lib, LUA_LIB_LIBARY_NAME )


#include <new>
#include <string.h>

namespace lua_tinker
{
// init LuaTinker
void    init(lua_State *L);

void    init_s64(lua_State *L);
void    init_u64(lua_State *L);

// string-buffer excution
void    dofile(lua_State *L, const char *filename);
void    dostring(lua_State *L, const char *buff);
void    dobuffer(lua_State *L, const char *buff, size_t sz);

// debug helpers
void    enum_stack(lua_State *L);
int     on_error(lua_State *L);
void    print_error(lua_State *L, const char *fmt, ...);

// dynamic type extention
struct lua_value
{
    virtual void to_lua(lua_State *L) = 0;
};

// type trait
template<typename T> struct class_name;
struct table;

template<bool C, typename A, typename B> struct if_ {};
template<typename A, typename B>        struct if_<true, A, B>
{
    typedef A type;
};
template<typename A, typename B>        struct if_<false, A, B>
{
    typedef B type;
};

template<typename A>
struct is_ptr
{
    static const bool value = false;
};
template<typename A>
struct is_ptr<A *>
{
    static const bool value = true;
};

template<typename A>
struct is_ref
{
    static const bool value = false;
};
template<typename A>
struct is_ref<A &>
{
    static const bool value = true;
};

template<typename A>
struct remove_const
{
    typedef A type;
};
template<typename A>
struct remove_const<const A>
{
    typedef A type;
};

template<typename A>
struct base_type
{
    typedef A type;
};
template<typename A>
struct base_type<A *>
{
    typedef A type;
};
template<typename A>
struct base_type<A &>
{
    typedef A type;
};

template<typename A>
struct class_type
{
    typedef typename remove_const<typename base_type<A>::type>::type type;
};

template<typename A>
struct is_obj
{
    static const bool value = true;
};
template<> struct is_obj<char>
{
    static const bool value = false;
};
template<> struct is_obj<unsigned char>
{
    static const bool value = false;
};
template<> struct is_obj<short>
{
    static const bool value = false;
};
template<> struct is_obj<unsigned short>
{
    static const bool value = false;
};
template<> struct is_obj<long>
{
    static const bool value = false;
};
template<> struct is_obj<unsigned long>
{
    static const bool value = false;
};
template<> struct is_obj<int>
{
    static const bool value = false;
};
template<> struct is_obj<unsigned int>
{
    static const bool value = false;
};
template<> struct is_obj<float>
{
    static const bool value = false;
};
template<> struct is_obj<double>
{
    static const bool value = false;
};
template<> struct is_obj<char *>
{
    static const bool value = false;
};
template<> struct is_obj<const char *>
{
    static const bool value = false;
};
template<> struct is_obj<bool>
{
    static const bool value = false;
};
template<> struct is_obj<lua_value *>
{
    static const bool value = false;
};
template<> struct is_obj<long long>
{
    static const bool value = false;
};
template<> struct is_obj<unsigned long long>
{
    static const bool value = false;
};
template<> struct is_obj<table>
{
    static const bool value = false;
};

/////////////////////////////////
enum { no = 1, yes = 2 };
typedef char (& no_type )[no];
typedef char (& yes_type)[yes];

struct int_conv_type
{
    int_conv_type(int);
};

no_type int_conv_tester (...);
yes_type int_conv_tester (int_conv_type);

no_type vfnd_ptr_tester (const volatile char *);
no_type vfnd_ptr_tester (const volatile short *);
no_type vfnd_ptr_tester (const volatile int *);
no_type vfnd_ptr_tester (const volatile long *);
no_type vfnd_ptr_tester (const volatile double *);
no_type vfnd_ptr_tester (const volatile float *);
no_type vfnd_ptr_tester (const volatile bool *);
yes_type vfnd_ptr_tester (const volatile void *);

template <typename T> T *add_ptr(T &);

template <bool C> struct bool_to_yesno
{
    typedef no_type type;
};
template <> struct bool_to_yesno<true>
{
    typedef yes_type type;
};

template <typename T>
struct is_enum
{
    static T arg;
    static const bool value = ( (sizeof(int_conv_tester(arg)) == sizeof(yes_type)) && (sizeof(vfnd_ptr_tester(add_ptr(arg))) == sizeof(yes_type)) );
};
/////////////////////////////////

// from lua
template<typename T>
struct void2val
{
    static T invoke(void *input)
    {
        return *(T *)input;
    }
};
template<typename T>
struct void2ptr
{
    static T *invoke(void *input)
    {
        return (T *)input;
    }
};
template<typename T>
struct void2ref
{
    static T &invoke(void *input)
    {
        return *(T *)input;
    }
};

//����T�����ͣ�������void *����ʲô����ת��
template<typename T>
struct void2type
{
    static T invoke(void *ptr)
    {
        //if_�ж��Ƕ�ף��������Ϊ����if  else{ if  else }
        return  if_ < is_ptr<T>::value , void2ptr<typename base_type<T>::type> ,
                typename if_ < is_ref<T>::value , void2ref<typename base_type<T>::type> , void2val<typename base_type<T>::type>  >::type
                >::type::invoke(ptr);
    }
};

struct user
{
    user(void *p) : m_p(p) {}
    virtual ~user() {}
    void *m_p;
};

//���û�push��user data��Ϣ����ת����push light data ��void *
template<typename T>
struct user2type
{
    static T invoke(lua_State *L, int index)
    {
        return void2type<T>::invoke(lua_touserdata(L, index));
    }
};

template<typename T>
struct lua2enum
{
    static T invoke(lua_State *L, int index)
    {
        return (T)(int)lua_tonumber(L, index);
    }
};

template<typename T>
struct lua2object
{
    static T invoke(lua_State *L, int index)
    {
        if (!lua_isuserdata(L, index))
        {
            lua_pushstring(L, "no class at first argument. (forgot ':' expression ?)");
            lua_error(L);
        }
        return void2type<T>::invoke(user2type<user *>::invoke(L, index)->m_p);
    }
};

template<typename T>
T lua2type(lua_State *L, int index)
{
    return  if_ < is_enum<T>::value
            , lua2enum<T>
            , lua2object<T>
            >::type::invoke(L, index);
}

//T��ע�������
//��user�̳е��࣬���ڰ�����ɹ����࣬ͬʱͨ��user�����ṩ�����ͷŵķ�����
//��Ҫ������ת���ķ�ʽ������ֱ����T��ԭ���ǣ�
//ԭ���ҵĸо�����ΪΪ�˱�εĹ��캯�����о���C11��û�б�Ҫ��C11����ֱ����ɱ���ˡ�
//����������ʵ�仹��val��ptr��ref���˿��ǣ� ��Ȼ�������δ��������

template<typename T>
struct val2user : user
{
    val2user() : user(new T) {}

    template<typename T1>
    val2user(T1 t1) : user(new T(t1)) {}

    //T1,T2�ǹ��캯���Ĳ���
    template<typename T1, typename T2>
    val2user(T1 t1, T2 t2) : user(new T(t1, t2)) {}

    template<typename T1, typename T2, typename T3>
    val2user(T1 t1, T2 t2, T3 t3) : user(new T(t1, t2, t3)) {}

    template<typename T1, typename T2, typename T3, typename T4>
    val2user(T1 t1, T2 t2, T3 t3, T4 t4) : user(new T(t1, t2, t3, t4)) {}

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    val2user(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5) : user(new T(t1, t2, t3, t4, t5)) {}

    //�����������,ԭ����������virtual
    virtual ~val2user()
    {
        delete ((T *)m_p);
    }
};

template<typename T>
struct ptr2user : user
{
    ptr2user(T *t) : user((void *)t) {}
};

template<typename T>
struct ref2user : user
{
    ref2user(T &t) : user(&t) {}
};


//��һЩ�ṹת����lua�������˺ܶ�ģ��ɻ
//ԭ����Ϊ�������ǿ��Լ򻯵ģ�������������ʵtinker��ptr��ref�Ŀ���
//�Ƿ�װ��ָ���LUA���������ptr��ref���кܶ��ٴη�װ������Ͽ��ܲ��ܼ�

// to lua
template<typename T>
struct val2lua
{
    static void invoke(lua_State *L, T input)
    {
        new(lua_newuserdata(L, sizeof(val2user<T>))) val2user<T>(input);
    }
};

//
template<typename T>
struct ptr2lua
{
    static void invoke(lua_State *L, T *input)
    {
        if (input)
        {
            new(lua_newuserdata(L, sizeof(ptr2user<T>))) ptr2user<T>(input);
        }
        else
        {
            lua_pushnil(L);
        }
    }
};
template<typename T>
struct ref2lua
{
    static void invoke(lua_State *L, T &input)
    {
        new(lua_newuserdata(L, sizeof(ref2user<T>))) ref2user<T>(input);
    }
};

//enumֻ�Ǳ���������ʹ��
template<typename T>
struct enum2lua
{
    static void invoke(lua_State *L, T val)
    {
        lua_pushnumber(L, (int)val);
    }
};

//�Ҳ�֪��ΪʲôҪ�����ַ�ʽת��object��ֱ��ʹ���ػ���������һ�����ԴﵽЧ����
template<typename T>
struct object2lua
{
    static void invoke(lua_State *L, T val)
    {
        if_ < is_ptr<T>::value , ptr2lua<typename base_type<T>::type>
        , typename if_ < is_ref<T>::value
        , ref2lua<typename base_type<T>::type>
        , val2lua<typename base_type<T>::type>
        >::type
        >::type::invoke(L, val);

        //ע������ط�����ͨ��class_type<T>::type ��ȡ����ʵ�ʵ����ͣ�
        //class_type��ȥ�����õ���Ϣ
        push_meta(L, class_name<typename class_type<T>::type>::name());
        lua_setmetatable(L, -2);
    }
};

template<typename T>
void type2lua(lua_State *L, T val)
{
    //�����ö�٣�����ö�٣���������أ�����object
    if_ < is_enum<T>::value
    , enum2lua<T>
    , object2lua<T>
    >::type::invoke(L, val);
}

// get value from cclosure
//�õ������ģ�upvalue��������ɺ�������
//T ���û������ͣ�
//����Ҫת���ĵ�T���в�����
template<typename T>
T upvalue_(lua_State *L)
{
    //
    return user2type<T>::invoke(L, lua_upvalueindex(1));
}

// read a value from lua stack
template<typename T>
T read(lua_State *L, int index)
{
    return lua2type<T>(L, index);
}

template<>  char               *read(lua_State *L, int index);
template<>  const char         *read(lua_State *L, int index);
template<>  char                read(lua_State *L, int index);
template<>  unsigned char       read(lua_State *L, int index);
template<>  short               read(lua_State *L, int index);
template<>  unsigned short      read(lua_State *L, int index);
template<>  long                read(lua_State *L, int index);
template<>  unsigned long       read(lua_State *L, int index);
template<>  int                 read(lua_State *L, int index);
template<>  unsigned int        read(lua_State *L, int index);
template<>  float               read(lua_State *L, int index);
template<>  double              read(lua_State *L, int index);
template<>  bool                read(lua_State *L, int index);
template<>  void                read(lua_State *L, int index);
template<>  long long           read(lua_State *L, int index);
template<>  unsigned long long  read(lua_State *L, int index);
template<>  table               read(lua_State *L, int index);

// push a value to lua stack

//PUSH ������lua�ģ�ʱ��һ������Ͷ����ػ��������ʵ��û�о����������
template<typename T>
void push(lua_State *L, T ret)
{
    type2lua<T>(L, ret);
}

template<>  void push(lua_State *L, char ret);
template<>  void push(lua_State *L, unsigned char ret);
template<>  void push(lua_State *L, short ret);
template<>  void push(lua_State *L, unsigned short ret);
template<>  void push(lua_State *L, long ret);
template<>  void push(lua_State *L, unsigned long ret);
template<>  void push(lua_State *L, int ret);
template<>  void push(lua_State *L, unsigned int ret);
template<>  void push(lua_State *L, float ret);
template<>  void push(lua_State *L, double ret);
template<>  void push(lua_State *L, char *ret);
template<>  void push(lua_State *L, const char *ret);
template<>  void push(lua_State *L, bool ret);
template<>  void push(lua_State *L, lua_value *ret);
template<>  void push(lua_State *L, long long ret);
template<>  void push(lua_State *L, unsigned long long ret);
template<>  void push(lua_State *L, table ret);

// pop a value from lua stack
template<typename T>
T pop(lua_State *L)
{
    T t = read<T>(L, -1);
    lua_pop(L, 1);
    return t;
}

template<>  void    pop(lua_State *L);
template<>  table   pop(lua_State *L);


// functor (with return value)
//LUA����C�����ķ�װ
//ע��functor ����һ��return void �ĺ�����ƫ�ػ�����
//���������Ϊ��������
//push �����RVal ѹ���ջ
//upvalue_ ��ʵ��һ����ͳ��static �����������ڲ������ķ�����ֻ����upvalue_��ͨ��LUA ���е�upvalueʵ�ֵ�
//upvalue_ ��󷵻صĺ���ָ�룬ͨ������ָ����ɺ�������
//read ��ɴӶ�ջ��ȡ����������

template<typename RVal, typename T1 = void, typename T2 = void, typename T3 = void, typename T4 = void, typename T5 = void>
struct functor
{
    static int invoke(lua_State *L)
    {
        //push�ǽ���������ջ
        push(L, 
            upvalue_<RVal( *)(T1, T2, T3, T4, T5)>(L)(
            read<T1>(L, 1),
            read<T2>(L, 2), 
            read<T3>(L, 3), 
            read<T4>(L, 4), 
            read<T5>(L, 5))
            );
        return 1;
    }
};

template<typename RVal, typename T1, typename T2, typename T3, typename T4>
struct functor<RVal, T1, T2, T3, T4>
{
    static int invoke(lua_State *L)
    {
        push(L, upvalue_<RVal( *)(T1, T2, T3, T4)>(L)(read<T1>(L, 1), read<T2>(L, 2), read<T3>(L, 3), read<T4>(L, 4)));
        return 1;
    }
};

template<typename RVal, typename T1, typename T2, typename T3>
struct functor<RVal, T1, T2, T3>
{
    static int invoke(lua_State *L)
    {
        push(L, upvalue_<RVal( *)(T1, T2, T3)>(L)(read<T1>(L, 1), read<T2>(L, 2), read<T3>(L, 3)));
        return 1;
    }
};


template<typename RVal, typename T1, typename T2>
struct functor<RVal, T1, T2>
{
    static int invoke(lua_State *L)
    {
        push(L, upvalue_<RVal( *)(T1, T2)>(L)(read<T1>(L, 1), read<T2>(L, 2)));
        return 1;
    }
};

template<typename RVal, typename T1>
struct functor<RVal, T1>
{
    static int invoke(lua_State *L)
    {
        push(L, upvalue_<RVal( *)(T1)>(L)(read<T1>(L, 1)));
        return 1;
    }
};

template<typename RVal>
struct functor<RVal>
{
    static int invoke(lua_State *L)
    {
        push(L, upvalue_<RVal( *)()>(L)());
        return 1;
    }
};

// functor (without return value)
template<typename T1, typename T2, typename T3, typename T4, typename T5>
struct functor<void, T1, T2, T3, T4, T5>
{
    static int invoke(lua_State *L)
    {
        upvalue_<void( *)(T1, T2, T3, T4, T5)>(L)(read<T1>(L, 1), read<T2>(L, 2), read<T3>(L, 3), read<T4>(L, 4), read<T5>(L, 5));
        return 0;
    }
};

template<typename T1, typename T2, typename T3, typename T4>
struct functor<void, T1, T2, T3, T4>
{
    static int invoke(lua_State *L)
    {
        upvalue_<void( *)(T1, T2, T3, T4)>(L)(read<T1>(L, 1), read<T2>(L, 2), read<T3>(L, 3), read<T4>(L, 4));
        return 0;
    }
};

template<typename T1, typename T2, typename T3>
struct functor<void, T1, T2, T3>
{
    static int invoke(lua_State *L)
    {
        upvalue_<void( *)(T1, T2, T3)>(L)(read<T1>(L, 1), read<T2>(L, 2), read<T3>(L, 3));
        return 0;
    }
};

template<typename T1, typename T2>
struct functor<void, T1, T2>
{
    static int invoke(lua_State *L)
    {
        upvalue_<void( *)(T1, T2)>(L)(read<T1>(L, 1), read<T2>(L, 2));
        return 0;
    }
};

template<typename T1>
struct functor<void, T1>
{
    static int invoke(lua_State *L)
    {
        upvalue_<void( *)(T1)>(L)(read<T1>(L, 1));
        return 0;
    }
};

template<>
struct functor<void>
{
    static int invoke(lua_State *L)
    {
        upvalue_<void( *)()>(L)();
        return 0;
    }
};

// functor (non-managed)
template<typename T1>
struct functor<int, lua_State *, T1>
{
    static int invoke(lua_State *L)
    {
        return upvalue_<int( *)(lua_State *, T1)>(L)(L, read<T1>(L, 1));
    }
};

template<>
struct functor<int, lua_State *>
{
    static int invoke(lua_State *L)
    {
        return upvalue_<int( *)(lua_State *)>(L)(L);
    }
};

// push_functor
//ע�ͼ����һ������
template<typename RVal>
void push_functor(lua_State *L, RVal (*func)())
{
    lua_pushcclosure(L, functor<RVal>::invoke, 1);
}


template<typename RVal, typename T1>
void push_functor(lua_State *L, RVal (*func)(T1))
{
    lua_pushcclosure(L, functor<RVal, T1>::invoke, 1);
}


template<typename RVal, typename T1, typename T2>
void push_functor(lua_State *L, RVal (*func)(T1, T2))
{
    lua_pushcclosure(L, functor<RVal, T1, T2>::invoke, 1);
}

template<typename RVal, typename T1, typename T2, typename T3>
void push_functor(lua_State *L, RVal (*func)(T1, T2, T3))
{
    lua_pushcclosure(L, functor<RVal, T1, T2, T3>::invoke, 1);
}

template<typename RVal, typename T1, typename T2, typename T3, typename T4>
void push_functor(lua_State *L, RVal (*func)(T1, T2, T3, T4))
{
    lua_pushcclosure(L, functor<RVal, T1, T2, T3, T4>::invoke, 1);
}
//ֻ����һ��������RVal����ֵ��
//T1����T5�����Ĳ���
template<typename RVal, typename T1, typename T2, typename T3, typename T4, typename T5>
void push_functor(lua_State *L, RVal (*func)(T1, T2, T3, T4, T5))
{
    //�����closue �� functor<RVal, T1, T2>::invoke һ��static ����
    //����1��ʾ��һ��upvalue
    lua_pushcclosure(L, functor<RVal, T1, T2, T3, T4, T5>::invoke, 1);
}

// member variable
//var_base ����һ����ģ��ĺ����������Ϳ��Ա�֤ͨ��void * ת��Ϊ var_base *
//��ͨ��var_base *�ĵ��� get, set ��æǡǡ��ֱ�ӵ��õ�������mem_var <T,V>
struct var_base
{
    //ԭ����������ط�д©��һ����������
    //virtual ~var_base();

    virtual void get(lua_State *L) = 0;
    virtual void set(lua_State *L) = 0;
};


//T Ϊclass ���ͣ�
//V Ϊ��������
template<typename T, typename V>
struct mem_var : var_base
{
    V T::*_var;
    mem_var(V T::*val) : 
        _var(val) 
    {
    }
    //get��LUA��ȡ�Ĳ�����Ҳ���ǰ�C++�����ݶ�ȡ��LUA���棬������PUSH
    void get(lua_State *L)
    {
        //read��ʵ���ǰ���Ķ����ָ���ȡ������
        //ע������ط�ʹ�õ�������
        push<if_<is_obj<V>::value, V &, V>::type>(L, read<T *>(L, 1)->*(_var));
    }
    //
    void set(lua_State *L)
    {
        //
        read<T *>(L, 1)->*(_var) = read<V>(L, 3);
    }
};

// class member functor (with return value)
template<typename RVal, typename T, typename T1 = void, typename T2 = void, typename T3 = void, typename T4 = void, typename T5 = void>
struct mem_functor
{
    static int invoke(lua_State *L)
    {
        push(L, (read<T *>(L, 1)->*upvalue_<RVal(T:: *)(T1, T2, T3, T4, T5)>(L))(read<T1>(L, 2), read<T2>(L, 3), read<T3>(L, 4), read<T4>(L, 5), read<T5>(L, 6)));;
        return 1;
    }
};

template<typename RVal, typename T, typename T1, typename T2, typename T3, typename T4>
struct mem_functor<RVal, T, T1, T2, T3, T4>
{
    static int invoke(lua_State *L)
    {
        push(L, (read<T *>(L, 1)->*upvalue_<RVal(T:: *)(T1, T2, T3, T4)>(L))(read<T1>(L, 2), read<T2>(L, 3), read<T3>(L, 4), read<T4>(L, 5)));
        return 1;
    }
};

template<typename RVal, typename T, typename T1, typename T2, typename T3>
struct mem_functor<RVal, T, T1, T2, T3>
{
    static int invoke(lua_State *L)
    {
        push(L, (read<T *>(L, 1)->*upvalue_<RVal(T:: *)(T1, T2, T3)>(L))(read<T1>(L, 2), read<T2>(L, 3), read<T3>(L, 4)));
        return 1;
    }
};

template<typename RVal, typename T, typename T1, typename T2>
struct mem_functor<RVal, T, T1, T2>
{
    static int invoke(lua_State *L)
    {
        push(L, (read<T *>(L, 1)->*upvalue_<RVal(T:: *)(T1, T2)>(L))(read<T1>(L, 2), read<T2>(L, 3)));
        return 1;
    }
};

template<typename RVal, typename T, typename T1>
struct mem_functor<RVal, T, T1>
{
    static int invoke(lua_State *L)
    {
        push(L, (read<T *>(L, 1)->*upvalue_<RVal(T:: *)(T1)>(L))(read<T1>(L, 2)));
        return 1;
    }
};

template<typename RVal, typename T>
struct mem_functor<RVal, T>
{
    static int invoke(lua_State *L)
    {
        push(L, (read<T *>(L, 1)->*upvalue_<RVal(T:: *)()>(L))());
        return 1;
    }
};

// class member functor (without return value)
template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
struct mem_functor<void, T, T1, T2, T3, T4, T5>
{
    static int invoke(lua_State *L)
    {
        (read<T *>(L, 1)->*upvalue_<void(T:: *)(T1, T2, T3, T4, T5)>(L))(read<T1>(L, 2), read<T2>(L, 3), read<T3>(L, 4), read<T4>(L, 5), read<T5>(L, 6));
        return 0;
    }
};

template<typename T, typename T1, typename T2, typename T3, typename T4>
struct mem_functor<void, T, T1, T2, T3, T4>
{
    static int invoke(lua_State *L)
    {
        (read<T *>(L, 1)->*upvalue_<void(T:: *)(T1, T2, T3, T4)>(L))(read<T1>(L, 2), read<T2>(L, 3), read<T3>(L, 4), read<T4>(L, 5));
        return 0;
    }
};

template<typename T, typename T1, typename T2, typename T3>
struct mem_functor<void, T, T1, T2, T3>
{
    static int invoke(lua_State *L)
    {
        (read<T *>(L, 1)->*upvalue_<void(T:: *)(T1, T2, T3)>(L))(read<T1>(L, 2), read<T2>(L, 3), read<T3>(L, 4));
        return 0;
    }
};

template<typename T, typename T1, typename T2>
struct mem_functor<void, T, T1, T2>
{
    static int invoke(lua_State *L)
    {
        (read<T *>(L, 1)->*upvalue_<void(T:: *)(T1, T2)>(L))(read<T1>(L, 2), read<T2>(L, 3));
        return 0;
    }
};

template<typename T, typename T1>
struct mem_functor<void, T, T1>
{
    static int invoke(lua_State *L)
    {
        (read<T *>(L, 1)->*upvalue_<void(T:: *)(T1)>(L))(read<T1>(L, 2));
        return 0;
    }
};

template<typename T>
struct mem_functor<void, T>
{
    static int invoke(lua_State *L)
    {
        (read<T *>(L, 1)->*upvalue_<void(T:: *)()>(L))();
        return 0;
    }
};

// class member functor (non-managed)
template<typename T, typename T1>
struct mem_functor<int, T, lua_State *, T1>
{
    static int invoke(lua_State *L)
    {
        return (read<T *>(L, 1)->*upvalue_<int(T:: *)(lua_State *, T1)>(L))(L, read<T1>(L, 2));
    }
};

template<typename T>
struct mem_functor<int, T, lua_State *>
{
    static int invoke(lua_State *L)
    {
        return (read<T *>(L, 1)->*upvalue_<int(T:: *)(lua_State *)>(L))(L);
    }
};

// push_functor
template<typename RVal, typename T>
void push_functor(lua_State *L, RVal (T::*func)())
{
    lua_pushcclosure(L, mem_functor<RVal, T>::invoke, 1);
}

template<typename RVal, typename T>
void push_functor(lua_State *L, RVal (T::*func)() const)
{
    lua_pushcclosure(L, mem_functor<RVal, T>::invoke, 1);
}

template<typename RVal, typename T, typename T1>
void push_functor(lua_State *L, RVal (T::*func)(T1))
{
    lua_pushcclosure(L, mem_functor<RVal, T, T1>::invoke, 1);
}

template<typename RVal, typename T, typename T1>
void push_functor(lua_State *L, RVal (T::*func)(T1) const)
{
    lua_pushcclosure(L, mem_functor<RVal, T, T1>::invoke, 1);
}

template<typename RVal, typename T, typename T1, typename T2>
void push_functor(lua_State *L, RVal (T::*func)(T1, T2))
{
    lua_pushcclosure(L, mem_functor<RVal, T, T1, T2>::invoke, 1);
}

template<typename RVal, typename T, typename T1, typename T2>
void push_functor(lua_State *L, RVal (T::*func)(T1, T2) const)
{
    lua_pushcclosure(L, mem_functor<RVal, T, T1, T2>::invoke, 1);
}

template<typename RVal, typename T, typename T1, typename T2, typename T3>
void push_functor(lua_State *L, RVal (T::*func)(T1, T2, T3))
{
    lua_pushcclosure(L, mem_functor<RVal, T, T1, T2, T3>::invoke, 1);
}

template<typename RVal, typename T, typename T1, typename T2, typename T3>
void push_functor(lua_State *L, RVal (T::*func)(T1, T2, T3) const)
{
    lua_pushcclosure(L, mem_functor<RVal, T, T1, T2, T3>::invoke, 1);
}

template<typename RVal, typename T, typename T1, typename T2, typename T3, typename T4>
void push_functor(lua_State *L, RVal (T::*func)(T1, T2, T3, T4))
{
    lua_pushcclosure(L, mem_functor<RVal, T, T1, T2, T3, T4>::invoke, 1);
}

template<typename RVal, typename T, typename T1, typename T2, typename T3, typename T4>
void push_functor(lua_State *L, RVal (T::*func)(T1, T2, T3, T4) const)
{
    lua_pushcclosure(L, mem_functor<RVal, T, T1, T2, T3, T4>::invoke, 1);
}

//ע�������ע�����ѽ���Ҿ�дһ��ע�ͣ�
//push_functor ��2�֣�һ����������ڲ���Ա����static�������ģ�
//mem_functor�ǳ�Ա������ģ��
template<typename RVal, typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
void push_functor(lua_State *L, RVal (T::*func)(T1, T2, T3, T4, T5))
{
    lua_pushcclosure(L, mem_functor<RVal, T, T1, T2, T3, T4, T5>::invoke, 1);
}

//��Գ�Ա���������Ļ���һ����ʽ��const�ģ�
template<typename RVal, typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
void push_functor(lua_State *L, RVal (T::*func)(T1, T2, T3, T4, T5) const)
{
    lua_pushcclosure(L, mem_functor<RVal, T, T1, T2, T3, T4, T5>::invoke, 1);
}

// constructor
//new һ�� userdata,��Ӧclass��ͬʱ��ɹ��캯����
//ͬʱ����userdata��metatableΪclass_add������Ǹ�metatable
template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
int constructor(lua_State *L)
{
    //new һ��user data����val2user<T>�Ĵ�С,ͬʱ��ͬʱ��placement new �ķ�ʽ��ָ��ʽlua_newuserdata����ģ���
    //��ɹ��캯��
    //val2user<T> ��һ����user�̳е���,user��һ����װvoid * ���࣬
    //�����ķ�װ����meta_get����meta_set�ĵ��ó�Ϊ�˿��ܣ�
    //meta_get��meta_set��ʵû��ģ����Ϣ����meta_get��meta_get����class ע���ʱ��ʹ�õģ�
    //��ʱ��û��ע������Ա
    new(lua_newuserdata(L, sizeof(val2user<T>))) 
        val2user<T>(
        read<T1>(L, 2),
        read<T2>(L, 3), 
        read<T3>(L, 4), 
        read<T4>(L, 5), 
        read<T5>(L, 6));
    push_meta(L, class_name<typename class_type<T>::type>::name());
    lua_setmetatable(L, -2);

    return 1;
}

template<typename T, typename T1, typename T2, typename T3, typename T4>
int constructor(lua_State *L)
{
    new(lua_newuserdata(L, sizeof(val2user<T>))) val2user<T>(read<T1>(L, 2), read<T2>(L, 3), read<T3>(L, 4), read<T4>(L, 5));
    push_meta(L, class_name<typename class_type<T>::type>::name());
    lua_setmetatable(L, -2);

    return 1;
}

template<typename T, typename T1, typename T2, typename T3>
int constructor(lua_State *L)
{
    new(lua_newuserdata(L, sizeof(val2user<T>))) val2user<T>(read<T1>(L, 2), read<T2>(L, 3), read<T3>(L, 4));
    push_meta(L, class_name<typename class_type<T>::type>::name());
    lua_setmetatable(L, -2);

    return 1;
}

template<typename T, typename T1, typename T2>
int constructor(lua_State *L)
{
    new(lua_newuserdata(L, sizeof(val2user<T>))) val2user<T>(read<T1>(L, 2), read<T2>(L, 3));
    push_meta(L, class_name<typename class_type<T>::type>::name());
    lua_setmetatable(L, -2);

    return 1;
}

template<typename T, typename T1>
int constructor(lua_State *L)
{
    enum_stack(L);
    new(lua_newuserdata(L, sizeof(val2user<T>))) val2user<T>(read<T1>(L, 2));
    push_meta(L, class_name<typename class_type<T>::type>::name());
    enum_stack(L);
    lua_setmetatable(L, -2);
    enum_stack(L);
    return 1;
}

template<typename T>
int constructor(lua_State *L)
{
    new(lua_newuserdata(L, sizeof(val2user<T>))) val2user<T>();
    push_meta(L, class_name<typename class_type<T>::type>::name());
    lua_setmetatable(L, -2);

    return 1;
}

//��������������������������
//��ʵ����������Ͽ���û�б�Ҫ��ģ�溯��<T>������ֱ����user���������麯�����ġ�
//��������û�еط��õ���T��
//����USER_DATA�Ļ��������,����user��ʵ��һ��LUAʹ�õ�userdata����Ļ��࣬
//���������3�֣�val,ptr,ref,����val���������ͷŶ���ptr��ref�Ķ���ʲô����������
//�����ͱ�֤�����㴫�ݸ�LUAʲô�����ǵ��������ڶ�����ȷ�ģ�
template<typename T>
int destroyer(lua_State *L)
{
    ((user *)lua_touserdata(L, 1))->~user();
    return 0;
}

//����һ��ȫ�ֺ�����������ľ�̬������lua����
template<typename F>
void def(lua_State *L, const char *name, F func)
{
    //��������
    lua_pushstring(L, name);
    //������ָ��ת��Ϊvoid * ����Ϊlightuserdata �����ջ����Ϊclosure��upvalue����
    lua_pushlightuserdata(L, (void *)func);
    //ģ�庯��������closure,func��ģ�����
    push_functor(L, func);
    //�������ȫ�ֻ�������
    lua_settable(L, LUA_GLOBALSINDEX);
}

// global variable
//ȫ�ֱ�����get set��

template<typename T>
void set(lua_State *L, const char *name, T object)
{
    //���ƶ���
    lua_pushstring(L, name);
    //ģ�庯��������T�������push
    push(L, object);
    lua_settable(L, LUA_GLOBALSINDEX);
}

template<typename T>
T get(lua_State *L, const char *name)
{
    lua_pushstring(L, name);
    lua_gettable(L, LUA_GLOBALSINDEX);
    return pop<T>(L);
}

template<typename T>
void decl(lua_State *L, const char *name, T object)
{
    set(L, name, object);
}

//����LUA�ĺ���

// call
template<typename RVal>
RVal call(lua_State *L, const char *name)
{
    lua_pushcclosure(L, on_error, 0);
    int errfunc = lua_gettop(L);

    lua_pushstring(L, name);
    lua_gettable(L, LUA_GLOBALSINDEX);

    if (lua_isfunction(L, -1))
    {
        lua_pcall(L, 0, 1, errfunc);
    }
    else
    {
        print_error(L, "lua_tinker::call() attempt to call global `%s' (not a function)", name);
    }

    lua_remove(L, errfunc);
    return pop<RVal>(L);
}

template<typename RVal, typename T1>
RVal call(lua_State *L, const char *name, T1 arg)
{
    lua_pushcclosure(L, on_error, 0);
    int errfunc = lua_gettop(L);

    lua_pushstring(L, name);
    lua_gettable(L, LUA_GLOBALSINDEX);
    if (lua_isfunction(L, -1))
    {
        push(L, arg);
        lua_pcall(L, 1, 1, errfunc);
    }
    else
    {
        print_error(L, "lua_tinker::call() attempt to call global `%s' (not a function)", name);
    }

    lua_remove(L, errfunc);
    return pop<RVal>(L);
}


//�����Ϊ���ӽ��⣬
//RVal ����ֵ
//T1��T2����

template<typename RVal, typename T1, typename T2>
RVal call(lua_State *L, const char *name, T1 arg1, T2 arg2)
{
    //���������ĺ��������Ҽ�¼��ջ�ĵ�ַ
    lua_pushcclosure(L, on_error, 0);
    int errfunc = lua_gettop(L);

    lua_pushstring(L, name);
    lua_gettable(L, LUA_GLOBALSINDEX);
    //������Ƿ��Ǻ���
    if (lua_isfunction(L, -1))
    {
        //�����ջ������arg1��arg2��
        push(L, arg1);
        push(L, arg2);
        //����lua�ĺ�����Ĭ��ֻ��һ������ֵ��
        lua_pcall(L, 2, 1, errfunc);
    }
    else
    {
        print_error(L, "lua_tinker::call() attempt to call global `%s' (not a function)", name);
    }
    //�ڶ�ջɾ����������ĺ���
    lua_remove(L, errfunc);

    //�ڶ�ջ��������ֵ
    return pop<RVal>(L);
}

template<typename RVal, typename T1, typename T2, typename T3>
RVal call(lua_State *L, const char *name, T1 arg1, T2 arg2, T3 arg3)
{
    lua_pushcclosure(L, on_error, 0);
    int errfunc = lua_gettop(L);

    lua_pushstring(L, name);
    lua_gettable(L, LUA_GLOBALSINDEX);
    if (lua_isfunction(L, -1))
    {
        push(L, arg1);
        push(L, arg2);
        push(L, arg3);
        lua_pcall(L, 3, 1, errfunc);
    }
    else
    {
        print_error(L, "lua_tinker::call() attempt to call global `%s' (not a function)", name);
    }

    lua_remove(L, errfunc);
    return pop<RVal>(L);
}

// class helper
int meta_get(lua_State *L);
int meta_set(lua_State *L);
void push_meta(lua_State *L, const char *name);

// class init
//��ĳ�ʼ������class����lua��ʹ��
//�������metatable�ı�����˵ԭ�͵ı�
template<typename T>
void class_add(lua_State *L, const char *name)
{
    //��T������
    class_name<T>::name(name);

    //�������
    lua_pushstring(L, name);
    //new һ��table�����table����Ϊ���������metatable�ģ�ĳ�̶ֳ���Ҳ����˵��ԭ�ͣ���
    lua_newtable(L);

    //__name���Ǳ�׼��Ԫ������������������ʹ��
    lua_pushstring(L, "__name");
    lua_pushstring(L, name);
    lua_rawset(L, -3);

    //��meta_get������Ϊ__index����
    lua_pushstring(L, "__index");
    lua_pushcclosure(L, meta_get, 0);
    lua_rawset(L, -3);

    //��meta_set������Ϊ__index����
    lua_pushstring(L, "__newindex");
    lua_pushcclosure(L, meta_set, 0);
    lua_rawset(L, -3);

    //�������պ���
    lua_pushstring(L, "__gc");
    lua_pushcclosure(L, destroyer<T>, 0);
    lua_rawset(L, -3);

    lua_settable(L, LUA_GLOBALSINDEX);
}

// Tinker Class Inheritence
//ʵ����ļ̳й�ϵ�ķ�����T��P��Ҫ��class_add

template<typename T, typename P>
void class_inh(lua_State *L)
{
    //������������ƣ�ȡ�������metatable�ı�����˵ԭ�͡�
    push_meta(L, class_name<T>::name());
    //���ջ����һ����
    if (lua_istable(L, -1))
    {
        //����__parent Ϊ �������ƣ�Ŀǰ���ܶ��ؼ̳�
        lua_pushstring(L, "__parent");
        push_meta(L, class_name<P>::name());
        lua_rawset(L, -3);
    }
    //�Ӷ�ջ����push_metaȡ�õ�vlue
    lua_pop(L, 1);
}

// Tinker Class Constructor
// T ����
// F �ǹ��캯���ķ�װ��lua_tinker::constructor
template<typename T, typename F>
void class_con(lua_State *L, F func)
{
    //����������ƣ�ȡ�����metatable�ı�����˵ԭ�͡�
    push_meta(L, class_name<T>::name());
    //���ջ����һ����
    if (lua_istable(L, -1))
    {
        //��������metatable�ı�����һ��metatable������������һ��__call�Ķ�Ӧ����
        //������Ŀ���������ģ�__call�Ƕ�Ӧһ��()���ã���ʵ�岻�Ǻ���ʽ���ĵ��ú���
        //LUA�г��������ĵ��ã�
        //object =class_name()
        lua_newtable(L);
        
        lua_pushstring(L, "__call");
        lua_pushcclosure(L, func, 0);
        lua_rawset(L, -3);
        //�������table��Ϊclass ԭ�͵�metatable.
        //����˵�������table��Ϊclass metatable��metatable.
        lua_setmetatable(L, -2);
    }
    lua_pop(L, 1);
}

// Tinker Class Functions
template<typename T, typename F>
void class_def(lua_State *L, const char *name, F func)
{
    push_meta(L, class_name<T>::name());
    if (lua_istable(L, -1))
    {
        lua_pushstring(L, name);
        //�����ĺ���ָ����Ϊupvalue_�ġ�
        //ע���������ĳ�Աָ�루���ӽӽ�size_t����������ʵ�ʵ�ָ�룬�������������light userdata
        new(lua_newuserdata(L, sizeof(F))) F(func);
        //
        push_functor(L, func);
        lua_rawset(L, -3);
    }
    lua_pop(L, 1);
}

// Tinker Class Variables
// T �󶨵���
// VAR �ǰ󶨵ı��������ͣ�
// BASE ��Ա�������࣬һ������ΪT��BASE��һ����
template<typename T, typename BASE, typename VAR>
void class_mem(lua_State *L, const char *name, VAR BASE::*val)
{
    //����������ƣ�ȡ�����metatable
    push_meta(L, class_name<T>::name());
    if (lua_istable(L, -1))
    {
        lua_pushstring(L, name);
        //mem_var �̳���var_base,ʵ�ʵ��õ�ʱ������var_base���麯����ɻص���
        new(lua_newuserdata(L, sizeof(mem_var<BASE, VAR>))) mem_var<BASE, VAR>(val);
        lua_rawset(L, -3);
    }
    lua_pop(L, 1);
}

//��ģ�庯��������æʵ��һ������������ͨ��class �ҵ���Ӧ�������ƣ�ע�ᵽLUA�����ƣ���
template<typename T>
struct class_name
{
    // global name
    static const char *name(const char *name = NULL)
    {
        static char temp[256] = "";
        if (name)
        {
            strcpy_s(temp, name);
        }
        return temp;
    }
};

// Table Object on Stack
struct table_obj
{
    table_obj(lua_State *L, int index);
    ~table_obj();

    void inc_ref();
    void dec_ref();

    bool validate();

    template<typename T>
    void set(const char *name, T object)
    {
        if (validate())
        {
            lua_pushstring(m_L, name);
            push(m_L, object);
            lua_settable(m_L, m_index);
        }
    }

    template<typename T>
    T get(const char *name)
    {
        if (validate())
        {
            lua_pushstring(m_L, name);
            lua_gettable(m_L, m_index);
        }
        else
        {
            lua_pushnil(m_L);
        }

        return pop<T>(m_L);
    }

    lua_State      *m_L;
    int             m_index;
    const void     *m_pointer;
    int             m_ref;
};

// Table Object Holder
struct table
{
    table(lua_State *L);
    table(lua_State *L, int index);
    table(lua_State *L, const char *name);
    table(const table &input);
    ~table();

    template<typename T>
    void set(const char *name, T object)
    {
        m_obj->set(name, object);
    }

    template<typename T>
    T get(const char *name)
    {
        return m_obj->get<T>(name);
    }

    table_obj      *m_obj;
};



} // namespace lua_tinker

#endif //_LUA_TINKER_H_
