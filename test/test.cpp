#include "stdafx.h"
#include <iostream>
#include <windows.h >
#include <fstream>
#include<stdio.h>
#include<string>
using namespace std;
struct Base
{
	virtual void a() { std::cout << "Base::a()" << std::endl; }

	virtual void b() { std::cout << "Base::b()" << std::endl; }

	virtual	 void c() { std::cout << "Base::c()" << std::endl; }

	void d() { std::cout << "Base::d() " << std::endl; };
	void e() { std::cout << "Base::g() " << std::endl; };
};

struct Derived :Base
{
	virtual void f() { std::cout << "Derived::e()" << std::endl; }
};

template <typename VF >
int discovertableindex(VF fun)
{
	return (int)(*(int*)(*(int*)&fun + 0x8) / 4);
}


typedef void(Base:: *functionPtr)();

template <class T>
int SeeBits(T func)
{
	union
	{
		T ptr;
		int i;
	};
	ptr = func;

	return i;
}
void* find_f_address(void* aClass)
{
	/* The virtual function table is stored at the beginning of the object.  */
	void** vtable = *(void***)aClass;

	/* This structure is described in the cross-platform "Itanium" C++ ABI:

	http://mentorembedded.github.io/cxx-abi/abi.html

	The particular layout replicated here is described in:

	http://mentorembedded.github.io/cxx-abi/abi.html#member-pointers  */
	struct pointerToMember
	{
		/* This field has separate representations for non-virtual and virtual
		functions.  For non-virtual functions, this field is simply the
		address of the function.  For our case, virtual functions, this
		field is 1 plus the virtual table offset (in bytes) of the function
		in question.  The least-significant bit therefore discriminates
		between virtual and non-virtual functions.

		"Ah," you say, "what about architectures where function pointers do
		not necessarily have even addresses?"  (ARM, MIPS, and AArch64 are
		the major ones.)  Excellent point.  Please see below.  */
		size_t pointerOrOffset;

		/* This field is only interesting for calling the function; it
		describes the amount that the `this' pointer must be adjusted
		prior to the call.  However, on architectures where function
		pointers do not necessarily have even addresses, this field has the
		representation:

		2 * adjustment + (virtual_function_p ? 1 : 0)  */
		ptrdiff_t thisAdjustment;
	};

	/* Translate from the opaque pointer-to-member type representation to
	the representation given above.  */
	pointerToMember p;
	//int((AbstractClass::*m)()) = &AbstractClass::f;
void*	m = nullptr;
	memcpy(&p, &m, sizeof(p));

	/* Compute the actual offset into the vtable.  Given the differing meaing
	of the fields between architectures, as described above, and that
	there's no convenient preprocessor macro, we have to do this
	ourselves.  */
#if defined(__arm__) || defined(__mips__) || defined(__aarch64__)
	/* No adjustment required to `pointerOrOffset'.  */
	static const size_t pfnAdjustment = 0;
#else
	/* Strip off the lowest bit of `pointerOrOffset'.  */
	static const size_t pfnAdjustment = 1;
#endif

	size_t offset = (p.pointerOrOffset - pfnAdjustment) / sizeof(void*);

	/* Now grab the address out of the vtable and return it.  */
	return vtable[offset];
}
char *buffer = new char[0xff];
std::ofstream log_file(
	"E:\\log\\hk.log");


void logxxx(const std::string &text)
{

	log_file << text << std::endl;
}
int main()
{
	LPOSVERSIONINFO mod_lpVersionInfo = new OSVERSIONINFO;

	GetVersionEx(mod_lpVersionInfo);
	printf_s("dwOSVersionInfoSize=%x\ndwBuildNumber=%x\ndwPlatformId:%x\nszCSDVersion:%ls\n",mod_lpVersionInfo->dwOSVersionInfoSize
	, mod_lpVersionInfo->dwBuildNumber,
		mod_lpVersionInfo->dwPlatformId,mod_lpVersionInfo->szCSDVersion);
}