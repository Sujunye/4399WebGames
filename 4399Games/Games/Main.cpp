// Games.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Games.h"
#include "MainWnd.h"
#include "CefBase/util.h"
#include "CefBase/CefAppEx.h"

#ifdef _DEBUG
#	pragma comment(lib, "./cef/lib_Debug/libcef_dll_wrapper90")
#else
#	pragma comment(lib, "./cef/lib_Release/libcef_dll_wrapper90")
#endif
#	pragma comment(lib, "./cef/lib_Release/libcef")


void ChangeRegedit(const wchar_t* pExeName);
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	CefMainArgs main_args(hInstance);
	CefRefPtr<CCefAppEx> app(new CCefAppEx);
	int exit_code = CefExecuteProcess(main_args, app.get()); //���������
	if (exit_code >= 0)
	{
		return exit_code;
	}
	CoInitialize(NULL);
	g_strExePath = GetRunPathW();
	CefSettings settings;
	settings.log_severity = LOGSEVERITY_DISABLE;
	wstring strCachePath = g_strExePath + L"Cache\\Web";
	SHCreateDirectoryEx(NULL, strCachePath.c_str(), NULL);
	cef_string_set(strCachePath.c_str(), strCachePath.size(), &settings.cache_path, 1);
	//settings.multi_threaded_message_loop = true;
	CefInitialize(main_args, settings, app.get());

// 	wchar_t szPath[MAX_PATH];
// 	GetModuleFileName(NULL, szPath, MAX_PATH);
// 	ChangeRegedit(szPath);
	CPaintManagerUI::SetInstance(hInstance);
	CWndShadow::Initialize(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	CMainWnd* pWnd = new CMainWnd;
	pWnd->Create(NULL, L"����С��Ϸ", UI_WNDSTYLE_FRAME^WS_MAXIMIZEBOX, 0);
	pWnd->StartLoadImgs();
	pWnd->CenterWindow();
	pWnd->ShowWindow();
	//CPaintManagerUI::MessageLoop();
	CefRunMessageLoop();
#ifndef _DEBUG
	CefShutdown();
#endif
	CoUninitialize();
	delete pWnd;
	pWnd=NULL;
	return 0;
}


void ChangeRegedit(const wchar_t* pExeName)  
{  
	if ( NULL == pExeName )  
		return ;  
	TCHAR szVersion[64] = {0};     
	DWORD dwSize = 64;     
	HKEY hKey;  
	// �Ȼ�ȡIE�汾  
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Internet Explorer"), 0, KEY_READ, &hKey))  
	{  
		//���ȶ�ȡIE11��λ��  
		DWORD dwIeVersion = 0;  
		if ( ERROR_SUCCESS == RegQueryValueEx(hKey, L"svcVersion", 0, NULL, (LPBYTE)szVersion, &dwSize) )  
		{  
			TCHAR *pos = _tcschr(szVersion, TEXT('.'));  
			if ( pos )  
				dwIeVersion = _ttoi(szVersion);  
		}  
		if ( dwIeVersion == 0 )  
		{//��ȡIE�Ͱ汾��λ��  
			if ( ERROR_SUCCESS == (hKey, L"Version", 0, NULL, (LPBYTE)szVersion, &dwSize) )  
			{  
				TCHAR *pos = _tcschr(szVersion, TEXT('.'));  
				if (NULL == pos)  
				{  
					RegCloseKey(hKey);  
					return ;  
				}  
				*pos = 0;  
				dwIeVersion = _ttoi(szVersion);  
			}  
		}  
		RegCloseKey(hKey);  
		switch( dwIeVersion )  
		{  
		case 11: dwIeVersion = 11001; break;  
		case 10: dwIeVersion = 10001; break;  
		case 9: dwIeVersion = 9999; break;  
		case 8: dwIeVersion = 8888; break;  
		default: return ;  
		}  
		// ����Ӧ�ó���ʹ�õ�IE�汾  
		if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Internet Explorer\\MAIN\\FeatureControl\\FEATURE_BROWSER_EMULATION", 0, KEY_WRITE, &hKey))  
		{  
			dwSize = sizeof(dwIeVersion);  
			RegSetValueEx(hKey, pExeName, 0, REG_DWORD, (LPBYTE)&dwIeVersion, dwSize);  
			RegCloseKey(hKey);  
		}  
	}  
}  
