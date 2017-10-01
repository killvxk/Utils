#ifndef _ClientChildComponent_H
#define _ClientChildComponent_H
#include "Frostbite_Classes.h"
namespace fb
{
	class ClientChildComponent
	{
	public:
		virtual void GetType(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //

		char pad_0x0008[0x30]; //0x0008
		ClientChildBarrelComponent m_ClientChildBarrelComponent; //0x0038 
		char pad_0x0078[0x38]; //0x0078
	
		char pad_0x00D0[0x3A8]; //0x00D0

	}; //Size=0x0478
}
#endif