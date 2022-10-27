/*******************************************************************************
 * Size: 4 px
 * Bpp: 8
 * Opts: --bpp=8 --size=4 --format=lvgl --output=////Users/tgil/gitv4/STM32H735G-DK//designlab/fonts/sourcecode_r_4.c --font=////Users/tgil/gitv4/STM32H735G-DK/designlab/fonts/SourceCode/SourceCodePro-Regular.ttf --range=0x20-0x7F --no-compress
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef SOURCECODE_R_4
#define SOURCECODE_R_4 1
#endif

#if SOURCECODE_R_4

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x0, 0x4c, 0x0, 0x2f, 0x6, 0x3b,

    /* U+0022 "\"" */
    0x8, 0x8, 0x61, 0x61, 0x11, 0x11,

    /* U+0023 "#" */
    0x28, 0x44, 0x0, 0x4a, 0x63, 0x4, 0x4f, 0x63,
    0x0,

    /* U+0024 "$" */
    0x16, 0x5d, 0x0, 0x57, 0x2c, 0x0, 0x11, 0x73,
    0x2, 0x20, 0x5c, 0x0,

    /* U+0025 "%" */
    0x59, 0x44, 0x15, 0x4c, 0x49, 0x14, 0x34, 0x4c,
    0x2d,

    /* U+0026 "&" */
    0x48, 0x49, 0x0, 0x6d, 0x47, 0x1b, 0x60, 0x98,
    0x18,

    /* U+0027 "'" */
    0x0, 0x8, 0x1, 0x5f, 0x0, 0x11,

    /* U+0028 "(" */
    0x0, 0x48, 0x15, 0x34, 0xc, 0x3f, 0x0, 0x34,

    /* U+0029 ")" */
    0x2c, 0x1b, 0x0, 0x48, 0x1, 0x48, 0x2a, 0xa,

    /* U+002A "*" */
    0x27, 0x6b, 0x1, 0x25, 0x40, 0x0,

    /* U+002B "+" */
    0x0, 0x37, 0x0, 0x2a, 0x73, 0x4,

    /* U+002C "," */
    0x5, 0x48, 0xc, 0x32,

    /* U+002D "-" */
    0x2a, 0x40, 0x4,

    /* U+002E "." */
    0x9, 0x48,

    /* U+002F "/" */
    0x0, 0x4c, 0x0, 0x4b, 0x36, 0x15, 0x26, 0x0,

    /* U+0030 "0" */
    0x4d, 0x61, 0x2, 0x51, 0x65, 0x15, 0x4c, 0x60,
    0x2,

    /* U+0031 "1" */
    0x23, 0x60, 0x0, 0x0, 0x54, 0x0, 0x2b, 0x84,
    0x9,

    /* U+0032 "2" */
    0x33, 0x6d, 0x0, 0x0, 0x5d, 0x0, 0x60, 0x63,
    0x6,

    /* U+0033 "3" */
    0x31, 0x71, 0x0, 0xc, 0x6f, 0x0, 0x36, 0x6e,
    0x6,

    /* U+0034 "4" */
    0x2, 0x8b, 0x0, 0x48, 0x5f, 0x0, 0x56, 0x7c,
    0xc,

    /* U+0035 "5" */
    0x5c, 0x48, 0x0, 0x47, 0x55, 0x1, 0x34, 0x6b,
    0x8,

    /* U+0036 "6" */
    0x48, 0x50, 0x2, 0x66, 0x50, 0x5, 0x49, 0x62,
    0xf,

    /* U+0037 "7" */
    0x36, 0x82, 0xa, 0x0, 0x4e, 0x0, 0xd, 0x48,
    0x0,

    /* U+0038 "8" */
    0x4b, 0x66, 0x0, 0x58, 0x8e, 0x2, 0x5a, 0x65,
    0xe,

    /* U+0039 "9" */
    0x55, 0x62, 0x1, 0x3f, 0x71, 0xf, 0x32, 0x66,
    0x0,

    /* U+003A ":" */
    0xa, 0x49, 0x9, 0x48,

    /* U+003B ";" */
    0xa, 0x49, 0x5, 0x48, 0xc, 0x32,

    /* U+003C "<" */
    0x0, 0x26, 0x41, 0x2d, 0x3, 0x4a,

    /* U+003D "=" */
    0x54, 0x80, 0x8,

    /* U+003E ">" */
    0x25, 0x1, 0x9, 0x69, 0x30, 0x1e,

    /* U+003F "?" */
    0x25, 0x6c, 0x2, 0x55, 0xc, 0x35,

    /* U+0040 "@" */
    0x3c, 0x4a, 0x10, 0x46, 0x5e, 0x2f, 0x45, 0x4d,
    0x1b, 0x21, 0x3b, 0x0,

    /* U+0041 "A" */
    0x22, 0x77, 0x0, 0x64, 0x6e, 0x0, 0x83, 0x7d,
    0x1e,

    /* U+0042 "B" */
    0x6b, 0x74, 0x2, 0x6b, 0x79, 0x6, 0x6b, 0x69,
    0x16,

    /* U+0043 "C" */
    0x49, 0x4d, 0x6, 0x56, 0x0, 0x0, 0x4c, 0x50,
    0xc,

    /* U+0044 "D" */
    0x6d, 0x64, 0xa, 0x58, 0x27, 0x2f, 0x6e, 0x68,
    0x9,

    /* U+0045 "E" */
    0x66, 0x48, 0x5, 0x66, 0x3f, 0x0, 0x66, 0x48,
    0x9,

    /* U+0046 "F" */
    0x61, 0x48, 0xa, 0x61, 0x44, 0x0, 0x58, 0x0,
    0x0,

    /* U+0047 "G" */
    0x4f, 0x4d, 0x2, 0x56, 0x42, 0x14, 0x51, 0x67,
    0x17,

    /* U+0048 "H" */
    0x58, 0x40, 0x14, 0x70, 0x76, 0x14, 0x58, 0x40,
    0x14,

    /* U+0049 "I" */
    0x2d, 0x87, 0x1, 0x0, 0x58, 0x0, 0x2d, 0x87,
    0x1,

    /* U+004A "J" */
    0x22, 0x84, 0x0, 0x54, 0x35, 0x74,

    /* U+004B "K" */
    0x58, 0x59, 0x8, 0x7c, 0x69, 0x0, 0x58, 0x44,
    0x19,

    /* U+004C "L" */
    0x54, 0x0, 0x0, 0x54, 0x0, 0x0, 0x5e, 0x48,
    0xb,

    /* U+004D "M" */
    0x87, 0x69, 0x1c, 0x75, 0x92, 0x1c, 0x50, 0x43,
    0x1c,

    /* U+004E "N" */
    0x86, 0x45, 0x14, 0x5a, 0x8a, 0x14, 0x50, 0x79,
    0x14,

    /* U+004F "O" */
    0x53, 0x68, 0x9, 0x55, 0x2a, 0x2b, 0x54, 0x6b,
    0x9,

    /* U+0050 "P" */
    0x66, 0x69, 0x16, 0x67, 0x58, 0x6, 0x54, 0x0,
    0x0,

    /* U+0051 "Q" */
    0x57, 0x6c, 0x8, 0x5e, 0x32, 0x2c, 0x56, 0x70,
    0x8, 0x0, 0x45, 0xd,

    /* U+0052 "R" */
    0x66, 0x6e, 0xe, 0x67, 0x7d, 0x1, 0x54, 0x54,
    0xc,

    /* U+0053 "S" */
    0x55, 0x4e, 0x1, 0x32, 0x71, 0x5, 0x3a, 0x6c,
    0xf,

    /* U+0054 "T" */
    0x3b, 0x87, 0x10, 0x0, 0x58, 0x0, 0x0, 0x58,
    0x0,

    /* U+0055 "U" */
    0x58, 0x3c, 0x14, 0x57, 0x3c, 0x13, 0x55, 0x6c,
    0x3,

    /* U+0056 "V" */
    0x59, 0x3d, 0x19, 0x52, 0x51, 0x0, 0x20, 0x6c,
    0x0,

    /* U+0057 "W" */
    0x5b, 0xc, 0x4b, 0x67, 0x94, 0x29, 0x83, 0x84,
    0x9,

    /* U+0058 "X" */
    0x58, 0x54, 0x4, 0x20, 0x78, 0x0, 0x54, 0x54,
    0x8,

    /* U+0059 "Y" */
    0x58, 0x42, 0x11, 0x2b, 0x69, 0x0, 0x0, 0x58,
    0x0,

    /* U+005A "Z" */
    0x2e, 0x8d, 0xc, 0x10, 0x4e, 0x0, 0x75, 0x49,
    0xb,

    /* U+005B "[" */
    0x18, 0x50, 0x0, 0x18, 0x28, 0x0, 0x18, 0x28,
    0x0, 0xe, 0x40, 0x0,

    /* U+005C "\\" */
    0x4a, 0x1, 0x12, 0x39, 0x0, 0x4c, 0x0, 0x26,

    /* U+005D "]" */
    0x1d, 0x4f, 0x0, 0x44, 0x0, 0x44, 0x1d, 0x33,

    /* U+005E "^" */
    0x6, 0x33, 0x43, 0x4a,

    /* U+005F "_" */
    0x37, 0x48, 0xb,

    /* U+0060 "`" */
    0x3, 0x0, 0x15, 0x23,

    /* U+0061 "a" */
    0x2e, 0x89, 0x4, 0x63, 0x72, 0x10,

    /* U+0062 "b" */
    0x53, 0x0, 0x0, 0x67, 0x68, 0x11, 0x64, 0x67,
    0xd,

    /* U+0063 "c" */
    0x51, 0x48, 0x3, 0x53, 0x46, 0x6,

    /* U+0064 "d" */
    0x0, 0x4b, 0x8, 0x5a, 0x7a, 0x8, 0x64, 0x79,
    0x8,

    /* U+0065 "e" */
    0x59, 0x7a, 0xb, 0x62, 0x4e, 0x2,

    /* U+0066 "f" */
    0x1, 0x67, 0x11, 0x2e, 0x7b, 0x7, 0x8, 0x4c,
    0x0,

    /* U+0067 "g" */
    0x4c, 0x80, 0x11, 0x65, 0x7e, 0x4, 0x50, 0x54,
    0x22,

    /* U+0068 "h" */
    0x53, 0x0, 0x0, 0x66, 0x6c, 0x9, 0x54, 0x3c,
    0x18,

    /* U+0069 "i" */
    0x0, 0x32, 0x2b, 0x66, 0x0, 0x54,

    /* U+006A "j" */
    0x0, 0x32, 0x2b, 0x66, 0x0, 0x54, 0x32, 0x52,

    /* U+006B "k" */
    0x54, 0x0, 0x0, 0x58, 0x63, 0x4, 0x68, 0x52,
    0xf,

    /* U+006C "l" */
    0x35, 0x50, 0x0, 0x4, 0x50, 0x0, 0x1, 0x6f,
    0x7,

    /* U+006D "m" */
    0x71, 0x8a, 0x2c, 0x54, 0x68, 0x3c,

    /* U+006E "n" */
    0x62, 0x6c, 0x9, 0x54, 0x3c, 0x18,

    /* U+006F "o" */
    0x59, 0x65, 0xd, 0x59, 0x64, 0xe,

    /* U+0070 "p" */
    0x65, 0x68, 0x11, 0x66, 0x6f, 0xd, 0x53, 0x0,
    0x0,

    /* U+0071 "q" */
    0x5a, 0x78, 0x8, 0x64, 0x7c, 0x8, 0x0, 0x4b,
    0x8,

    /* U+0072 "r" */
    0x58, 0x4c, 0x9, 0x54, 0x0, 0x0,

    /* U+0073 "s" */
    0x59, 0x5a, 0x0, 0x2f, 0x83, 0x9,

    /* U+0074 "t" */
    0x24, 0x28, 0x0, 0x51, 0x61, 0x7, 0x1b, 0x61,
    0xa,

    /* U+0075 "u" */
    0x54, 0x50, 0x4, 0x5c, 0x78, 0x4,

    /* U+0076 "v" */
    0x52, 0x45, 0xd, 0x2b, 0x66, 0x0,

    /* U+0077 "w" */
    0x60, 0x68, 0x42, 0x84, 0x81, 0x10,

    /* U+0078 "x" */
    0x42, 0x63, 0x1, 0x45, 0x61, 0x3,

    /* U+0079 "y" */
    0x50, 0x3f, 0xd, 0x27, 0x65, 0x0, 0x39, 0x32,
    0x0,

    /* U+007A "z" */
    0x26, 0x8e, 0x5, 0x64, 0x59, 0x8,

    /* U+007B "{" */
    0x0, 0x5f, 0x0, 0x24, 0x36, 0x0, 0x0, 0x46,
    0x0, 0x0, 0x3e, 0x0,

    /* U+007C "|" */
    0x4c, 0x4c, 0x4c, 0x4c,

    /* U+007D "}" */
    0x1f, 0x42, 0x0, 0x5b, 0x0, 0x46, 0x1e, 0x20,

    /* U+007E "~" */
    0x22, 0x3b, 0x1
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 38, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 38, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 38, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 12, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 38, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 33, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 38, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 57, .adv_w = 38, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 65, .adv_w = 38, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 73, .adv_w = 38, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 38, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 85, .adv_w = 38, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 89, .adv_w = 38, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 92, .adv_w = 38, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 38, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 102, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 38, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 38, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 202, .adv_w = 38, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 38, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 211, .adv_w = 38, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 38, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 38, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 235, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 38, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 38, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 388, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 424, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 433, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 451, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 469, .adv_w = 38, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 481, .adv_w = 38, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 489, .adv_w = 38, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 497, .adv_w = 38, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 501, .adv_w = 38, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 504, .adv_w = 38, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 508, .adv_w = 38, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 38, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 529, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 538, .adv_w = 38, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 553, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 562, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 38, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 577, .adv_w = 38, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 585, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 603, .adv_w = 38, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 609, .adv_w = 38, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 615, .adv_w = 38, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 630, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 639, .adv_w = 38, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 645, .adv_w = 38, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 660, .adv_w = 38, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 38, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 672, .adv_w = 38, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 678, .adv_w = 38, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 38, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 693, .adv_w = 38, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 699, .adv_w = 38, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 711, .adv_w = 38, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 715, .adv_w = 38, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 723, .adv_w = 38, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 8,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t sourcecode_r_4 = {
#else
lv_font_t sourcecode_r_4 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 5,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if SOURCECODE_R_4*/

