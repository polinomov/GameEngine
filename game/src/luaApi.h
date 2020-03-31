#ifndef _LUA_API_H_
#define _LUA_API_H_
#include "context.h"
#include "core.h"
#include "types.h"
#include <primitives.h>
#include <map>
#include <tuple>

struct LuaApi_FunctionCall{
  lua::FlatTable params;
  Context*       context;
};


static void getLuaCallInfo(lua_State* state, LuaApi_FunctionCall& out){
  void*    contextPtr;
  lua::read_global(state,std::string("_SCRIPT"),contextPtr);
  out.context = (Context*) contextPtr;
  lua::read_struct(state,out.params);
}

static int LuaApi_test(lua_State* lua){
  cprint_debug("LuaApi") << "LuaApi_test called" << std::endl;
  return 0;
}

static int LuaApi_addComponent(lua_State* lua){
  LuaApi_FunctionCall callInfo;
  getLuaCallInfo(lua,callInfo);
  return 1;
}

static int LuaApi_createWindow(lua_State* lua){ 
  LuaApi_FunctionCall callInfo;
  getLuaCallInfo(lua,callInfo);
  callInfo.context->createWindow(callInfo.params["name"],callInfo.params["width"],callInfo.params["height"]);
  return 0;
}


static int LuaApi_loadScript(lua_State* lua){ 
  LuaApi_FunctionCall callInfo;
  getLuaCallInfo(lua,callInfo);
  callInfo.context->loadLua(callInfo.params["path"]);
  return 1;
}


struct Lua_ApiCall{
  const char* name;
  int(*call)(lua_State*);  
};

constexpr Lua_ApiCall LuaApi[] = {
  {"create",&LuaApi_addComponent},
  {"test",&LuaApi_test},
  {"createWindow",&LuaApi_createWindow},
  {"loadScript",&LuaApi_loadScript}
};

#endif
