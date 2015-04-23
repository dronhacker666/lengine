#ifndef _LEOS_H_
#define _LEOS_H_

typedef enum {
	LEOS_LOG_INFO,
	LEOS_LOG_WARNING,
	LEOS_LOG_ERROR
} LEOSLogType;

void le_os_log(const wchar_t*, LEOSLogType);
void le_os_info(const wchar_t*);
void le_os_warning(const wchar_t*);
void le_os_error(const wchar_t*);

#endif
