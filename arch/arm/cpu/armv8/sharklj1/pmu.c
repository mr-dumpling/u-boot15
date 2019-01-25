/******************************************************************************
 ** File Name:      pmu.c                                             *
 ** Author:         Zhongfa.Wang                                              *
 ** DATE:           26/12/2016                                                *
 ** Copyright:      2014 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the basic information on chip.          *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               *
 ** 26/12/2016     Zhongfa.Wang		Create.                                   *
 ******************************************************************************/

/**---------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **---------------------------------------------------------------------------*/
#include <asm/io.h>
#include "adi_hal_internal.h"
//#include "asm/arch/wdg_drvapi.h"
#include "asm/arch/sprd_reg.h"
#include "asm/arch-sharklj1/common.h"
/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
extern   "C"
{
#endif

#ifndef CONFIG_FPGA
void pmu_commom_config(void)
{
	uint32_t reg_val;

	CHIP_REG_SET(REG_PMU_APB_CGM_PMU_SEL,
		BIT_PMU_APB_AON_APB_PROTECT_RC_SEL(0x01) | //set 1 in 32k case
		BIT_PMU_APB_AON_APB_PROTECT_EN |  // set 1
		BIT_PMU_APB_CGM_PMU_26M_EN |   //default cfg
		BIT_PMU_APB_CGM_PMU_26M_SEL |  //default cfg
		BIT_PMU_APB_CGM_PMU_SEL(0x0) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PWR_CNT_WAIT_CFG1,
		BIT_PMU_APB_EFUSE_PWON_WAIT_CNT(0x0A) |	// default cfg
		BIT_PMU_APB_SLP_CTRL_CLK_DIV_CFG(0x7C) |  //only for pmu_clk 4M , 32k ignores it.
		BIT_PMU_APB_ARM7_PWR_WAIT_CNT(0x0) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PWR_ST_DEBUG_DLY0,
		BIT_PMU_APB_CGM_OFF_DLY(0x0) |
		BIT_PMU_APB_CGM_ON_DLY(0x0) |
		BIT_PMU_APB_ISO_OFF_DLY(0x0) |
		BIT_PMU_APB_RST_DEASSERT_DLY(0x0) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PWR_ST_DEBUG_DLY1,
		BIT_PMU_APB_SHUTDOWN_M_D_DLY(0x0) |
		BIT_PMU_APB_PWR_ST_CLK_DIV_CFG(0x07) | //only for pmu_clk 4M , 32k ignores it.
		BIT_PMU_APB_RST_ASSERT_DLY(0x0) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PWR_ST_DEBUG_DLY3,
		BIT_PMU_APB_CORE_CGM_OFF_DLY(0x0) |
		BIT_PMU_APB_MP2_CGM_OFF_DLY(0x01) |
		BIT_PMU_APB_DCDC_PWR_OFF_DLY(0x0) |
		BIT_PMU_APB_DCDC_PWR_ON_DLY(0x08) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_BISR_WAIT_SRAM_CFG,
		BIT_PMU_APB_SAVE_RESTORE_DLY(0x0) |
		//BIT_PMU_APB_BISR_WAIT_SRAM_CA53_LIT_MP2_EN |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA53_TOP_CFG,
		//BIT_PMU_APB_PD_CA53_TOP_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_TOP_PD_SEL |		//all default cfg, set 0.
		//BIT_PMU_APB_PD_CA53_TOP_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_CA53_TOP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA53_TOP_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_CA53_TOP_PWR_ON_SEQ_DLY(0x0) |
		BIT_PMU_APB_PD_CA53_TOP_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA53_LIT_C0_CFG,
		//BIT_PMU_APB_PD_CA53_LIT_C0_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_LIT_C0_PD_SEL |
		BIT_PMU_APB_CA53_LIT_C0_WAKEUP_EN |		//Main core enable, the other diable, same as default.
		//BIT_PMU_APB_PD_CA53_LIT_C0_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_CA53_LIT_C0_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA53_LIT_C0_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_CA53_LIT_C0_PWR_ON_SEQ_DLY(0x0c) |
		BIT_PMU_APB_PD_CA53_LIT_C0_ISO_ON_DLY(0x0) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA53_LIT_C1_CFG,
		//BIT_PMU_APB_PD_CA53_LIT_C1_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_LIT_C1_PD_SEL |
		//BIT_PMU_APB_CA53_LIT_C1_WAKEUP_EN |
		BIT_PMU_APB_PD_CA53_LIT_C1_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_CA53_LIT_C1_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA53_LIT_C1_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_CA53_LIT_C1_PWR_ON_SEQ_DLY(0x0B) |
		BIT_PMU_APB_PD_CA53_LIT_C1_ISO_ON_DLY(0x01) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA53_LIT_MP2_CFG,
		//BIT_PMU_APB_PD_CA53_LIT_MP2_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_LIT_MP2_PD_SEL |
		//BIT_PMU_APB_PD_CA53_LIT_MP2_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_CA53_LIT_MP2_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA53_LIT_MP2_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_CA53_LIT_MP2_PWR_ON_SEQ_DLY(0x0A) |
		BIT_PMU_APB_PD_CA53_LIT_MP2_ISO_ON_DLY(0x03) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA53_BIG_C0_CFG,
		//BIT_PMU_APB_CA53_BIG_C0_T1_WAKEUP_EN |
		BIT_PMU_APB_PD_CA53_BIG_C0_T1_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_CA53_BIG_C0_T1_AUTO_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_BIG_C0_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_BIG_C0_PD_SEL |
		//BIT_PMU_APB_CA53_BIG_C0_WAKEUP_EN |
		BIT_PMU_APB_PD_CA53_BIG_C0_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_CA53_BIG_C0_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA53_BIG_C0_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_CA53_BIG_C0_PWR_ON_SEQ_DLY(0x0D) |
		BIT_PMU_APB_PD_CA53_BIG_C0_ISO_ON_DLY(0x0) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA53_BIG_C1_CFG,
		//BIT_PMU_APB_CA53_BIG_C1_T1_WAKEUP_EN |
		BIT_PMU_APB_PD_CA53_BIG_C1_T1_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_CA53_BIG_C1_T1_AUTO_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_BIG_C1_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_BIG_C1_PD_SEL |
		//BIT_PMU_APB_CA53_BIG_C1_WAKEUP_EN |
		BIT_PMU_APB_PD_CA53_BIG_C1_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_CA53_BIG_C1_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA53_BIG_C1_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_CA53_BIG_C1_PWR_ON_SEQ_DLY(0x0C) |
		BIT_PMU_APB_PD_CA53_BIG_C1_ISO_ON_DLY(0x01) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA53_BIG_MP2_CFG,
		//BIT_PMU_APB_PD_CA53_BIG_MP2_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_BIG_MP2_PD_SEL |
		BIT_PMU_APB_PD_CA53_BIG_MP2_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_CA53_BIG_MP2_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA53_BIG_MP2_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_CA53_BIG_MP2_PWR_ON_SEQ_DLY(0x0A) |
		BIT_PMU_APB_PD_CA53_BIG_MP2_ISO_ON_DLY(0x03) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_AP_SYS_CFG,
		//BIT_PMU_APB_PD_AP_SYS_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_AP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_AP_SYS_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_AP_SYS_PWR_ON_SEQ_DLY(0x0) |
		BIT_PMU_APB_PD_AP_SYS_ISO_ON_DLY(0x01) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_MM_TOP_CFG,
		//BIT_PMU_APB_PD_MM_TOP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_MM_TOP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_MM_TOP_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_MM_TOP_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_MM_TOP_ISO_ON_DLY(0x0) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_GPU_TOP_CFG,
		//BIT_PMU_APB_PD_GPU_TOP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_GPU_TOP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_GPU_TOP_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_GPU_TOP_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_GPU_TOP_ISO_ON_DLY(0x0) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_TD_CFG,
		BIT_PMU_APB_PD_WTLCP_TD_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_TD_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_TD_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_WTLCP_TD_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_TD_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LTE_P1_CFG,
		BIT_PMU_APB_PD_WTLCP_LTE_P1_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_LTE_P1_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LTE_P1_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_WTLCP_LTE_P1_PWR_ON_SEQ_DLY(0x02) |
		BIT_PMU_APB_PD_WTLCP_LTE_P1_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LTE_P2_CFG,
		BIT_PMU_APB_PD_WTLCP_LTE_P2_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_LTE_P2_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LTE_P2_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_WTLCP_LTE_P2_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_LTE_P2_ISO_ON_DLY(0x03) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LDSP_CFG,
		//BIT_PMU_APB_PD_WTLCP_LDSP_PD_SEL |	//default cfg:0
		BIT_PMU_APB_PD_WTLCP_LDSP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_LDSP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LDSP_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_WTLCP_LDSP_PWR_ON_SEQ_DLY(0x03) |
		BIT_PMU_APB_PD_WTLCP_LDSP_ISO_ON_DLY(0x01) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_TGDSP_CFG,
		BIT_PMU_APB_PD_WTLCP_TGDSP_PD_SEL |		//default cfg:0
		BIT_PMU_APB_PD_WTLCP_TGDSP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_TGDSP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_SEQ_DLY(0x04) |
		BIT_PMU_APB_PD_WTLCP_TGDSP_ISO_ON_DLY(0x0) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_HU3GE_A_CFG,
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_HU3GE_A_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_SEQ_DLY(0x02) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_HU3GE_B_CFG,
		BIT_PMU_APB_PD_WTLCP_HU3GE_B_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_HU3GE_B_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_HU3GE_B_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_B_PWR_ON_SEQ_DLY(0x02) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_B_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_SYS_CFG,
		BIT_PMU_APB_PD_WTLCP_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_SYS_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_WTLCP_SYS_PWR_ON_SEQ_DLY(0x0) |
		BIT_PMU_APB_PD_WTLCP_SYS_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_PUBCP_SYS_CFG,
		//BIT_PMU_APB_PD_PUBCP_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_PUBCP_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_PUBCP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_PUBCP_SYS_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_PUBCP_SYS_PWR_ON_SEQ_DLY(0x0) |
		BIT_PMU_APB_PD_PUBCP_SYS_ISO_ON_DLY(0x0) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LTE_P3_CFG,
		BIT_PMU_APB_PD_WTLCP_LTE_P3_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_LTE_P3_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LTE_P3_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_WTLCP_LTE_P3_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_LTE_P3_ISO_ON_DLY(0x03) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LTE_P4_CFG,
		BIT_PMU_APB_PD_WTLCP_LTE_P4_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_LTE_P4_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LTE_P4_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_WTLCP_LTE_P4_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_LTE_P4_ISO_ON_DLY(0x03) |
		0
	);

	reg_val = CHIP_REG_GET(REG_PMU_APB_PD_PUB_SYS_CFG) & 0xff000000;
	CHIP_REG_SET(REG_PMU_APB_PD_PUB_SYS_CFG,
		//BIT_PMU_APB_PD_PUB_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_PUB_SYS_AUTO_SHUTDOWN_EN |
		//reg_val |
		BIT_PMU_APB_PD_PUB_SYS_PWR_ON_DLY(0x0) |
		BIT_PMU_APB_PD_PUB_SYS_PWR_ON_SEQ_DLY(0x0) |
		BIT_PMU_APB_PD_PUB_SYS_ISO_ON_DLY(0x01) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_XTL_WAIT_CNT,
		BIT_PMU_APB_XTL1_WAIT_CNT(0x40) |
		BIT_PMU_APB_XTL0_WAIT_CNT(0x40) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_XTLBUF_WAIT_CNT,
		BIT_PMU_APB_XTLBUF1_WAIT_CNT(0x07) |
		BIT_PMU_APB_XTLBUF0_WAIT_CNT(0x07) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT1,
		BIT_PMU_APB_LTEPLL_WAIT_CNT(0x07) |
		BIT_PMU_APB_TWPLL_WAIT_CNT(0x07) |
		BIT_PMU_APB_DPLL_WAIT_CNT(0x07) |
		BIT_PMU_APB_MPLL_WAIT_CNT(0x07) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT2,
		BIT_PMU_APB_CPPLL_WAIT_CNT(0x07) |
		BIT_PMU_APB_RPLL_WAIT_CNT(0x07) |
		BIT_PMU_APB_GPLL_WAIT_CNT(0x07) |
		BIT_PMU_APB_LVDSDIS_PLL_WAIT_CNT(0x07) |
		0
	);
	reg_val = CHIP_REG_GET(REG_PMU_APB_RC_CNT_WAIT_CFG) & 0xffffff00;
	CHIP_REG_SET(REG_PMU_APB_RC_CNT_WAIT_CFG,
		//BIT_PMU_APB_RC1_WAIT_CNT(x) | // not used, default cfg
		reg_val |
		BIT_PMU_APB_RC0_WAIT_CNT(0x03) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT3,
		BIT_PMU_APB_BMPLL_WAIT_CNT(0x07) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PWR_CNT_WAIT_CFG0,
		BIT_PMU_APB_PUBCP_PWR_WAIT_CNT(0x0) |
		BIT_PMU_APB_WTLCP_PWR_WAIT_CNT(0x0) |
		BIT_PMU_APB_AP_PWR_WAIT_CNT(0x0) |
		0
	);
}

/*sharklj1 deepsleep: 0.7V; normal: 0.9V*/
static void dcdc_core_ds_config(uint32_t core_cal_para, uint32_t core_ctrl_para)
{
	ANA_REG_SET(ANA_REG_GLB_DCDC_CORE_SLP_CTRL1,
		BITS_DCDC_CORE_CAL_DS_SW(core_cal_para)|
		BITS_DCDC_CORE_CTRL_DS_SW(core_ctrl_para)
	);
}

void CSP_Init(uint32_t gen_para)
{
	//uint32_t reg_val;
	pmu_commom_config();
	dcdc_core_ds_config(0x0,0x3);
}
#endif

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

