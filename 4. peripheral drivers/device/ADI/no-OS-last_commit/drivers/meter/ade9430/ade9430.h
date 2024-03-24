/***************************************************************************//**
 *   @file   ade9430.h
 *   @brief  Header file of ADE9430 Driver.
 *   @author Antoniu Miclaus (antoniu.miclaus@analog.com)
********************************************************************************
 * Copyright 2023(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/
#ifndef __ADE9430_H__
#define __ADE9430_H__

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "no_os_util.h"
#include "no_os_spi.h"

/******************************************************************************/
/********************** Macros and Constants Definitions **********************/
/******************************************************************************/

/* SPI commands */
#define ADE9430_SPI_READ		NO_OS_BIT(3)
#define ADE9430_R1B			NO_OS_BIT(16)
#define ADE9430_R2B			NO_OS_BIT(17)

/* ADE9430 Register Map */
#define ADE9430_REG_AIGAIN		0x0000
#define ADE9430_REG_AIGAIN0		0x0001
#define ADE9430_REG_AIGAIN1		0x0002
#define ADE9430_REG_AIGAIN2		0x0003
#define ADE9430_REG_AIGAIN3		0x0004
#define ADE9430_REG_AIGAIN4		0x0005
#define ADE9430_REG_APHCAL0		0x0006
#define ADE9430_REG_APHCAL1		0x0007
#define ADE9430_REG_APHCAL2		0x0008
#define ADE9430_REG_APHCAL3		0x0009
#define ADE9430_REG_APHCAL4		0x000A
#define ADE9430_REG_AVGAIN		0x000B
#define ADE9430_REG_AIRMSOS		0x000C
#define ADE9430_REG_AVRMSOS		0x000D
#define ADE9430_REG_APGAIN		0x000E
#define ADE9430_REG_AWATTOS		0x000F
#define ADE9430_REG_AVAROS		0x0010
#define ADE9430_REG_AFWATTOS		0x0011
#define ADE9430_REG_AFVAROS		0x0012
#define ADE9430_REG_AIFRMSOS		0x0013
#define ADE9430_REG_AVFRMSOS		0x0014
#define ADE9430_REG_AVRMSONEOS		0x0015
#define ADE9430_REG_AIRMSONEOS		0x0016
#define ADE9430_REG_AVRMS1012OS		0x0017
#define ADE9430_REG_AIRMS1012OS 	0x0018
#define ADE9430_REG_BIGAIN		0x0020
#define ADE9430_REG_BIGAIN0		0x0021
#define ADE9430_REG_BIGAIN1		0x0022
#define ADE9430_REG_BIGAIN2		0x0023
#define ADE9430_REG_BIGAIN3		0x0024
#define ADE9430_REG_BIGAIN4		0x0025
#define ADE9430_REG_BPHCAL0 		0x0026
#define ADE9430_REG_BPHCAL1		0x0027
#define ADE9430_REG_BPHCAL2 		0x0028
#define ADE9430_REG_BPHCAL3		0x0029
#define ADE9430_REG_BPHCAL4		0x002A
#define ADE9430_REG_BVGAIN		0x002B
#define ADE9430_REG_BIRMSOS		0x002C
#define ADE9430_REG_BVRMSOS		0x002D
#define ADE9430_REG_BPGAIN		0x002E
#define ADE9430_REG_BWATTOS		0x002F
#define ADE9430_REG_BVAROS		0x0030
#define ADE9430_REG_BFWATTOS		0x0031
#define ADE9430_REG_BFVAROS		0x0032
#define ADE9430_REG_BIFRMSOS		0x0033
#define ADE9430_REG_BVFRMSOS		0x0034
#define ADE9430_REG_BVRMSONEOS		0x0035
#define ADE9430_REG_BIRMSONEOS		0x0036
#define ADE9430_REG_BVRMS1012OS		0x0037
#define ADE9430_REG_BIRMS1012OS		0x0038
#define ADE9430_REG_CIGAIN		0x0040
#define ADE9430_REG_CIGAIN0		0x0041
#define ADE9430_REG_CIGAIN1		0x0042
#define ADE9430_REG_CIGAIN2		0x0043
#define ADE9430_REG_CIGAIN3		0x0044
#define ADE9430_REG_CIGAIN4		0x0045
#define ADE9430_REG_CPHCAL0		0x0046
#define ADE9430_REG_CPHCAL1		0x0047
#define ADE9430_REG_CPHCAL2		0x0048
#define ADE9430_REG_CPHCAL3		0x0049
#define ADE9430_REG_CPHCAL4		0x004A
#define ADE9430_REG_CVGAIN		0x004B
#define ADE9430_REG_CIRMSOS		0x004C
#define ADE9430_REG_CVRMSOS		0x004D
#define ADE9430_REG_CPGAIN		0x004E
#define ADE9430_REG_CWATTOS		0x004F
#define ADE9430_REG_CVAROS		0x0050
#define ADE9430_REG_CFWATTOS		0x0051
#define ADE9430_REG_CFVAROS		0x0052
#define ADE9430_REG_CIFRMSOS		0x0053
#define ADE9430_REG_CVFRMSOS		0x0054
#define ADE9430_REG_CVRMSONEOS		0x0055
#define ADE9430_REG_CIRMSONEOS		0x0056
#define ADE9430_REG_CVRMS1012OS		0x0057
#define ADE9430_REG_CIRMS1012OS 	0x0058
#define ADE9430_REG_CONFIG0		0x0060
#define ADE9430_REG_MTTHR_L0		0x0061
#define ADE9430_REG_MTTHR_L1 		0x0062
#define ADE9430_REG_MTTHR_L2 		0x0063
#define ADE9430_REG_MTTHR_L3		0x0064
#define ADE9430_REG_MTTHR_L4		0x0065
#define ADE9430_REG_MTTHR_H0		0x0066
#define ADE9430_REG_MTTHR_H1 		0x0067
#define ADE9430_REG_MTTHR_H2 		0x0068
#define ADE9430_REG_MTTHR_H3		0x0069
#define ADE9430_REG_MTTHR_H4		0x006A
#define ADE9430_REG_NIRMSOS		0x006B
#define ADE9430_REG_ISUMRMSOS		0x006C
#define ADE9430_REG_NIGAIN		0x006D
#define ADE9430_REG_NPHCAL		0x006E
#define ADE9430_REG_NIRMSONEOS		0x006F
#define ADE9430_REG_NIRMS1012OS		0x0070
#define ADE9430_REG_VNOM		0x0071
#define ADE9430_REG_ISUMLVL		0x0073
#define ADE9430_REG_AI_PCF		0x020A
#define ADE9430_REG_AV_PCF		0x020B
#define ADE9430_REG_AIRMS		0x020C
#define ADE9430_REG_AVRMS		0x020D
#define ADE9430_REG_AIFRMS		0x020E
#define ADE9430_REG_AVFRMS		0x020F
#define ADE9430_REG_AWATT		0x0210
#define ADE9430_REG_AVAR		0x0211
#define ADE9430_REG_AVA			0x0212
#define ADE9430_REG_AFWATT		0x0213
#define ADE9430_REG_AFVAR		0x0214
#define ADE9430_REG_AFVA		0x0215
#define ADE9430_REG_APF			0x0216
#define ADE9430_REG_AIRMSONE		0x0219
#define ADE9430_REG_AVRMSONE		0x021A
#define ADE9430_REG_AIRMS1012		0x021B
#define ADE9430_REG_AVRMS1012 		0x021C
#define ADE9430_REG_AMTREGION 		0x021D
#define ADE9430_REG_BI_PCF		0x022A
#define ADE9430_REG_BV_PCF		0x022B
#define ADE9430_REG_BIRMS		0x022C
#define ADE9430_REG_BVRMS		0x022D
#define ADE9430_REG_BIFRMS		0x022E
#define ADE9430_REG_BVFRMS		0x022F
#define ADE9430_REG_BWATT		0x0230
#define ADE9430_REG_BVAR		0x0231
#define ADE9430_REG_BVA			0x0232
#define ADE9430_REG_BFWATT		0x0233
#define ADE9430_REG_BFVAR		0x0234
#define ADE9430_REG_BFVA		0x0235
#define ADE9430_REG_BPF			0x0236
#define ADE9430_REG_BIRMSONE		0x0239
#define ADE9430_REG_BVRMSONE		0x023A
#define ADE9430_REG_BIRMS1012		0x023B
#define ADE9430_REG_BVRMS1012		0x023C
#define ADE9430_REG_BMTREGION		0x023D
#define ADE9430_REG_CI_PCF		0x024A
#define ADE9430_REG_CV_PCF		0x024B
#define ADE9430_REG_CIRMS		0x024C
#define ADE9430_REG_CVRMS		0x024D
#define ADE9430_REG_CIFRMS		0x024E
#define ADE9430_REG_CVFRMS		0x024F
#define ADE9430_REG_CWATT		0x0250
#define ADE9430_REG_CVAR		0x0251
#define ADE9430_REG_CVA			0x0252
#define ADE9430_REG_CFWATT		0x0253
#define ADE9430_REG_CFVAR		0x0254
#define ADE9430_REG_CFVA		0x0255
#define ADE9430_REG_CPF			0x0256
#define ADE9430_REG_CIRMSONE		0x0259
#define ADE9430_REG_CVRMSONE		0x025A
#define ADE9430_REG_CIRMS1012		0x025B
#define ADE9430_REG_CVRMS1012		0x025C
#define ADE9430_REG_CMTREGION		0x025D
#define ADE9430_REG_NI_PCF		0x0265
#define ADE9430_REG_NIRMS		0x0266
#define ADE9430_REG_NIRMSONE		0x0267
#define ADE9430_REG_NIRMS1012		0x0268
#define ADE9430_REG_ISUMRMS		0x0269
#define ADE9430_REG_VERSION2		0x026A
#define ADE9430_REG_NPERIOD_FORRMS	0x026B
#define ADE9430_REG_COH_PAGE		0x026C
#define ADE9430_REG_RESAMPLE_STATUS	0x026D
#define ADE9430_REG_AWATT_ACC		0x02E5
#define ADE9430_REG_AWATTHR_LO		0x02E6
#define ADE9430_REG_AWATTHR_HI		0x02E7
#define ADE9430_REG_AVAR_ACC		0x02EF
#define ADE9430_REG_AVARHR_LO		0x02F0
#define ADE9430_REG_AVARHR_HI		0x02F1
#define ADE9430_REG_AVA_ACC		0x02F9
#define ADE9430_REG_AVAHR_LO		0x02FA
#define ADE9430_REG_AVAHR_HI		0x02FB
#define ADE9430_REG_AFWATT_ACC		0x0303
#define ADE9430_REG_AFWATTHR_LO 	0x0304
#define ADE9430_REG_AFWATTHR_HI 	0x0305
#define ADE9430_REG_AFVAR_ACC	 	0x030D
#define ADE9430_REG_AFVARHR_LO 		0x030E
#define ADE9430_REG_AFVARHR_HI	 	0x030F
#define ADE9430_REG_AFVA_ACC	 	0x0317
#define ADE9430_REG_AFVAHR_LO	 	0x0318
#define ADE9430_REG_AFVAHR_HI	 	0x0319
#define ADE9430_REG_BWATT_ACC	 	0x0321
#define ADE9430_REG_BWATTHR_LO	 	0x0322
#define ADE9430_REG_BWATTHR_HI	 	0x0323
#define ADE9430_REG_BVAR_ACC	 	0x032B
#define ADE9430_REG_BVARHR_LO	 	0x032C
#define ADE9430_REG_BVARHR_HI	 	0x032D
#define ADE9430_REG_BVA_ACC	 	0x0335
#define ADE9430_REG_BVAHR_LO	 	0x0336
#define ADE9430_REG_BVAHR_HI	 	0x0337
#define ADE9430_REG_BFWATT_ACC	 	0x033F
#define ADE9430_REG_BFWATTHR_LO 	0x0340
#define ADE9430_REG_BFWATTHR_HI		0x0341
#define ADE9430_REG_BFVAR_ACC		0x0349
#define ADE9430_REG_BFVARHR_LO		0x034A
#define ADE9430_REG_BFVARHR_HI		0x034B
#define ADE9430_REG_BFVA_ACC		0x0353
#define ADE9430_REG_BFVAHR_LO		0x0354
#define ADE9430_REG_BFVAHR_HI		0x0355
#define ADE9430_REG_CWATT_ACC		0x0355
#define ADE9430_REG_CWATTHR_LO		0x035E
#define ADE9430_REG_CWATTHR_HI		0x035F
#define ADE9430_REG_CVAR_ACC		0x0367
#define ADE9430_REG_CVARHR_LO		0x0368
#define ADE9430_REG_CVARHR_HI		0x0369
#define ADE9430_REG_CVA_ACC		0x0371
#define ADE9430_REG_CVAHR_LO		0x0372
#define ADE9430_REG_CVAHR_HI		0x0373
#define ADE9430_REG_CFWATT_ACC 		0x037B
#define ADE9430_REG_CFWATTHR_LO		0x037C
#define ADE9430_REG_CFWATTHR_HI		0x037D
#define ADE9430_REG_CFVAR_ACC		0x0385
#define ADE9430_REG_CFVARHR_LO		0x0386
#define ADE9430_REG_CFVARHR_HI		0x0387
#define ADE9430_REG_CFVA_ACC 		0x038F
#define ADE9430_REG_CFVAHR_LO		0x0390
#define ADE9430_REG_CFVAHR_HI		0x0391
#define ADE9430_REG_PWATT_ACC		0x0397
#define ADE9430_REG_NWATT_ACC		0x039B
#define ADE9430_REG_PVAR_ACC		0x039F
#define ADE9430_REG_NVAR_ACC		0x03A3
#define ADE9430_REG_IPEAK		0x0400
#define ADE9430_REG_VPEAK		0x0401
#define ADE9430_REG_STATUS0		0x0402
#define ADE9430_REG_STATUS1		0x0403
#define ADE9430_REG_EVENT_STATUS	0x0404
#define ADE9430_REG_MASK0		0x0405
#define ADE9430_REG_MASK1		0x0406
#define ADE9430_REG_EVENT_MASK		0x0407
#define ADE9430_REG_OILVL 		0x0409
#define ADE9430_REG_OIA			0x040A
#define ADE9430_REG_OIB			0x040B
#define ADE9430_REG_OIC 		0x040C
#define ADE9430_REG_OIN			0x040D
#define ADE9430_REG_USER_PERIOD		0x040E
#define ADE9430_REG_VLEVEL 		0x040F
#define ADE9430_REG_APERIOD		0x0418
#define ADE9430_REG_BPERIOD		0x0419
#define ADE9430_REG_CPERIOD		0x041A
#define ADE9430_REG_COM_PERIOD		0x041B
#define ADE9430_REG_ACT_NL_LVL		0x041C
#define ADE9430_REG_REACT_NL_LVL	0x041D
#define ADE9430_REG_APP_NL_LVL		0x041E
#define ADE9430_REG_PHNOLOAD		0x041F
#define ADE9430_REG_WTHR		0x0420
#define ADE9430_REG_VARTHR		0x0421
#define ADE9430_REG_VATHR		0x0422
#define ADE9430_REG_LAST_DATA_32	0x0423
#define ADE9430_REG_ADC_REDIRECT	0x0424
#define ADE9430_REG_CF_LCFG		0x0425
#define ADE9430_REG_PART_ID		0x0472
#define ADE9430_REG_TEMP_TRIM		0x0474
#define ADE9430_REG_RUN 		0x0480
#define ADE9430_REG_CONFIG1		0x0481
#define ADE9430_REG_ANGL_VA_VB		0x0482
#define ADE9430_REG_ANGL_VB_VC		0x0483
#define ADE9430_REG_ANGL_VA_VC		0x0484
#define ADE9430_REG_ANGL_VB_IA		0x0485
#define ADE9430_REG_ANGL_VB_IB		0x0486
#define ADE9430_REG_ANGL_VC_IC		0x0487
#define ADE9430_REG_ANGL_IA_IB		0x0488
#define ADE9430_REG_ANGL_IB_IC		0x0489
#define ADE9430_REG_ANGL_IA_IC		0x048A
#define ADE9430_REG_OISTATUS		0x048F
#define ADE9430_REG_CFMODE		0x0490
#define ADE9430_REG_COMPMODE		0x0491
#define ADE9430_REG_ACCMODE		0x0492
#define ADE9430_REG_CONFIG3		0x0493
#define ADE9430_REG_CF1DEN		0x0494
#define ADE9430_REG_CF2DEN		0x0495
#define ADE9430_REG_CF3DEN		0x0496
#define ADE9430_REG_CF4DEN		0x0497
#define ADE9430_REG_ZXTOUT		0x0498
#define ADE9430_REG_ZXTHRSH		0x0499
#define ADE9430_REG_ZX_LP_SEL		0x049A
#define ADE9430_REG_SEQ_CYC		0x049C
#define ADE9430_REG_PHSIGN		0x049D
#define ADE9430_REG_WFB_CFG		0x04A0
#define ADE9430_REG_WFB_PG_IRQEN	0x04A1
#define ADE9430_REG_WFB_TRG_CFG		0x04A2
#define ADE9430_REG_WFB_TRG_STAT	0x04A3
#define ADE9430_REG_CONFIG5		0x04A4
#define ADE9430_REG_CRC_RSLT		0x04A8
#define ADE9430_REG_CRC_SPI		0x04A9
#define ADE9430_REG_LAST_DATA_16	0x04AC
#define ADE9430_REG_LAST_CMD		0x04AE
#define ADE9430_REG_CONFIG2		0x04AF
#define ADE9430_REG_EP_CFG		0x04B0
#define ADE9430_REG_PWR_TIME		0x04B1
#define ADE9430_REG_EGY_TIME		0x04B2
#define ADE9430_REG_CRC_FORCE		0x04B4
#define ADE9430_REG_CRC_OPTEN		0x04B5
#define ADE9430_REG_TEMP_CFG		0x04B6
#define ADE9430_REG_TEMP_RSLT		0x04B7
#define ADE9430_REG_PGA_GAIN		0x04B9
#define ADE9430_REG_CHNL_DIS		0x04BA
#define ADE9430_REG_WR_LOCK 		0x04BF
#define ADE9430_REG_VAR_DIS		0x04E0
#define ADE9430_REG_RESERVED1		0x04F0
#define ADE9430_REG_VERSION 		0x04FE
#define ADE9430_REG_AI_SINC_DAT		0x0500
#define ADE9430_REG_AV_SINC_DAT		0x0501
#define ADE9430_REG_BI_SINC_DAT 	0x0502
#define ADE9430_REG_BV_SINC_DAT 	0x0503
#define ADE9430_REG_CI_SINC_DAT 	0x0504
#define ADE9430_REG_CV_SINC_DAT 	0x0505
#define ADE9430_REG_NI_SINC_DAT 	0x0506
#define ADE9430_REG_AI_LPF_DAT	 	0x0510
#define ADE9430_REG_AV_LPF_DAT	 	0x0511
#define ADE9430_REG_BI_LPF_DAT	 	0x0512
#define ADE9430_REG_BV_LPF_DAT	 	0x0513
#define ADE9430_REG_CI_LPF_DAT	 	0x0514
#define ADE9430_REG_CV_LPF_DAT	 	0x0515
#define ADE9430_REG_NI_LPF_DAT	 	0x0516
#define ADE9430_REG_AV_PCF_1	 	0x0600
#define ADE9430_REG_BV_PCF_1	 	0x0601
#define ADE9430_REG_CV_PCF_1	 	0x0602
#define ADE9430_REG_NI_PCF_1	 	0x0603
#define ADE9430_REG_AI_PCF_1	 	0x0604
#define ADE9430_REG_BI_PCF_1	 	0x0605
#define ADE9430_REG_CI_PCF_1	 	0x0606
#define ADE9430_REG_AIRMS_1	 	0x0607
#define ADE9430_REG_BIRMS_1	 	0x0608
#define ADE9430_REG_CIRMS_1	 	0x0609
#define ADE9430_REG_AVRMS_1	 	0x060A
#define ADE9430_REG_BVRMS_1	 	0x060B
#define ADE9430_REG_CVRMS_1	 	0x060C
#define ADE9430_REG_NIRMS_1	 	0x060D
#define ADE9430_REG_AWATT_1	 	0x060E
#define ADE9430_REG_BWATT_1	 	0x060F
#define ADE9430_REG_CWATT_1	 	0x0610
#define ADE9430_REG_AVA_1	 	0x0611
#define ADE9430_REG_BVA_1	 	0x0612
#define ADE9430_REG_CVA_1	 	0x0613
#define ADE9430_REG_AVAR_1	 	0x0614
#define ADE9430_REG_BVAR_1	 	0x0615
#define ADE9430_REG_CVAR_1	 	0x0616
#define ADE9430_REG_AFVAR_1	 	0x0617
#define ADE9430_REG_BFVAR_1	 	0x0618
#define ADE9430_REG_CFVAR_1	 	0x0619
#define ADE9430_REG_APF_1	 	0x061A
#define ADE9430_REG_BPF_1	 	0x061B
#define ADE9430_REG_CPF_1	 	0x061C
#define ADE9430_REG_AFWATT_1	 	0x0623
#define ADE9430_REG_BFWATT_1	 	0x0624
#define ADE9430_REG_CFWATT_1	 	0x0625
#define ADE9430_REG_AFVA_1	 	0x0626
#define ADE9430_REG_BFVA_1	 	0x0627
#define ADE9430_REG_CFVA_1	 	0x0628
#define ADE9430_REG_AFIRMS_1	 	0x0629
#define ADE9430_REG_BFIRMS_1	 	0x062A
#define ADE9430_REG_CFIRMS_1	 	0x062B
#define ADE9430_REG_AFVRMS_1	 	0x062C
#define ADE9430_REG_BFVRMS_1	 	0x062D
#define ADE9430_REG_CFVRMS_1	 	0x062E
#define ADE9430_REG_AIRMSONE_1	 	0x062F
#define ADE9430_REG_BIRMSONE_1	 	0x0630
#define ADE9430_REG_CIRMSONE_1	 	0x0631
#define ADE9430_REG_AVRMSONE_1	 	0x0622
#define ADE9430_REG_BVRMSONE_1	 	0x0633
#define ADE9430_REG_CVRMSONE_1	 	0x0634
#define ADE9430_REG_NIRSONE_1	 	0x0635
#define ADE9430_REG_AIRMS1012_1	 	0x0636
#define ADE9430_REG_BIRMS1012_1	 	0x0637
#define ADE9430_REG_CIRMS1012_1	 	0x0638
#define ADE9430_REG_AVRMS1012_1	 	0x0639
#define ADE9430_REG_BVRMS1012_1	 	0x063A
#define ADE9430_REG_CVRMS1012_1	 	0x063B
#define ADE9430_REG_NIRMS1012_1	 	0x063C
#define ADE9430_REG_AV_PCF_2	 	0x0680
#define ADE9430_REG_AI_PCF_2	 	0x0681
#define ADE9430_REG_AIRMS_2	 	0x0682
#define ADE9430_REG_AVRMS_2	 	0x0683
#define ADE9430_REG_AWATT_2	 	0x0684
#define ADE9430_REG_AVA_2	 	0x0685
#define ADE9430_REG_AVAR_2 	 	0x0686
#define ADE9430_REG_AFVAR_2 	 	0x0687
#define ADE9430_REG_APF_2 	 	0x0688
#define ADE9430_REG_AFWATT_2 	 	0x068B
#define ADE9430_REG_AFVA_2 	 	0x068C
#define ADE9430_REG_AFIRMS_2 	 	0x068D
#define ADE9430_REG_AFVRMS_2 	 	0x068E
#define ADE9430_REG_AIRMSONE_2 	 	0x068F
#define ADE9430_REG_AVRMSONE_2 	 	0x0690
#define ADE9430_REG_AIRMS1012_2	 	0x0691
#define ADE9430_REG_AVRMS1012_2	 	0x0692
#define ADE9430_REG_BV_PCF_2	 	0x0693
#define ADE9430_REG_BI_PCF_2	 	0x0694
#define ADE9430_REG_BIRMS_2	 	0x0695
#define ADE9430_REG_BVRMS_2	 	0x0696
#define ADE9430_REG_BWATT_2 	 	0x0697
#define ADE9430_REG_BVA_2 	 	0x0698
#define ADE9430_REG_BVAR_2 	 	0x0699
#define ADE9430_REG_BFVAR_2 	 	0x069A
#define ADE9430_REG_BPF_2 	 	0x069B
#define ADE9430_REG_BFWATT_2  	 	0x069E
#define ADE9430_REG_BFVA_2  	 	0x069F
#define ADE9430_REG_BFIRMS_2  	 	0x06A0
#define ADE9430_REG_BFVRMS_2		0x06A1
#define ADE9430_REG_BIRMSONE_2 	 	0x06A2
#define ADE9430_REG_BVRMSONE_2	 	0x06A3
#define ADE9430_REG_BIRMS1012_2	 	0x06A4
#define ADE9430_REG_BVRMS1012_2 	0x06A5
#define ADE9430_REG_CV_PCF_2  	 	0x06A6
#define ADE9430_REG_CI_PCF_2  	 	0x06A7
#define ADE9430_REG_CIRMS_2  	 	0x06A8
#define ADE9430_REG_CVRMS_2  	 	0x06A9
#define ADE9430_REG_CWATT_2  	 	0x06AA
#define ADE9430_REG_CVA_2  	 	0x06AB
#define ADE9430_REG_CVAR_2  	 	0x06AC
#define ADE9430_REG_CFVAR_2  	 	0x06AD
#define ADE9430_REG_CPF_2  	 	0x06AE
#define ADE9430_REG_CFWATT_2  	 	0x06B1
#define ADE9430_REG_CFVA_2		0x06B2
#define ADE9430_REG_CFIRMS_2	 	0x06B3
#define ADE9430_REG_CFVRMS_2	 	0x06B4
#define ADE9430_REG_CIRMSONE_2	 	0x06B5
#define ADE9430_REG_CVRMSONE_2	 	0x06B6
#define ADE9430_REG_CIRMS1012_2	 	0x06B7
#define ADE9430_REG_CVRMS1012_2	 	0x06B8
#define ADE9430_REG_NI_PCF_2	 	0x06B9
#define ADE9430_REG_NIRMS_2 	 	0x06BA
#define ADE9430_REG_NIRMSONE_2 	 	0x06BB
#define ADE9430_REG_NIRMS1012_2	 	0x06BC

/* ADE9430_REG_CONFIG0 Bit Definition */
#define ADE9430_PERIOD_AVG_CFG		NO_OS_GENMASK(17, 16)
#define ADE9430_RESAMPLE_RATE		NO_OS_BIT(15)
#define ADE9430_RMSONE_RATE		NO_OS_BIT(14)
#define ADE9430_DISRPLPF		NO_OS_BIT(13)
#define ADE9430_DISAPLPF		NO_OS_BIT(12)
#define ADE9430_ININTEN			NO_OS_BIT(11)
#define ADE9430_VNOMC_EN		NO_OS_BIT(10)
#define ADE9430_VNOMB_EN		NO_OS_BIT(9)
#define ADE9430_VNOMA_EN 		NO_OS_BIT(8)
#define ADE9430_RMS_SRC_SEL		NO_OS_BIT(7)
#define ADE9430_ZX_SRC_SEL 		NO_OS_BIT(6)
#define ADE9430_INTEN 			NO_OS_BIT(5)
#define ADE9430_MTEN 			NO_OS_BIT(4)
#define ADE9430_HPFDIS 			NO_OS_BIT(3)
#define ADE9430_ISUM_CFG		NO_OS_GENMASK(1, 0)

/* ADE9430_REG_AMTREGION Bit Definition */
#define ADE9430_AREGION			NO_OS_GENMASK(3, 0)

/* ADE9430_REG_BMTREGION Bit Definition */
#define ADE9430_BREGION			NO_OS_GENMASK(3, 0)

/* ADE9430_REG_CMTREGION Bit Definition */
#define ADE9430_CREGION			NO_OS_GENMASK(3, 0)

/* ADE9430_REG_IPEAK Bit Definition */
#define ADE9430_IPPHASE			NO_OS_GENMASK(26, 24)
#define ADE9430_IPEAKVAL		NO_OS_GENMASK(23, 0)

/* ADE9430_REG_VPEAK Bit Definition */
#define ADE9430_VPPHASE			NO_OS_GENMASK(26, 24)
#define ADE9430_VPEAKVAL		NO_OS_GENMASK(23, 0)

/* ADE9430_REG_STATUS0 Bit Definition */
#define ADE9430_STATUS0_TEMP_RDY	NO_OS_BIT(25)
#define ADE9430_STATUS0_MISMTCH		NO_OS_BIT(24)
#define ADE9430_STATUS0_COH_PAGE_RDY	NO_OS_BIT(23)
#define ADE9430_STATUS0_WFB_TRIG	NO_OS_BIT(22)
#define ADE9430_STATUS0_PF_RDY		NO_OS_BIT(21)
#define ADE9430_STATUS0_RMS1012RDY	NO_OS_BIT(20)
#define ADE9430_STATUS0_RMSONERDY	NO_OS_BIT(19)
#define ADE9430_STATUS0_PWRRDY		NO_OS_BIT(18)
#define ADE9430_STATUS0_PAGE_FULL	NO_OS_BIT(17)
#define ADE9430_STATUS0_WFB_TRIG_IRQ	NO_OS_BIT(16)
#define ADE9430_STATUS0_DREADY		NO_OS_BIT(15)
#define ADE9430_STATUS0_CF4 		NO_OS_BIT(14)
#define ADE9430_STATUS0_CF3 		NO_OS_BIT(13)
#define ADE9430_STATUS0_CF2 		NO_OS_BIT(12)
#define ADE9430_STATUS0_CF1 		NO_OS_BIT(11)
#define ADE9430_STATUS0_REVPSUM4 	NO_OS_BIT(10)
#define ADE9430_STATUS0_REVPSUM3 	NO_OS_BIT(9)
#define ADE9430_STATUS0_REVPSUM2 	NO_OS_BIT(8)
#define ADE9430_STATUS0_REVPSUM1 	NO_OS_BIT(7)
#define ADE9430_STATUS0_REVRPC 		NO_OS_BIT(6)
#define ADE9430_STATUS0_REVRPB 		NO_OS_BIT(5)
#define ADE9430_STATUS0_REVRPA 		NO_OS_BIT(4)
#define ADE9430_STATUS0_REVAPC 		NO_OS_BIT(3)
#define ADE9430_STATUS0_REVAPB 		NO_OS_BIT(2)
#define ADE9430_STATUS0_REVAPA 		NO_OS_BIT(1)
#define ADE9430_STATUS0_EGYRDY		NO_OS_BIT(0)

/* ADE9430_REG_STATUS1 Bit Definition */
#define ADE9430_STATUS1_ERROR3		NO_OS_BIT(31)
#define ADE9430_STATUS1_RROR2		NO_OS_BIT(30)
#define ADE9430_STATUS1_ERROR1		NO_OS_BIT(29)
#define ADE9430_STATUS1_ERROR0		NO_OS_BIT(28)
#define ADE9430_STATUS1_CRC_DONE	NO_OS_BIT(27)
#define ADE9430_STATUS1_CRC_CHG		NO_OS_BIT(26)
#define ADE9430_STATUS1_SEQERR		NO_OS_BIT(18)
#define ADE9430_STATUS1_OI		NO_OS_BIT(17)
#define ADE9430_STATUS1_RSTDONE		NO_OS_BIT(16)
#define ADE9430_STATUS1_ZXIC		NO_OS_BIT(15)
#define ADE9430_STATUS1_ZXIB		NO_OS_BIT(14)
#define ADE9430_STATUS1_ZXIA		NO_OS_BIT(13)
#define ADE9430_STATUS1_ZXCOMB		NO_OS_BIT(12)
#define ADE9430_STATUS1_ZXVC		NO_OS_BIT(11)
#define ADE9430_STATUS1_ZXVB		NO_OS_BIT(10)
#define ADE9430_STATUS1_ZXVA		NO_OS_BIT(9)
#define ADE9430_STATUS1_ZXTOVC		NO_OS_BIT(8)
#define ADE9430_STATUS1_ZXTOVB		NO_OS_BIT(7)
#define ADE9430_STATUS1_ZXTOVA		NO_OS_BIT(6)
#define ADE9430_STATUS1_VAFNOLOAD	NO_OS_BIT(5)
#define ADE9430_STATUS1_RFNOLOAD	NO_OS_BIT(4)
#define ADE9430_STATUS1_AFNOLOAD	NO_OS_BIT(3)
#define ADE9430_STATUS1_VANLOAD		NO_OS_BIT(2)
#define ADE9430_STATUS1_RNLOAD		NO_OS_BIT(1)
#define ADE9430_STATUS1_ANLOAD		NO_OS_BIT(0)

/* ADE9430_REG_EVENT_STATUS Bit Definition */
#define ADE9430_EVENT_DREADY		NO_OS_BIT(16)
#define ADE9430_EVENT_VAFNOLOAD		NO_OS_BIT(15)
#define ADE9430_EVENT_RFNOLOAD 		NO_OS_BIT(14)
#define ADE9430_EVENT_AFNOLOAD		NO_OS_BIT(13)
#define ADE9430_EVENT_VANLOAD		NO_OS_BIT(12)
#define ADE9430_EVENT_RNLOAD		NO_OS_BIT(11)
#define ADE9430_EVENT_ANLOAD		NO_OS_BIT(10)
#define ADE9430_EVENT_REVPSUM4		NO_OS_BIT(9)
#define ADE9430_EVENT_REVPSUM3		NO_OS_BIT(8)
#define ADE9430_EVENT_REVPSUM2		NO_OS_BIT(7)
#define ADE9430_EVENT_REVPSUM1		NO_OS_BIT(6)

/* ADE9430_REG_MASK0 Bit Definition */
#define ADE9430_MASK0_TEMP_RDY		NO_OS_BIT(25)
#define ADE9430_MASK0_ISMTCH		NO_OS_BIT(24)
#define ADE9430_MASK0_COH_PAGE_RDY 	NO_OS_BIT(23)
#define ADE9430_MASK0_WFB_TRIG		NO_OS_BIT(22)
#define ADE9430_MASK0_PF_RDY		NO_OS_BIT(21)
#define ADE9430_MASK0_RMS1012RDY	NO_OS_BIT(20)
#define ADE9430_MASK0_RMSONERDY		NO_OS_BIT(19)
#define ADE9430_MASK0_PWRRDY		NO_OS_BIT(18)
#define ADE9430_MASK0_PAGE_FULL		NO_OS_BIT(17)
#define ADE9430_MASK0_WFB_TRIG_IRQ	NO_OS_BIT(16)
#define ADE9430_MASK0_DREADY		NO_OS_BIT(15)
#define ADE9430_MASK0_CF4		NO_OS_BIT(14)
#define ADE9430_MASK0_CF3		NO_OS_BIT(13)
#define ADE9430_MASK0_CF2	 	NO_OS_BIT(12)
#define ADE9430_MASK0_CF1		NO_OS_BIT(11)
#define ADE9430_MASK0_REVPSUM4		NO_OS_BIT(10)
#define ADE9430_MASK0_REVPSUM3		NO_OS_BIT(9)
#define ADE9430_MASK0_REVPSUM2		NO_OS_BIT(8)
#define ADE9430_MASK0_REVPSUM1		NO_OS_BIT(7)
#define ADE9430_MASK0_REVRPC		NO_OS_BIT(6)
#define ADE9430_MASK0_REVRPB		NO_OS_BIT(5)
#define ADE9430_MASK0_REVRPA		NO_OS_BIT(4)
#define ADE9430_MASK0_REVAPC		NO_OS_BIT(3)
#define ADE9430_MASK0_REVAPB		NO_OS_BIT(2)
#define ADE9430_MASK0_REVAPA		NO_OS_BIT(1)
#define ADE9430_MASK0_EGYRDY		NO_OS_BIT(0)

/* ADE9430_REG_MASK1 Bit Definition */
#define ADE9430_MASK1_ERROR3		NO_OS_BIT(31)
#define ADE9430_MASK1_ERROR2		NO_OS_BIT(30)
#define ADE9430_MASK1_ERROR1		NO_OS_BIT(29)
#define ADE9430_MASK1_ERROR0		NO_OS_BIT(28)
#define ADE9430_MASK1_CRC_DONE		NO_OS_BIT(27)
#define ADE9430_MASK1_CRC_CHG		NO_OS_BIT(26)
#define ADE9430_MASK1_SEQERR		NO_OS_BIT(18)
#define ADE9430_MASK1_OI		NO_OS_BIT(17)
#define ADE9430_MASK1_ZXIC		NO_OS_BIT(15)
#define ADE9430_MASK1_ZXIB		NO_OS_BIT(14)
#define ADE9430_MASK1_ZXIA		NO_OS_BIT(13)
#define ADE9430_MASK1_ZXCOMB		NO_OS_BIT(12)
#define ADE9430_MASK1_ZXVC		NO_OS_BIT(11)
#define ADE9430_MASK1_ZXVB 		NO_OS_BIT(10)
#define ADE9430_MASK1_ZXVA		NO_OS_BIT(9)
#define ADE9430_MASK1_ZXTOVC		NO_OS_BIT(8)
#define ADE9430_MASK1_ZXTOVB		NO_OS_BIT(7)
#define ADE9430_MASK1_ZXTOVA		NO_OS_BIT(6)
#define ADE9430_MASK1_VAFNOLOAD		NO_OS_BIT(5)
#define ADE9430_MASK1_RFNOLOAD		NO_OS_BIT(4)
#define ADE9430_MASK1_AFNOLOAD		NO_OS_BIT(3)
#define ADE9430_MASK1_VANLOAD		NO_OS_BIT(2)
#define ADE9430_MASK1_RNLOAD		NO_OS_BIT(1)
#define ADE9430_MASK1_ANLOAD		NO_OS_BIT(0)

/* ADE9430_REG_EVENT_MASK Bit Definition */
#define ADE9430_EVENT_READY_MSK		NO_OS_BIT(16)
#define ADE9430_EVENT_VAFNOLOAD_MSK	NO_OS_BIT(15)
#define ADE9430_EVENT_RFNOLOAD_MSK	NO_OS_BIT(14)
#define ADE9430_EVENT_AFNOLOAD_MSK	NO_OS_BIT(13)
#define ADE9430_EVENT_VANLOAD_MSK	NO_OS_BIT(12)
#define ADE9430_EVENT_RNLOAD_MSK	NO_OS_BIT(11)
#define ADE9430_EVENT_ANLOAD_MSK	NO_OS_BIT(10)
#define ADE9430_EVENT_REVPSUM4_MSK	NO_OS_BIT(9)
#define ADE9430_EVENT_REVPSUM3_MSK	NO_OS_BIT(8)
#define ADE9430_EVENT_REVPSUM2_MSK	NO_OS_BIT(7)
#define ADE9430_EVENT_REVPSUM1_MSK	NO_OS_BIT(6)

/* ADE9430_REG_OILVL Bit Definition */
#define ADE9430_OILVL_VAL		NO_OS_GENMASK(23, 0)

/* ADE9430_REG_OIA Bit Definition */
#define ADE9430_OI_VAL			NO_OS_GENMASK(23, 0)

/* ADE9430_REG_OIB Bit Definition */
#define ADE9430_OIB_VAL			NO_OS_GENMASK(23, 0)

/* ADE9430_REG_OIC Bit Definition */
#define ADE9430_OIC_VAL			NO_OS_GENMASK(23, 0)

/* ADE9430_REG_OIN Bit Definition */
#define ADE9430_OIN_VAL			NO_OS_GENMASK(23, 0)

/* ADE9430_REG_VLEVEL Bit Definition */
#define ADE9430_VLEVEL_VAL 		NO_OS_GENMASK(23, 0)

/* ADE9430_REG_PHNOLOAD Bit Definition */
#define ADE9430_CFVANL			NO_OS_BIT(17)
#define ADE9430_CFVARNL			NO_OS_BIT(16)
#define ADE9430_CFWATTNL		NO_OS_BIT(15)
#define ADE9430_CVANL			NO_OS_BIT(14)
#define ADE9430_CVARNL			NO_OS_BIT(13)
#define ADE9430_CWATTNL			NO_OS_BIT(12)
#define ADE9430_BFVANL 			NO_OS_BIT(11)
#define ADE9430_BFVARNL			NO_OS_BIT(10)
#define ADE9430_BFWATTNL		NO_OS_BIT(9)
#define ADE9430_BVANL			NO_OS_BIT(8)
#define ADE9430_BVARNL			NO_OS_BIT(7)
#define ADE9430_BWATTNL			NO_OS_BIT(6)
#define ADE9430_AFVANL			NO_OS_BIT(5)
#define ADE9430_AFVARNL			NO_OS_BIT(4)
#define ADE9430_AFWATTNL 		NO_OS_BIT(3)
#define ADE9430_AVANL			NO_OS_BIT(2)
#define ADE9430_AVARNL			NO_OS_BIT(1)
#define ADE9430_AWATTNL			NO_OS_BIT(0)

/* ADE9430_REG_ADC_REDIRECT Bit Definition */
#define ADE9430_VC_DIN	 		NO_OS_GENMASK(20, 18)
#define ADE9430_VB_DIN	 		NO_OS_GENMASK(17, 15)
#define ADE9430_VA_DIN	 		NO_OS_GENMASK(14, 12)
#define ADE9430_IN_DIN	 		NO_OS_GENMASK(11, 9)
#define ADE9430_IC_DIN	 		NO_OS_GENMASK(8, 6)
#define ADE9430_IB_DIN	 		NO_OS_GENMASK(5, 3)
#define ADE9430_IA_DIN	 		NO_OS_GENMASK(2, 0)

/* ADE9430_REG_CF_LCFG Bit Definition */
#define ADE9430_CF4_LT			NO_OS_BIT(22)
#define ADE9430_CF3_LT			NO_OS_BIT(21)
#define ADE9430_CF2_LT			NO_OS_BIT(20)
#define ADE9430_CF1_LT			NO_OS_BIT(19)
#define ADE9430_CF_LTMR			NO_OS_GENMASK(18, 0)

/* ADE9430_REG_PART_ID Bit Definition */
#define ADE9430_ADE9430_ID		NO_OS_BIT(20)

/* ADE9430_REG_TEMP_TRIM Bit Definition */
#define ADE9430_TEMP_OFFSET 		NO_OS_GENMASK(31, 16)
#define ADE9430_TEMP_GAIN 		NO_OS_GENMASK(15, 0)

/* ADE9430_REG_CONFIG1 Bit Definition */
#define ADE9430_EXT_REF			NO_OS_BIT(15)
#define ADE9430_IRQ0_ON_IRQ1		NO_OS_BIT(12)
#define ADE9430_BURST_EN		NO_OS_BIT(11)
#define ADE9430_PWR_SETTLE		NO_OS_GENMASK(9, 8)
#define ADE9430_CF_ACC_CLR		NO_OS_BIT(5)
#define ADE9430_CF4_CFG			NO_OS_GENMASK(3, 2)
#define ADE9430_CF3_CFG			NO_OS_BIT(1)
#define ADE9430_SWRST			NO_OS_BIT(0)

/* ADE9430_REG_OISTATUS Bit Definition */
#define ADE9430_OIPHASE			NO_OS_GENMASK(3, 0)

/* ADE9430_REG_CFMODE Bit Definition */
#define ADE9430_CF4DIS			NO_OS_BIT(15)
#define ADE9430_CF3DIS			NO_OS_BIT(14)
#define ADE9430_CF2DIS			NO_OS_BIT(13)
#define ADE9430_CF1DIS			NO_OS_BIT(12)
#define ADE9430_CF4SEL			NO_OS_GENMASK(11, 9)
#define ADE9430_CF3SEL			NO_OS_GENMASK(8, 6)
#define ADE9430_CF2SEL			NO_OS_GENMASK(5, 3)
#define ADE9430_CF1SEL 			NO_OS_GENMASK(2, 0)

/* ADE9430_REG_COMPMODE Bit Definition */
#define ADE9430_TERMSEL4		NO_OS_GENMASK(11, 9)
#define ADE9430_TERMSEL3		NO_OS_GENMASK(8, 6)
#define ADE9430_TERMSEL2		NO_OS_GENMASK(5, 3)
#define ADE9430_TERMSEL1 		NO_OS_GENMASK(2, 0)

/* ADE9430_REG_ACCMODE Bit Definition */
#define ADE9430_SELFREQ			NO_OS_BIT(8)
#define ADE9430_ICONSEL			NO_OS_BIT(7)
#define ADE9430_VCONSEL			NO_OS_GENMASK(6, 4)
#define ADE9430_VARACC	 		NO_OS_GENMASK(3, 2)
#define ADE9430_WATTACC			NO_OS_GENMASK(3, 2)

/* ADE9430_REG_CONFIG3 Bit Definition */
#define ADE9430_OC_EN			NO_OS_GENMASK(15, 12)
#define ADE9430_PEAKSEL	 		NO_OS_GENMASK(4, 2)

/* ADE9430_REG_ZX_LP_SEL Bit Definition */
#define ADE9430_LP_SEL			NO_OS_GENMASK(4, 3)
#define ADE9430_ZX_SEL	 		NO_OS_GENMASK(2, 1)

/* ADE9430_REG_PHSIGN Bit Definition */
#define ADE9430_SUM4SIGN		NO_OS_BIT(9)
#define ADE9430_SUM3SIGN		NO_OS_BIT(8)
#define ADE9430_SUM2SIGN		NO_OS_BIT(7)
#define ADE9430_SUM1SIGN		NO_OS_BIT(6)
#define ADE9430_CVARSIGN		NO_OS_BIT(5)
#define ADE9430_CWSIGN			NO_OS_BIT(4)
#define ADE9430_BVARSIGN 		NO_OS_BIT(3)
#define ADE9430_BWSIGN			NO_OS_BIT(2)
#define ADE9430_AVARSIGN		NO_OS_BIT(1)
#define ADE9430_AWSIGN			NO_OS_BIT(0)

/* ADE9430_REG_WFB_CFG Bit Definition */
#define ADE9430_WF_IN_EN		NO_OS_BIT(12)
#define ADE9430_WF_SRC			NO_OS_GENMASK(9, 8)
#define ADE9430_WF_MODE			NO_OS_BIT(7, 6)
#define ADE9430_WF_CAP_SEL		NO_OS_BIT(5)
#define ADE9430_WF_CAP_EN		NO_OS_BIT(4)
#define ADE9430_BURST_CHAN		NO_OS_GENMASK(3, 0)

/* ADE9430_WFB_TRG_CFG Bit Definition */
#define ADE9430_TRIG_FORCE		NO_OS_BIT(10)
#define ADE9430_ZXCOMB			NO_OS_BIT(9)
#define ADE9430_ZXVC			NO_OS_BIT(8)
#define ADE9430_ZXVB 			NO_OS_BIT(7)
#define ADE9430_ZXVA			NO_OS_BIT(6)
#define ADE9430_ZXIC			NO_OS_BIT(5)
#define ADE9430_ZXIB			NO_OS_BIT(4)
#define ADE9430_ZXIA			NO_OS_BIT(3)
#define ADE9430_OI			NO_OS_BIT(2)

/* ADE9430_WFB_TRG_STAT Bit Definition */
#define ADE9430_WFB_LAST_PAGE		NO_OS_GENMASK(15, 12)
#define ADE9430_WFB_TRIG_ADDR		NO_OS_GENMASK(10, 0)

/* ADE9430_CONFIG2 Bit Definition */
#define ADE9430_UPERIOD_SEL		NO_OS_BIT(12)
#define ADE9430_HPF_CRN			NO_OS_GENMASK(12, 9)

/* ADE9430_EP_CFG Bit Definition */
#define ADE9430_NOLOAD_TMR		NO_OS_GENMASK(15, 13)
#define ADE9430_PWR_SIGN_SEL_1		NO_OS_BIT(7)
#define ADE9430_PWR_SIGN_SEL_0		NO_OS_BIT(6)
#define ADE9430_RD_RST_EN		NO_OS_BIT(5)
#define ADE9430_EGY_LD_ACCUM		NO_OS_BIT(4)
#define ADE9430_EGY_TMR_MODE		NO_OS_BIT(1)
#define ADE9430_EGY_PWR_EN		NO_OS_BIT(0)

/* ADE9430_CRC_FORCE Bit Definition */
#define ADE9430_FORCE_CRC_UPDATE	NO_OS_BIT(0)

/* ADE9430_CRC_OPTEN Bit Definition */
#define ADE9430_CRC_WFB_TRG_CFG_EN	NO_OS_BIT(15)
#define ADE9430_CRC_WFB_PG_IRQEN	NO_OS_BIT(15)
#define ADE9430_CRC_WFB_CFG_EN		NO_OS_BIT(15)
#define ADE9430_CRC_SEQ_CYC_EN		NO_OS_BIT(15)
#define ADE9430_CRC_ZXLPSEL_EN		NO_OS_BIT(15)
#define ADE9430_CRC_ZXTOUT_EN		NO_OS_BIT(15)
#define ADE9430_CRC_APP_NL_LVL_EN	NO_OS_BIT(15)
#define ADE9430_CRC_REACT_NL_LVL_EN	NO_OS_BIT(15)
#define ADE9430_CRC_ACT_NL_LVL_EN	NO_OS_BIT(15)
#define ADE9430_CRC_EVENT_MASK_EN	NO_OS_BIT(15)
#define ADE9430_CRC_MASK1_EN		NO_OS_BIT(15)
#define ADE9430_CRC_MASK0_EN		NO_OS_BIT(15)

/* ADE9430_TEMP_CFG Bit Definition */
#define ADE9430_TEMP_START		NO_OS_BIT(3)
#define ADE9430_TEMP_EN			NO_OS_BIT(2)
#define ADE9430_TEMP_TIME		NO_OS_GENMASK(1, 0)

/* ADE9430_TEMP_RSLT Bit Definition */
#define ADE9430_TEMP_RESULT		NO_OS_GENMASK(11, 0)

/* ADE9430_PGA_GAIN Bit Definition */
#define ADE9430_VC_GAIN			NO_OS_GENMASK(13, 12)
#define ADE9430_VB_GAIN			NO_OS_GENMASK(11, 10)
#define ADE9430_VA_GAIN			NO_OS_GENMASK(9, 8)
#define ADE9430_IN_GAIN			NO_OS_GENMASK(7, 6)
#define ADE9430_IC_GAIN			NO_OS_GENMASK(5, 4)
#define ADE9430_IB_GAIN			NO_OS_GENMASK(3, 2)
#define ADE9430_IA_GAIN			NO_OS_GENMASK(1, 0)

/* ADE9430_CHNL_DIS Bit Definition */
#define ADE9430_VC_DISADC		NO_OS_BIT(6)
#define ADE9430_VB_DISADC		NO_OS_BIT(5)
#define ADE9430_VA_DISADC		NO_OS_BIT(4)
#define ADE9430_IN_DISADC		NO_OS_BIT(3)
#define ADE9430_IC_DISADC		NO_OS_BIT(2)
#define ADE9430_IB_DISADC		NO_OS_BIT(1)
#define ADE9430_IA_DISADC		NO_OS_BIT(0)

/* ADE9430_VAR_DIS Bit Definition */
#define ADE9430_VARDIS			NO_OS_BIT(0)

/* Miscellaneous Definitions */
#define ADE9430_CHIP_ID			0x63
#define ADE9430_I_RES_NA		4018ULL
#define ADE9430_V_RES_NV		13357ULL
#define ADE9430_W_RES_UW		7203ULL

/******************************************************************************/
/*************************** Types Declarations *******************************/
/******************************************************************************/

/**
 * @enum ade9430_phase
 * @brief ADE9430 available phases.
 */
enum ade9430_phase {
	ADE9430_PHASE_A,
	ADE9430_PHASE_B,
	ADE9430_PHASE_C
};

/**
 * @enum ade9430_egy_model
 * @brief ADE9430 available user energy use models.
 */
enum ade9430_egy_model {
	ADE9430_EGY_WITH_RESET,
	ADE9430_EGY_HALF_LINE_CYCLES,
	ADE9430_EGY_NR_SAMPLES
};

/**
 * @struct ade9430_init_param
 * @brief ADE9430 Device initialization parameters.
 */
struct ade9430_init_param {
	/** Device communication descriptor */
	struct no_os_spi_init_param 	*spi_init;
	/** Enable the temperature */
	bool				temp_en;
};

/**
 * @struct ade9430_dev
 * @brief ADE9430 Device structure.
 */
struct ade9430_dev {
	/** Device communication descriptor */
	struct no_os_spi_desc		*spi_desc;
	/** Variable storing the WATT value */
	uint32_t			watt_val;
	/** Variable storing the IRMS value */
	uint32_t			irms_val;
	/** Variable storing the VRMS value */
	uint32_t			vrms_val;
	/** Variable storing the temperature value in degrees */
	int32_t				temp_deg;
};

/******************************************************************************/
/************************ Functions Declarations ******************************/
/******************************************************************************/

/* Read device register. */
int ade9430_read(struct ade9430_dev *dev, uint16_t reg_addr,
		 uint32_t *reg_data);

/* Write device register. */
int ade9430_write(struct ade9430_dev *dev, uint16_t reg_addr,
		  uint32_t reg_data);

/* Update specific register bits. */
int ade9430_update_bits(struct ade9430_dev *dev, uint16_t reg_addr,
			uint32_t mask, uint32_t reg_data);

/* Read temperature */
int ade9430_read_temp(struct ade9430_dev *dev);

/* Read Energy/Power for specific phase */
int ade9430_read_data_ph(struct ade9430_dev *dev, enum ade9430_phase phase);

/* Set User Energy use model */
int ade9430_set_egy_model(struct ade9430_dev *dev, enum ade9430_egy_model model,
			  uint16_t value);

/* Initialize the device. */
int ade9430_init(struct ade9430_dev **device,
		 struct ade9430_init_param init_param);

/* Remove the device and release resources. */
int ade9430_remove(struct ade9430_dev *dev);

#endif // __ADE9430_H__
