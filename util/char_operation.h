#ifndef ___CHAR_OPERATION__H__
#define ___CHAR_OPERATION__H__

#ifdef __cplusplus
extern "C"{
#endif

// wchar_t * utf8_dup_unicode(const char* src)
// {
// 	int nchar;
// 	wchar_t* buf = NULL;
// 
// 	nchar = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
// 	buf = (wchar_t*)malloc(nchar*sizeof(wchar_t[0]));
// 	if (!buf) return NULL;
// 
// 	nchar = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, nchar);
// 	if (nchar == 0) {
// 		free(buf);
// 		buf = NULL;
// 	}
// 	return buf;

// 	return 0;
// }

#ifdef __cplusplus
}
#endif

#endif //___CHAR_OPERATION__H__