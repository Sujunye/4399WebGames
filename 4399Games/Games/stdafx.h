// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <process.h>

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "public/Common/Common.h"
#include "public/Http/HttpClient.h"
#include "public/Json/json/json.h"
#include "public/Json/json/json-forwards.h"


#ifdef _DEBUG
#pragma comment(lib, "..\\..\\DuiLib\\Lib\\DuiLibD_MT.lib")
#else
#pragma comment(lib, "..\\..\\DuiLib\\Lib\\DuiLib_MT.lib")
#endif
#include "..\..\DuiLib\UIlib.h"
using namespace DuiLib;