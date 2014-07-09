// sample3.cpp : LuaTinker 의 클래스 기능을 알아본다.
//

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

#include "lua_tinker.h"


struct TestA
{
    TestA(int a) :a_(a)
    {
    }

    int set(int a)
    {
        a_ = a;
        return a_;
    }
    int a_;
};



int main()
{
    // Lua 를 초기화 한다.
    lua_State *L = lua_open();

    // Lua 기본 함수들을 로드한다.- print() 사용
    luaopen_base(L);
    // Lua 문자열 함수들을 로드한다.- string 사용
    luaopen_string(L);

    lua_tinker::class_add<TestA>(L, "TestA");
    lua_tinker::class_def<TestA>(L, "set", &TestA::set);
    lua_tinker::class_con<TestA>(L, lua_tinker::constructor<TestA, int>);
    lua_tinker::class_mem<TestA>(L, "a_",&TestA::a_);


    TestA *ptr_a = new TestA(100);
    lua_tinker::set(L, "ptr_a", ptr_a);

    TestA val_a(200);
    lua_tinker::set(L, "val_a", val_a);

    TestA temp_a(300);
    TestA &ref_a = temp_a;
    lua_tinker::set<TestA &>(L, "ref_a", ref_a);

    // sample7.lua
    lua_tinker::dofile(L, "sample7.lua");

    printf("ptr_a->a_ = %d\n", ptr_a->a_);
    printf("val_a.a_ = %d\n", val_a.a_);
    printf("ref_a.a_ = %d\n", ref_a.a_);

    // 프로그램 종료
    lua_close(L);

    return 0;
}

