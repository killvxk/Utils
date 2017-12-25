#include "stdafx.h"
#include <Windows.h>
#include <string>
#include <shellapi.h>
#using <system.dll>


using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace System::Diagnostics;

bool IsPathValid(String^ path) {
    if (!(path->Contains(":\\")))return false;
    try {
        String^ fullPath = System::IO::Path::GetFullPath(path);
        return !String::Compare(fullPath, path, true);
    }
    catch (System::Exception^) {
        return false;
    }
}


int main(array<String^>^ args)
{
    setlocale(LC_ALL, "");

    String^ oExe = System::Diagnostics::Process::GetCurrentProcess()->MainModule->FileName;

    String^ outputExe= System::IO::Path::GetFileNameWithoutExtension(oExe);

    StringBuilder^ commandBuffer = gcnew StringBuilder("wsl.exe ");

    commandBuffer->Append(outputExe);

    for (int i = 0; i < args->Length; i++) {

        commandBuffer->Append(" ");

        String ^ str_parameter = gcnew String(args[i]);

        if (IsPathValid(str_parameter)) {

            StringBuilder path(L"/mnt/");

            path.Append(str_parameter->Substring(0, 1)->ToLower());

            path.Append(str_parameter->Substring(2));

            path.Replace(__T('\\'), __T('/'));

            str_parameter = path.ToString();

        }

        commandBuffer->Append(str_parameter);

    }

    String^ argsx = commandBuffer->ToString();

    const wchar_t* chars = (const wchar_t*)
        (Runtime::InteropServices::Marshal::StringToHGlobalUni(argsx)).ToPointer();

    //wprintf(chars);

    return _wsystem(chars);

}
