#ifndef __COMP14_H__
#define __COMP14_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char COMP_BYTE;
typedef signed short COMP_PIXEL;

#ifdef _DEBUG
    extern int diff3, diff7, diff14;
#endif

int compress_line(COMP_PIXEL* inp, COMP_BYTE* out, int count);
int expand_line(COMP_BYTE* inp, COMP_PIXEL* out, int count);

#ifdef __cplusplus
}
#endif

#endif /* __COMP14_H__ */
