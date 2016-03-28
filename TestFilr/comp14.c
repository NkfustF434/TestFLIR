#include "comp14.h"

#define HIBYTE(x)   ((COMP_BYTE) ((x) >> 8))
#define LOBYTE(x)   ((COMP_BYTE) (x))

#define PIXEL_DEFAULT   8192

#ifdef _DEBUG
int diff3, diff7, diff14;
#endif

/*
 *  ===== compress_line =====
 *      Compress line of 14-bit pixels into compressed data based on dynamic range.
 *   _______________________________
 *  |0 0|       14-bit pixel        |
 *  |_._|_._._._._._._._._._._._._._|
 *   _______________
 *  |0 1|3-bit|3-bit|
 *  |_._|_|_|_|_|_|_|
 *   _______________
 *  |1|   7-bit     |
 *  |_|_._._._._._._|
 *
 *  Returns number of bytes in compressed line (variable 25% - 100%)
 */

int compress_line(COMP_PIXEL* inp, COMP_BYTE* out, int count)
{
    int prev = PIXEL_DEFAULT;
    int bytes = 0;
    int diff1,diff2;

    while (count > 0)
    {
        /* Read 2 pixels at a time */
        int p1 = inp[0];
        int p2 = inp[1];
        inp += 2;
        diff1 = p1 - prev;
        diff2 = p2 - p1;

        /* pair of 3-bit differences? */
        if (diff1 >= -4 && diff1 <= 3 && diff2 >= -4 && diff2 <= 3)
        {
            out[0] = ((diff1 + 12) << 3) | (diff2 + 4);
            ++out;
            ++bytes;
#ifdef _DEBUG
            diff3 += 2;
#endif
        }
        else
        {
            /* 7-bit difference? */
            if (diff1 >= -64 && diff1 <= 63)
            {
                out[0] = diff1 + 192;
                ++out;
                ++bytes;
#ifdef _DEBUG
                ++diff7;
#endif
            }
            else
            {
                out[0] = HIBYTE(p1);
                out[1] = LOBYTE(p1);
                out += 2;
                bytes += 2;
#ifdef _DEBUG
                ++diff14;
#endif
            }
            /* 7-bit difference? */
            if (diff2 >= -64 && diff2 <= 63)
            {
                out[0] = diff2 + 192;
                ++out;
                ++bytes;
#ifdef _DEBUG
                ++diff7;
#endif
            }
            else
            {
                out[0] = HIBYTE(p2);
                out[1] = LOBYTE(p2);
                out += 2;
                bytes += 2;
#ifdef _DEBUG
                ++diff14;
#endif
            }
        }
        prev = p2;
        count -= 4;
    }
    return bytes;
}

/*
 *  ===== expand_line =====
 *      Expand line of compressed data back into 14-bit pixels.
 *   _______________________________
 *  |0 0|       14-bit pixel        |
 *  |_._|_._._._._._._._._._._._._._|
 *   _______________
 *  |0 1|3-bit|3-bit|
 *  |_._|_|_|_|_|_|_|
 *   _______________
 *  |1|   7-bit     |
 *  |_|_._._._._._._|
 *
 *  Returns number of bytes read from input (variable 25% - 100%)
 */
int expand_line(COMP_BYTE* inp, COMP_PIXEL* out, int count)
{
    int pixel = PIXEL_DEFAULT;
    int bytes = 0;

    while (count > 0)
    {
        COMP_BYTE code = inp[bytes++];
        if (code & 0x80)
        {
            pixel = pixel + (code & 0x7F) - 64;
        }
        else if (code & 0x40)
        {
            pixel = pixel + ((code >> 3) & 7) - 4;
            out[0] = pixel;
            ++out;
            count -= 2;
            pixel = pixel + (code & 7) - 4;
        }
        else
        {
            pixel = (code << 8) | inp[bytes++];
        }
        out[0] = pixel;
        ++out;
        count -= 2;
    }
    return bytes;
}
