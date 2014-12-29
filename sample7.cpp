// sample3.cpp : LuaTinker �� Ŭ���� ����� �˾ƺ���.
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
    // Lua �� �ʱ�ȭ �Ѵ�.
    lua_State *L = lua_open();

    // Lua �⺻ �Լ����� �ε��Ѵ�.- print() ���
    luaopen_base(L);
    // Lua ���ڿ� �Լ����� �ε��Ѵ�.- string ���
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
    //�����д�����޷��õ����õģ�������ʽָ��������
    //lua_tinker::set(L, "ref_a", ref_a);
    lua_tinker::set<TestA &>(L, "ref_a", ref_a);

    // sample7.lua
    lua_tinker::dofile(L, "sample7.lua");

    printf("ptr_a->a_ = %d\n", ptr_a->a_);
    printf("val_a.a_ = %d\n", val_a.a_);
    printf("ref_a.a_ = %d\n", ref_a.a_);

    // ���α׷� ����
    lua_close(L);

    return 0;
}

