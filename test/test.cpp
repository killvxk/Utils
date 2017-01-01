#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include <wchar.h>  
#include <locale.h>  
int _tmain(int argc, TCHAR *argv[])
{
	setlocale(LC_ALL, "");
	wchar_t* s = L"我的及哦";


	printf("printf content start: %ls\n", s);
	
	

}