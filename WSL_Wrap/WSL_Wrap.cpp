#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include  <string>
#include <algorithm>
#include <vector>
#using <system.dll>


using namespace System;

bool IsPathValid(String^ path) {


	if (!(path->Contains(":\\")))return false;

	try {
		String^ fullPath = System::IO::Path::GetFullPath(path);


		return !String::Compare(fullPath, path, true);

	}
	catch (System::Exception^

		) {


		return false;

	}

}
int _tmain(int argc, TCHAR*argv[])
{
	setlocale(LC_ALL, "");


	TCHAR**  rArray =  new TCHAR*[argc+1];

	for (int i = 0; i < argc; i++) {


	
	

		rArray[i]= _tcsdup(argv[i]);
		


			
	}
	std::wstring exeString(rArray[0]);

	

	std::wstring str_parameter0(GetCommandLine());
	
	if (str_parameter0.at(0) == L'\"'){
		str_parameter0.erase(str_parameter0.begin(), str_parameter0.begin()+ exeString.length()+2);

	}
	else {

		str_parameter0.erase(str_parameter0.begin(), str_parameter0.begin() + exeString.length());

	}

	size_t pos = exeString.rfind(L"\\")+1;
	size_t len = exeString.rfind(L".") - pos;


	std::wstring exeFileName = exeString.substr(pos, len);

//	_tprintf(L"%ls", exeFileName.c_str()); return 0;

	TCHAR buffer[8200] =
		__T("bash -c \"");


	
	
	

		_tcscat_s(buffer, 
			
			
			exeFileName.c_str());

	System::String^ str_parameter;


	std::vector<std::wstring>* v_pathVector = new std::vector<std::wstring>;
	std::vector<std::wstring>* v_pathVectorOri = new std::vector<std::wstring>;

	for (size_t i = 1; i < argc; i++) {

		str_parameter = gcnew System::String(rArray[i]);

		if (IsPathValid(str_parameter)) {

			std::wstring path(L"/mnt/");

			

			TCHAR  letter = tolower(rArray[i][0]);

			path.append(&letter);


			path.append(&rArray[i][2]);



			std::replace(path.begin(), path.end(), __T('\\'), __T('/'));



			std::wstring s1(rArray[i]);
			
			
			v_pathVectorOri->push_back(s1);
			v_pathVector->push_back(path);




		}


		delete str_parameter;



	}

	


	while (v_pathVector->size() != 0)

	{
	
		size_t pos = str_parameter0.rfind(v_pathVectorOri->back());
		str_parameter0.replace(pos, v_pathVectorOri->back().size(), v_pathVector->back());

		v_pathVectorOri->pop_back();
		v_pathVector->pop_back();
	}


	
	_tcscat_s(buffer, str_parameter0.c_str());
	

	_tcscat_s(buffer, __T("\""));



//	_tprintf(L"%ls", buffer); return 0;



	return  _wsystem(buffer);


}
