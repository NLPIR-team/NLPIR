
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LICENSE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LICENSE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#if !defined(AFX_LICENSE_H__0EB77608_3AD2_4F68_B95C_DFD20CB3B4FE__INCLUDED_)
#define AFX_LICENSE_H__0EB77608_3AD2_4F68_B95C_DFD20CB3B4FE__INCLUDED_

#ifdef LICENSE_EXPORTS
	#define LICENSE_API extern "C" __declspec(dllexport)
#else 
	#define LICENSE_API extern "C" __declspec(dllimport)
#endif

#if defined(LICENSE_INTERNAL_CALL) || defined(OS_LINUX)
		#define LICENSE_API 
#endif
// This class is exported from the License.dll

// GetMACAdapters.cpp : Defines the entry point for the console application.
//
// Author:	Khalid Shaikh [Shake@ShakeNet.com]
// Date:	April 5th, 2002
//
// This program fetches the MAC address of the localhost by fetching the 
// information through GetAdapatersInfo.  It does not rely on the NETBIOS
// protocol and the ethernet adapter need not be connect to a network.
//
// Supported in Windows NT/2000/XP
// Supported in Windows 95/98/Me
//
// Supports multiple NIC cards on a PC.

#ifdef OS_LINUX
	#define _off_t          off_t
#endif
#define LICENSE_BUF_LEN 255
#define LT_LIMITED 0
#define LT_UNLIMITED 1
#define LT_TRIAL 2

#define LS_UNACTIVE  0
#define LS_ACTIVATED 1
#define LS_LOCKED    2
#define LS_KILLED    3

#include <stdlib.h> 
#include <stdio.h> 
#include <time.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>
#include <string>

#ifdef LICENSE_ADMIN
	#include <string>
#endif
struct LJ_Version
{
	//Product information
	char sys_name[LICENSE_BUF_LEN];//system name
	char producer[LICENSE_BUF_LEN];//producer
	char url[LICENSE_BUF_LEN];     //url
	char email[LICENSE_BUF_LEN];   //email
	char product_id[LICENSE_BUF_LEN];//product id
	char version_id[LICENSE_BUF_LEN];//version id
	int  date;//date


	//User Information
	char user_name[LICENSE_BUF_LEN];//用户名
	char user_org[LICENSE_BUF_LEN];//用户单位
	char user_tel[LICENSE_BUF_LEN];//用户电话
	char user_mobile[LICENSE_BUF_LEN];//用户手机号
	char user_email[LICENSE_BUF_LEN];//用户Email
	char machine_id[LICENSE_BUF_LEN];//machine ID
	int machine_id_length;//Machine ID Length

	//Licence Information
	int  licence_date;//Licenced Date
	int  licence_expdate;//Licence Expiration Data
	int  licence_type;
	//Licence type: 0:1 month trial;1: one year licence;2: unlimited; 3.
	
    int licence_max_machines;//限制的最大机器数目
	int license_max_docs;//限制的最大文档数目

	//Activate information
	int  licence_status;//0:未激活；1：已激活 2:授权封锁;3:已注销
	int  invalid_count;//invalid count
	unsigned char sn[LICENSE_BUF_LEN];//active code
};

class CLicense  
{
public:
	bool Kill();
	LJ_Version * ReadData();
	bool SysRelease(LJ_Version *pSysInfo);
	bool InfoCollect(const char *user_name,
					 const char *user_org,
					 const char *user_tel,
					 const char *user_mobile,
					 const char *user_email);
	int Activate(const char *sSN,int nExpiredDate,int nLicenceType=LT_LIMITED,bool bNoCheck=false);
	bool IsValid(const char *sUnLimitCode=NULL);
	char * GenerateSN(char *sResult);
	bool Save(const char *sFilename);
	bool Save();
	bool Load(const char *sFilename);
	const char* GetMachineID();
	bool testGetMachineID();

	char * GetUnlimitCode(char *sResult);
	
	CLicense();
	virtual ~CLicense();

public:
	char m_machine_id[200];
	int m_length;
	LJ_Version m_data;
	char m_sCharMap[300];
#ifdef LICENSE_ADMIN
	FILE *m_fpUserInfo;//用户信息
	std::vector<std::string> m_vecMachine;
#endif
#ifdef MY_DEBUG
	FILE *m_fpLog;//用户信息
#endif
	char m_sDataFileName[1000];
protected:
	_off_t ReadFile(const char *sFilename,char **pBuffer);
	bool IsDateEffective(int nStartDay,int nEndDay);
	size_t  GetMachineVector(const char *sMachineID,std::vector<std::string> &vecMachine);
public:
	bool IsValidMachine(const char * sCurMachineID, const char *sRegMachineID);
	int GetMaxDocCount(void);
	int GetMaxMachineCount(void);
	const char * GetSysName(void);
	int GetLicenseType(void);
	int GetLicenseStatus(void);
};


/*********************************************************************
*
*  Func Name  : IsValidLicense
*
*  Description: 判断授权是否合法的API
*
*  Parameters : const char * sFilename:授权文件名，需要包含路径，默认为当前路径
*							  sSysname:系统名称
*						  sLicenseCode:授权码，不限制机器授权时使用，一般默认为空
*
*  Returns    : 1： 系统授权合法; 其他为非法
*  Author     : Kevin Zhang
*  History    :
*              1.create 2017-7-20
*********************************************************************/
LICENSE_API int IsValidLicense(const char *sFilename, const char *sSysname, const char *sLicenseCode=NULL,int *p_nMaxDocCount=NULL);

#endif
