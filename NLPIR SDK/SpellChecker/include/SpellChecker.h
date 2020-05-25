// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 SPELLCHECKER_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// SPELLCHECKER_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#if !defined(__NLPIR_SPELL_CHECK_2020_H_INCLUDED__)
#define __NLPIR_SPELL_CHECK_2020_H_INCLUDED__

#ifdef OS_LINUX
	#define SPELLCHECKER_API extern "C" 
#else
	#ifdef SPELLCHECKER_EXPORTS
		#define SPELLCHECKER_API extern "C" __declspec(dllexport)
	#else
		#define SPELLCHECKER_API extern "C" __declspec(dllimport)
	#endif
#endif


/*********************************************************************
*
*  Func Name  : NLPRIR_SpellChecker
*
*  Description: NLPIR spell checker 校对功能
*
*  Parameters : const char * sLine: input sentence or line
*				 encode: encoding code; 1: utf-8编码，0: ANSI/GBK编码
*				 sPath:  Path where Data directory stored.
*				 the default value is NULL, it indicates the initial directory is current working directory path；
*				 Data所在的文件夹路径（存放了配置和授权文件）
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2020-5-23
*********************************************************************/
SPELLCHECKER_API const char* NLPRIR_SpellChecker(const char *sLine,int encode=1, const char *sPath=0);

SPELLCHECKER_API void NLPRIR_SpellChecker_Exit();
#endif//__NLPIR_SPELL_CHECK_2020_H_INCLUDED__