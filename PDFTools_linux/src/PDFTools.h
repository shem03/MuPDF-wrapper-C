#ifndef __PDFTOOLS_H__
#define __PDFTOOLS_H__

// =================================================================================
//  Include Header Files
#include <string>
using namespace std;

/*********************************************************************************************
	根据错误号取错误信息
	nErrCode         - [输入参数] 错误码
	Return: 返回错误信息串std::string 
*********************************************************************************************/
string PDFTools_GetErrorString( int nErrCode );

/*********************************************************************************************
	转换PNG(可指定转换页数)
	file_path           - [输入参数] 待转换文件路径
	file_name           - [输入参数] 待转换文件名
	output_path         - [输入参数] 输出文件路径
	page_number_start   - [输入参数] 转换开始页数
	page_number_end     - [输入参数] 转换结束页数
	dpi                 - [输入参数] 转换分辨率
	rotate              - [输入参数] 旋转角度
	Return: 返回转换结果，用PDFTools_GetErrorString获取详细错误信息
*********************************************************************************************/
int PDFTools_convert2png_by_pagenum(char *file_path, const char *file_name, const char *output_path, int page_number_start,
	int page_number_end, float dpi, float rotate);

/*********************************************************************************************
	转换PNG(全部转换)
	file_path           - [输入参数] 待转换文件路径
	file_name           - [输入参数] 待转换文件名
	output_path         - [输入参数] 输出文件路径
	dpi                 - [输入参数] 转换分辨率
	rotate              - [输入参数] 旋转角度
	Return: 返回转换结果，用PDFTools_GetErrorString获取详细错误信息
*********************************************************************************************/
int PDFTools_convert2png_all(char *file_path, const char *file_name, const char *output_path, float dpi, float rotate);




//test
int PDFTools_convert2png_test(char *file_path, const char *file_name, const char *output_path, int output_id, 
	int page_number_start, int page_number_end, float dpi, float rotate);

#endif //__PDFTOOLS_H__

