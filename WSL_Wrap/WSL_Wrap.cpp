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

	LPTSTR exeName = new TCHAR[MAX_PATH];


	GetModuleFileName(nullptr, exeName, MAX_PATH);

	

	LPTSTR sz_AllParametersOrigin= _tcsdup(GetCommandLine());


	sz_AllParametersOrigin = sz_AllParametersOrigin + _tcslen(rArray[0]);



	TCHAR buffer[8200] =
		__T("bash -c \"");

	exeName = _tcsrchr(exeName, __T('\\'));

	if (exeName) {


		exeName = &(exeName[1]);


	}
	
	std::wstring exeString(exeName);
	std::string::size_type iii = exeString.find(__T(".exe"));

	if (iii != std::string::npos)
		exeString.erase(iii, 4);

		_tcscat_s(buffer, exeString.c_str());

	System::String^ str_parameter;


	std::vector<std::wstring>* v_pathVector = new std::vector<std::wstring>;
	std::vector<std::wstring>* v_pathVectorOri = new std::vector<std::wstring>;

	for (size_t i = 1; i < argc; i++) {

		str_parameter = gcnew System::String(rArray[i]);

		if (IsPathValid(str_parameter)) {

			TCHAR path[MAX_PATH] = __T("/mnt/");

			TCHAR sa = _totlower(*rArray[i]);

			_tcsncat_s(path, &sa, 1);

			std::wstring s(&rArray[i][2]);

			std::replace(s.begin(), s.end(), __T('\\'), __T('/'));

			_tcscat_s(path, s.c_str());
		

			std::wstring s1(rArray[i]);
			std::wstring s2(path);
			
			v_pathVectorOri->push_back(s1);
			v_pathVector->push_back(s2);




		}


		delete str_parameter;



	}

	std::wstring s(sz_AllParametersOrigin);


	while (v_pathVector->size() != 0)

	{
	
		size_t pos = s.rfind(v_pathVectorOri->back());
		s.replace(pos, v_pathVectorOri->back().size(), v_pathVector->back());

		v_pathVectorOri->pop_back();
		v_pathVector->pop_back();
	}


	
	_tcscat_s(buffer, s.c_str());

	_tcscat_s(buffer, __T("\""));



	_tprintf(L"%ls", buffer);



	return 0; //_wsystem(buffer);


}
