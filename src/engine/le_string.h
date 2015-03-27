#ifndef _LE_STRING_H_
#define _LE_STRING_H_

#include <wchar.h>
#include <string.h>

/**
 * [fgettokwcs description]
 * @param  fp     [description]
 * @param  allow  [description]
 * @param  buffer [description]
 * @return        [description]
 */
int fgettokwcs(FILE* fp, const wchar_t* allow, wchar_t* buffer);


/**
 * [fgettokwcsn description]
 * @param  fp     [description]
 * @param  allow  [description]
 * @param  buffer [description]
 * @return        [description]
 */
int fgettokwcsn(FILE* fp, const wchar_t* stop, wchar_t* buffer);

/**
 * [wcinrange description]
 * @param  ch    [description]
 * @param  range [description]
 * @return       [description]
 */
int wcinrange(wchar_t ch, const wchar_t* range);

/**
 * [wcstolower description]
 * @param  p [description]
 * @return   [description]
 */
wchar_t* wcstolower(wchar_t* p);

#endif
