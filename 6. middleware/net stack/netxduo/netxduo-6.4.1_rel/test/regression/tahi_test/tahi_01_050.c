#include "nx_api.h"
#if defined(NX_TAHI_ENABLE) && defined(FEATURE_NX_IPV6)  

#include "netx_tahi.h"

/* Frame (102 bytes) */
static char pkt1[102] = {
0x33, 0x33, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, /* 33...... */
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x30, 0x3a, 0xff, 0xfe, 0x80, /* ...0:... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xff, 0x02, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, /* ........ */
0x42, 0x5c, 0x40, 0x00, 0x07, 0x0d, 0x00, 0x00, /* B\@..... */
0x75, 0x35, 0x00, 0x00, 0x03, 0xed, 0x03, 0x04, /* u5...... */
0x40, 0xc0, 0x00, 0x00, 0x27, 0x10, 0x00, 0x00, /* @...'... */
0x27, 0x10, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, /* '.....?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00              /* ...... */
};

/* Frame (78 bytes) */
static char pkt2[78] = {
0x33, 0x33, 0xff, 0x33, 0x44, 0x56, 0x00, 0x11, /* 33.3DV.. */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x18, 0x3a, 0xff, 0x00, 0x00, /* ....:... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x02, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x01, 0xff, 0x33, 0x44, 0x56, 0x87, 0x00, /* ...3DV.. */
0x88, 0x85, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, /* ......?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56              /* "..3DV */
};

#if 0
/* Frame (78 bytes) */
static char pkt3[78] = {
0x33, 0x33, 0xff, 0x33, 0x44, 0x56, 0x00, 0x11, /* 33.3DV.. */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x18, 0x3a, 0xff, 0x00, 0x00, /* ....:... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x02, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x01, 0xff, 0x33, 0x44, 0x56, 0x87, 0x00, /* ...3DV.. */
0x88, 0x85, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, /* ......?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56              /* "..3DV */
};
#endif

/* Frame (70 bytes) */
static char pkt4[70] = {
0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, /* .."3DV.. */
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x10, 0x3a, 0xff, 0xfe, 0x80, /* ....:... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xfe, 0x80, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x80, 0x00, /* "..3DV.. */
0x69, 0x64, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, /* id...... */
0x03, 0x04, 0x05, 0x06, 0x07, 0x08              /* ...... */
};

/* Frame (86 bytes) */
static char pkt5[86] = {
0x33, 0x33, 0xff, 0x00, 0xa0, 0xa0, 0x00, 0x11, /* 33...... */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, /* ... :... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xff, 0x02, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x01, 0xff, 0x00, 0xa0, 0xa0, 0x87, 0x00, /* ........ */
0x6c, 0x27, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, /* l'...... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, /* ........ */
0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (86 bytes) */
static char pkt6[86] = {
0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, /* .."3DV.. */
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, /* ... :... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xfe, 0x80, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x88, 0x00, /* "..3DV.. */
0x4e, 0xa4, 0xe0, 0x00, 0x00, 0x00, 0xfe, 0x80, /* N....... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x02, 0x01, /* ........ */
0x00, 0x00, 0x00, 0x00, 0xa0, 0xa0              /* ...... */
};

/* Frame (70 bytes) */
static char pkt7[70] = {
0x00, 0x00, 0x00, 0x00, 0xa0, 0xa0, 0x00, 0x11, /* ........ */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x10, 0x3a, 0x40, 0xfe, 0x80, /* ....:@.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x81, 0x00, /* ........ */
0x68, 0x64, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, /* hd...... */
0x03, 0x04, 0x05, 0x06, 0x07, 0x08              /* ...... */
};

/* Frame (94 bytes) */
static char pkt8[94] = {
0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, /* .."3DV.. */
0x00, 0x00, 0x01, 0x00, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x28, 0x2c, 0xff, 0x3f, 0xfe, /* ...(,.?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0x3f, 0xfe, /* ......?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x3a, 0x00, /* "..3DV:. */
0x00, 0x01, 0x00, 0x00, 0x05, 0x26, 0x80, 0x00, /* .....&.. */
0x48, 0x72, 0x05, 0x26, 0x00, 0x00, 0x01, 0x01, /* Hr.&.... */
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, /* ........ */
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, /* ........ */
0x01, 0x01, 0x01, 0x01, 0x01, 0x01              /* ...... */
};

/* Frame (86 bytes) */
static char pkt9[86] = {
0x33, 0x33, 0xff, 0x00, 0x01, 0x00, 0x00, 0x11, /* 33...... */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0x3f, 0xfe, /* ... :.?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xff, 0x02, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x01, 0xff, 0x00, 0x01, 0x00, 0x87, 0x00, /* ........ */
0x1c, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, /* .l....?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0x01, 0x01, /* ........ */
0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (86 bytes) */
static char pkt10[86] = {
0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, /* .."3DV.. */
0x00, 0x00, 0x01, 0x00, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0x3f, 0xfe, /* ... :.?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0x3f, 0xfe, /* ......?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x88, 0x00, /* "..3DV.. */
0xd7, 0x0b, 0x60, 0x00, 0x00, 0x00, 0x3f, 0xfe, /* ..`...?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0x02, 0x01, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x01, 0x00              /* ...... */
};

/* Frame (142 bytes) */
static char pkt11[142] = {
0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x11, /* ........ */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x58, 0x3a, 0xff, 0x3f, 0xfe, /* ...X:.?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x3f, 0xfe, /* "..3DV?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0x03, 0x01, /* ........ */
0x6b, 0x47, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, /* kG....`. */
0x00, 0x00, 0x00, 0x28, 0x2c, 0xff, 0x3f, 0xfe, /* ...(,.?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0x3f, 0xfe, /* ......?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x3a, 0x00, /* "..3DV:. */
0x00, 0x01, 0x00, 0x00, 0x05, 0x26, 0x80, 0x00, /* .....&.. */
0x48, 0x72, 0x05, 0x26, 0x00, 0x00, 0x01, 0x01, /* Hr.&.... */
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, /* ........ */
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, /* ........ */
0x01, 0x01, 0x01, 0x01, 0x01, 0x01              /* ...... */
};

/* Frame (86 bytes) */
static char pkt12[86] = {
0x33, 0x33, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, /* 33...... */
0x00, 0x00, 0x01, 0x00, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0x3f, 0xfe, /* ... :.?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0xff, 0x02, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x88, 0x00, /* ........ */
0x3e, 0x08, 0x20, 0x00, 0x00, 0x00, 0x3f, 0xfe, /* >. ...?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0x02, 0x01, /* ........ */
0x00, 0x11, 0x33, 0x77, 0x55, 0x11              /* ..3wU. */
};

/* Frame (70 bytes) */
static char pkt13[70] = {
0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, /* .."3DV.. */
0x00, 0x00, 0x01, 0x00, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x10, 0x3a, 0xff, 0x3f, 0xfe, /* ....:.?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0x3f, 0xfe, /* ......?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x80, 0x00, /* "..3DV.. */
0x7a, 0x08, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, /* z....... */
0x03, 0x04, 0x05, 0x06, 0x07, 0x08              /* ...... */
};

/* Frame (70 bytes) */
static char pkt14[70] = {
0x00, 0x11, 0x33, 0x77, 0x55, 0x11, 0x00, 0x11, /* ..3wU... */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x10, 0x3a, 0x40, 0x3f, 0xfe, /* ....:@?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x3f, 0xfe, /* "..3DV?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0x81, 0x00, /* ........ */
0x79, 0x08, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, /* y....... */
0x03, 0x04, 0x05, 0x06, 0x07, 0x08              /* ...... */
};

/* Frame (86 bytes) */
static char pkt15[86] = {
0x00, 0x11, 0x33, 0x77, 0x55, 0x11, 0x00, 0x11, /* ..3wU... */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0x3f, 0xfe, /* ... :.?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x3f, 0xfe, /* "..3DV?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0x87, 0x00, /* ........ */
0xd3, 0x71, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, /* .q....?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0x01, 0x01, /* ........ */
0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (86 bytes) */
static char pkt16[86] = {
0x00, 0x11, 0x33, 0x77, 0x55, 0x11, 0x00, 0x11, /* ..3wU... */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0x3f, 0xfe, /* ... :.?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x3f, 0xfe, /* "..3DV?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0x87, 0x00, /* ........ */
0xd3, 0x71, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, /* .q....?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0x01, 0x01, /* ........ */
0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (86 bytes) */
static char pkt17[86] = {
0x00, 0x11, 0x33, 0x77, 0x55, 0x11, 0x00, 0x11, /* ..3wU... */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0x3f, 0xfe, /* ... :.?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x3f, 0xfe, /* "..3DV?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0x87, 0x00, /* ........ */
0xd3, 0x71, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, /* .q....?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0x01, 0x01, /* ........ */
0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (102 bytes) */
static char pkt18[102] = {
0x33, 0x33, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, /* 33...... */
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x30, 0x3a, 0xff, 0xfe, 0x80, /* ...0:... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xff, 0x02, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, /* ........ */
0x97, 0x89, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, /* ..@..... */
0x75, 0x35, 0x00, 0x00, 0x03, 0xed, 0x03, 0x04, /* u5...... */
0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* @....... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, /* ......?. */
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00              /* ...... */
};

/* Frame (86 bytes) */
static char pkt19[86] = {
0x33, 0x33, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, /* 33...... */
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, /* ... :... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xff, 0x02, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x88, 0x00, /* ........ */
0x0d, 0xc3, 0xa0, 0x00, 0x00, 0x00, 0xfe, 0x80, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x02, 0x01, /* ........ */
0x00, 0x11, 0x33, 0x77, 0x55, 0x11              /* ..3wU. */
};

/* Frame (70 bytes) */
static char pkt20[70] = {
0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, /* .."3DV.. */
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
0x00, 0x00, 0x00, 0x10, 0x3a, 0xff, 0xfe, 0x80, /* ....:... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xfe, 0x80, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x80, 0x00, /* "..3DV.. */
0x69, 0x64, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, /* id...... */
0x03, 0x04, 0x05, 0x06, 0x07, 0x08              /* ...... */
};

/* Frame (70 bytes) */
static char pkt21[70] = {
0x00, 0x11, 0x33, 0x77, 0x55, 0x11, 0x00, 0x11, /* ..3wU... */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x10, 0x3a, 0x40, 0xfe, 0x80, /* ....:@.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x81, 0x00, /* ........ */
0x68, 0x64, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, /* hd...... */
0x03, 0x04, 0x05, 0x06, 0x07, 0x08              /* ...... */
};

/* Frame (86 bytes) */
static char pkt22[86] = {
0x00, 0x11, 0x33, 0x77, 0x55, 0x11, 0x00, 0x11, /* ..3wU... */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, /* ... :... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x87, 0x00, /* ........ */
0x6a, 0xab, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, /* j....... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, /* ........ */
0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (86 bytes) */
static char pkt23[86] = {
0x00, 0x11, 0x33, 0x77, 0x55, 0x11, 0x00, 0x11, /* ..3wU... */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, /* ... :... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x87, 0x00, /* ........ */
0x6a, 0xab, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, /* j....... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, /* ........ */
0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (86 bytes) */
static char pkt24[86] = {
0x00, 0x11, 0x33, 0x77, 0x55, 0x11, 0x00, 0x11, /* ..3wU... */
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, /* ... :... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, /* "..3DV.. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x87, 0x00, /* ........ */
0x6a, 0xab, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, /* j....... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, /* ........ */
0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};




TAHI_TEST_SEQ tahi_01_050[] = {
    {TITLE, "01-050", 6, 0},
    {WAIT, NX_NULL, 0, 5},

    {INJECT, &pkt1[0], sizeof(pkt1), 0},
    {CHECK, &pkt2[0], sizeof(pkt2), 5}, 

    {WAIT, NX_NULL, 0, 5},
    {INJECT, &pkt4[0], sizeof(pkt4), 0},
    {CHECK, &pkt5[0], sizeof(pkt5), 5}, 
    {INJECT, &pkt6[0], sizeof(pkt6), 0},
    {CHECK, &pkt7[0], sizeof(pkt7), 5}, 

    {WAIT, NX_NULL, 0, 5},
    {INJECT, &pkt8[0], sizeof(pkt8), 0},   //step 10
    {CHECK, &pkt9[0], sizeof(pkt9), 65},   

    {INJECT, &pkt10[0], sizeof(pkt10), 0},
    {CHECK, &pkt11[0], sizeof(pkt11), 5}, 
    {INJECT, &pkt12[0], sizeof(pkt12), 0},  
    {INJECT, &pkt13[0], sizeof(pkt13), 0},   
    {CHECK, &pkt14[0], sizeof(pkt14), 5},
    {CHECK, &pkt15[0], sizeof(pkt15), 10}, 
    {CHECK, &pkt16[0], sizeof(pkt16), 5},
    {CHECK, &pkt17[0], sizeof(pkt17), 5},

    {WAIT, NX_NULL, 0, 3},
    {INJECT, &pkt18[0], sizeof(pkt18), 0},
    {INJECT, &pkt19[0], sizeof(pkt19), 0},
    {INJECT, &pkt20[0], sizeof(pkt20), 0},
    {CHECK, &pkt21[0], sizeof(pkt21), 5},

    {CHECK, &pkt22[0], sizeof(pkt22), 10},
    {CHECK, &pkt23[0], sizeof(pkt23), 5},
    {CHECK, &pkt24[0], sizeof(pkt24), 5},

    {CLEANUP, NX_NULL, 0, 0},
    {DUMP, NX_NULL, 0, 0}
};

int tahi_01_050_size = sizeof(tahi_01_050) / sizeof(TAHI_TEST_SEQ);

#endif /* NX_TAHI_ENABLE */
