#ifndef _VEC3_H
#define _VEC3_H

//#include "../Frostbite_classes.h"

namespace fb
{

	class Vec4
	{
	public:
		union
		{
			struct
			{
				FLOAT x;
				FLOAT y;
				FLOAT z;
				FLOAT w;
			};
			FLOAT data[4];
		};
		Vec4() : x(0.f), y(0.f), z(0.f), w(0.f) {


		}


		Vec4(FLOAT x,
			FLOAT y,
			FLOAT z,
			FLOAT w) : x(x), y(y), z(z), w(w) {


		}

		Vec4(FLOAT x,
			FLOAT y,
			FLOAT z) : x(x), y(y), z(z), w(0.f) {


		}
		void print(char* pthis)
		{
			//LOG.Write("%s Vec3 at 0x%.8X: (%5.1f|%5.1f|%5.1f)\n",pthis,this,x,y,z);
		}
		float len(void)
		{
			return sqrt(x*x + y*y + z*z);
		}
		void normalize(void)
		{
			float _l = len();
			this->x /= _l;
			this->y /= _l;
			this->z /= _l;
		}
		void initialize(void)
		{

			this->x /= 1;
			this->y /= 1;
			this->z = 1;
		}
		Vec4 operator * (float const &other)
		{
			this->x *= other;
			this->y *= other;
			this->z *= other;
			return *this;
		}
		Vec4 operator + (Vec4 const &other)
		{
			Vec4 v;
			v.x = this->x + other.x;
			v.y = this->y + other.y;
			v.z = this->z + other.z;
			return v;
		}

		Vec4 operator - (Vec4 const &other)
		{
			Vec4 v;
			v.x = this->x - other.x;
			v.y = this->y - other.y;
			v.z = this->z - other.z;
			return v;
		}
		Vec4 operator += (Vec4 const &other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			return *this;
		}
		//new from me 
		Vec4 operator -= (Vec4 const &other)
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			return *this;
		}
		bool operator ==(Vec4 const &other)
		{
			if (this->x == other.x)
			{
				if (this->y == other.y)
				{
					if (this->z == other.z)
					{
						return true;
					}
				}
			}
			return false;
		}
		//new from me Calculate Dotproduct
		float Dot(Vec4 Vec)
		{
			return this->x * Vec.x + this->y * Vec.y + this->z * Vec.z;
		}

		// new from me get VecLength
		float VectorLength()
		{
			return sqrt(((this->x)*(this->x)) + ((this->y)*(this->y)) + ((this->z)*(this->z)));
		}
		float VectorLength2()
		{
			return sqrt(((this->x)*(this->x)) + ((this->z)*(this->z)));
		}
		//new from me get distance to vec
		float DistanceToVector(Vec4 const &other)
		{
			Vec4 Distance;
			Distance.x = other.x - this->x;
			Distance.y = other.y - this->y;
			Distance.z = other.z - this->z;
			return sqrt((Distance.x * Distance.x) + (Distance.y * Distance.y) + (Distance.z * Distance.z));
		}
		float DistanceFrom(Vec4 & point)
		{
			float x2 = (point.x - x) * (point.x - x);
			float y2 = (point.y - y) * (point.y - y);
			float z2 = (point.z - z) * (point.z - z);

			float dist = sqrt(x2 + y2 + z2);

			return dist;
		}



		//new from me calc Veccrossize
		Vec4 VectorCrossSize(CONST Vec4 *pV1, CONST Vec4 *pV2)
		{
			this->x = pV1->y * pV2->z - pV1->z * pV2->y;
			this->y = pV1->z * pV2->x - pV1->x * pV2->z;
			this->z = pV1->x * pV2->y - pV1->y * pV2->x;
			return *this;
		}



		

	};


};

#endif