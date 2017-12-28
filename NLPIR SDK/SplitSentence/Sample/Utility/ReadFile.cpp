#include <stdio.h>
#include <sys/stat.h>
#include "ReadFile.h"
/*********************************************************************
*
*  Func Name  : Read(const char *sFilename,char *pBuffer)
*  Description:
*        Read file to a buffer and return the file size
*
*
*  Parameters :
*               sFilename: filename;
*               pBuffer: buffer
*
*  Returns    : _off_t file size
*  Author     : Kevin Zhang
*  History    :
*              1.create 2003-11-28
*********************************************************************/
size_t ReadFile(const char *sFilename, char **pBuffer)
{
	FILE *fp;
	struct _stat buf;
	if ((fp = fopen(sFilename, "rb")) == NULL)
		return 0;//read file false
	int nRet = _fstat(_fileno(fp), &buf);//Get file information
	if (nRet != 0)//File length of the lexicon file
	{
		return 0;
	}
	*pBuffer = new char[buf.st_size + 1];
	//The buffer for file
	if (*pBuffer == 0)
	{
		return 0;
	}
	fread(*pBuffer, buf.st_size, 1, fp);//Read 
	(*pBuffer)[buf.st_size] = 0;
	fclose(fp);
	return buf.st_size;
}
