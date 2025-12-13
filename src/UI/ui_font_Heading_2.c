/*******************************************************************************
 * Size: 14 px
 * Bpp: 2
 * Opts: --bpp 2 --size 14 --font C:/Users/Nguoi Viet Chim Tay/SquareLine/assets/Inter-Regular.otf -o C:/Users/Nguoi Viet Chim Tay/SquareLine/assets\ui_font_Heading_2.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "ui.h"

#ifndef UI_FONT_HEADING_2
#define UI_FONT_HEADING_2 1
#endif

#if UI_FONT_HEADING_2

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0xaa, 0xaa, 0xaa, 0xa5, 0x9, 0xa0,

    /* U+0022 "\"" */
    0xc6, 0xc6, 0xc6, 0x85,

    /* U+0023 "#" */
    0x3, 0x9, 0x1, 0x82, 0x40, 0x60, 0xc0, 0xff,
    0xfe, 0x9, 0xc, 0x3, 0x6, 0x0, 0xc1, 0x82,
    0xff, 0xfc, 0x18, 0x34, 0x6, 0xc, 0x2, 0x43,
    0x0,

    /* U+0024 "$" */
    0x0, 0xc0, 0x1, 0xfe, 0x1, 0xdd, 0xe0, 0xd3,
    0x18, 0x34, 0xc0, 0x7, 0xb0, 0x0, 0x6f, 0x80,
    0x3, 0x78, 0x0, 0xc3, 0xd, 0x30, 0xc2, 0xdd,
    0xe0, 0x2f, 0xe0, 0x0, 0xc0, 0x0,

    /* U+0025 "%" */
    0x3d, 0x3, 0x49, 0x30, 0x60, 0xc3, 0xc, 0x9,
    0x32, 0x40, 0x3d, 0x70, 0x0, 0xc, 0x0, 0x2,
    0x8b, 0x40, 0x32, 0x8c, 0xd, 0x24, 0xc2, 0x82,
    0x4c, 0x30, 0xf, 0x40,

    /* U+0026 "&" */
    0x7, 0xd0, 0x7, 0x5d, 0x1, 0xc3, 0x40, 0x31,
    0xc0, 0xb, 0xd0, 0x2, 0xe0, 0x2, 0xdd, 0x20,
    0xc1, 0xdc, 0x30, 0x2e, 0xe, 0xb, 0x80, 0xbe,
    0x34,

    /* U+0027 "'" */
    0xcc, 0xc8,

    /* U+0028 "(" */
    0xc, 0x18, 0x34, 0x30, 0x30, 0x70, 0x60, 0x70,
    0x30, 0x30, 0x34, 0x18, 0xc,

    /* U+0029 ")" */
    0x30, 0x24, 0x1c, 0xc, 0xd, 0xd, 0xa, 0xd,
    0xd, 0xc, 0x1c, 0x24, 0x30,

    /* U+002A "*" */
    0x3, 0x0, 0x8c, 0x81, 0xfd, 0x7, 0xf4, 0x23,
    0x20, 0xc, 0x0,

    /* U+002B "+" */
    0x2, 0x0, 0xc, 0x0, 0x30, 0x2f, 0xfe, 0x3,
    0x0, 0xc, 0x0, 0x30, 0x0,

    /* U+002C "," */
    0x0, 0xa2, 0x8d, 0x30,

    /* U+002D "-" */
    0xff, 0x40, 0x0,

    /* U+002E "." */
    0x9a,

    /* U+002F "/" */
    0x0, 0x40, 0x90, 0x30, 0xc, 0x6, 0x2, 0x40,
    0xc0, 0x30, 0x28, 0xd, 0x3, 0x1, 0xc0, 0xa0,
    0x0,

    /* U+0030 "0" */
    0x7, 0xe0, 0xd, 0x2c, 0x28, 0xd, 0x30, 0xa,
    0x30, 0x7, 0x30, 0x7, 0x30, 0x7, 0x30, 0xa,
    0x28, 0xd, 0xd, 0x2c, 0x7, 0xe0,

    /* U+0031 "1" */
    0x3, 0x43, 0xd3, 0xb4, 0xd, 0x3, 0x40, 0xd0,
    0x34, 0xd, 0x3, 0x40, 0xd0, 0x34,

    /* U+0032 "2" */
    0x1f, 0x81, 0xd2, 0xcd, 0x3, 0x0, 0xc, 0x0,
    0x70, 0x3, 0x40, 0x38, 0x2, 0x80, 0x2c, 0x1,
    0xc0, 0xf, 0xff, 0x40,

    /* U+0033 "3" */
    0x1f, 0xd1, 0xd1, 0xca, 0x3, 0x40, 0x9, 0x0,
    0x70, 0x1f, 0x0, 0x7, 0x40, 0x7, 0x90, 0x1e,
    0xd1, 0xd1, 0xfd, 0x0,

    /* U+0034 "4" */
    0x0, 0x3c, 0x0, 0x2f, 0x0, 0xe, 0xc0, 0xa,
    0x70, 0x3, 0x1c, 0x2, 0x47, 0x1, 0xc1, 0xc0,
    0xd0, 0x70, 0x3f, 0xff, 0x0, 0x7, 0x0, 0x1,
    0xc0,

    /* U+0035 "5" */
    0x3f, 0xf1, 0xc0, 0x6, 0x0, 0x28, 0x0, 0xbf,
    0x81, 0x92, 0xc0, 0x3, 0x40, 0xa, 0x90, 0x35,
    0xd2, 0xc1, 0xf8, 0x0,

    /* U+0036 "6" */
    0x2, 0xf4, 0xe, 0x1c, 0x18, 0xa, 0x34, 0x0,
    0x32, 0xf4, 0x3d, 0x1c, 0x38, 0xa, 0x34, 0x7,
    0x24, 0xa, 0xd, 0x1c, 0x7, 0xf4,

    /* U+0037 "7" */
    0x7f, 0xfc, 0x0, 0x1c, 0x0, 0x28, 0x0, 0x30,
    0x0, 0xa0, 0x0, 0xc0, 0x2, 0x80, 0x3, 0x40,
    0x7, 0x0, 0xd, 0x0, 0x1c, 0x0,

    /* U+0038 "8" */
    0x7, 0xe0, 0x1d, 0x2c, 0x28, 0xd, 0x28, 0xc,
    0x1c, 0x1c, 0xb, 0xf0, 0x2d, 0x1c, 0x30, 0xa,
    0x30, 0xa, 0x2d, 0x1d, 0xb, 0xf4,

    /* U+0039 "9" */
    0x7, 0xe0, 0x1d, 0x2c, 0x34, 0xd, 0x30, 0xa,
    0x34, 0xb, 0x2c, 0x1f, 0xb, 0xe6, 0x0, 0xa,
    0x24, 0xc, 0x2d, 0x28, 0xb, 0xe0,

    /* U+003A ":" */
    0xa9, 0x0, 0x0, 0x9a,

    /* U+003B ";" */
    0x2c, 0x60, 0x0, 0x0, 0x2, 0x8a, 0x34, 0xc0,
    0x0,

    /* U+003C "<" */
    0x0, 0x18, 0x2, 0xd0, 0xb8, 0x2e, 0x0, 0x78,
    0x0, 0x1e, 0x0, 0xb, 0x80, 0x1,

    /* U+003D "=" */
    0x7f, 0xf4, 0x0, 0x0, 0x0, 0x1f, 0xfd, 0x0,
    0x0,

    /* U+003E ">" */
    0x90, 0x1, 0xe0, 0x0, 0xb8, 0x0, 0x2e, 0x0,
    0xb4, 0x2d, 0xb, 0x80, 0x10, 0x0,

    /* U+003F "?" */
    0xf, 0xd0, 0xe2, 0xc6, 0x3, 0x40, 0xc, 0x0,
    0xb0, 0xb, 0x0, 0x30, 0x1, 0xc0, 0x0, 0x0,
    0x18, 0x0, 0x70, 0x0,

    /* U+0040 "@" */
    0x0, 0xbf, 0x90, 0x1, 0xd0, 0x1e, 0x0, 0xc0,
    0x0, 0xd0, 0x90, 0xba, 0xc, 0x30, 0xe1, 0xc3,
    0xc, 0x70, 0x30, 0x97, 0x18, 0xc, 0x24, 0xc7,
    0x3, 0x9, 0x30, 0xc1, 0xd3, 0xd, 0x1f, 0x9f,
    0x40, 0xc0, 0x0, 0x0, 0x1e, 0x0, 0x40, 0x0,
    0xbf, 0xd0, 0x0,

    /* U+0041 "A" */
    0x0, 0xe0, 0x0, 0x1f, 0x0, 0x3, 0xb0, 0x0,
    0x32, 0x80, 0x7, 0x1c, 0x0, 0xe0, 0xc0, 0xc,
    0xe, 0x1, 0xff, 0xf0, 0x38, 0x3, 0x43, 0x0,
    0x28, 0x70, 0x1, 0xc0,

    /* U+0042 "B" */
    0xff, 0xe0, 0xe0, 0x78, 0xd0, 0x1c, 0xd0, 0x1c,
    0xd0, 0x34, 0xff, 0xe0, 0xe0, 0x2c, 0xd0, 0xc,
    0xd0, 0xc, 0xe0, 0x2c, 0xff, 0xe0,

    /* U+0043 "C" */
    0x2, 0xfd, 0x0, 0xf4, 0x74, 0x1c, 0x1, 0xc3,
    0x40, 0x4, 0x30, 0x0, 0x3, 0x0, 0x0, 0x30,
    0x0, 0x3, 0x40, 0x4, 0x1c, 0x1, 0xc0, 0xf4,
    0x74, 0x2, 0xfd, 0x0,

    /* U+0044 "D" */
    0xff, 0xe0, 0x38, 0x1f, 0xd, 0x0, 0xe3, 0x40,
    0x1c, 0xd0, 0x3, 0x34, 0x0, 0xcd, 0x0, 0x33,
    0x40, 0x1c, 0xd0, 0xe, 0x38, 0x1f, 0xf, 0xfe,
    0x0,

    /* U+0045 "E" */
    0xff, 0xf7, 0x80, 0xd, 0x0, 0x34, 0x0, 0xd0,
    0x3, 0xff, 0xce, 0x0, 0x34, 0x0, 0xd0, 0x3,
    0x80, 0xf, 0xff, 0x40,

    /* U+0046 "F" */
    0xff, 0xf7, 0x80, 0xd, 0x0, 0x34, 0x0, 0xd0,
    0x3, 0xff, 0xce, 0x0, 0x34, 0x0, 0xd0, 0x3,
    0x40, 0xd, 0x0, 0x0,

    /* U+0047 "G" */
    0x2, 0xfd, 0x0, 0xf4, 0xb4, 0x1c, 0x1, 0xc3,
    0x40, 0x9, 0x30, 0x0, 0x3, 0x0, 0x0, 0x30,
    0x1f, 0xe3, 0x40, 0xd, 0x1c, 0x0, 0xc0, 0xf4,
    0x78, 0x2, 0xfd, 0x0,

    /* U+0048 "H" */
    0xd0, 0x3, 0x34, 0x0, 0xcd, 0x0, 0x33, 0x40,
    0xc, 0xd0, 0x3, 0x3f, 0xff, 0xce, 0x0, 0x33,
    0x40, 0xc, 0xd0, 0x3, 0x34, 0x0, 0xcd, 0x0,
    0x30,

    /* U+0049 "I" */
    0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xd0,

    /* U+004A "J" */
    0x0, 0x34, 0x0, 0xd0, 0x3, 0x40, 0xd, 0x0,
    0x34, 0x0, 0xd0, 0x3, 0x40, 0xd, 0x20, 0x30,
    0xe2, 0xc1, 0xfc, 0x0,

    /* U+004B "K" */
    0xd0, 0x1d, 0xd0, 0x34, 0xd0, 0xe0, 0xd3, 0x80,
    0xdb, 0x0, 0xff, 0x0, 0xf7, 0x80, 0xe0, 0xd0,
    0xd0, 0x70, 0xd0, 0x38, 0xd0, 0xd,

    /* U+004C "L" */
    0xd0, 0x3, 0x40, 0xd, 0x0, 0x34, 0x0, 0xd0,
    0x3, 0x40, 0xd, 0x0, 0x34, 0x0, 0xd0, 0x3,
    0x80, 0xf, 0xff, 0x0,

    /* U+004D "M" */
    0xf0, 0x0, 0x73, 0xd0, 0x3, 0xcf, 0x80, 0xf,
    0x3b, 0x0, 0xac, 0xdd, 0x3, 0x73, 0x5c, 0x1c,
    0xcd, 0x30, 0x93, 0x34, 0xa3, 0xc, 0xd1, 0xe8,
    0x33, 0x43, 0xd0, 0xcd, 0xb, 0x3, 0x0,

    /* U+004E "N" */
    0xe0, 0x3, 0x7d, 0x0, 0xdf, 0xc0, 0x37, 0x68,
    0xd, 0xd3, 0x43, 0x74, 0x70, 0xdd, 0xe, 0x37,
    0x40, 0xdd, 0xd0, 0x1f, 0x74, 0x3, 0xdd, 0x0,
    0x34,

    /* U+004F "O" */
    0x2, 0xf9, 0x0, 0xf4, 0x74, 0x1c, 0x1, 0xc3,
    0x40, 0xa, 0x30, 0x0, 0xa3, 0x0, 0x7, 0x30,
    0x0, 0xa3, 0x40, 0xa, 0x1c, 0x1, 0xc0, 0xf4,
    0x74, 0x2, 0xfd, 0x0,

    /* U+0050 "P" */
    0xff, 0xe0, 0xe0, 0x78, 0xd0, 0x1c, 0xd0, 0xc,
    0xd0, 0xc, 0xd0, 0x38, 0xff, 0xe0, 0xe0, 0x0,
    0xd0, 0x0, 0xd0, 0x0, 0xd0, 0x0,

    /* U+0051 "Q" */
    0x2, 0xf9, 0x0, 0xf4, 0x74, 0x1c, 0x1, 0xc3,
    0x40, 0xa, 0x30, 0x0, 0xa3, 0x0, 0x7, 0x30,
    0x0, 0xa3, 0x41, 0x9, 0x1c, 0x1d, 0xc0, 0xf4,
    0xf4, 0x2, 0xff, 0x40, 0x0, 0x1c,

    /* U+0052 "R" */
    0xff, 0xe0, 0xe0, 0x78, 0xd0, 0x1c, 0xd0, 0xc,
    0xd0, 0xc, 0xd0, 0x38, 0xff, 0xf0, 0xe0, 0xe0,
    0xd0, 0x70, 0xd0, 0x28, 0xd0, 0xc,

    /* U+0053 "S" */
    0x7, 0xf4, 0x7, 0x47, 0x83, 0x40, 0x60, 0xd0,
    0x0, 0x1e, 0x40, 0x0, 0xbe, 0x0, 0x1, 0xe0,
    0x0, 0xc, 0x30, 0x3, 0xb, 0x47, 0x80, 0xbf,
    0x40,

    /* U+0054 "T" */
    0x7f, 0xff, 0x40, 0x30, 0x0, 0xc, 0x0, 0x3,
    0x0, 0x0, 0xc0, 0x0, 0x30, 0x0, 0xc, 0x0,
    0x3, 0x0, 0x0, 0xc0, 0x0, 0x30, 0x0, 0xc,
    0x0,

    /* U+0055 "U" */
    0xd0, 0x3, 0x34, 0x0, 0xcd, 0x0, 0x33, 0x40,
    0xc, 0xd0, 0x3, 0x34, 0x0, 0xcd, 0x0, 0x32,
    0x80, 0xc, 0x70, 0x7, 0xf, 0x5b, 0x40, 0xbf,
    0x40,

    /* U+0056 "V" */
    0x70, 0x1, 0xc3, 0x0, 0x28, 0x34, 0x3, 0x41,
    0xc0, 0x70, 0xc, 0xa, 0x0, 0xd0, 0xc0, 0x7,
    0x1c, 0x0, 0x32, 0x80, 0x3, 0x70, 0x0, 0x1f,
    0x0, 0x0, 0xe0, 0x0,

    /* U+0057 "W" */
    0xa0, 0xd, 0x1, 0xdc, 0x7, 0x80, 0xa3, 0x2,
    0xf0, 0x34, 0xd0, 0xdc, 0xc, 0x28, 0x32, 0x47,
    0x7, 0x1c, 0x62, 0x80, 0xca, 0xc, 0xd0, 0x37,
    0x43, 0x30, 0xa, 0xc0, 0xac, 0x1, 0xe0, 0x1e,
    0x0, 0x34, 0x3, 0x40,

    /* U+0058 "X" */
    0x70, 0x3, 0x4a, 0x2, 0x80, 0xd1, 0xc0, 0x2c,
    0xe0, 0x3, 0xf0, 0x0, 0x78, 0x0, 0x3f, 0x0,
    0x2c, 0xe0, 0xd, 0x1c, 0xa, 0x2, 0x87, 0x0,
    0x34,

    /* U+0059 "Y" */
    0x70, 0x2, 0x8e, 0x1, 0xc0, 0xc0, 0xe0, 0x28,
    0x70, 0x3, 0x74, 0x0, 0xbc, 0x0, 0xd, 0x0,
    0x3, 0x40, 0x0, 0xd0, 0x0, 0x34, 0x0, 0xd,
    0x0,

    /* U+005A "Z" */
    0x3f, 0xff, 0x0, 0xe, 0x0, 0x1c, 0x0, 0x34,
    0x0, 0xa0, 0x1, 0xc0, 0x3, 0x40, 0xb, 0x0,
    0xc, 0x0, 0x38, 0x0, 0x3f, 0xff,

    /* U+005B "[" */
    0x7e, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70,
    0x70, 0x70, 0x70, 0x70, 0x7e, 0x0,

    /* U+005C "\\" */
    0x60, 0xc, 0x3, 0x0, 0x90, 0x18, 0x3, 0x0,
    0xc0, 0x24, 0x6, 0x0, 0xc0, 0x30, 0x9,

    /* U+005D "]" */
    0x7d, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9,
    0x9, 0x9, 0x9, 0x9, 0x7d, 0x0,

    /* U+005E "^" */
    0x5, 0x0, 0xf4, 0x1d, 0xc3, 0x4d, 0x30, 0x70,

    /* U+005F "_" */
    0x3f, 0xfd, 0x0, 0x0,

    /* U+0060 "`" */
    0x50, 0xc2, 0x80,

    /* U+0061 "a" */
    0xb, 0xe0, 0xe0, 0xe0, 0x1, 0xc1, 0xaf, 0x3d,
    0x5c, 0xc0, 0x73, 0x47, 0xc7, 0xe7,

    /* U+0062 "b" */
    0xd0, 0x3, 0x40, 0xd, 0x0, 0x36, 0xf4, 0xf4,
    0x77, 0x80, 0xad, 0x1, 0xf4, 0x7, 0xe0, 0x1b,
    0xd0, 0xdd, 0xbd, 0x0,

    /* U+0063 "c" */
    0x7, 0xe0, 0x2d, 0x2c, 0x30, 0x4, 0x30, 0x0,
    0x30, 0x0, 0x30, 0x4, 0x2d, 0x2c, 0xb, 0xe0,

    /* U+0064 "d" */
    0x0, 0x9, 0x0, 0x9, 0x0, 0x9, 0xb, 0xd9,
    0x2c, 0x2d, 0x30, 0xd, 0x30, 0xd, 0x30, 0xd,
    0x30, 0xd, 0x2c, 0x2d, 0xb, 0xd9,

    /* U+0065 "e" */
    0x7, 0xe0, 0x2c, 0x2c, 0x30, 0xc, 0x3f, 0xfd,
    0x30, 0x0, 0x30, 0x4, 0x2d, 0x2c, 0x7, 0xf0,

    /* U+0066 "f" */
    0xb, 0x87, 0x41, 0xc2, 0xfd, 0x1c, 0x7, 0x1,
    0xc0, 0x70, 0x1c, 0x7, 0x1, 0xc0,

    /* U+0067 "g" */
    0xb, 0xd9, 0x2c, 0x2d, 0x30, 0xd, 0x30, 0xd,
    0x30, 0xd, 0x30, 0xd, 0x2c, 0x2d, 0xb, 0xd9,
    0x0, 0xd, 0x28, 0x1c, 0xb, 0xf4,

    /* U+0068 "h" */
    0xc0, 0x3, 0x0, 0xc, 0x0, 0x36, 0xf0, 0xf4,
    0xb3, 0x40, 0xcd, 0x3, 0x30, 0xc, 0xc0, 0x33,
    0x0, 0xcc, 0x3, 0x0,

    /* U+0069 "i" */
    0x34, 0x80, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3,
    0x0,

    /* U+006A "j" */
    0xd, 0x8, 0x0, 0xc, 0xc, 0xc, 0xc, 0xc,
    0xc, 0xc, 0xc, 0xc, 0x1c, 0x34,

    /* U+006B "k" */
    0xc0, 0x3, 0x0, 0xc, 0x0, 0x30, 0x28, 0xc2,
    0x83, 0x6c, 0xf, 0xc0, 0x3a, 0x80, 0xd3, 0x83,
    0x3, 0x4c, 0x7, 0x0,

    /* U+006C "l" */
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xc0,

    /* U+006D "m" */
    0xdf, 0x8b, 0xc3, 0xc7, 0xd2, 0xcd, 0xb, 0x3,
    0x34, 0x28, 0xc, 0xc0, 0xa0, 0x33, 0x2, 0x80,
    0xcc, 0xa, 0x3, 0x30, 0x28, 0xc,

    /* U+006E "n" */
    0xdb, 0xc3, 0xd2, 0xcd, 0x3, 0x34, 0xc, 0xc0,
    0x33, 0x0, 0xcc, 0x3, 0x30, 0xc,

    /* U+006F "o" */
    0xb, 0xe0, 0x2d, 0x2c, 0x30, 0xd, 0x30, 0xa,
    0x30, 0xa, 0x30, 0xd, 0x2d, 0x2c, 0xb, 0xe0,

    /* U+0070 "p" */
    0xdb, 0xc3, 0xd1, 0xce, 0x2, 0xb4, 0x6, 0xd0,
    0x1b, 0x80, 0xaf, 0x47, 0x36, 0xf4, 0xc0, 0x3,
    0x0, 0xc, 0x0, 0x0,

    /* U+0071 "q" */
    0xb, 0xd9, 0x2c, 0x2d, 0x30, 0xd, 0x30, 0xd,
    0x30, 0xd, 0x30, 0xd, 0x2c, 0x2d, 0xb, 0xd9,
    0x0, 0x9, 0x0, 0x9, 0x0, 0x9,

    /* U+0072 "r" */
    0xdf, 0x3d, 0xd, 0x3, 0x0, 0xc0, 0x30, 0xc,
    0x3, 0x0,

    /* U+0073 "s" */
    0xb, 0xd0, 0xe1, 0xc3, 0x40, 0xb, 0x90, 0x1,
    0xf0, 0x0, 0xa3, 0x47, 0x47, 0xf4,

    /* U+0074 "t" */
    0x1c, 0x7, 0xb, 0xf4, 0x70, 0x1c, 0x7, 0x1,
    0xc0, 0x70, 0x1d, 0x2, 0xd0,

    /* U+0075 "u" */
    0xc0, 0x33, 0x0, 0xcc, 0x3, 0x30, 0xc, 0xd0,
    0x33, 0x41, 0xcb, 0x5f, 0xb, 0x8c,

    /* U+0076 "v" */
    0x70, 0xc, 0x30, 0x1c, 0x28, 0x34, 0x1c, 0x30,
    0xc, 0x60, 0xa, 0xd0, 0x3, 0xc0, 0x3, 0x80,

    /* U+0077 "w" */
    0x70, 0x34, 0x18, 0xc1, 0xe0, 0x93, 0x4a, 0xc3,
    0xa, 0x33, 0x1c, 0xc, 0xca, 0xa0, 0x3a, 0x1f,
    0x40, 0xb4, 0x3c, 0x1, 0xc0, 0xa0,

    /* U+0078 "x" */
    0x30, 0x28, 0xb0, 0xc0, 0xdd, 0x1, 0xf0, 0x7,
    0xc0, 0x37, 0x42, 0xc7, 0xc, 0xa,

    /* U+0079 "y" */
    0x70, 0xc, 0x30, 0x1c, 0x28, 0x34, 0x1c, 0x30,
    0xd, 0x60, 0xa, 0xd0, 0x3, 0xc0, 0x3, 0x80,
    0x3, 0x40, 0x7, 0x0, 0x3c, 0x0,

    /* U+007A "z" */
    0x3f, 0xf8, 0x0, 0xd0, 0xa, 0x0, 0x70, 0x3,
    0x0, 0x34, 0x2, 0xc0, 0xf, 0xff,

    /* U+007B "{" */
    0x3, 0x83, 0x80, 0xc0, 0x30, 0xc, 0x7, 0x7,
    0x0, 0xb0, 0xc, 0x3, 0x0, 0xc0, 0x34, 0x7,
    0x80, 0x0,

    /* U+007C "|" */
    0x13, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
    0x33,

    /* U+007D "}" */
    0x74, 0x7, 0x0, 0xc0, 0x30, 0xc, 0x3, 0x40,
    0x38, 0x38, 0xc, 0x3, 0x0, 0xc0, 0x70, 0x74,
    0x0, 0x0,

    /* U+007E "~" */
    0x3c, 0xb, 0x9c, 0x7c, 0x1f, 0x40, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 63, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 62, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 90, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 10, .adv_w = 141, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 35, .adv_w = 143, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 65, .adv_w = 182, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 143, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 50, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 120, .adv_w = 81, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 133, .adv_w = 81, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 146, .adv_w = 112, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 157, .adv_w = 144, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 170, .adv_w = 63, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 174, .adv_w = 103, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 177, .adv_w = 62, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 80, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 195, .adv_w = 140, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 99, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 136, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 143, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 144, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 136, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 140, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 128, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 138, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 382, .adv_w = 140, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 62, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 408, .adv_w = 63, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 417, .adv_w = 144, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 144, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 440, .adv_w = 144, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 114, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 210, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 517, .adv_w = 151, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 545, .adv_w = 146, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 567, .adv_w = 163, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 595, .adv_w = 161, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 640, .adv_w = 131, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 660, .adv_w = 166, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 688, .adv_w = 166, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 713, .adv_w = 59, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 719, .adv_w = 122, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 739, .adv_w = 146, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 761, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 781, .adv_w = 204, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 812, .adv_w = 169, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 837, .adv_w = 171, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 865, .adv_w = 142, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 887, .adv_w = 171, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 917, .adv_w = 143, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 939, .adv_w = 143, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 964, .adv_w = 144, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 989, .adv_w = 166, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1014, .adv_w = 151, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1042, .adv_w = 213, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1078, .adv_w = 144, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1103, .adv_w = 149, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1128, .adv_w = 140, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1150, .adv_w = 81, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1164, .adv_w = 80, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1179, .adv_w = 81, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1193, .adv_w = 105, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1201, .adv_w = 101, .box_w = 8, .box_h = 2, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 1205, .adv_w = 111, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 1208, .adv_w = 126, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1222, .adv_w = 139, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1242, .adv_w = 125, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1258, .adv_w = 139, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1280, .adv_w = 130, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1296, .adv_w = 81, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1310, .adv_w = 136, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1332, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1352, .adv_w = 53, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1361, .adv_w = 53, .box_w = 4, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 1375, .adv_w = 122, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1395, .adv_w = 53, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1401, .adv_w = 195, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1423, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1437, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1453, .adv_w = 136, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1473, .adv_w = 136, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1495, .adv_w = 86, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1505, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1519, .adv_w = 81, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1532, .adv_w = 130, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1546, .adv_w = 125, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1562, .adv_w = 182, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1584, .adv_w = 121, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1598, .adv_w = 125, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1620, .adv_w = 121, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1634, .adv_w = 81, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1652, .adv_w = 73, .box_w = 2, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1661, .adv_w = 81, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1679, .adv_w = 144, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 2}
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

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    3, 7,
    3, 13,
    3, 15,
    3, 21,
    3, 34,
    3, 43,
    7, 3,
    7, 8,
    7, 53,
    7, 55,
    7, 56,
    7, 58,
    7, 87,
    7, 88,
    7, 90,
    8, 7,
    8, 13,
    8, 15,
    8, 21,
    8, 34,
    8, 43,
    9, 68,
    9, 69,
    9, 70,
    9, 72,
    9, 75,
    9, 80,
    11, 7,
    11, 13,
    11, 15,
    11, 21,
    11, 34,
    11, 43,
    11, 64,
    12, 19,
    12, 20,
    12, 24,
    12, 53,
    12, 55,
    12, 56,
    12, 57,
    12, 58,
    12, 89,
    13, 3,
    13, 8,
    13, 17,
    13, 18,
    13, 20,
    13, 23,
    13, 25,
    13, 32,
    13, 53,
    13, 58,
    13, 65,
    14, 19,
    14, 20,
    14, 24,
    14, 53,
    14, 55,
    14, 56,
    14, 57,
    14, 58,
    14, 89,
    15, 3,
    15, 8,
    15, 17,
    15, 18,
    15, 20,
    15, 23,
    15, 25,
    15, 32,
    15, 53,
    15, 58,
    15, 65,
    16, 13,
    16, 15,
    16, 43,
    17, 24,
    17, 58,
    17, 64,
    19, 21,
    20, 13,
    20, 15,
    21, 13,
    21, 15,
    21, 18,
    22, 13,
    22, 15,
    23, 13,
    23, 15,
    23, 64,
    24, 4,
    24, 7,
    24, 13,
    24, 15,
    24, 17,
    24, 20,
    24, 21,
    24, 22,
    24, 23,
    24, 24,
    24, 25,
    24, 26,
    24, 27,
    24, 28,
    24, 29,
    24, 34,
    24, 43,
    24, 64,
    24, 66,
    24, 68,
    24, 69,
    24, 70,
    24, 72,
    24, 80,
    24, 84,
    25, 13,
    25, 15,
    26, 24,
    26, 58,
    26, 64,
    27, 53,
    27, 55,
    28, 53,
    28, 55,
    30, 34,
    30, 55,
    30, 56,
    30, 57,
    30, 58,
    30, 87,
    30, 89,
    30, 90,
    31, 24,
    31, 53,
    31, 55,
    31, 56,
    31, 57,
    31, 58,
    31, 59,
    32, 34,
    34, 3,
    34, 8,
    34, 11,
    34, 18,
    34, 30,
    34, 32,
    34, 36,
    34, 40,
    34, 48,
    34, 50,
    34, 53,
    34, 55,
    34, 56,
    34, 58,
    34, 63,
    34, 74,
    34, 85,
    34, 87,
    34, 88,
    34, 90,
    36, 57,
    36, 64,
    37, 13,
    37, 15,
    37, 16,
    37, 34,
    37, 53,
    37, 55,
    37, 57,
    37, 58,
    37, 64,
    39, 13,
    39, 15,
    39, 34,
    39, 43,
    39, 64,
    39, 68,
    39, 69,
    39, 70,
    39, 72,
    39, 78,
    39, 79,
    39, 80,
    39, 81,
    39, 82,
    39, 83,
    39, 86,
    39, 87,
    39, 90,
    39, 91,
    40, 34,
    40, 53,
    40, 55,
    40, 57,
    40, 74,
    40, 75,
    41, 64,
    42, 64,
    43, 13,
    43, 15,
    43, 16,
    43, 64,
    44, 12,
    44, 14,
    44, 29,
    44, 30,
    44, 36,
    44, 40,
    44, 48,
    44, 50,
    44, 68,
    44, 69,
    44, 70,
    44, 72,
    44, 74,
    44, 80,
    44, 86,
    44, 87,
    44, 88,
    44, 90,
    44, 95,
    45, 3,
    45, 8,
    45, 11,
    45, 12,
    45, 14,
    45, 18,
    45, 34,
    45, 36,
    45, 40,
    45, 48,
    45, 50,
    45, 53,
    45, 55,
    45, 58,
    45, 63,
    45, 85,
    45, 87,
    45, 90,
    45, 95,
    46, 64,
    47, 64,
    48, 13,
    48, 15,
    48, 16,
    48, 34,
    48, 53,
    48, 55,
    48, 57,
    48, 58,
    48, 64,
    49, 7,
    49, 12,
    49, 13,
    49, 14,
    49, 15,
    49, 34,
    49, 43,
    49, 68,
    49, 69,
    49, 70,
    49, 72,
    49, 80,
    49, 95,
    50, 13,
    50, 15,
    50, 16,
    50, 34,
    50, 53,
    50, 55,
    50, 57,
    50, 58,
    50, 64,
    51, 55,
    51, 68,
    51, 69,
    51, 70,
    51, 72,
    51, 80,
    53, 7,
    53, 12,
    53, 13,
    53, 14,
    53, 15,
    53, 16,
    53, 21,
    53, 27,
    53, 28,
    53, 29,
    53, 34,
    53, 36,
    53, 40,
    53, 43,
    53, 48,
    53, 50,
    53, 64,
    53, 66,
    53, 68,
    53, 69,
    53, 70,
    53, 72,
    53, 78,
    53, 79,
    53, 80,
    53, 81,
    53, 82,
    53, 83,
    53, 84,
    53, 86,
    53, 87,
    53, 88,
    53, 89,
    53, 90,
    53, 91,
    53, 95,
    54, 13,
    54, 15,
    54, 16,
    54, 64,
    55, 7,
    55, 12,
    55, 13,
    55, 14,
    55, 15,
    55, 16,
    55, 21,
    55, 27,
    55, 28,
    55, 29,
    55, 30,
    55, 33,
    55, 34,
    55, 36,
    55, 40,
    55, 43,
    55, 48,
    55, 50,
    55, 64,
    55, 66,
    55, 68,
    55, 69,
    55, 70,
    55, 72,
    55, 80,
    55, 84,
    55, 95,
    56, 7,
    56, 12,
    56, 13,
    56, 14,
    56, 15,
    56, 21,
    56, 27,
    56, 28,
    56, 29,
    56, 30,
    56, 34,
    56, 36,
    56, 40,
    56, 43,
    56, 48,
    56, 50,
    56, 66,
    56, 68,
    56, 69,
    56, 70,
    56, 72,
    56, 78,
    56, 79,
    56, 80,
    56, 81,
    56, 82,
    56, 83,
    56, 84,
    56, 95,
    57, 12,
    57, 14,
    57, 29,
    57, 30,
    57, 36,
    57, 40,
    57, 48,
    57, 50,
    57, 68,
    57, 69,
    57, 70,
    57, 72,
    57, 80,
    57, 95,
    58, 7,
    58, 12,
    58, 13,
    58, 14,
    58, 15,
    58, 21,
    58, 27,
    58, 28,
    58, 29,
    58, 30,
    58, 34,
    58, 36,
    58, 40,
    58, 43,
    58, 48,
    58, 50,
    58, 53,
    58, 66,
    58, 68,
    58, 69,
    58, 70,
    58, 72,
    58, 78,
    58, 79,
    58, 80,
    58, 81,
    58, 82,
    58, 83,
    58, 84,
    58, 86,
    58, 95,
    59, 12,
    59, 14,
    59, 29,
    59, 36,
    59, 40,
    59, 48,
    59, 50,
    59, 95,
    60, 68,
    60, 69,
    60, 70,
    60, 72,
    60, 75,
    60, 80,
    61, 13,
    61, 15,
    61, 53,
    61, 55,
    61, 87,
    61, 90,
    63, 7,
    63, 13,
    63, 15,
    63, 21,
    63, 34,
    63, 43,
    63, 64,
    64, 11,
    64, 17,
    64, 18,
    64, 20,
    64, 21,
    64, 22,
    64, 23,
    64, 25,
    64, 26,
    64, 36,
    64, 40,
    64, 48,
    64, 50,
    64, 53,
    64, 54,
    64, 55,
    64, 63,
    64, 74,
    64, 75,
    64, 78,
    64, 79,
    64, 81,
    64, 82,
    64, 83,
    64, 87,
    64, 90,
    66, 18,
    66, 53,
    66, 55,
    66, 56,
    66, 58,
    66, 87,
    66, 90,
    67, 10,
    67, 34,
    67, 53,
    67, 55,
    67, 56,
    67, 57,
    67, 58,
    67, 62,
    67, 87,
    67, 88,
    67, 89,
    67, 90,
    67, 94,
    68, 53,
    68, 58,
    68, 89,
    69, 64,
    70, 53,
    70, 55,
    70, 56,
    70, 58,
    70, 89,
    71, 12,
    71, 13,
    71, 14,
    71, 15,
    71, 16,
    71, 21,
    71, 34,
    71, 43,
    71, 58,
    71, 64,
    71, 66,
    71, 68,
    71, 69,
    71, 70,
    71, 72,
    71, 80,
    71, 84,
    71, 95,
    72, 53,
    72, 64,
    73, 18,
    73, 53,
    73, 55,
    73, 56,
    73, 58,
    73, 87,
    73, 90,
    74, 10,
    74, 55,
    74, 56,
    74, 62,
    74, 64,
    74, 94,
    75, 10,
    75, 55,
    75, 56,
    75, 62,
    75, 64,
    75, 94,
    76, 12,
    76, 14,
    76, 21,
    76, 29,
    76, 53,
    76, 68,
    76, 69,
    76, 70,
    76, 72,
    76, 80,
    76, 95,
    77, 64,
    78, 18,
    78, 53,
    78, 55,
    78, 56,
    78, 58,
    78, 87,
    78, 90,
    79, 18,
    79, 53,
    79, 55,
    79, 56,
    79, 58,
    79, 87,
    79, 90,
    80, 10,
    80, 34,
    80, 53,
    80, 55,
    80, 56,
    80, 57,
    80, 58,
    80, 62,
    80, 87,
    80, 88,
    80, 89,
    80, 90,
    80, 94,
    81, 10,
    81, 34,
    81, 53,
    81, 55,
    81, 56,
    81, 57,
    81, 58,
    81, 62,
    81, 87,
    81, 88,
    81, 89,
    81, 90,
    81, 94,
    82, 10,
    82, 34,
    82, 53,
    82, 55,
    82, 56,
    82, 57,
    82, 58,
    82, 62,
    82, 87,
    82, 88,
    82, 89,
    82, 90,
    82, 94,
    83, 12,
    83, 13,
    83, 14,
    83, 15,
    83, 16,
    83, 29,
    83, 34,
    83, 43,
    83, 53,
    83, 59,
    83, 68,
    83, 69,
    83, 70,
    83, 71,
    83, 72,
    83, 80,
    83, 85,
    83, 87,
    83, 88,
    83, 89,
    83, 90,
    83, 95,
    84, 53,
    84, 55,
    84, 56,
    84, 58,
    85, 12,
    85, 14,
    85, 21,
    85, 29,
    85, 35,
    85, 37,
    85, 38,
    85, 39,
    85, 41,
    85, 42,
    85, 44,
    85, 45,
    85, 46,
    85, 47,
    85, 49,
    85, 51,
    85, 53,
    85, 55,
    85, 56,
    85, 58,
    85, 67,
    85, 68,
    85, 69,
    85, 70,
    85, 72,
    85, 73,
    85, 76,
    85, 77,
    85, 80,
    85, 84,
    85, 93,
    85, 95,
    86, 53,
    86, 58,
    87, 13,
    87, 15,
    87, 16,
    87, 29,
    87, 30,
    87, 34,
    87, 43,
    87, 53,
    87, 58,
    87, 64,
    87, 68,
    87, 69,
    87, 70,
    87, 72,
    87, 74,
    87, 80,
    88, 7,
    88, 13,
    88, 15,
    88, 34,
    88, 43,
    88, 53,
    88, 59,
    88, 68,
    88, 69,
    88, 70,
    88, 72,
    88, 80,
    89, 12,
    89, 14,
    89, 30,
    89, 53,
    89, 68,
    89, 69,
    89, 70,
    89, 72,
    89, 80,
    89, 95,
    90, 13,
    90, 15,
    90, 16,
    90, 29,
    90, 30,
    90, 34,
    90, 43,
    90, 53,
    90, 58,
    90, 64,
    90, 68,
    90, 69,
    90, 70,
    90, 72,
    90, 74,
    90, 80,
    91, 53,
    91, 68,
    91, 69,
    91, 70,
    91, 72,
    91, 80,
    92, 68,
    92, 69,
    92, 70,
    92, 72,
    92, 75,
    92, 80,
    93, 64,
    95, 19,
    95, 20,
    95, 24,
    95, 53,
    95, 55,
    95, 56,
    95, 57,
    95, 58,
    95, 89
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -8, -18, -18, -14, -18, -37, -8, -8,
    -13, -14, -9, -17, -8, -8, -8, -8,
    -18, -18, -14, -18, -37, -3, -3, -3,
    -3, 6, -3, -8, -31, -31, -10, -18,
    -22, -15, -8, -3, -5, -17, -11, -11,
    -14, -18, -5, -18, -18, -9, -18, -8,
    -9, -8, -20, -8, -8, -31, -8, -3,
    -5, -17, -11, -11, -14, -18, -5, -18,
    -18, -9, -18, -8, -9, -8, -20, -8,
    -8, -31, -9, -9, -14, -4, -8, -10,
    -3, -8, -8, -8, -8, -2, -8, -8,
    -8, -8, -10, -13, -10, -28, -28, -3,
    -4, -13, -2, -3, 4, -3, -2, -8,
    -8, -20, -24, -22, -36, -10, -11, -11,
    -11, -11, -11, -9, -8, -8, -4, -8,
    -10, -8, -14, -8, -14, -11, -15, -14,
    -11, -22, -9, -8, -9, -17, -18, -17,
    -17, -13, -20, -14, -14, -18, -18, -18,
    -8, -11, -14, -8, -8, -8, -8, -19,
    -15, -13, -17, -18, 1, -8, -15, -15,
    -15, -1, -9, -10, -10, -9, -8, -7,
    -8, -3, -8, -9, -9, -8, -20, -15,
    -8, -9, -9, -9, -9, -1, -1, -9,
    -1, -1, -1, -8, -8, -8, -8, -5,
    8, -5, -1, 8, 8, 8, 8, -8,
    -8, -13, -11, -24, -24, -15, -8, -8,
    -8, -8, -8, -9, -9, -9, -9, 8,
    -9, -8, -9, -14, -9, -24, -20, -20,
    -9, -19, -11, -10, 10, -6, -6, -6,
    -6, -22, -15, -8, -29, -5, -15, -15,
    -9, 8, 8, -10, -10, -9, -8, -7,
    -8, -3, -8, -9, -8, -10, -9, -10,
    -8, -17, -22, -1, -1, -1, -1, -1,
    -10, -10, -10, -9, -8, -7, -8, -3,
    -8, -9, -4, -1, -1, -1, -1, -1,
    -8, -17, -8, -17, -8, -18, -15, -8,
    -8, -18, -19, -7, -7, -20, -7, -7,
    -13, -17, -18, -18, -18, -18, -13, -13,
    -18, -13, -13, -13, -17, -17, -14, -14,
    -14, -14, -10, -17, -8, -8, -13, -11,
    -11, -11, -22, -11, -22, -17, -8, -14,
    -14, -17, -14, -8, -14, -8, -8, -22,
    -8, -8, -18, -11, -11, -11, -11, -11,
    -11, -10, -11, -11, -11, -22, -11, -22,
    -8, -11, -11, -17, -14, -13, -8, -8,
    -14, -8, -8, -11, -11, -11, -11, -11,
    -8, -8, -11, -8, -8, -8, -8, -11,
    -15, -15, -13, -11, -3, -3, -3, -3,
    -6, -6, -6, -6, -6, -15, -14, -18,
    -8, -18, -8, -15, -14, -14, -23, -22,
    -17, -8, -8, -8, -8, -8, 10, -16,
    -17, -17, -17, -17, -9, -9, -17, -9,
    -9, -9, -15, -9, -18, -9, -9, -14,
    -8, -8, -8, -8, -9, -3, -3, -3,
    -3, 6, -3, 9, 9, -9, -11, -11,
    -11, -8, -31, -31, -10, -18, -22, -15,
    -15, -10, -24, -10, -13, -10, -10, -10,
    -10, -9, -9, -9, -9, -13, -9, -18,
    -15, 8, 22, 10, 10, 10, 10, 10,
    -18, -18, -9, -10, -11, -11, -17, -4,
    -4, -3, -8, -9, -11, -11, -6, -19,
    -3, -4, -4, -5, -4, -3, -17, -14,
    -1, 8, -11, -11, -11, -19, -3, -6,
    -13, -6, -13, -6, -14, -8, -14, 2,
    -3, -5, -5, -5, -5, -5, -5, -5,
    -6, -11, 8, -9, -10, -11, -11, -17,
    -4, -4, 8, 8, 8, 8, 9, 8,
    8, 8, 8, 8, 9, 8, -10, -10,
    -10, -19, -13, -5, -5, -5, -5, -5,
    -10, 8, -9, -10, -11, -11, -17, -4,
    -4, -9, -10, -11, -11, -17, -4, -4,
    -3, -8, -9, -11, -11, -6, -19, -3,
    -4, -4, -5, -4, -3, -3, -8, -9,
    -11, -11, -6, -19, -3, -4, -4, -5,
    -4, -3, -3, -8, -9, -11, -11, -6,
    -19, -3, -4, -4, -5, -4, -3, -9,
    -14, -9, -14, -8, -9, -9, -13, -13,
    -8, -4, -4, -4, 8, -4, -4, 8,
    2, 2, 2, 2, -9, -17, -10, -8,
    -17, -4, -4, -3, -6, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3,
    3, -8, -2, -2, -3, 3, -1, -1,
    -1, -1, 3, 3, 3, -1, -2, 3,
    -4, -11, -13, -8, -8, -13, -8, -9,
    -15, -14, -8, -8, -18, -4, -4, -4,
    -4, 8, -4, -8, -17, -17, -15, -13,
    -11, -8, -4, -4, -4, -4, -4, -5,
    -5, -8, -14, -5, -5, -5, -5, -5,
    -5, -8, -8, -13, -8, -9, -15, -14,
    -8, -8, -18, -4, -4, -4, -4, 8,
    -4, -8, -3, -3, -3, -3, -3, -3,
    -3, -3, -3, 6, -3, 8, -8, -3,
    -5, -17, -11, -11, -14, -18, -5
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 743,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_Heading_2 = {
#else
lv_font_t ui_font_Heading_2 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_HEADING_2*/

