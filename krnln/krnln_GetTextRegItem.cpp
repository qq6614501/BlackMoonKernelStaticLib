#include "stdafx.h"
#include "Myfunctions.h"
#pragma comment(lib,"advapi32.lib") 

//系统处理 - 取文本注册项
/*
    调用格式： 〈文本型〉 取文本注册项 （整数型 根目录，文本型 全路径注册项名，［文本型 默认文本］） - 系统核心支持库->系统处理
    英文名称：GetTextRegItem
    在 Windows 注册表中返回指定的文本类型注册表项值。如欲读取注册项默认值，请在项目名后加“\”号，如“test\”。与“取文本注册表项”命令不同的是本命令可以取任意位置处的注册表项。本命令为中级命令。
    参数<1>的名称为“根目录”，类型为“整数型（int）”。可以为以下常量值之一： 1、#根类； 2、#现行设置； 3、#现行用户； 4、#本地机器； 5、#所有用户。
    参数<2>的名称为“全路径注册项名”，类型为“文本型（text）”。
    参数<3>的名称为“默认文本”，类型为“文本型（text）”，可以被省略。如果指定的注册表项不存在，将返回此默认文本。如果指定的注册表项不存在且本参数被省略，将返回一个长度为 0 的空文本。
*/
LIBAPI(char*, krnln_GetTextRegItem)
{
	PMDATA_INF pArgInf = &ArgInf;
	HKEY hRootkey = GetRegRootVal(pArgInf[0].m_int);
	LPSTR pText = NULL;
	INT nLen = mystrlen(pArgInf[1].m_pText);
	if(hRootkey && nLen)
	{
		HKEY hkey;
		LPSTR pSubkey = new char [nLen +1];
		strcpy(pSubkey,pArgInf[1].m_pText);
		LPSTR pKeyname = strrchr(pSubkey,'\\');
		if(pKeyname)
		{
			*pKeyname = 0;
			pKeyname++;
		}
		if(RegOpenKey(hRootkey,pSubkey,&hkey)==ERROR_SUCCESS)
		{
		
			DWORD nLen = 1024;
			DWORD dwType = REG_SZ;
			INT nRet;
			LPSTR pData;
			do
			{
				pData = new char[nLen];

				nRet = RegQueryValueEx(hkey,pKeyname,NULL,&dwType,(LPBYTE)pData,&nLen);
				if(nRet == ERROR_SUCCESS)
				{
					if(dwType == REG_SZ || dwType == REG_EXPAND_SZ)
						pText = CloneTextData(pData,mystrlen(pData));
					break;

				}else if (nRet == ERROR_MORE_DATA)
				{
					delete [] pData;

				}else 	
					break;


			}while(1);

			delete [] pData;

			RegCloseKey(hkey);


		}
		delete [] pSubkey;
	}

	if(pText ==NULL && pArgInf[2].m_dtDataType != _SDT_NULL && pArgInf[2].m_pText)
	{
		pText = CloneTextData(pArgInf[2].m_pText,mystrlen(pArgInf[2].m_pText));
	}
	return pText;

}
