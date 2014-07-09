
-- 전역 g_test 의 멤버 변수 _test 의 값을 출력한다.
print(g_test._test)

-- temp 에 새 test 객체를 만들어 넣는다.
temp = test(4)

-- test 의 멤버 변수 _test 값을 출력한다.
print(temp._test)

-- Lua 에 추가되지 않은 A 구조체값을 a라는 변수에 넣는다.
a = g_test:get()

-- 임의의 객체 a를 Lua->C++로 전달한다.
temp:set(a)




