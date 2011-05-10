#ifndef INCLUDES_GUI_CONTROL_H
#define INCLUDES_GUI_CONTROL_H

#include "common.h"
#include "scripting/object.h"

#include <list>

namespace Gui
{
	class Control : public Scripting::Object
	{
		public:
			Control( double X, double Y, Control* Parent = 0 );
		
		protected:
			Control* m_Parent;
			std::list<Control*> m_Children;
			
			double X, Y;
			
		public:
			LUA_OBJECT()
			LUA_HASFUNCTIONS()
	};
}

#endif /* INCLUDES_GUI_CONTROL_H */

