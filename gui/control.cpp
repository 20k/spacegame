#include "gui/control.h"

namespace Gui
{
	Control::Control( double X, double Y, Control* Parent )
		: m_Parent(Parent), X(X), Y(Y)
	{
	}
	
	// Lua
	
	LUA_CONSTRUCTOR(Control)
		LUA_ARG_DOUBLE()
		LUA_ARG_DOUBLE()
		LUA_ARG_USERDATA_END(Control)
	LUA_ENDCONSTRUCTOR(Control)
	
	LUA_FUNCTIONS(Control)
		LUA_FUNCTION("New", &Control::Lua_New)
	LUA_ENDFUNCTIONS()
}

