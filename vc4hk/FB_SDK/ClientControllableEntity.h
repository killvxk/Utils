#ifndef _ClientControllableEntity_H
#define _ClientControllableEntity_H
#include "Frostbite_Classes.h"

namespace fb
{
	class ClientControllableEntity
	{
	public:
		virtual TypeInfo* GetType();
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //
		virtual void Function10(); //
		virtual void Function11(); //
		virtual void Function12(); //
		virtual void Function13(); //
		virtual void Function14(); //
		virtual void Function15(); //
		virtual void Function16(); //
		virtual void Function17(); //
		virtual void Function18(); //
		virtual void Function19(); //
		virtual void Function20(); //
		virtual void Function21(); //
		virtual void GetAABB(void* pAABB); //TransformAABBStruct*
		virtual void GetTransform(void* mTransform);
		virtual void Function24(); //
		virtual void Function25(); //
		virtual void Function26(); //
		virtual void Function27();
		virtual void Function28(); //
		virtual void Function29(); //
		virtual void Function30(); //
		virtual void Function31(); //
		virtual void Function32(); //
		virtual void Function33(); //
		virtual void Function34(); //
		virtual void Function35(); //
		virtual void Function36(); //
		virtual void Function37(); //
		virtual void Function38(); //
		virtual void Function39(); //
		virtual void Function40(); //
		virtual void Function41(); //
		virtual void Function42(); //
		virtual void Function43(); //
		virtual void Function44(); //
		virtual void Function45(); //
		virtual void Function46(); //
		virtual void Function47(); //
		virtual void Function48(); //
		virtual void Function49(); //
		virtual void Function50(); //
		virtual void Function51(); //
		virtual void Function52(); //
		virtual void Function53(); //
		virtual void Function54(); //
		virtual void Function55(); //
		virtual void Function56(); //
		virtual void Function57(); //
		virtual void Function58(); //
		virtual void Function59(); //
		virtual void* GetPhysiscsEntity(); //physics
		virtual Vec4 * GetVelocity(); //velocity
		virtual void Function62(); //
		virtual void Function63(); //
		virtual void Function64(); //
		virtual void Function65(); //
		virtual void Function66(); //
		virtual void Function67(); //
		virtual void Function68(); //
		virtual void Function69(); //
		virtual void Function70(); //
		virtual void Function71(); //
		virtual void Function72(); //
		virtual void Function73(); //
		virtual void Function74(); //

		char pad_0x0008[0x12]; //0x0008 
		BYTE m_RenderChamsBehindBigWall; //0x001A
		char pad_0x001B[0x15]; //0x001B
		__int64 m_Data; //0x0030 
		void* m_Complist;//0x0038
		char _0x0040[0xc0]; 
		float m_Velocity; //0x0100 
	
		char _0x104[0xc];//0x0104
		void * m_entryComponent;//0x110
		char _0x118[0x28];

		HealthComponent* m_pHealthComp; //0x0140 

	

	

	};//Size=0x0148


};

#endif