// sample3.cpp : LuaTinker 의 클래스 기능을 알아본다.
//

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

#include "lua_tinker.h"

//
//
int TestFunc(lua_State *L)
{
    printf("# TestFunc is invoke.\n");
    return lua_yield(L, 0);
}

int TestFunc2(lua_State *L, float a)
{
    printf("# TestFunc2(L,%f) is invoke.\n", a);
    return lua_yield(L, 0);
}

class TestClass
{
public:

    //
    //
    int TestFunc(lua_State *L)
    {
        printf("# TestClass::TestFunc is invoke.\n");
        return lua_yield(L, 0);
    }

    int TestFunc2(lua_State *L, float a)
    {
        printf("# TestClass::TestFunc2(L,%f) is invoke.\n", a);
        return lua_yield(L, 0);
    }
};

int main()
{
    // Lua 를 초기화 한다.
    lua_State *L = lua_open();

    // Lua 기본 함수들을 로드한다.- print() 사용
    luaopen_base(L);
    // Lua 문자열 함수들을 로드한다.- string 사용
    luaopen_string(L);

    // TestFunc 함수를 Lua 에 등록한다.
    lua_tinker::def(L, "TestFunc", &TestFunc);
    lua_tinker::def(L, "TestFunc2", &TestFunc2);

    // TestClass 클래스를 Lua 에 추가한다.
    lua_tinker::class_add<TestClass>(L, "TestClass");
    // TestClass 의 함수를 등록한다.
    lua_tinker::class_def<TestClass>(L, "TestFunc", &TestClass::TestFunc);
    lua_tinker::class_def<TestClass>(L, "TestFunc2", &TestClass::TestFunc2);

    // TestClass 를 전역 변수로 선언한다.
    TestClass g_test;
    lua_tinker::set(L, "g_test", &g_test);

    // sample3.lua 파일을 로드한다.
    lua_tinker::dofile(L, "sample6.lua");

    // Thread 를 시작한다.
    lua_State *L1 = lua_newthread(L);
    lua_pushstring(L1, "ThreadTest");
    lua_gettable(L1, LUA_GLOBALSINDEX);

    printf("L stack ========================================\n");
    lua_tinker::enum_stack(L);
    printf("L1 stack ========================================\n");
    lua_tinker::enum_stack(L1);
    printf("========================================\n");

    // Thread 를 시작한다.
    printf("* lua_resume() to.. \n");
    lua_resume(L1, 0);

    // Thread 를 다시 시작한다.
    printf("* lua_resume() to.. \n");
    lua_resume(L1, 0);

    // Thread 를 다시 시작한다.
    printf("* lua_resume() to.. \n");
    lua_resume(L1, 0);

    // Thread 를 다시 시작한다.
    printf("* lua_resume() to.. \n");
    lua_resume(L1, 0);

    // Thread 를 다시 시작한다.
    printf("* lua_resume() to.. \n");
    lua_resume(L1, 0);

    // 프로그램 종료
    lua_close(L);

    return 0;
}

