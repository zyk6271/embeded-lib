#include "nx_api.h"
#if defined(NX_TAHI_ENABLE) && defined(FEATURE_NX_IPV6)  

#include "netx_tahi.h"

static char pkt1[] = {
0x33, 0x33, 0xff, 0x33, 0x44, 0x56, 0x00, 0x11, 
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x18, 0x3a, 0xff, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x02, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x01, 0xff, 0x33, 0x44, 0x56, 0x87, 0x00, 
0xd0, 0x03, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56 };

#if 0
static char pkt2[] = {
0x33, 0x33, 0xff, 0x33, 0x44, 0x56, 0x00, 0x11, 
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x18, 0x3a, 0xff, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x02, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x01, 0xff, 0x33, 0x44, 0x56, 0x87, 0x00, 
0xd0, 0x03, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56 };

static char pkt3[] = {
0x33, 0x33, 0xff, 0x33, 0x44, 0x56, 0x00, 0x11, 
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x18, 0x3a, 0xff, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x02, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x01, 0xff, 0x33, 0x44, 0x56, 0x87, 0x00, 
0xd0, 0x03, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56 };
#endif

static char pkt4[] = {
0x33, 0x33, 0x00, 0x00, 0x00, 0x02, 0x00, 0x11, 
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x10, 0x3a, 0xff, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xff, 0x02, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x85, 0x00, 
0xad, 0xf9, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
0x00, 0x11, 0x22, 0x33, 0x44, 0x56 };

static char pkt5[] = {
0x33, 0x33, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 
0x00, 0x00, 0x01, 0x00, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x38, 0x3a, 0xff, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0xff, 0x02, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, 
0x6d, 0xec, 0x40, 0x00, 0x07, 0x0d, 0x00, 0x00, 
0x75, 0x35, 0x00, 0x00, 0x03, 0xed, 0x01, 0x01, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x04, 
0x00, 0xc0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 
0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, 
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

static char pkt6[] = {
0x33, 0x33, 0xff, 0x33, 0x44, 0x56, 0x00, 0x00, 
0x00, 0x00, 0x01, 0x00, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0x01, 0x00, 0xff, 0x02, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x01, 0xff, 0x33, 0x44, 0x56, 0x87, 0x00, 
0x85, 0xfb, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, 
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x01, 0x01, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x00 };

TAHI_TEST_SEQ tahi_03_037[] = {
    {TITLE, "03-037", 6, 0},

    {CHECK, &pkt1[0], sizeof(pkt1), 130},
    {CHECK, &pkt4[0], sizeof(pkt4), 5},

    {INJECT, &pkt5[0], sizeof(pkt5), 0},
    {N_CHECK, (char *)NS, 0, 5},

    {INJECT, &pkt6[0], sizeof(pkt6), 0},
    {N_CHECK, (char *)NA, 0, 5},

    {CLEANUP, NX_NULL, 0, 0},
    {DUMP, NX_NULL, 0, 0}
};

int tahi_03_037_size = sizeof(tahi_03_037) / sizeof(TAHI_TEST_SEQ);

#endif /* NX_TAHI_ENABLE */
