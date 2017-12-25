#ifndef _MaterialContainerPair_H
#define _MaterialContainerPair_H

#include "FB_SDK/Frostbite_Classes.h"



namespace fb
{
	class MaterialContainerPair
		: public DataContainer			// 0x00
	{
	public:
		DWORD m_flagsAndIndex;			// 0x08
		char m_physicsPropertyIndex;	// 0x0C
		char m_physicsMaterialIndex;	// 0x0D
		PAD(0x2);						// 0x0E
		__forceinline BOOL isPenetrable()
		{
			return m_flagsAndIndex & 0x80000000;
		};

		__forceinline BOOL isSeeTrough()
		{
			return m_flagsAndIndex & 0x20000000 ;
		};


		__forceinline BOOL isClientDestructible()
		{
			return m_flagsAndIndex & 0x40000000;
		};

		__forceinline BOOL isBashable(void)
		{
			return m_flagsAndIndex & MfBashable;
		};


	    __forceinline BOOL NoCollisionResponse(void)
		{
			return m_flagsAndIndex & MfNoCollisionResponse ;
		};

		__forceinline BOOL NoCollisionResponseCombined(void)
		{
			return m_flagsAndIndex & MfNoCollisionResponseCombined ;
		}
		
	}; // 0x10

};

#endif