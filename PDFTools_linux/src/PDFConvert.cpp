#include <mupdf/fitz.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PDFTools.h"
#include "ErrorCode.h"

string PDFTools_GetErrorString( int nErrCode )
{
	switch (nErrCode)
	{
		case 0:
			return "ת���ɹ�";
		case 101:
			return "����contextʧ��";
		case 102:
			return "ע��handleʧ��";
		case 103:
			return "���ļ�ʧ��";
		case 104:
			return "ͳ��ҳ��ʧ��";
		case 105:
			return "�������ҳ��";
		case 106:
			return "ת��ʧ��";
		default:
			return "δ֪����";
	}
}

//ת��PNG(��ָ��ת��ҳ��)
int PDFTools_convert2png_by_pagenum(char *file_path, const char *file_name, const char *output_path, int page_number_start,
	int page_number_end, float dpi, float rotate)
{
	char file_path_all[128] = {0};
	strcat(file_path_all, file_path);
	strcat(file_path_all, file_name);
	//char *file_path_all = strcat(file_path, file_name);
	int page_count = 0; //PDF��ҳ��
	float zoom = dpi/72*100; //���ű���*100,Ĭ��72dpi,������

	fz_context *ctx;
	fz_document *doc;
	fz_pixmap *pix;
	fz_matrix ctm;

	/* Create a context to hold the exception stack and various caches. */
	ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
	if (!ctx)
	{
		return CREATE_CONTEXT_FAILED;
	}
	/* Register the default file types to handle. */
	fz_try(ctx)
		fz_register_document_handlers(ctx);
	fz_catch(ctx)
	{
		fz_drop_context(ctx);
		return REGISTER_HANDEL_FAILED;
	}
	/* Open the document. */
	fz_try(ctx)
		doc = fz_open_document(ctx, file_path_all);
	fz_catch(ctx)
	{
		fz_drop_context(ctx);
		return OPEN_DOCUMENT_FAILED;
	}
	/* Count the number of pages. */
	fz_try(ctx)
		page_count = fz_count_pages(ctx, doc);
	fz_catch(ctx)
	{
		fz_drop_document(ctx, doc);
		fz_drop_context(ctx);
		return COUNT_PAGES_FAILED;
	}

	//�ж�ҳ���Ƿ񳬳���Χ
	if (page_number_start < 0 || page_number_start > page_number_end || page_number_end > page_count)
	{
		fz_drop_document(ctx, doc);
		fz_drop_context(ctx);
		return INPUT_PAGES_ERROR;
	}

	/* Compute a transformation matrix for the zoom and rotation desired. */
	/* The default resolution without scaling is 72 dpi. */
	ctm = fz_scale(zoom / 100, zoom / 100);
	ctm = fz_pre_rotate(ctm, rotate);

	/* Render page to an RGB pixmap. */
	//��ӡҳ����Ҫ-1
	page_number_start = page_number_start - 1;
	page_number_end = page_number_end - 1;
	int n;
	for (n = page_number_start; n <= page_number_end; n++)
	{
		fz_try(ctx)
			pix = fz_new_pixmap_from_page_number(ctx, doc, n, ctm, fz_device_rgb(ctx), 0);
		fz_catch(ctx)
		{
			fprintf(stderr, "cannot render page: %s\n", fz_caught_message(ctx));
			fz_drop_document(ctx, doc);
			fz_drop_context(ctx);
			return CONVERT_FAILED;
		}
		// Save a (Greyscale or RGB) pixmap as a png.
		char png_name[128];
		sprintf(png_name, "%s%s_%d.png",output_path,file_name,n+1);
		fz_save_pixmap_as_png(ctx, pix, png_name);
	}

	/* Clean up. */
	fz_drop_pixmap(ctx, pix);
	fz_drop_document(ctx, doc);
	fz_drop_context(ctx);
	return CONVERT_SUCCESS;
}


//ת��PNG(ȫ��ת��)
int PDFTools_convert2png_all(char *file_path, const char *file_name, const char *output_path, 
							float dpi, float rotate)
{
	char file_path_all[128] = {0};
	strcat(file_path_all, file_path);
	strcat(file_path_all, file_name);
	//char *file_path_all = strcat(file_path, file_name);
	int page_count = 0; //PDF��ҳ��
	float zoom = dpi/72*100; //���ű���*100,Ĭ��72dpi,������

	fz_context *ctx;
	fz_document *doc;
	fz_pixmap *pix;
	fz_matrix ctm;

	/* Create a context to hold the exception stack and various caches. */
	ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
	if (!ctx)
	{
		return CREATE_CONTEXT_FAILED;
	}
	/* Register the default file types to handle. */
	fz_try(ctx)
		fz_register_document_handlers(ctx);
	fz_catch(ctx)
	{
		fz_drop_context(ctx);
		return REGISTER_HANDEL_FAILED;
	}
	/* Open the document. */
	fz_try(ctx)
		doc = fz_open_document(ctx, file_path_all);
	fz_catch(ctx)
	{
		fz_drop_context(ctx);
		return OPEN_DOCUMENT_FAILED;
	}
	/* Count the number of pages. */
	fz_try(ctx)
		page_count = fz_count_pages(ctx, doc);
	fz_catch(ctx)
	{
		fz_drop_document(ctx, doc);
		fz_drop_context(ctx);
		return COUNT_PAGES_FAILED;
	}

	/* Compute a transformation matrix for the zoom and rotation desired. */
	/* The default resolution without scaling is 72 dpi. */
	ctm = fz_scale(zoom / 100, zoom / 100);
	ctm = fz_pre_rotate(ctm, rotate);

	/* Render page to an RGB pixmap. */
	//��ӡҳ����Ҫ-1
	int page_number_start = 0;
	int page_number_end = page_count - 1;
	int n;
	for (n = page_number_start; n <= page_number_end; n++)
	{
		fz_try(ctx)
			pix = fz_new_pixmap_from_page_number(ctx, doc, n, ctm, fz_device_rgb(ctx), 0);
		fz_catch(ctx)
		{
			fprintf(stderr, "cannot render page: %s\n", fz_caught_message(ctx));
			fz_drop_document(ctx, doc);
			fz_drop_context(ctx);
			return CONVERT_FAILED;
		}
		// Save a (Greyscale or RGB) pixmap as a png.
		char png_name[128];
		sprintf(png_name, "%s%s_%d.png",output_path,file_name,n+1);
		fz_save_pixmap_as_png(ctx, pix, png_name);
	}

	/* Clean up. */
	fz_drop_pixmap(ctx, pix);
	fz_drop_document(ctx, doc);
	fz_drop_context(ctx);
	return CONVERT_SUCCESS;
}


int PDFTools_convert2png_test(char *file_path, const char *file_name, const char *output_path, int output_id, 
	int page_number_start, int page_number_end, float dpi, float rotate)
{
	char file_path_all[128] = {0};
	strcat(file_path_all, file_path);
	strcat(file_path_all, file_name);
	//char *file_path_all = strcat(file_path, file_name);
	int page_count = 0; //PDF��ҳ��
	float zoom = dpi/72*100; //���ű���*100,Ĭ��72dpi,������

	fz_context *ctx;
	fz_document *doc;
	fz_pixmap *pix;
	fz_matrix ctm;

	/* Create a context to hold the exception stack and various caches. */
	ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
	if (!ctx)
	{
		return CREATE_CONTEXT_FAILED;
	}
	/* Register the default file types to handle. */
	fz_try(ctx)
		fz_register_document_handlers(ctx);
	fz_catch(ctx)
	{
		fz_drop_context(ctx);
		return REGISTER_HANDEL_FAILED;
	}
	/* Open the document. */
	fz_try(ctx)
		doc = fz_open_document(ctx, file_path_all);
	fz_catch(ctx)
	{
		fz_drop_context(ctx);
		return OPEN_DOCUMENT_FAILED;
	}
	/* Count the number of pages. */
	fz_try(ctx)
		page_count = fz_count_pages(ctx, doc);
	fz_catch(ctx)
	{
		fz_drop_document(ctx, doc);
		fz_drop_context(ctx);
		return COUNT_PAGES_FAILED;
	}

	//�ж�ҳ���Ƿ񳬳���Χ
	if (page_number_start < 0 || page_number_start > page_number_end || page_number_end > page_count)
	{
		fz_drop_document(ctx, doc);
		fz_drop_context(ctx);
		return INPUT_PAGES_ERROR;
	}

	/* Compute a transformation matrix for the zoom and rotation desired. */
	/* The default resolution without scaling is 72 dpi. */
	ctm = fz_scale(zoom / 100, zoom / 100);
	ctm = fz_pre_rotate(ctm, rotate);

	/* Render page to an RGB pixmap. */
	//��ӡҳ����Ҫ-1
	page_number_start = page_number_start - 1;
	page_number_end = page_number_end - 1;
	int n;
	for (n = page_number_start; n <= page_number_end; n++)
	{
		fz_try(ctx)
			pix = fz_new_pixmap_from_page_number(ctx, doc, n, ctm, fz_device_rgb(ctx), 0);
		fz_catch(ctx)
		{
			fprintf(stderr, "cannot render page: %s\n", fz_caught_message(ctx));
			fz_drop_document(ctx, doc);
			fz_drop_context(ctx);
			return CONVERT_FAILED;
		}
		// Save a (Greyscale or RGB) pixmap as a png.
		char png_name[128];
		sprintf(png_name, "%s%s_%d_%d.png",output_path,file_name,output_id,n+1);
		fz_save_pixmap_as_png(ctx, pix, png_name);
	}

	/* Clean up. */
	fz_drop_pixmap(ctx, pix);
	fz_drop_document(ctx, doc);
	fz_drop_context(ctx);
	return CONVERT_SUCCESS;
}