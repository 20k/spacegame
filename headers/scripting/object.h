#ifndef INCLUDES_SCRIPTING_OBJECT_H
#define INCLUDES_SCRIPTING_OBJECT_H

#include "common.h"

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#define LUA_OBJECT() \
	static int Lua_New( lua_State* Lua );

#define LUA_CONSTRUCTOR(type) \
	int type::Lua_New( lua_State* Lua ) \
	{ \
		int argc = 1; \
		type* Obj = new type(

#define LUA_ENDCONSTRUCTOR(type) \
		); \
		Proxy* p = (Proxy*)lua_newuserdata(Lua, sizeof(Proxy)); \
		p->Data = Obj; \
		luaL_newmetatable(Lua, #type); \
		lua_setmetatable(Lua, -2); \
		return 1;\
	}

#define LUA_ARG_DOUBLE() \
	luaL_checknumber(Lua, argc++),
	
#define LUA_ARG_DOUBLE_END() \
	luaL_checknumber(Lua, argc++)

#define LUA_ARG_INTEGER() \
	(int)luaL_checknumber(Lua, argc++),
	
#define LUA_ARG_INTEGER_END() \
	(int)luaL_checknumber(Lua, argc++)
	
#define LUA_ARG_USERDATA(_type) \
	(_type*)(((Proxy*)lua_touserdata(Lua, argc++))->Data),
	
#define LUA_ARG_USERDATA_END(_type) \
	(_type*)(((Proxy*)lua_touserdata(Lua, argc++))->Data)

#define LUA_HASFUNCTIONS() \
	static const luaL_Reg Lua_Functions[];
	
#define LUA_FUNCTIONS(_class) \
	const luaL_Reg _class::Lua_Functions[] = {
	
#define LUA_FUNCTION(_name, _func) \
	 	{ _name , _func },

#define LUA_ENDFUNCTIONS() \
		{ 0, 0 }, \
	};

#define LUA_REGISTER(_lua, _class) \
	Scripting::Object::Register(_lua, #_class, &_class::Lua_Functions);

namespace Scripting
{
	class Object
	{
		public:
			virtual ~Object() { }

			// Registers a Lua 'class'
			static int Register( lua_State* Lua, const char* Name, luaL_Reg* Functions );
			
			// Initalizes a Lua 'class' with existing C++ data
			static void Initialize( lua_State* Lua, const char* Name, void* Data );
			
			struct Proxy { void* Data; };
			
		private:
			// Deletes the underlying C++ type
			static int GarbageCollect( lua_State* Lua );
	};
}

#endif /* INCLUDES_SCRIPTING_OBJECT_H */

