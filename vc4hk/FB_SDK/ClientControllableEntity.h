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
		virtual const Vec3 * GetVelocity(); //velocity
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

		char _0x0000[10]; //0x0000 
		unsigned char m_OcclusionFlags; //0x0012 
		char _0x0013[13]; //0x0013 
		char _0x0020[16];
		__int64 m_Data; //0x0030 
		char _0x0038[200];
		float m_Velocity; //0x0100 
		char _0x104[0xc];//0x0104
		void * m_entryComponent;//0x110
		char _0x108[0x38];

		HealthComponent* m_pHealthComp; //0x0140 

		class trashclass
		{
		public:
			ITypedObject* Object; //0x0000
			BYTE size;//0x8
			char a[0x17];//0x9
			
		};//Size=0x0020


	
		std::vector<void*>* GetClientComponentByID(int Id)

		{
			trashclass* trashclass1 = *((trashclass**)((intptr_t)this + 0x38));

			
			std::vector<void*>* vector = new std::vector<void*>;

			for (int obj_index = 0; obj_index <= trashclass1[0].size;obj_index++) 

			{
				

				fb::ClassInfo* pType = (fb::ClassInfo*)trashclass1[obj_index].Object->GetType();

				if (POINTERCHK(pType)) {


				if (pType->m_ClassId == Id) {

					vector->push_back((void*)(trashclass1[obj_index].Object));


				}
			}

				
			


			}

			if (vector->size()>0) {
				return	vector;
			}
			else {
				delete vector;
				vector = nullptr;
				return nullptr;
			}
		}
	};//Size=0x0148


};

#endif