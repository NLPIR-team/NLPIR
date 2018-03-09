/****************************************************************************
 *
 *
 *  Created:	14:9:2005   13:10
 *	File Path:	D:\NLPIR\Src\Utility
 * 	Filename: 	ReadFile
 *	File ext:	h
 *  
 *  Purpose:	Utility Function definition
 *  
 *  History:    1. Created   2005-9-14
 *              2.             
 ****************************************************************************/

#if !defined(__NLPIR_READ_FILE__INCLUDED_)
#define __NLPIR_READ_FILE__INCLUDED_

#ifndef OS_LINUX
	#include <io.h>
	#include <process.h>
	#include <direct.h>
	#include <assert.h>
	#include <conio.h>
	#include <afxmt.h>
	#pragma warning(disable:4786)
	#define PATH_DELEMETER  "\\"
	#define LONG64U __int64
	#define DATE_DELEMETER  "/"
	//#include <windows.h>
	#define SLEEP(x) Sleep(x*1000)
	//#define sprintf sprintf_s
	//#define fopen fopen_s
	#define stricmp  _stricmp
	#define strnicmp _strnicmp
	#define strlwr _strlwr
	#define access _access
	#define itoa _itoa
	#define fcloseall _fcloseall
	
#else
	#include <dirent.h>
	#include <ctype.h>
	#include <unistd.h> 
	#include <fcntl.h>
	#include <pthread.h>
	#include <netdb.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <semaphore.h>

	#define _chdir(x) chdir(x)    // change dir
	#define _mkdir(x) mkdir(x, 0777)    // 这步骤必须，否则文件夹只读
	#define _stricmp strcasecmp
	#define stricmp strcasecmp
	#define strnicmp strncasecmp
	#define _strnicmp strncasecmp
	#define Sleep(x) sleep(x/1000)
	#define _fstat(X,Y)     fstat((X),(Y))
	#define _fileno(X)     fileno((X))
	#define _stat           stat
	#define _getcwd         getcwd
	#define _off_t          off_t
	#define PATH_DELEMETER  "/"
	#define DATE_DELEMETER  "/"
	#define LONG64U long long
	#define __int64 long long
	#define _atoi64(val) strtoll(val, NULL, 10)
	#define _fseeki64(stream,offset,whence) fseeko((stream),(offset),(whence))
	#include <unistd.h>
	#define SLEEP(x) sleep(x)
	char* strrev(char* szt);
	char* itoa(int value, char*  str, int radix);
	char* strlwr(char* _src);
	char* strupr(char* _src);
	#define  nullptr 0
	#define SOCKADDR_IN	sockaddr_in
	#define SOCKADDR	 sockaddr 
#endif

size_t ReadFile(const char *sFilename, char **pBuffer);
#endif