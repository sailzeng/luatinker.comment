-- lua coroutine 
function ThreadTest()
	print("ThreadTest invoke start.")
	
	print("TestFunc invoke start.")
	--  lua_yield() 
	TestFunc()
	TestFunc2(1.2)
	print("TestFunc and TestFunc2 invoke end.")
	
	print("g_test::TestFunc() invoke start.")
	--  lua_yield() .
	g_test:TestFunc()
	g_test:TestFunc2(2.3)
	print("g_test::TestFunc() and g_test::TestFunc2() invoke end.")
	
	print("ThreadTest  invok end.")
end
