#pragma once
#ifndef __INCLUDES__H_
#define __INCLUDES__H_
#include<vector>





#define _PTR_MAX_VALUE (0x000F000000000000)
//#define POINTERCHK(p)  ((p >= (void*)0x10000) && (p < _PTR_MAX_VALUE) && (p != nullptr))

#define one_pi 0x141A0D8D8



#define M_PI 3.1415926535897932384626433832795f
#define Twice_PI  6.283185307179586476925286766559f
#define DegToRad 0.01745329251994329576923690768489f

#define Float32 float
#define Float64 double
#define Boolean bool
#define Uint32 unsigned __int32
#define Int32 __int32
#define Uint8  unsigned __int8
#define Int8	__int8
#define Uint16 unsigned __int16
#define Int16 __int16
#define Uint64 unsigned __int64
#define Int64 __int64
#define CString char*

#endif

inline static bool IsValidPtr(void* ptr) {


	if (((intptr_t)ptr >= 0x10000) && ((intptr_t)ptr < _PTR_MAX_VALUE)&&(ptr!=nullptr) ) {
		__try
		{
			
			BYTE a = *(BYTE*)ptr;
				return true;
		
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return false;
		}

	}
	else
	{
		return false;
	}

}