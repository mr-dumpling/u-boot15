/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "sprd_panel.h"
#include "sprd_dsi.h"
#include "dsi/mipi_dsi_api.h"
#include "sprd_dphy.h"
#include <i2c.h>

static uint8_t init_data[] = {
	//CMD2_P0
	0x23, 0x00, 0x00, 0x02, 0xFF, 0x20,
	0x23, 0x00, 0x00, 0x02, 0x00, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x01, 0x55,
	0x23, 0x00, 0x00, 0x02, 0x02, 0x45,
	0x23, 0x00, 0x00, 0x02, 0x03, 0x55,
	0x23, 0x00, 0x00, 0x02, 0x05, 0x50,
	0x23, 0x00, 0x00, 0x02, 0x06, 0x4A,
	0x23, 0x00, 0x00, 0x02, 0x07, 0x24,
	0x23, 0x00, 0x00, 0x02, 0x08, 0x0C,
	0x23, 0x00, 0x00, 0x02, 0x0B, 0x87,
	0x23, 0x00, 0x00, 0x02, 0x0C, 0x87,
	0x23, 0x00, 0x00, 0x02, 0x0E, 0xB0,
	0x23, 0x00, 0x00, 0x02, 0x0F, 0xB3,
	0x23, 0x00, 0x00, 0x02, 0x11, 0x25,//0X10 VCOM
	0x23, 0x00, 0x00, 0x02, 0x12, 0x10,
	0x23, 0x00, 0x00, 0x02, 0x13, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x14, 0x4A,
	0x23, 0x00, 0x00, 0x02, 0x15, 0x12,
	0x23, 0x00, 0x00, 0x02, 0x16, 0x12,
	0x23, 0x00, 0x00, 0x02, 0x30, 0x01,

	0x23, 0x00, 0x00, 0x02, 0x58, 0x82,
	0x23, 0x00, 0x00, 0x02, 0x59, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x5A, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x5B, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x5C, 0x82,
	0x23, 0x00, 0x00, 0x02, 0x5D, 0x82,
	0x23, 0x00, 0x00, 0x02, 0x5E, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x5F, 0x02,

	0x23, 0x00, 0x00, 0x02, 0x72, 0x31,
	0x23, 0x00, 0x00, 0x02, 0xFB, 0x01,
	//CMD2_P4
	0x23, 0x00, 0x00, 0x02, 0xFF, 0x24,

	0x23, 0x00, 0x00, 0x02, 0x00, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x01, 0x0B,
	0x23, 0x00, 0x00, 0x02, 0x02, 0x0C,
	0x23, 0x00, 0x00, 0x02, 0x03, 0x09,
	0x23, 0x00, 0x00, 0x02, 0x04, 0x0A,
	0x23, 0x00, 0x00, 0x02, 0x05, 0x1C,
	0x23, 0x00, 0x00, 0x02, 0x06, 0x10,
	0x23, 0x00, 0x00, 0x02, 0x07, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x08, 0x1C,
	0x23, 0x00, 0x00, 0x02, 0x09, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x0A, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x0B, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x0C, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x0D, 0x13,
	0x23, 0x00, 0x00, 0x02, 0x0E, 0x15,
	0x23, 0x00, 0x00, 0x02, 0x0F, 0x17,
	0x23, 0x00, 0x00, 0x02, 0x10, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x11, 0x0B,
	0x23, 0x00, 0x00, 0x02, 0x12, 0x0C,
	0x23, 0x00, 0x00, 0x02, 0x13, 0x09,
	0x23, 0x00, 0x00, 0x02, 0x14, 0x0A,
	0x23, 0x00, 0x00, 0x02, 0x15, 0x1C,
	0x23, 0x00, 0x00, 0x02, 0x16, 0x10,
	0x23, 0x00, 0x00, 0x02, 0x17, 0x10,
	0x23, 0x00, 0x00, 0x02, 0x18, 0x1C,
	0x23, 0x00, 0x00, 0x02, 0x19, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x1A, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x1B, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x1C, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x1D, 0x13,
	0x23, 0x00, 0x00, 0x02, 0x1E, 0x15,
	0x23, 0x00, 0x00, 0x02, 0x1F, 0x17,


	0x23, 0x00, 0x00, 0x02, 0x20, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x21, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x22, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x23, 0x4A,
	0x23, 0x00, 0x00, 0x02, 0x24, 0x4A,
	0x23, 0x00, 0x00, 0x02, 0x25, 0x6D,
	0x23, 0x00, 0x00, 0x02, 0x26, 0x40,
	0x23, 0x00, 0x00, 0x02, 0x27, 0x40,

	0x23, 0x00, 0x00, 0x02, 0xBD, 0x20,
	0x23, 0x00, 0x00, 0x02, 0xB6, 0x22,
	0x23, 0x00, 0x00, 0x02, 0xB7, 0x24,
	0x23, 0x00, 0x00, 0x02, 0xB8, 0x07,
	0x23, 0x00, 0x00, 0x02, 0xB9, 0x07,
	0x23, 0x00, 0x00, 0x02, 0xC1, 0x6D,
	0x23, 0x00, 0x00, 0x02, 0xBE, 0x07,
	0x23, 0x00, 0x00, 0x02, 0xBF, 0x07,

	0x23, 0x00, 0x00, 0x02, 0x29, 0xD8,
	0x23, 0x00, 0x00, 0x02, 0x2A, 0x2A,

	0x23, 0x00, 0x00, 0x02, 0x4B, 0x04,
	0x23, 0x00, 0x00, 0x02, 0x4C, 0x12,
	0x23, 0x00, 0x00, 0x02, 0x4D, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x4E, 0x22,
	0x23, 0x00, 0x00, 0x02, 0x4F, 0x22,
	0x23, 0x00, 0x00, 0x02, 0x50, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x51, 0x61,
	0x23, 0x00, 0x00, 0x02, 0x52, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x53, 0x08,
	0x23, 0x00, 0x00, 0x02, 0x56, 0x08,
	0x23, 0x00, 0x00, 0x02, 0x54, 0x8A,
	0x23, 0x00, 0x00, 0x02, 0x58, 0x8A,
	0x23, 0x00, 0x00, 0x02, 0x55, 0x6D,

	0x23, 0x00, 0x00, 0x02, 0x5B, 0x43,
	0x23, 0x00, 0x00, 0x02, 0x5C, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x5F, 0x73,
	0x23, 0x00, 0x00, 0x02, 0x60, 0x73,
	0x23, 0x00, 0x00, 0x02, 0x63, 0x22,
	0x23, 0x00, 0x00, 0x02, 0x64, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x67, 0x08,
	0x23, 0x00, 0x00, 0x02, 0x68, 0x04,

	0x23, 0x00, 0x00, 0x02, 0x7A, 0x80,
	0x23, 0x00, 0x00, 0x02, 0x7B, 0x91,
	0x23, 0x00, 0x00, 0x02, 0x7C, 0xD8,
	0x23, 0x00, 0x00, 0x02, 0x7D, 0x60,
	0x23, 0x00, 0x00, 0x02, 0x75, 0x20,
	0x23, 0x00, 0x00, 0x02, 0x7F, 0x20,
	0x23, 0x00, 0x00, 0x02, 0x74, 0x10,
	0x23, 0x00, 0x00, 0x02, 0x7E, 0x10,

	0x23, 0x00, 0x00, 0x02, 0x93, 0x06,
	0x23, 0x00, 0x00, 0x02, 0x94, 0x06,

	0x23, 0x00, 0x00, 0x02, 0xB3, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xB4, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xB5, 0x00,

	0x23, 0x00, 0x00, 0x02, 0x78, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x79, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x80, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x83, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x84, 0x04,

	0x23, 0x00, 0x00, 0x02, 0x8A, 0x33,
	0x23, 0x00, 0x00, 0x02, 0x9B, 0x0F,
	0x23, 0x00, 0x00, 0x02, 0x8B, 0xF0,

	//BK_EN
	0x23, 0x00, 0x00, 0x02, 0xE3, 0x00,

	0x23, 0x00, 0x00, 0x02, 0xFB, 0x01,

	0x23, 0x00, 0x00, 0x02, 0xEC, 0x00,

	//CMD1
	0x23, 0x00, 0x00, 0x02, 0xFF, 0x10,
	0x39, 0x00, 0x00, 0x04, 0x3B, 0x03, 0x24, 0x20,
	//TE ON
	0x23, 0x00, 0x00, 0x02, 0x35, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xBB, 0x03,//video:0x03  cmd:0x10 0x13: video ???ram
	//CABC ON
	0x39, 0x00, 0x00, 0x03, 0x51, 0xFF, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x53, 0x2C,
	0x23, 0x00, 0x00, 0x02, 0x55, 0x00,
#if 1
	0x13, 0x78, 0x00, 0x01, 0x11,
        0x13, 0x78, 0x00, 0x01, 0x29,
#else  //bist mode
	0x23, 0x00, 0x00, 0x02,0xFF, 0x24,
	0x23, 0x00, 0x00, 0x02,0xEC, 0x01,
#endif
	CMD_END
};

static int mipi_dsi_send_cmds(struct sprd_dsi *dsi, void *data)
{
	uint16_t len;
	struct dsi_cmd_desc *cmds = data;

	if ((cmds == NULL) || (dsi == NULL))
		return -1;

	for (; cmds->data_type != CMD_END;) {
		len = (cmds->wc_h << 8) | cmds->wc_l;
		mipi_dsi_gen_write(dsi, cmds->payload, len);
		if (cmds->wait)
			msleep(cmds->wait);
		cmds = (struct dsi_cmd_desc *)(cmds->payload + len);
	}
	return 0;
}

static int nt35695_init(void)
{
	struct sprd_dsi *dsi = &dsi_device;
	struct sprd_dphy *dphy = &dphy_device;

	mipi_dsi_lp_cmd_enable(dsi, true);
	mipi_dsi_send_cmds(dsi, init_data);
	mipi_dsi_set_work_mode(dsi, SPRD_MIPI_MODE_VIDEO);
	mipi_dsi_state_reset(dsi);
	mipi_dphy_hs_clk_en(dphy, true);

	return 0;
}

static int nt35695_readid(void)
{
	struct sprd_dsi *dsi = &dsi_device;
	uint8_t read_buf[4] = {0};
	uint8_t pwr_val;

	mipi_dsi_lp_cmd_enable(dsi, true);
	mipi_dsi_set_max_return_size(dsi, 3);
	mipi_dsi_dcs_read(dsi, 0xDA, &read_buf[0], 1);
	mipi_dsi_dcs_read(dsi, 0xDB, &read_buf[1], 1);
	mipi_dsi_dcs_read(dsi, 0xDC, &read_buf[2], 1);
	if((0x0 == read_buf[0]) && (0x80 == read_buf[1]) && (0x0 == read_buf[2])) {
		pr_info("nt35695 read id success!\n");
		return 0;
        }

	pr_err("nt35695 read id failed!\n");
	return -1;
}

static int nt35695_power(int on)
{
	if (on) {
		sprd_gpio_request(NULL, CONFIG_LCM_GPIO_AVDDEN);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_AVDDEN, 1);
		mdelay(10);

		sprd_gpio_request(NULL, CONFIG_LCM_GPIO_AVEEEN);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_AVEEEN, 1);
		mdelay(20);

		sprd_gpio_request(NULL, CONFIG_LCM_GPIO_RSTN);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 1);
		mdelay(5);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 0);
		mdelay(5);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 1);
		mdelay(5);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 0);
		mdelay(5);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 1);
		mdelay(20);
	} else {
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_AVEEEN, 0);
		mdelay(20);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_AVDDEN, 0);
		mdelay(10);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 0);
		mdelay(5);
	}

	return 0;
}

static struct panel_ops nt35695_ops = {
	.init = nt35695_init,
	.read_id = nt35695_readid,
	.power = nt35695_power,
};

static struct panel_info nt35695_info = {
	/* common parameters */
	.lcd_name = "lcd_nt35695_truly_mipi_fhd",
	.type = SPRD_PANEL_TYPE_MIPI,
	.bpp = 24,
//	.fps = 60,
	.width = 1080,
	.height = 1920,

	/* DPI specific parameters */
	.pixel_clk = 153600000, /*Hz*/
	.rgb_timing = {
		.hfp = 176,
		.hbp = 16,
		.hsync = 10,
		.vfp = 32,
		.vbp = 32,
		.vsync = 4,
	},

	/* MIPI DSI specific parameters */
	.phy_freq = 9798*100,
	.lane_num = 4,
	.work_mode = SPRD_MIPI_MODE_VIDEO,
	.burst_mode = PANEL_VIDEO_BURST_MODE,
	.nc_clk_en = false,
};

struct panel_driver nt35695_truly_driver = {
	.info = &nt35695_info,
	.ops = &nt35695_ops,
};
