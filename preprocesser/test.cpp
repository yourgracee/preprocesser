#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
extern "C"
{
#include "src/lua.h"
#include "src/lualib.h"
#include "src/lauxlib.h"
}
#include "lua_expand.hpp"

using namespace std;
string add(string  x,string  y)
{
        return x+y;
}

IMPL_LUA_WRAPPER(add)
int main()
{ 
    lua_State *L = luaL_newstate();    // 创建Lua状态机。
    luaL_openlibs(L);    // 打开Lua状态机"L"中的所有Lua标准库。

    LUA_REGISTER_FUNCION(add);

    const char* testfunc = "print(add(\"a\",\"b\"))";
    if(luaL_dostring(L, testfunc))    // 执行Lua命令。
        printf("Failed to invoke.\n");
    lua_close(L);    // 关闭Lua状态机。
    return 0;
}