/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2008-2009 coresystems GmbH
 * Copyright (C) 2014 Vladimir Serbinenko
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdint.h>
#include <cpu/intel/romstage.h>
#include <cpu/intel/haswell/haswell.h>
#include <northbridge/intel/haswell/haswell.h>
#include <northbridge/intel/haswell/raminit.h>
#include <southbridge/intel/common/gpio.h>
#include <southbridge/intel/lynxpoint/pch.h>

// root complex base addresses
static const struct rcba_config_instruction rcba_config[] = {
	RCBA_SET_REG_16(D31IR, DIR_ROUTE(PIRQA, PIRQA, PIRQA, PIRQA)),
	RCBA_SET_REG_16(D29IR, DIR_ROUTE(PIRQA, PIRQA, PIRQA, PIRQA)),
	RCBA_SET_REG_16(D28IR, DIR_ROUTE(PIRQA, PIRQA, PIRQA, PIRQA)),
	RCBA_SET_REG_16(D27IR, DIR_ROUTE(PIRQA, PIRQA, PIRQA, PIRQA)),
	RCBA_SET_REG_16(D26IR, DIR_ROUTE(PIRQA, PIRQA, PIRQA, PIRQA)),
	RCBA_SET_REG_16(D25IR, DIR_ROUTE(PIRQA, PIRQA, PIRQA, PIRQA)),
	RCBA_SET_REG_16(D22IR, DIR_ROUTE(PIRQA, PIRQA, PIRQA, PIRQA)),
	RCBA_SET_REG_16(D20IR, DIR_ROUTE(PIRQA, PIRQA, PIRQA, PIRQA)),

	RCBA_RMW_REG_32(FD, ~0, PCH_DISABLE_ALWAYS),

	RCBA_END_CONFIG,
};

void mainboard_config_superio(void)
{
}

void mainboard_romstage_entry(unsigned long bist)
{
	struct pei_data pei_data = {
		.pei_version = PEI_VERSION,
		.mchbar = (uintptr_t)DEFAULT_MCHBAR,
		.dmibar = (uintptr_t)DEFAULT_DMIBAR,
		.epbar = DEFAULT_EPBAR,
		.pciexbar = CONFIG_MMCONF_BASE_ADDRESS,
		.smbusbar = SMBUS_IO_BASE,
		.wdbbar = 0x4000000,
		.wdbsize = 0x1000,
		.hpet_address = HPET_ADDR,
		.rcba = (uintptr_t)DEFAULT_RCBA,
		.pmbase = DEFAULT_PMBASE,
		.gpiobase = DEFAULT_GPIOBASE,
		.temp_mmio_base = 0xfed08000,
		.system_type = 1, /* desktop/server, FIXME: check this */
		.tseg_size = CONFIG_SMM_TSEG_SIZE,
		// left-shifted by 1 for mrc.bin
		.spd_addresses = { 0xa0, 0x00, 0xa4, 0x00 },
		.ec_present = 0,
		// 0 = leave channel enabled
		// 1 = disable dimm 0 on channel
		// 2 = disable dimm 1 on channel
		// 3 = disable dimm 0+1 on channel
		.dimm_channel0_disabled = 2, /* FIXME: leave channel 0 enabled */
		.dimm_channel1_disabled = 2, /* FIXME: leave channel 1 enabled */
		.max_ddr3_freq = 1600,
		.usb2_ports = {
			/* Length, Enable, OCn#, Location */
			{ 0x0040, 1, 0, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, 0, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, 1, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, 2, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, 3, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, 3, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, 4, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, 4, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, 5, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, 5, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, 6, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, 6, USB_PORT_BACK_PANEL },
		},
		.usb3_ports = {
			{ 1, 0 },
			{ 1, 0 },
			{ 1, 1 },
			{ 1, 1 },
			{ 1, 2 },
			{ 1, 2 },
		},
	};

	struct romstage_params romstage_params = {
		.pei_data = &pei_data,
		.gpio_map = &mainboard_gpio_map,
		.rcba_config = rcba_config,
		.bist = bist,
	};

	/* SuperIO */
	pch_enable_lpc();

	/* Main romstage entry */
	romstage_common(&romstage_params);
}
