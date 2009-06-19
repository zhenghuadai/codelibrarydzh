#include "stdafx.h"
#include "windows.h"
#include "iostream"
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
#if 0
	　　BOOL CreateProcess
		　　(
				　　LPCTSTR lpApplicationName,
				　　LPTSTR lpCommandLine,
				　　LPSECURITY_ATTRIBUTES lpProcessAttributes。
				　　LPSECURITY_ATTRIBUTES lpThreadAttributes,
				　　BOOL bInheritHandles,
				　　DWORD dwCreationFlags,
				　　LPVOID lpEnvironment,
				　　LPCTSTR lpCurrentDirectory,
				　　LPSTARTUPINFO lpStartupInfo,
				　　LPPROCESS_INFORMATION lpProcessInformation
				　　);
#endif
#if 1
	STARTUPINFO startupInfo;
	memset(&startupInfo,0,sizeof(STARTUPINFO));
	startupInfo.cb = sizeof(STARTUPINFO);
	startupInfo.dwFlags |= STARTF_USESHOWWINDOW;
	startupInfo.wShowWindow = SW_SHOWMAXIMIZED;
	PROCESS_INFORMATION ProcessInfo;
	LPCWSTR cmdline = _T("c:\\windows\\notepad.exe");
	LPWSTR  cmdargs = _T(" mytext.txt");
	BOOL ret;
	ret = CreateProcess(ret
			cmdline,
			cmdargs,
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&startupInfo,
			&ProcessInfo);
	if(ret == false){
		cout<<"create err\n"<< endl;
	}
	WaitForSingleObject(ProcessInfo.hProcess,1000000);

#endif
#if 0
	WinExec("notepad.exe mytext.txt",SW_SHOW); 
#endif
	return 0;
}
