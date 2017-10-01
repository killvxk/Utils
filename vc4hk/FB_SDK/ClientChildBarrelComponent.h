#ifndef _ClientChildBarrelComponent_H
#define _ClientChildBarrelComponent_H
#include "Frostbite_Classes.h"
namespace fb
{
	class ChildRotationBodyData
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

		char pad_0x0008[0x8]; //0x0008
		float m_Mass; //0x0010 
		float m_Inertia; //0x0014 
		float m_AngularMomentumMultiplier; //0x0018 
		float m_AngularMomentumThreshold; //0x001C 
		float m_AngularMomentumDamping; //0x0020 
		float m_AngularMomentumDampingAcc; //0x0024 
		float m_AngularMomentumDampingDeacc; //0x0028 
		float m_AngularConstraintMin; //0x002C 
		float m_AngularConstraintMax; //0x0030 
		__int32 m_RotationAxis; //0x0034 
		char pad_0x0038[0x8]; //0x0038
		unsigned char m_UsePostSatisfyConstraints; //0x0040 
		unsigned char m_UseAngularMomentumThreshold; //0x0041 
		unsigned char m_UseAngularMomentumDamping; //0x0042 
		unsigned char m_UseAngularConstraint; //0x0043 
		char pad_0x0044[0x4]; //0x0044
		float m_ForceModifier; //0x0048 
		float m_ResetForceModifier; //0x004C 
		float m_ResetForceInputThreshold; //0x0050 
		char pad_0x0054[0x4]; //0x0054
		float m_WorldSpaceLockEfficiency; //0x0058 
		unsigned char m_UseLinearInput; //0x005C 
		char pad_0x005D[0x23]; //0x005D

	}; //Size=0x0080
	class ClientChildBarrelComponent
	{
	public:
		virtual void Function0(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual TypeInfo* GetType();
		virtual void Function9(); //

		void* N00002F68; //0x0008 
		DynamicPhysicsEntity* N00002F69; //0x0010 
		float N00002F6A; //0x0018 
		char pad_0x001C[0x4]; //0x001C
		ChildRotationBodyData* m_ChildRotationBodyData; //0x0020 
		char pad_0x0028[0x18]; //0x0028

	}; //Size=0x0040
}
#endif