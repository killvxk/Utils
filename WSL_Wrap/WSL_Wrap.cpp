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
int main(int argc, char* argv[])
{
	


	char buffer[8200] =
		"\"bash -c \"";

	char * exeName = _tcsrchr(argv[0], '\\');
	char * extName = _tcsrchr(exeName, '.');

	if (extName) {

		if (!_tcsicmp(extName, ".exe")) {

			extName[0] = '\0';


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





	for (int i = 1; i < argc; i++) {


		_tcscat_s(buffer," ");

		System::String^ para = gcnew System::String(argv[i]);



		if (IsPathValid(para)) {

			char path[MAX_PATH] = "/mnt/";
		
			char sa = _totlower(*argv[i]);
		
			_tcsncat_s(path,&sa ,1);

			std::string s(&argv[i][2]);

			std::replace(s.begin(), s.end(), '\\', '/');

			_tcscat_s(path,s.c_str() );

			_tcscat_s(buffer, path);
		


		}
		else
		{
			_tcscat_s(buffer, argv[i]);
		}



	}

	_tcscat_s(buffer, "\"\"");




//	_tprintf_s(buffer);
	

	return	system(buffer);


}
