#ifndef ITERATTING

template <typename T>
T lua_to_native(lua_State* L, int i) {}

template <>  bool lua_to_native<bool>(lua_State* L, int i) { return lua_toboolean(L, i) != 0; }
template <>  char lua_to_native<char>(lua_State* L, int i) { return (char)lua_tointeger(L, i); }
template <>  short lua_to_native<short>(lua_State* L, int i) { return (short)lua_tointeger(L, i); }
template <>  int lua_to_native<int>(lua_State* L, int i) { return (int)lua_tointeger(L, i); }
template <>  long lua_to_native<long>(lua_State* L, int i) { return (long)lua_tointeger(L, i); }
template <>  long long lua_to_native<long long>(lua_State* L, int i) { return lua_tointeger(L, i); }
template <>  float lua_to_native<float>(lua_State* L, int i) { return (float)lua_tonumber(L, i); }
template <>  double lua_to_native<double>(lua_State* L, int i) { return lua_tonumber(L, i); }
template <>  const char* lua_to_native<const char*>(lua_State* L, int i) { return lua_tostring(L, i); }
template <> inline std::string lua_to_native<std::string>(lua_State* L, int i) { return  lua_tostring(L, i);}

void native_to_lua(lua_State* L, bool v) { lua_pushboolean(L, v); }
void native_to_lua(lua_State* L, char v) { lua_pushinteger(L, v); }
void native_to_lua(lua_State* L, short v) { lua_pushinteger(L, v); }
void native_to_lua(lua_State* L, int v) { lua_pushinteger(L, v); }
void native_to_lua(lua_State* L, long v) { lua_pushinteger(L, v); }
void native_to_lua(lua_State* L, long long v) { lua_pushinteger(L, (lua_Integer)v); }
void native_to_lua(lua_State* L, float v) { lua_pushnumber(L, v); }
void native_to_lua(lua_State* L, double v) { lua_pushnumber(L, v); }
void native_to_lua(lua_State* L, char* v) { lua_pushstring(L, v); }
void native_to_lua(lua_State* L, const std::string& v) { lua_pushstring(L, v.c_str()); }

#include "preprocesser/repeat.hpp"
#include "preprocesser/enum_param.hpp"
#include "preprocesser/cat.hpp"
#include "preprocesser/inc.hpp"
#include "preprocesser/comma_if.hpp"


#define MY_ARG(n) typename arg_type##n
#define MY_ARGVAR(n) t##n
#define MY_ARGTYPE(n) arg_type##n

#define ADD_LUA_SUFFIX(f) lua_##f    

#define FILENAME_1 "lua_expand.hpp"    
#define LIMIT_1 (0,64)    
#include "preprocesser/self1.hpp"



#define IMPL_LUA_WRAPPER(function_name) int ADD_LUA_SUFFIX(function_name)(lua_State* L) {return lua_wrapper(L, &function_name);}    

#define LUA_REGISTER_FUNCION(function_name) lua_register(L, #function_name , (ADD_LUA_SUFFIX(function_name)))

#endif

#if defined(ITERATTING) && DEPTH == 1
#define n ITERATION_1
template<typename return_type COMMA_IF(n) ENUM_PARAMS(n,MY_ARG)> 
int lua_wrapper(lua_State *L , return_type(*funcptr)(ENUM_PARAMS(n,MY_ARGTYPE))) 
{ 
    #define LIMIT_2 (0,n-1)
    #define FILENAME_2 "lua_expand.hpp"
    #include "preprocesser/self2.hpp"
    #define n ITERATION_1
    native_to_lua(L, (*funcptr)(ENUM_PARAMS(n,MY_ARGVAR)));
    return 1;
}
#elif defined(ITERATION_2) && DEPTH == 2
#define nn ITERATION_2
    CAT(arg_type,nn) CAT(t,nn) = lua_to_native<CAT(arg_type,nn)>(L, INC(nn));
#endif