
// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LICENSE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LICENSE_API functions as being imported from a DLL, wheras this DLL sees symbols

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
int IsValidLicense(const char *sFilename, const char *sSysname, const char *sLicenseCode=NULL);

