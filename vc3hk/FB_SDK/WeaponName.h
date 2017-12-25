#ifndef _WeaponName_H
#define _WeaponName_H
#include "FB_SDK/Frostbite_Classes.h"
namespace fb
{
	
	class WeaponName
	{
	public:
		unsigned char pad0[8];
        char m_name[0x10];//eastl::basic_string<char> m_name;
	};

};

#endif