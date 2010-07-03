/*
NOTICE

The software accompanying this notice (the "Software") is provided to you
free of charge to facilitate your use of the data collected by the Mars
Orbiter Camera (the "MOC Data").  Malin Space Science Systems ("MSSS")
grants to you (either as an individual or entity) a personal,
non-transferable, and non-exclusive right (i) to use and reproduce the
Software solely for the purpose of accessing the MOC Data; (ii) to modify
the source code of the Software as necessary to maintain or adapt the
Software to run on alternate computer platforms; and (iii) to compile, use
and reproduce the modified versions of the Software solely for the purpose
of accessing the MOC Data.  In addition, you may distribute the Software,
including any modifications thereof, solely for use with the MOC Data,
provided that (i) you must include this notice with all copies of the
Software to be distributed; (ii) you may not remove or alter any
proprietary notices contained in the Software; (iii) you may not charge any
third party for the Software; and (iv) you will not export the Software
without the appropriate United States and foreign government licenses.

You acknowledge that no title to the intellectual property in the Software
is transferred to you.  You further acknowledge that title and full
ownership rights to the Software will remain the exclusive property of MSSS
or its suppliers, and you will not acquire any rights to the Software
except as expressly set forth above.  The Software is provided to you AS
IS.  MSSS MAKES NO WARRANTY, EXPRESS OR IMPLIED, WITH RESPECT TO THE
SOFTWARE, AND SPECIFICALLY DISCLAIMS THE IMPLIED WARRANTIES OF
NON-INFRINGEMENT OF THIRD PARTY RIGHTS, MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE.  SOME JURISDICTIONS DO NOT ALLOW THE EXCLUSION OR
LIMITATION OF INCIDENTAL OR CONSEQUENTIAL DAMAGES, SO SUCH LIMITATIONS OR
EXCLUSIONS MAY NOT APPLY TO YOU.

Your use or reproduction of the Software constitutes your agreement to the
terms of this Notice.  If you do not agree with the terms of this notice,
promptly return or destroy all copies of the Software in your possession.

Copyright (C) 1999 Malin Space Science Systems.  All Rights Reserved.

SCCSID @(#)encodeCoefs.static.h	1.1 10/04/99
*/
/* This file was automatically generated by 'makeEncode' */

#if !defined(encodeCoefs_static_h)

#define encodeCoefs_static_h

#include "fs.h"

/* Number of valid bits (LSBs) in each entry in "code0" */
static uint8 num0[25] = {
  24,      23,      20,      19,      16,      14,      13,      10,
  8,       6,       5,       3,       1,       2,       4,       7,
  9,      11,      12,      15,      17,      18,      21,      22,
  24,
};

/* Huffman code for encoding scheme 0, zero's code is index 12 */
static uint32 code0[25] = {
  0xffffff, 0x3fffff, 0x07ffff, 0x03ffff, 0x007fff, 0x001fff, 0x000fff, 0x0001ff,
  0x00007f, 0x00001f, 0x00000f, 0x000003, 0x000000, 0x000001, 0x000007, 0x00003f,
  0x0000ff, 0x0003ff, 0x0007ff, 0x003fff, 0x00ffff, 0x01ffff, 0x0fffff, 0x1fffff,
  0x7fffff,
};

/* Number of valid bits (LSBs) in each entry in "code1" */
static uint8 num1[47] = {
  24,      24,      23,      22,      21,      20,      19,      18,
  17,      16,      15,      14,      13,      12,      11,      10,
  9,       8,       7,       6,       5,       4,       2,       2,
  2,       4,       5,       6,       7,       8,       9,      10,
  11,      12,      13,      14,      15,      16,      17,      18,
  19,      20,      21,      22,      23,      24,      24,
};

/* Huffman code for encoding scheme 1, zero's code is index 23 */
static uint32 code1[47] = {
  0xffffff, 0xbfffff, 0x5fffff, 0x2fffff, 0x17ffff, 0x0bffff, 0x05ffff, 0x02ffff,
  0x017fff, 0x00bfff, 0x005fff, 0x002fff, 0x0017ff, 0x000bff, 0x0005ff, 0x0002ff,
  0x00017f, 0x0000bf, 0x00005f, 0x00002f, 0x000017, 0x00000b, 0x000002, 0x000001,
  0x000000, 0x000003, 0x000007, 0x00000f, 0x00001f, 0x00003f, 0x00007f, 0x0000ff,
  0x0001ff, 0x0003ff, 0x0007ff, 0x000fff, 0x001fff, 0x003fff, 0x007fff, 0x00ffff,
  0x01ffff, 0x03ffff, 0x07ffff, 0x0fffff, 0x1fffff, 0x3fffff, 0x7fffff,
};

/* Number of valid bits (LSBs) in each entry in "code2" */
static uint8 num2[69] = {
  24,      24,      23,      23,      22,      22,      21,      20,
  19,      19,      18,      17,      17,      16,      16,      15,
  14,      14,      13,      12,      11,      11,      10,       9,
  9,       8,       7,       7,       6,       6,       5,       4,
  4,       3,       2,       3,       3,       4,       5,       5,
  6,       7,       8,       8,       9,      10,      10,      11,
  12,      12,      13,      13,      14,      15,      15,      16,
  17,      18,      18,      19,      20,      20,      21,      21,
  22,      23,      23,      24,      24,
};

/* Huffman code for encoding scheme 2, zero's code is index 34 */
static uint32 code2[69] = {
  0xffffff, 0xfffffd, 0x7ffffe, 0x3ffffd, 0x1ffffe, 0x1fffff, 0x0fffff, 0x07fffe,
  0x03fffe, 0x03ffff, 0x01fffd, 0x00fffe, 0x00ffff, 0x007ffe, 0x007fff, 0x003fff,
  0x001ffe, 0x001fff, 0x000fff, 0x0007fe, 0x0003fe, 0x0003ff, 0x0001fe, 0x0000fe,
  0x0000ff, 0x00007d, 0x00003e, 0x00003d, 0x00001d, 0x00001f, 0x00000d, 0x000005,
  0x000007, 0x000001, 0x000000, 0x000003, 0x000002, 0x000006, 0x00000f, 0x00000e,
  0x00001e, 0x00003f, 0x00007f, 0x00007e, 0x0000fd, 0x0001ff, 0x0001fd, 0x0003fd,
  0x0007ff, 0x0007fd, 0x000ffd, 0x000ffe, 0x001ffd, 0x003ffd, 0x003ffe, 0x007ffd,
  0x00fffd, 0x01ffff, 0x01fffe, 0x03fffd, 0x07ffff, 0x07fffd, 0x0ffffd, 0x0ffffe,
  0x1ffffd, 0x3fffff, 0x3ffffe, 0x7ffffd, 0x7fffff,
};

/* Number of valid bits (LSBs) in each entry in "code3" */
static uint8 num3[109] = {
  23,      24,      24,      23,      23,      22,      22,      22,
  21,      21,      21,      20,      20,      19,      19,      18,
  18,      18,      17,      17,      16,      16,      16,      15,
  15,      14,      14,      14,      13,      13,      13,      12,
  12,      11,      11,      10,      10,      10,       9,       9,
  9,       8,       8,       7,       7,       6,       6,       6,
  5,       5,       4,       4,       4,       3,       3,       3,
  4,       4,       5,       5,       5,       6,       6,       7,
  7,       7,       8,       8,       8,       9,       9,      10,
  10,      11,      11,      11,      12,      12,      12,      13,
  13,      14,      14,      15,      15,      15,      16,      16,
  17,      17,      17,      18,      18,      19,      19,      19,
  20,      20,      20,      21,      21,      22,      22,      22,
  23,      23,      24,      24,      23,
};

/* Huffman code for encoding scheme 3, zero's code is index 54 */
static uint32 code3[109] = {
  0x7fffff, 0xfffffd, 0xdfffff, 0x7ffffe, 0x3ffffd, 0x3ffffc, 0x1ffffe, 0x3ffffb,
  0x0ffffe, 0x0ffffd, 0x0ffffb, 0x07fffd, 0x07ffff, 0x03fffc, 0x03ffff, 0x01fffc,
  0x01fffe, 0x01ffff, 0x00fffe, 0x00fffd, 0x007ffc, 0x007ffd, 0x007ffb, 0x003ffc,
  0x003fff, 0x001ffc, 0x001ffd, 0x001fff, 0x000ffc, 0x000ffd, 0x000ffb, 0x0007fd,
  0x0007fb, 0x0003fe, 0x0003fd, 0x0001fc, 0x0001fd, 0x0001ff, 0x0000fc, 0x0000ff,
  0x0000fb, 0x00007d, 0x00007b, 0x00003c, 0x00003d, 0x00001c, 0x00001e, 0x00001b,
  0x00000e, 0x00000f, 0x000004, 0x000006, 0x000003, 0x000002, 0x000001, 0x000000,
  0x000007, 0x000005, 0x00000b, 0x00000d, 0x00000c, 0x00001f, 0x00001d, 0x00003b,
  0x00003f, 0x00003e, 0x00007f, 0x00007e, 0x00007c, 0x0000fd, 0x0000fe, 0x0001fb,
  0x0001fe, 0x0003fb, 0x0003ff, 0x0003fc, 0x0007ff, 0x0007fe, 0x0007fc, 0x000fff,
  0x000ffe, 0x001ffb, 0x001ffe, 0x003ffb, 0x003ffd, 0x003ffe, 0x007fff, 0x007ffe,
  0x00fffb, 0x00ffff, 0x00fffc, 0x01fffb, 0x01fffd, 0x03fffb, 0x03fffd, 0x03fffe,
  0x07fffb, 0x07fffe, 0x07fffc, 0x0fffff, 0x0ffffc, 0x1ffffb, 0x1ffffd, 0x1ffffc,
  0x1fffff, 0x3ffffe, 0x5fffff, 0x7ffffd, 0x3fffff,
};

/* Number of valid bits (LSBs) in each entry in "code4" */
static uint8 num4[169] = {
  22,      24,      24,      24,      24,      23,      23,      23,
  23,      22,      22,      22,      22,      21,      21,      21,
  21,      20,      20,      20,      20,      19,      19,      19,
  19,      18,      18,      18,      18,      17,      17,      17,
  17,      16,      16,      16,      16,      15,      15,      15,
  15,      14,      14,      14,      14,      13,      13,      13,
  13,      12,      12,      12,      12,      11,      11,      11,
  11,      10,      10,      10,      10,       9,       9,       9,
  9,       8,       8,       8,       8,       7,       7,       7,
  7,       6,       6,       6,       6,       5,       5,       5,
  5,       4,       4,       4,       3,       4,       4,       4,
  5,       5,       5,       5,       6,       6,       6,       6,
  7,       7,       7,       7,       8,       8,       8,       8,
  9,       9,       9,       9,      10,      10,      10,      10,
  11,      11,      11,      11,      12,      12,      12,      12,
  13,      13,      13,      13,      14,      14,      14,      14,
  15,      15,      15,      15,      16,      16,      16,      16,
  17,      17,      17,      17,      18,      18,      18,      18,
  19,      19,      19,      19,      20,      20,      20,      20,
  21,      21,      21,      21,      22,      22,      22,      22,
  23,      23,      23,      23,      24,      24,      24,      24,
  22,
};

/* Huffman code for encoding scheme 4, zero's code is index 84 */
static uint32 code4[169] = {
  0x3fffff, 0xf7ffff, 0xe7ffff, 0xfdffff, 0xfffffe, 0x27ffff, 0x7bffff, 0x3dffff,
  0x5ffffe, 0x17ffff, 0x1bffff, 0x3ffffc, 0x2ffffe, 0x0bffff, 0x0dffff, 0x17fffc,
  0x17fffe, 0x03ffff, 0x0ffffd, 0x0bfffc, 0x0bfffe, 0x03fffd, 0x05fffd, 0x05fffc,
  0x05fffe, 0x02ffff, 0x02fffd, 0x02fffc, 0x02fffe, 0x017fff, 0x017ffd, 0x017ffc,
  0x017ffe, 0x00bfff, 0x00bffd, 0x00bffc, 0x00bffe, 0x005fff, 0x005ffd, 0x005ffc,
  0x005ffe, 0x002fff, 0x002ffd, 0x002ffc, 0x002ffe, 0x0017ff, 0x0017fd, 0x0017fc,
  0x0017fe, 0x000bff, 0x000bfd, 0x000bfc, 0x000bfe, 0x0005ff, 0x0005fd, 0x0005fc,
  0x0005fe, 0x0002ff, 0x0002fd, 0x0002fc, 0x0002fe, 0x00017f, 0x00017d, 0x00017c,
  0x00017e, 0x0000bf, 0x0000bd, 0x0000bc, 0x0000be, 0x00005f, 0x00005d, 0x00005c,
  0x00005e, 0x00002f, 0x00002d, 0x00002c, 0x00002e, 0x000017, 0x000015, 0x000014,
  0x000016, 0x000009, 0x000008, 0x00000a, 0x000003, 0x000002, 0x000000, 0x000001,
  0x000006, 0x000004, 0x000005, 0x000007, 0x00000e, 0x00000c, 0x00000d, 0x00000f,
  0x00001e, 0x00001c, 0x00001d, 0x00001f, 0x00003e, 0x00003c, 0x00003d, 0x00003f,
  0x00007e, 0x00007c, 0x00007d, 0x00007f, 0x0000fe, 0x0000fc, 0x0000fd, 0x0000ff,
  0x0001fe, 0x0001fc, 0x0001fd, 0x0001ff, 0x0003fe, 0x0003fc, 0x0003fd, 0x0003ff,
  0x0007fe, 0x0007fc, 0x0007fd, 0x0007ff, 0x000ffe, 0x000ffc, 0x000ffd, 0x000fff,
  0x001ffe, 0x001ffc, 0x001ffd, 0x001fff, 0x003ffe, 0x003ffc, 0x003ffd, 0x003fff,
  0x007ffe, 0x007ffc, 0x007ffd, 0x007fff, 0x00fffe, 0x00fffc, 0x00fffd, 0x00ffff,
  0x01fffe, 0x01fffc, 0x01fffd, 0x01ffff, 0x03fffe, 0x03fffc, 0x07fffd, 0x05ffff,
  0x07fffe, 0x07fffc, 0x0ffffc, 0x0fffff, 0x0ffffe, 0x1ffffc, 0x1dffff, 0x07ffff,
  0x1ffffe, 0x3ffffe, 0x3bffff, 0x37ffff, 0x7ffffe, 0x7dffff, 0x67ffff, 0x77ffff,
  0x1fffff,
};

/* Number of valid bits (LSBs) in each entry in "code5" */
static uint8 num5[247] = {
  21,      24,      24,      24,      24,      24,      24,      23,
  23,      23,      23,      23,      23,      22,      22,      22,
  22,      22,      22,      22,      21,      21,      21,      21,
  21,      20,      20,      20,      20,      20,      20,      19,
  19,      19,      19,      19,      19,      18,      18,      18,
  18,      18,      18,      17,      17,      17,      17,      17,
  17,      16,      16,      16,      16,      16,      16,      15,
  15,      15,      15,      15,      15,      14,      14,      14,
  14,      14,      14,      13,      13,      13,      13,      13,
  13,      12,      12,      12,      12,      12,      12,      11,
  11,      11,      11,      11,      11,      10,      10,      10,
  10,      10,      10,       9,       9,       9,       9,       9,
  9,       8,       8,       8,       8,       8,       8,       7,
  7,       7,       7,       7,       7,       6,       6,       6,
  6,       6,       6,       5,       5,       5,       5,       5,
  5,       5,       4,       4,       4,       5,       5,       5,
  5,       5,       5,       5,       6,       6,       6,       6,
  6,       6,       7,       7,       7,       7,       7,       7,
  8,       8,       8,       8,       8,       8,       9,       9,
  9,       9,       9,       9,      10,      10,      10,      10,
  10,      10,      11,      11,      11,      11,      11,      11,
  12,      12,      12,      12,      12,      12,      13,      13,
  13,      13,      13,      13,      14,      14,      14,      14,
  14,      14,      15,      15,      15,      15,      15,      15,
  16,      16,      16,      16,      16,      16,      17,      17,
  17,      17,      17,      17,      18,      18,      18,      18,
  18,      18,      19,      19,      19,      19,      19,      19,
  20,      20,      20,      20,      20,      20,      21,      21,
  21,      21,      21,      21,      22,      22,      22,      22,
  22,      22,      23,      23,      23,      23,      23,      23,
  24,      24,      24,      24,      24,      24,      21,
};

/* Huffman code for encoding scheme 5, zero's code is index 123 */
static uint32 code5[247] = {
  0x1fffff, 0xfffffd, 0xfffffe, 0xfffffa, 0xff7ffa, 0xfffffc, 0xfffff8, 0x5ffffd,
  0x3ffffd, 0x7fbffe, 0x3f7ffa, 0x5ffffc, 0x3ffffc, 0x37ffff, 0x3fdffd, 0x1fbffe,
  0x1f7ffa, 0x2ffffc, 0x2ffff8, 0x1ffff8, 0x0ffffd, 0x0fbffe, 0x0ffffa, 0x17fffc,
  0x17fff8, 0x0bffff, 0x07fffd, 0x07bffe, 0x077ffa, 0x0bfffc, 0x0bfff8, 0x05ffff,
  0x03fffd, 0x03fffe, 0x037ffa, 0x05fffc, 0x05fff8, 0x02ffff, 0x01dffd, 0x01fffe,
  0x017ffa, 0x02fffc, 0x02fff8, 0x017fff, 0x00fffd, 0x00fffe, 0x007ffa, 0x017ffc,
  0x017ff8, 0x00bfff, 0x005ffd, 0x003ffe, 0x00bffa, 0x00bffc, 0x00bff8, 0x005fff,
  0x001ffd, 0x005ffe, 0x005ffa, 0x005ffc, 0x005ff8, 0x002fff, 0x002ffd, 0x002ffe,
  0x002ffa, 0x002ffc, 0x002ff8, 0x0017ff, 0x0017fd, 0x0017fe, 0x0017fa, 0x0017fc,
  0x0017f8, 0x000bff, 0x000bfd, 0x000bfe, 0x000bfa, 0x000bfc, 0x000bf8, 0x0005ff,
  0x0005fd, 0x0005fe, 0x0005fa, 0x0005fc, 0x0005f8, 0x0002ff, 0x0002fd, 0x0002fe,
  0x0002fa, 0x0002fc, 0x0002f8, 0x00017f, 0x00017d, 0x00017e, 0x00017a, 0x00017c,
  0x000178, 0x0000bf, 0x0000bd, 0x0000be, 0x0000ba, 0x0000bc, 0x0000b8, 0x00005f,
  0x00005d, 0x00005e, 0x00005a, 0x00005c, 0x000058, 0x00002f, 0x00002d, 0x00002e,
  0x00002a, 0x00002c, 0x000028, 0x000017, 0x000015, 0x000019, 0x000016, 0x000012,
  0x000014, 0x000010, 0x00000b, 0x000001, 0x000003, 0x000000, 0x000004, 0x000002,
  0x000006, 0x000009, 0x000005, 0x000007, 0x000008, 0x00000c, 0x00000a, 0x00000e,
  0x00000d, 0x00000f, 0x000018, 0x00001c, 0x00001a, 0x00001e, 0x00001d, 0x00001f,
  0x000038, 0x00003c, 0x00003a, 0x00003e, 0x00003d, 0x00003f, 0x000078, 0x00007c,
  0x00007a, 0x00007e, 0x00007d, 0x00007f, 0x0000f8, 0x0000fc, 0x0000fa, 0x0000fe,
  0x0000fd, 0x0000ff, 0x0001f8, 0x0001fc, 0x0001fa, 0x0001fe, 0x0001fd, 0x0001ff,
  0x0003f8, 0x0003fc, 0x0003fa, 0x0003fe, 0x0003fd, 0x0003ff, 0x0007f8, 0x0007fc,
  0x0007fa, 0x0007fe, 0x0007fd, 0x0007ff, 0x000ff8, 0x000ffc, 0x000ffa, 0x000ffe,
  0x000ffd, 0x000fff, 0x001ff8, 0x001ffc, 0x001ffa, 0x001ffe, 0x003ffd, 0x001fff,
  0x003ff8, 0x003ffc, 0x003ffa, 0x007ffe, 0x007ffd, 0x003fff, 0x007ff8, 0x007ffc,
  0x00fffa, 0x00bffe, 0x00dffd, 0x007fff, 0x00fff8, 0x00fffc, 0x01fffa, 0x01bffe,
  0x01fffd, 0x00ffff, 0x01fff8, 0x01fffc, 0x03fffa, 0x03bffe, 0x03dffd, 0x01ffff,
  0x03fff8, 0x03fffc, 0x07fffa, 0x07fffe, 0x07dffd, 0x03ffff, 0x07fff8, 0x07fffc,
  0x0f7ffa, 0x0ffffe, 0x0fdffd, 0x07ffff, 0x0ffff8, 0x0ffffc, 0x1ffffa, 0x1ffffe,
  0x1fdffd, 0x17ffff, 0x3ffff8, 0x1ffffc, 0x3ffffa, 0x3fbffe, 0x3ffffe, 0x1ffffd,
  0x7ffff8, 0x7ffffc, 0x7f7ffa, 0x7ffffa, 0x7ffffe, 0x7ffffd, 0x0fffff,
};

/* Number of valid bits (LSBs) in each entry in "code6" */
static uint8 num6[395] = {
  21,      24,      24,      24,      24,      24,      24,      24,
  24,      24,      23,      23,      23,      23,      23,      23,
  23,      23,      23,      23,      22,      22,      22,      22,
  22,      22,      22,      22,      22,      22,      22,      21,
  21,      21,      21,      21,      21,      21,      21,      21,
  21,      20,      20,      20,      20,      20,      20,      20,
  20,      20,      20,      19,      19,      19,      19,      19,
  19,      19,      19,      19,      19,      18,      18,      18,
  18,      18,      18,      18,      18,      18,      18,      17,
  17,      17,      17,      17,      17,      17,      17,      17,
  17,      16,      16,      16,      16,      16,      16,      16,
  16,      16,      16,      15,      15,      15,      15,      15,
  15,      15,      15,      15,      15,      14,      14,      14,
  14,      14,      14,      14,      14,      14,      14,      13,
  13,      13,      13,      13,      13,      13,      13,      13,
  13,      12,      12,      12,      12,      12,      12,      12,
  12,      12,      12,      11,      11,      11,      11,      11,
  11,      11,      11,      11,      11,      10,      10,      10,
  10,      10,      10,      10,      10,      10,      10,       9,
  9,       9,       9,       9,       9,       9,       9,       9,
  9,       8,       8,       8,       8,       8,       8,       8,
  8,       8,       8,       7,       7,       7,       7,       7,
  7,       7,       7,       7,       7,       6,       6,       6,
  6,       6,       6,       6,       6,       6,       6,       6,
  5,       5,       5,       5,       5,       5,       5,       5,
  5,       5,       5,       6,       6,       6,       6,       6,
  6,       6,       6,       6,       6,       6,       7,       7,
  7,       7,       7,       7,       7,       7,       7,       7,
  8,       8,       8,       8,       8,       8,       8,       8,
  8,       8,       9,       9,       9,       9,       9,       9,
  9,       9,       9,       9,      10,      10,      10,      10,
  10,      10,      10,      10,      10,      10,      11,      11,
  11,      11,      11,      11,      11,      11,      11,      11,
  12,      12,      12,      12,      12,      12,      12,      12,
  12,      12,      13,      13,      13,      13,      13,      13,
  13,      13,      13,      13,      14,      14,      14,      14,
  14,      14,      14,      14,      14,      14,      15,      15,
  15,      15,      15,      15,      15,      15,      15,      15,
  16,      16,      16,      16,      16,      16,      16,      16,
  16,      16,      17,      17,      17,      17,      17,      17,
  17,      17,      17,      17,      18,      18,      18,      18,
  18,      18,      18,      18,      18,      18,      19,      19,
  19,      19,      19,      19,      19,      19,      19,      19,
  20,      20,      20,      20,      20,      20,      20,      20,
  20,      20,      21,      21,      21,      21,      21,      21,
  21,      21,      21,      21,      22,      22,      22,      22,
  22,      22,      22,      22,      22,      22,      23,      23,
  23,      23,      23,      23,      23,      23,      23,      23,
  23,      24,      24,      24,      24,      24,      24,      24,
  24,      24,      21,
};

/* Huffman code for encoding scheme 6, zero's code is index 197 */
static uint32 code6[395] = {
  0x1fffff, 0xfffffe, 0xfffffc, 0xfffff8, 0xffbff8, 0xfffffd, 0xfffff9, 0xfffffb,
  0xfffff3, 0xfffff7, 0x7ffffa, 0x5ffffe, 0x3ffffc, 0x7fdffc, 0x3ffff8, 0x5ffffd,
  0x3ffffd, 0x6ffffb, 0x3ffffb, 0x5ffff7, 0x1ffffa, 0x3feffa, 0x3fdffe, 0x1fdffc,
  0x1ffff8, 0x2ffffd, 0x2ffff9, 0x0ffffb, 0x1ffffb, 0x37ffff, 0x3fdff7, 0x0feffa,
  0x0fdffe, 0x0fdffc, 0x0ffff8, 0x17fffd, 0x17fff9, 0x17fffb, 0x17fff3, 0x0ffff3,
  0x0ffff7, 0x07effa, 0x07fffe, 0x07fffc, 0x07bff8, 0x0bfffd, 0x0bfff9, 0x0bfffb,
  0x0bfff3, 0x0bffff, 0x07dff7, 0x03effa, 0x03dffe, 0x03fffc, 0x03bff8, 0x05fffd,
  0x05fff9, 0x05fffb, 0x05fff3, 0x05ffff, 0x03fff7, 0x01effa, 0x01dffe, 0x01fffc,
  0x01bff8, 0x02fffd, 0x02fff9, 0x02fffb, 0x02fff3, 0x02ffff, 0x01dff7, 0x00fffa,
  0x00fffe, 0x00dffc, 0x00bff8, 0x017ffd, 0x017ff9, 0x017ffb, 0x017ff3, 0x017fff,
  0x00fff7, 0x006ffa, 0x007ffe, 0x007ffc, 0x003ff8, 0x00bffd, 0x00bff9, 0x00bffb,
  0x00bff3, 0x00bfff, 0x005ff7, 0x003ffa, 0x001ffe, 0x003ffc, 0x005ff8, 0x005ffd,
  0x005ff9, 0x005ffb, 0x005ff3, 0x005fff, 0x001ff7, 0x001ffa, 0x002ffe, 0x002ffc,
  0x002ff8, 0x002ffd, 0x002ff9, 0x002ffb, 0x002ff3, 0x002fff, 0x002ff7, 0x0017fa,
  0x0017fe, 0x0017fc, 0x0017f8, 0x0017fd, 0x0017f9, 0x0017fb, 0x0017f3, 0x0017ff,
  0x0017f7, 0x000bfa, 0x000bfe, 0x000bfc, 0x000bf8, 0x000bfd, 0x000bf9, 0x000bfb,
  0x000bf3, 0x000bff, 0x000bf7, 0x0005fa, 0x0005fe, 0x0005fc, 0x0005f8, 0x0005fd,
  0x0005f9, 0x0005fb, 0x0005f3, 0x0005ff, 0x0005f7, 0x0002fa, 0x0002fe, 0x0002fc,
  0x0002f8, 0x0002fd, 0x0002f9, 0x0002fb, 0x0002f3, 0x0002ff, 0x0002f7, 0x00017a,
  0x00017e, 0x00017c, 0x000178, 0x00017d, 0x000179, 0x00017b, 0x000173, 0x00017f,
  0x000177, 0x0000ba, 0x0000be, 0x0000bc, 0x0000b8, 0x0000bd, 0x0000b9, 0x0000bb,
  0x0000b3, 0x0000bf, 0x0000b7, 0x00005a, 0x00005e, 0x00005c, 0x000058, 0x00005d,
  0x000059, 0x00005b, 0x000053, 0x00005f, 0x000057, 0x00002a, 0x00002e, 0x00002c,
  0x000028, 0x00002d, 0x000029, 0x000031, 0x00002b, 0x000023, 0x00002f, 0x000027,
  0x000012, 0x000016, 0x000014, 0x000010, 0x000015, 0x000001, 0x000005, 0x000000,
  0x000004, 0x000006, 0x000002, 0x000007, 0x00000f, 0x000003, 0x00000b, 0x000011,
  0x000009, 0x00000d, 0x000008, 0x00000c, 0x00000e, 0x00000a, 0x000017, 0x00001f,
  0x000013, 0x00001b, 0x000019, 0x00001d, 0x000018, 0x00001c, 0x00001e, 0x00001a,
  0x000037, 0x00003f, 0x000033, 0x00003b, 0x000039, 0x00003d, 0x000038, 0x00003c,
  0x00003e, 0x00003a, 0x000077, 0x00007f, 0x000073, 0x00007b, 0x000079, 0x00007d,
  0x000078, 0x00007c, 0x00007e, 0x00007a, 0x0000f7, 0x0000ff, 0x0000f3, 0x0000fb,
  0x0000f9, 0x0000fd, 0x0000f8, 0x0000fc, 0x0000fe, 0x0000fa, 0x0001f7, 0x0001ff,
  0x0001f3, 0x0001fb, 0x0001f9, 0x0001fd, 0x0001f8, 0x0001fc, 0x0001fe, 0x0001fa,
  0x0003f7, 0x0003ff, 0x0003f3, 0x0003fb, 0x0003f9, 0x0003fd, 0x0003f8, 0x0003fc,
  0x0003fe, 0x0003fa, 0x0007f7, 0x0007ff, 0x0007f3, 0x0007fb, 0x0007f9, 0x0007fd,
  0x0007f8, 0x0007fc, 0x0007fe, 0x0007fa, 0x000ff7, 0x000fff, 0x000ff3, 0x000ffb,
  0x000ff9, 0x000ffd, 0x000ff8, 0x000ffc, 0x000ffe, 0x000ffa, 0x003ff7, 0x001fff,
  0x001ff3, 0x001ffb, 0x001ff9, 0x001ffd, 0x001ff8, 0x001ffc, 0x003ffe, 0x002ffa,
  0x007ff7, 0x003fff, 0x003ff3, 0x003ffb, 0x003ff9, 0x003ffd, 0x007ff8, 0x005ffc,
  0x005ffe, 0x007ffa, 0x00dff7, 0x007fff, 0x007ff3, 0x007ffb, 0x007ff9, 0x007ffd,
  0x00fff8, 0x00fffc, 0x00dffe, 0x00effa, 0x01fff7, 0x00ffff, 0x00fff3, 0x00fffb,
  0x00fff9, 0x00fffd, 0x01fff8, 0x01dffc, 0x01fffe, 0x01fffa, 0x03dff7, 0x01ffff,
  0x01fff3, 0x01fffb, 0x01fff9, 0x01fffd, 0x03fff8, 0x03dffc, 0x03fffe, 0x03fffa,
  0x07fff7, 0x03ffff, 0x03fff3, 0x03fffb, 0x03fff9, 0x03fffd, 0x07fff8, 0x07dffc,
  0x07dffe, 0x07fffa, 0x0fdff7, 0x07ffff, 0x07fff3, 0x07fffb, 0x07fff9, 0x07fffd,
  0x0fbff8, 0x0ffffc, 0x0ffffe, 0x0ffffa, 0x1fdff7, 0x17ffff, 0x1ffff3, 0x1ffff9,
  0x0ffff9, 0x0ffffd, 0x1fbff8, 0x1ffffc, 0x1fdffe, 0x1feffa, 0x3ffff7, 0x1ffff7,
  0x3ffff3, 0x2ffffb, 0x3ffff9, 0x1ffffd, 0x3fbff8, 0x3fdffc, 0x3ffffe, 0x1ffffe,
  0x3ffffa, 0x7ffff7, 0x7ffff3, 0x7ffffb, 0x7ffff9, 0x7ffffd, 0x7fbff8, 0x7ffff8,
  0x7ffffc, 0x7ffffe, 0x0fffff,
};

/* Number of valid bits (LSBs) in each entry in "code7" */
static uint8 num7[609] = {
  20,      24,      24,      24,      24,      24,      24,      24,
  24,      24,      24,      24,      24,      24,      24,      24,
  24,      23,      23,      23,      23,      23,      23,      23,
  23,      23,      23,      23,      23,      23,      23,      23,
  23,      22,      22,      22,      22,      22,      22,      22,
  22,      22,      22,      22,      22,      22,      22,      22,
  22,      21,      21,      21,      21,      21,      21,      21,
  21,      21,      21,      21,      21,      21,      21,      21,
  21,      20,      20,      20,      20,      20,      20,      20,
  20,      20,      20,      20,      20,      20,      20,      20,
  20,      19,      19,      19,      19,      19,      19,      19,
  19,      19,      19,      19,      19,      19,      19,      19,
  19,      18,      18,      18,      18,      18,      18,      18,
  18,      18,      18,      18,      18,      18,      18,      18,
  18,      17,      17,      17,      17,      17,      17,      17,
  17,      17,      17,      17,      17,      17,      17,      17,
  17,      16,      16,      16,      16,      16,      16,      16,
  16,      16,      16,      16,      16,      16,      16,      16,
  16,      15,      15,      15,      15,      15,      15,      15,
  15,      15,      15,      15,      15,      15,      15,      15,
  15,      14,      14,      14,      14,      14,      14,      14,
  14,      14,      14,      14,      14,      14,      14,      14,
  14,      13,      13,      13,      13,      13,      13,      13,
  13,      13,      13,      13,      13,      13,      13,      13,
  13,      12,      12,      12,      12,      12,      12,      12,
  12,      12,      12,      12,      12,      12,      12,      12,
  12,      11,      11,      11,      11,      11,      11,      11,
  11,      11,      11,      11,      11,      11,      11,      11,
  11,      10,      10,      10,      10,      10,      10,      10,
  10,      10,      10,      10,      10,      10,      10,      10,
  10,       9,       9,       9,       9,       9,       9,       9,
  9,       9,       9,       9,       9,       9,       9,       9,
  9,       8,       8,       8,       8,       8,       8,       8,
  8,       8,       8,       8,       8,       8,       8,       8,
  8,       7,       7,       7,       7,       7,       7,       7,
  7,       7,       7,       7,       7,       7,       7,       7,
  6,       6,       6,       6,       6,       6,       6,       6,
  6,       6,       6,       6,       6,       6,       6,       6,
  6,       6,       6,       6,       6,       6,       6,       6,
  6,       6,       6,       6,       6,       6,       6,       6,
  6,       7,       7,       7,       7,       7,       7,       7,
  7,       7,       7,       7,       7,       7,       7,       7,
  8,       8,       8,       8,       8,       8,       8,       8,
  8,       8,       8,       8,       8,       8,       8,       8,
  9,       9,       9,       9,       9,       9,       9,       9,
  9,       9,       9,       9,       9,       9,       9,       9,
  10,      10,      10,      10,      10,      10,      10,      10,
  10,      10,      10,      10,      10,      10,      10,      10,
  11,      11,      11,      11,      11,      11,      11,      11,
  11,      11,      11,      11,      11,      11,      11,      11,
  12,      12,      12,      12,      12,      12,      12,      12,
  12,      12,      12,      12,      12,      12,      12,      12,
  13,      13,      13,      13,      13,      13,      13,      13,
  13,      13,      13,      13,      13,      13,      13,      13,
  14,      14,      14,      14,      14,      14,      14,      14,
  14,      14,      14,      14,      14,      14,      14,      14,
  15,      15,      15,      15,      15,      15,      15,      15,
  15,      15,      15,      15,      15,      15,      15,      15,
  16,      16,      16,      16,      16,      16,      16,      16,
  16,      16,      16,      16,      16,      16,      16,      16,
  17,      17,      17,      17,      17,      17,      17,      17,
  17,      17,      17,      17,      17,      17,      17,      17,
  18,      18,      18,      18,      18,      18,      18,      18,
  18,      18,      18,      18,      18,      18,      18,      18,
  19,      19,      19,      19,      19,      19,      19,      19,
  19,      19,      19,      19,      19,      19,      19,      19,
  20,      20,      20,      20,      20,      20,      20,      20,
  20,      20,      20,      20,      20,      20,      20,      20,
  21,      21,      21,      21,      21,      21,      21,      21,
  21,      21,      21,      21,      21,      21,      21,      21,
  22,      22,      22,      22,      22,      22,      22,      22,
  22,      22,      22,      22,      22,      22,      22,      22,
  23,      23,      23,      23,      23,      23,      23,      23,
  23,      23,      23,      23,      23,      23,      23,      23,
  24,      24,      24,      24,      24,      24,      24,      24,
  24,      24,      24,      24,      24,      24,      24,      24,
  20,
};

/* Huffman code for encoding scheme 7, zero's code is index 304 */
static uint32 code7[609] = {
  0x0fffff, 0xfffffd, 0xeffffd, 0xfffff5, 0xfffff9, 0xfffff1, 0xfffffb, 0xfffff3,
  0xfffff7, 0xfdffff, 0xedffff, 0xfffffe, 0xfffffa, 0xfffffc, 0xf7fffc, 0xfffff8,
  0xfffff0, 0x2ffffd, 0x77fff5, 0x3ffff9, 0x5ffff9, 0x3ffffb, 0x7bfffb, 0x3ffff7,
  0x5ffff7, 0x2dffff, 0x7bfffe, 0x3ffffe, 0x5ffffa, 0x3ffffc, 0x7ffff4, 0x3ffff0,
  0x5ffff0, 0x0ffffd, 0x1ffff5, 0x37fff9, 0x3bfff1, 0x1ffffb, 0x1bfffb, 0x2ffff3,
  0x2ffff7, 0x1dffff, 0x1bfffe, 0x3bfffa, 0x3ffff2, 0x1ffffc, 0x1ffff8, 0x2ffff8,
  0x2ffff0, 0x17fffd, 0x0ffff5, 0x0ffff9, 0x0bfff1, 0x0bfffb, 0x1bfff3, 0x1bfff7,
  0x1bffff, 0x1ffff6, 0x0ffffe, 0x0ffffa, 0x0ffff2, 0x0ffff4, 0x17fff4, 0x17fff8,
  0x17fff0, 0x0bfffd, 0x0bfff5, 0x0bfff9, 0x07fff1, 0x07fffb, 0x07fff3, 0x03fff7,
  0x03ffff, 0x03fffe, 0x07fffe, 0x07fffa, 0x0bfff2, 0x0bfffc, 0x0bfff4, 0x0bfff8,
  0x0bfff0, 0x05fffd, 0x05fff5, 0x05fff9, 0x05fff1, 0x05fffb, 0x05fff3, 0x05fff7,
  0x01ffff, 0x05fff6, 0x05fffe, 0x05fffa, 0x05fff2, 0x05fffc, 0x05fff4, 0x05fff8,
  0x05fff0, 0x02fffd, 0x02fff5, 0x02fff9, 0x02fff1, 0x02fffb, 0x02fff3, 0x02fff7,
  0x02ffff, 0x02fff6, 0x02fffe, 0x02fffa, 0x02fff2, 0x02fffc, 0x02fff4, 0x02fff8,
  0x02fff0, 0x017ffd, 0x017ff5, 0x017ff9, 0x017ff1, 0x017ffb, 0x017ff3, 0x017ff7,
  0x017fff, 0x017ff6, 0x017ffe, 0x017ffa, 0x017ff2, 0x017ffc, 0x017ff4, 0x017ff8,
  0x017ff0, 0x00bffd, 0x00bff5, 0x00bff9, 0x00bff1, 0x00bffb, 0x00bff3, 0x00bff7,
  0x00bfff, 0x00bff6, 0x00bffe, 0x00bffa, 0x00bff2, 0x00bffc, 0x00bff4, 0x00bff8,
  0x00bff0, 0x005ffd, 0x005ff5, 0x005ff9, 0x005ff1, 0x005ffb, 0x005ff3, 0x005ff7,
  0x005fff, 0x005ff6, 0x005ffe, 0x005ffa, 0x005ff2, 0x005ffc, 0x005ff4, 0x005ff8,
  0x005ff0, 0x002ffd, 0x002ff5, 0x002ff9, 0x002ff1, 0x002ffb, 0x002ff3, 0x002ff7,
  0x002fff, 0x002ff6, 0x002ffe, 0x002ffa, 0x002ff2, 0x002ffc, 0x002ff4, 0x002ff8,
  0x002ff0, 0x0017fd, 0x0017f5, 0x0017f9, 0x0017f1, 0x0017fb, 0x0017f3, 0x0017f7,
  0x0017ff, 0x0017f6, 0x0017fe, 0x0017fa, 0x0017f2, 0x0017fc, 0x0017f4, 0x0017f8,
  0x0017f0, 0x000bfd, 0x000bf5, 0x000bf9, 0x000bf1, 0x000bfb, 0x000bf3, 0x000bf7,
  0x000bff, 0x000bf6, 0x000bfe, 0x000bfa, 0x000bf2, 0x000bfc, 0x000bf4, 0x000bf8,
  0x000bf0, 0x0005fd, 0x0005f5, 0x0005f9, 0x0005f1, 0x0005fb, 0x0005f3, 0x0005f7,
  0x0005ff, 0x0005f6, 0x0005fe, 0x0005fa, 0x0005f2, 0x0005fc, 0x0005f4, 0x0005f8,
  0x0005f0, 0x0002fd, 0x0002f5, 0x0002f9, 0x0002f1, 0x0002fb, 0x0002f3, 0x0002f7,
  0x0002ff, 0x0002f6, 0x0002fe, 0x0002fa, 0x0002f2, 0x0002fc, 0x0002f4, 0x0002f8,
  0x0002f0, 0x00017d, 0x000175, 0x000179, 0x000171, 0x00017b, 0x000173, 0x000177,
  0x00017f, 0x000176, 0x00017e, 0x00017a, 0x000172, 0x00017c, 0x000174, 0x000178,
  0x000170, 0x0000bd, 0x0000b5, 0x0000b9, 0x0000b1, 0x0000bb, 0x0000b3, 0x0000b7,
  0x0000bf, 0x0000b6, 0x0000be, 0x0000ba, 0x0000b2, 0x0000bc, 0x0000b4, 0x0000b8,
  0x0000b0, 0x00005d, 0x000055, 0x000059, 0x000051, 0x00005b, 0x000053, 0x000057,
  0x00005f, 0x000056, 0x00005e, 0x00005a, 0x000052, 0x00005c, 0x000054, 0x000058,
  0x00002d, 0x000025, 0x000029, 0x000021, 0x00002b, 0x000023, 0x000027, 0x00002f,
  0x000026, 0x00002e, 0x00002a, 0x000022, 0x00002c, 0x000024, 0x000028, 0x000020,
  0x000010, 0x000000, 0x000008, 0x000004, 0x00000c, 0x000002, 0x00000a, 0x00000e,
  0x000006, 0x00000f, 0x000007, 0x000003, 0x00000b, 0x000001, 0x000009, 0x000005,
  0x00000d, 0x000018, 0x000014, 0x00001c, 0x000012, 0x00001a, 0x00001e, 0x000016,
  0x00001f, 0x000017, 0x000013, 0x00001b, 0x000011, 0x000019, 0x000015, 0x00001d,
  0x000030, 0x000038, 0x000034, 0x00003c, 0x000032, 0x00003a, 0x00003e, 0x000036,
  0x00003f, 0x000037, 0x000033, 0x00003b, 0x000031, 0x000039, 0x000035, 0x00003d,
  0x000070, 0x000078, 0x000074, 0x00007c, 0x000072, 0x00007a, 0x00007e, 0x000076,
  0x00007f, 0x000077, 0x000073, 0x00007b, 0x000071, 0x000079, 0x000075, 0x00007d,
  0x0000f0, 0x0000f8, 0x0000f4, 0x0000fc, 0x0000f2, 0x0000fa, 0x0000fe, 0x0000f6,
  0x0000ff, 0x0000f7, 0x0000f3, 0x0000fb, 0x0000f1, 0x0000f9, 0x0000f5, 0x0000fd,
  0x0001f0, 0x0001f8, 0x0001f4, 0x0001fc, 0x0001f2, 0x0001fa, 0x0001fe, 0x0001f6,
  0x0001ff, 0x0001f7, 0x0001f3, 0x0001fb, 0x0001f1, 0x0001f9, 0x0001f5, 0x0001fd,
  0x0003f0, 0x0003f8, 0x0003f4, 0x0003fc, 0x0003f2, 0x0003fa, 0x0003fe, 0x0003f6,
  0x0003ff, 0x0003f7, 0x0003f3, 0x0003fb, 0x0003f1, 0x0003f9, 0x0003f5, 0x0003fd,
  0x0007f0, 0x0007f8, 0x0007f4, 0x0007fc, 0x0007f2, 0x0007fa, 0x0007fe, 0x0007f6,
  0x0007ff, 0x0007f7, 0x0007f3, 0x0007fb, 0x0007f1, 0x0007f9, 0x0007f5, 0x0007fd,
  0x000ff0, 0x000ff8, 0x000ff4, 0x000ffc, 0x000ff2, 0x000ffa, 0x000ffe, 0x000ff6,
  0x000fff, 0x000ff7, 0x000ff3, 0x000ffb, 0x000ff1, 0x000ff9, 0x000ff5, 0x000ffd,
  0x001ff0, 0x001ff8, 0x001ff4, 0x001ffc, 0x001ff2, 0x001ffa, 0x001ffe, 0x001ff6,
  0x001fff, 0x001ff7, 0x001ff3, 0x001ffb, 0x001ff1, 0x001ff9, 0x001ff5, 0x001ffd,
  0x003ff0, 0x003ff8, 0x003ff4, 0x003ffc, 0x003ff2, 0x003ffa, 0x003ffe, 0x003ff6,
  0x003fff, 0x003ff7, 0x003ff3, 0x003ffb, 0x003ff1, 0x003ff9, 0x003ff5, 0x003ffd,
  0x007ff0, 0x007ff8, 0x007ff4, 0x007ffc, 0x007ff2, 0x007ffa, 0x007ffe, 0x007ff6,
  0x007fff, 0x007ff7, 0x007ff3, 0x007ffb, 0x007ff1, 0x007ff9, 0x007ff5, 0x007ffd,
  0x00fff0, 0x00fff8, 0x00fff4, 0x00fffc, 0x00fff2, 0x00fffa, 0x00fffe, 0x00fff6,
  0x00ffff, 0x00fff7, 0x00fff3, 0x00fffb, 0x00fff1, 0x00fff9, 0x00fff5, 0x00fffd,
  0x01fff0, 0x01fff8, 0x01fff4, 0x01fffc, 0x01fff2, 0x01fffa, 0x01fffe, 0x01fff6,
  0x03fff6, 0x01fff7, 0x01fff3, 0x01fffb, 0x01fff1, 0x01fff9, 0x01fff5, 0x01fffd,
  0x03fff0, 0x03fff8, 0x03fff4, 0x03fffc, 0x03fff2, 0x07fff2, 0x03fffa, 0x07fff6,
  0x05ffff, 0x07fff7, 0x03fff3, 0x03fffb, 0x03fff1, 0x03fff9, 0x03fff5, 0x03fffd,
  0x07fff0, 0x07fff8, 0x07fff4, 0x07fffc, 0x0ffffc, 0x0bfffa, 0x0bfffe, 0x0ffff6,
  0x0bffff, 0x0bfff7, 0x0bfff3, 0x0ffffb, 0x0ffff1, 0x07fff9, 0x07fff5, 0x07fffd,
  0x0ffff0, 0x0ffff8, 0x1ffff4, 0x17fffc, 0x1ffff2, 0x1bfffa, 0x1ffffe, 0x0dffff,
  0x0ffff7, 0x0ffff3, 0x1ffff3, 0x1ffff1, 0x1bfff1, 0x17fff9, 0x17fff5, 0x1ffffd,
  0x1ffff0, 0x3ffff8, 0x3ffff4, 0x37fffc, 0x1ffffa, 0x3ffffa, 0x3bfffe, 0x3dffff,
  0x1ffff7, 0x3ffff3, 0x3bfffb, 0x3ffff1, 0x1ffff9, 0x3ffff5, 0x37fff5, 0x3ffffd,
  0x7ffff0, 0x7ffff8, 0x77fffc, 0x7ffffc, 0x7ffffa, 0x7ffffe, 0x6dffff, 0x7dffff,
  0x7ffff7, 0x7ffff3, 0x7ffffb, 0x7ffff1, 0x7ffff9, 0x7ffff5, 0x6ffffd, 0x7ffffd,
  0x07ffff,
};

/* Size of each Huffman encoding scheme */
static uint16 sizes[8] = {
  25, 47, 69, 109, 169, 247, 395, 609,
};

/* Array of bit count array pointers for each encoding scheme */
static uint8 *counts[8] = {
  num0, num1, num2, num3, num4, num5, num6, num7,
};

/* Array of Huffman code array pointers for each encoding scheme */
static uint32 *encodings[8] = {
  code0, code1, code2, code3, code4, code5, code6, code7,
};

#endif
