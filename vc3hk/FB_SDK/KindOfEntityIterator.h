#ifndef _KindOfEntityIterator_H
#define _KindOfEntityIterator_H
#include "FB_SDK/Frostbite_Classes.h"
#include "FB_SDK/EntityWorld.h"
namespace fb
{
	template<typename T> struct KindOfEntityIterator 
	:public fb::EntityWorld::EntityIterator
	{
			KindOfEntityIterator()
			{}

			KindOfEntityIterator(fb::EntityWorld* manager,fb::ClassInfo* classId, bool onlyIncludeIterable = true)
			{
				manager->kindOfQuery(classId,this,onlyIncludeIterable);
			}
	};

};

#endif