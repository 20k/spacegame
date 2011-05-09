#include "scripting/object.h"

#include <iostream>

namespace Scripting
{
	int Object::Register( lua_State* Lua, const char* Name, luaL_Reg* Functions )
	{
		std::cout << "Lua: Registering '" << Name << "' ..." << std::endl;
		
		// Create a metatable
		luaL_newmetatable(Lua, Name);
		
		// Set's the index to the table, thus producing a 'class'
		lua_pushvalue(Lua, -1);
		lua_setfield(Lua, -2, "__index");
		
		// Allow C++ to delete classes when Lua doesn't use them anymore
		lua_pushcfunction(Lua, &Object::GarbageCollect);
		lua_setfield(Lua, -2, "__gc");
		
		if(Functions)
			luaL_register(Lua, 0, Functions);
			
		// Pop the metatable
		lua_pop(Lua, 1);
		
		return 0;
	}
	
	void Object::Initialize( lua_State* Lua, const char* Name, void* Data )
	{
		Proxy* p = (Proxy*)lua_newuserdata(Lua, sizeof(Proxy));
		p->Data = Data;
		
		luaL_newmetatable(Lua, Name);
		lua_setmetatable(Lua, -2);
	}
	
	int Object::GarbageCollect( lua_State* Lua )
	{
		// Delete the underlying C++ class
		Proxy* p = (Proxy*)lua_touserdata(Lua, 1);
		Object* Obj = (Object*)p->Data;
		
		delete Obj;
		return 0;
	}
}


