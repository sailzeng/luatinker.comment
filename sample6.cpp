// sample3.cpp : LuaTinker �� Ŭ���� ����� �˾ƺ���.
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
    // Lua �� �ʱ�ȭ �Ѵ�.
    lua_State *L = lua_open();

    // Lua �⺻ �Լ����� �ε��Ѵ�.- print() ���
    luaopen_base(L);
    // Lua ���ڿ� �Լ����� �ε��Ѵ�.- string ���
    luaopen_string(L);

    // TestFunc �Լ��� Lua �� ����Ѵ�.
    lua_tinker::def(L, "TestFunc", &TestFunc);
    lua_tinker::def(L, "TestFunc2", &TestFunc2);

    // TestClass Ŭ������ Lua �� �߰��Ѵ�.
    lua_tinker::class_add<TestClass>(L, "TestClass");
    // TestClass �� �Լ��� ����Ѵ�.
    lua_tinker::class_def<TestClass>(L, "TestFunc", &TestClass::TestFunc);
    lua_tinker::class_def<TestClass>(L, "TestFunc2", &TestClass::TestFunc2);

    // TestClass �� ���� ������ �����Ѵ�.
    TestClass g_test;
    lua_tinker::set(L, "g_test", &g_test);

    // sample3.lua ������ �ε��Ѵ�.
    lua_tinker::dofile(L, "sample6.lua");

    // Thread �� �����Ѵ�.
    lua_State *L1 = lua_newthread(L);
    lua_pushstring(L1, "ThreadTest");
    lua_gettable(L1, LUA_GLOBALSINDEX);

    printf("L stack ========================================\n");
    lua_tinker::enum_stack(L);
    printf("L1 stack ========================================\n");
    lua_tinker::enum_stack(L1);
    printf("========================================\n");

    // Thread �� �����Ѵ�.
    printf("* lua_resume() to.. \n");
    lua_resume(L1, 0);

    // Thread �� �ٽ� �����Ѵ�.
    printf("* lua_resume() to.. \n");
    lua_resume(L1, 0);

    // Thread �� �ٽ� �����Ѵ�.
    printf("* lua_resume() to.. \n");
    lua_resume(L1, 0);

    // Thread �� �ٽ� �����Ѵ�.
    printf("* lua_resume() to.. \n");
    lua_resume(L1, 0);

    // Thread �� �ٽ� �����Ѵ�.
    printf("* lua_resume() to.. \n");
    lua_resume(L1, 0);

    // ���α׷� ����
    lua_close(L);

    return 0;
}

