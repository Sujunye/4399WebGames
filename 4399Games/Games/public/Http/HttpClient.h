/********************************************************
*Desc���򵥷�װ��WinHttp API�ӿڣ��ṩHTTP�������ع���
*Author��Jelinyao
*Date��	2015-5
*/

#pragma once
#include <Windows.h>
#include "Winhttp.h"
#include <string>
using std::string;
using std::wstring;
typedef LPVOID HINTERNET;


class CHttpClientLoadCallback
{
public:
	virtual void	OnHttpLoading(const DWORD dwTotalSize, const DWORD dwLoadSize, void* lpParam) = 0;
};

class CHttpClientStopCallback
{
public:
	virtual BOOL	IsNeedStop() = 0;
};

enum RequestType
{
	Post,
	Get,
};

class CHttpClient
{
public:
	CHttpClient(void);
	virtual ~CHttpClient(void);
	bool	Init();
	void	Release();
	bool	DownLoadFile(LPCTSTR lpUrl, LPCTSTR lpFilePath);
	bool	DownLoadMem(LPCTSTR lpUrl, OUT void** lpBuffer, OUT DWORD& dwSize);
	string	Request(LPCTSTR lpUrl, RequestType type, LPCSTR lpPostData = NULL);
	void	SetLoadCallback(CHttpClientLoadCallback* pCallback, void* lpParam)	{ m_pLoadCallback = pCallback; m_lpParam = lpParam; }
	void	SetTimeOut(int dwConnectTime,  int dwSendTime, int dwRecvTime);
	bool	DownloadFileForRetry(LPCTSTR lpUrl, const wstring& strFilePath, int nTryCount = 3);//���غ������ṩ��ʱ���ƣ�Ĭ������3��
	LPCTSTR	GetError()		{ return m_strError.c_str(); }
	void	SetStopCallback(CHttpClientStopCallback* pCallback)	{ m_pStopCallback = pCallback; }

protected:
	//init
	bool	InitConnect(LPCTSTR lpUrl, RequestType type, LPCSTR lpPostData=NULL);
	bool	ConnectHttpServer(LPCTSTR lpIP, WORD wPort);
	bool	CreateHttpRequest(LPCTSTR lpPage, RequestType type, DWORD dwFlag=0);
	bool	SendHttpRequest(LPCSTR lpPostData=NULL);
	//query 
	bool	QueryRawHeaders(OUT wstring& strHeaders);
	bool	QueryContentLength(OUT DWORD& dwLength);
	//error
	void	SetError(LPCTSTR lpError)
	{
		wchar_t szError[256] = {0};
		swprintf_s(szError, L"%s��ϵͳ�����룺%u", lpError, GetLastError());
		m_strError = szError;
	}
private:
	HINTERNET	m_hInternet;
	HINTERNET	m_hConnect;
	HINTERNET	m_hRequest;
	void*		m_lpParam;
	int			m_nConnTimeout;
	int			m_nSendTimeout;
	int			m_nRecvTimeout;
	wstring		m_strError;
	CHttpClientLoadCallback*	m_pLoadCallback;
	CHttpClientStopCallback*	m_pStopCallback;
};

inline void CloseInternetHandle(HINTERNET* hInternet)
{
	if ( *hInternet )
	{
		WinHttpCloseHandle(*hInternet);
		*hInternet = NULL;
	}
}
