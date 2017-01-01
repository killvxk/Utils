#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include  <string>
#include <algorithm>
#using <system.dll>


using namespace System;

bool IsPathValid(String^ path) {


	try {
		String^ fullPath = System::IO::Path::GetFullPath(path);


		return !String::Compare(fullPath, path, true);

	}
	catch (System::Exception^

		) {


		return false;

	}

}
int _tmain(int argc, TCHAR *argv[])
{
	setlocale(LC_ALL, "");
	


		TCHAR buffer[8200] =
			__T("\"bash -c \"");

	TCHAR * exeName = _tcsrchr(argv[0], __T('\\'));
	TCHAR * extName = _tcsrchr(exeName, __T('.'));

	if (extName) {

		if (!_tcsicmp(extName, __T(".exe"))) {

			extName[0] = __T('\0');


		}


	}

	if (exeName) {
		exeName++;


	}



	if (exeName) {
		_tcscat_s(buffer, exeName);

	}
	else
	{
		_tcscat_s(buffer, argv[0]);
	}

	System::String^ para;



	for (int i = 1; i < argc; i++) {


		_tcscat_s(buffer, __T(" "));

		 para = gcnew System::String(argv[i]);



		if (IsPathValid(para)) {

			TCHAR path[MAX_PATH] = __T("/mnt/");
		
			TCHAR sa = _totlower(*argv[i]);
		
			_tcsncat_s(path,&sa ,1);

			std::wstring s(&argv[i][2]);

			std::replace(s.begin(), s.end(), __T('\\'), __T('/'));

			_tcscat_s(path,s.c_str() );

			_tcscat_s(buffer, path);
		


		}
		else
		{
			_tcscat_s(buffer, argv[i]);
		}

	}

	delete para;

	_tcscat_s(buffer, __T("\"\""));




	return	_wsystem(buffer);


}
