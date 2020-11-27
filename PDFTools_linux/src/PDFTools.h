#ifndef __PDFTOOLS_H__
#define __PDFTOOLS_H__

// =================================================================================
//  Include Header Files
#include <string>
using namespace std;

/*********************************************************************************************
	���ݴ����ȡ������Ϣ
	nErrCode         - [�������] ������
	Return: ���ش�����Ϣ��std::string 
*********************************************************************************************/
string PDFTools_GetErrorString( int nErrCode );

/*********************************************************************************************
	ת��PNG(��ָ��ת��ҳ��)
	file_path           - [�������] ��ת���ļ�·��
	file_name           - [�������] ��ת���ļ���
	output_path         - [�������] ����ļ�·��
	page_number_start   - [�������] ת����ʼҳ��
	page_number_end     - [�������] ת������ҳ��
	dpi                 - [�������] ת���ֱ���
	rotate              - [�������] ��ת�Ƕ�
	Return: ����ת���������PDFTools_GetErrorString��ȡ��ϸ������Ϣ
*********************************************************************************************/
int PDFTools_convert2png_by_pagenum(char *file_path, const char *file_name, const char *output_path, int page_number_start,
	int page_number_end, float dpi, float rotate);

/*********************************************************************************************
	ת��PNG(ȫ��ת��)
	file_path           - [�������] ��ת���ļ�·��
	file_name           - [�������] ��ת���ļ���
	output_path         - [�������] ����ļ�·��
	dpi                 - [�������] ת���ֱ���
	rotate              - [�������] ��ת�Ƕ�
	Return: ����ת���������PDFTools_GetErrorString��ȡ��ϸ������Ϣ
*********************************************************************************************/
int PDFTools_convert2png_all(char *file_path, const char *file_name, const char *output_path, float dpi, float rotate);




//test
int PDFTools_convert2png_test(char *file_path, const char *file_name, const char *output_path, int output_id, 
	int page_number_start, int page_number_end, float dpi, float rotate);

#endif //__PDFTOOLS_H__

