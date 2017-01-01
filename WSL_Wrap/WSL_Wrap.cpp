#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include  <string>

#using <system.dll>


using namespace System;


int main(int argc, char *argv[])
{
	

	


	char buffer[8200] =
		"\"bash -c \"";

	char * exeName = strrchr(argv[0], '\\');
	char * extName = strrchr(exeName, '.');

	if (extName) {

		if (!_stricmp(extName, ".exe")) {
		
			extName[0] = '\0';


		}


	}

	if (exeName) {
		exeName++;


	}



	if (exeName) {
		strcat_s(buffer, exeName);

	}
	else
	{
		strcat_s(buffer, argv[0]);
	}
	try{
	System::Uri^  siteUri = gcnew Uri("dsd");
	}
	finally{


	}

	for (int i = 1; i < argc; i++) {


		strcat_s(buffer, " ");

		System::String^ para=gcnew System::String(argv[i]);
	
		System::Uri  siteUri(para);

		if (siteUri.IsWellFormedOriginalString()) {

			System::Console::WriteLine(para);

		}
		else
		{
			strcat_s(buffer, argv[i]);
		}
	
		
aa
	}

	//strcat_s(buffer, " \"\"");

//	system(buffer);



}
