#include "stdafx.h"
#include <Windows.h>
#include <string>
#using <system.dll>


using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;

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

void MarshalString(String ^ s, std::wstring& os) {
	using namespace Runtime::InteropServices;
	const wchar_t* chars =
		(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}
int _tmain(int argc, TCHAR*argv[])
{
	setlocale(LC_ALL, "");


	String^   str_Exe_Const = gcnew String(argv[0]);


	String ^ str_fullCommandLine_Const = gcnew String(GetCommandLine());


	Text::StringBuilder^ str_fullCommandLine;


	Text::StringBuilder^   str_Exe;

	if (str_fullCommandLine_Const->StartsWith(L"\"")) {

		str_fullCommandLine = gcnew StringBuilder(
			str_fullCommandLine_Const->Substring(str_Exe_Const->Length + 2));


	}
	else {
		str_fullCommandLine = gcnew StringBuilder(
			str_fullCommandLine_Const->Substring(str_Exe_Const->Length));
	}

	int n_FileNameStart = str_Exe_Const->LastIndexOf(L'\\') + 1;

	int n_FileNameLen = str_Exe_Const->LastIndexOf(L'.') - n_FileNameStart;

	str_Exe = gcnew System::Text::StringBuilder(str_Exe_Const->Substring(n_FileNameStart, n_FileNameLen));

	StringBuilder^ str_commandBuffer = gcnew StringBuilder(__T("bash -c \""));

	str_commandBuffer->Append(str_Exe);




	for (int i = 1; i < argc; i++) {

		String ^	str_parameter = gcnew String(argv[i]);

		if (IsPathValid(str_parameter)) {

			StringBuilder path(L"/mnt/");

			path.Append(str_parameter->Substring(0, 1)->ToLower());

			path.Append(str_parameter->Substring(2));

			path.Replace(__T('\\'), __T('/'));


			str_fullCommandLine->Replace(str_parameter, path.ToString());

		}
		else {
			continue;
		}

	}

	str_commandBuffer->Append(str_fullCommandLine);


	str_commandBuffer->Append(__T('\"'));


	std::wstring a;
	MarshalString(str_commandBuffer->ToString(), a);
#ifdef DEBUG
	printf_s("%ls", a.c_str());
	return 0;
#else
	return _wsystem(a.c_str());
#endif 
}
