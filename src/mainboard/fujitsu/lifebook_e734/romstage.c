/* SPDX-License-Identifier: GPL-2.0-only */

#include <stdint.h>
#include <arch/romstage.h>
#include <cpu/intel/haswell/haswell.h>
#include <northbridge/intel/haswell/haswell.h>
// TODO: taken from beltino
//#include <northbridge/intel/haswell/raminit.h>
#include <northbridge/intel/haswell/pei_data.h>
#include <southbridge/intel/common/gpio.h>
// TODO: taken from beltino
//#include <southbridge/intel/lynxpoint/lp_gpio.h>
#include <southbridge/intel/lynxpoint/pch.h>

static const struct rcba_config_instruction rcba_config[] = {
	RCBA_SET_REG_16(D31IR, DIR_ROUTE(PIRQA, PIRQD, PIRQC, PIRQA)),
	RCBA_SET_REG_16(D29IR, DIR_ROUTE(PIRQH, PIRQD, PIRQA, PIRQC)),
	RCBA_SET_REG_16(D28IR, DIR_ROUTE(PIRQA, PIRQA, PIRQA, PIRQA)),
	RCBA_SET_REG_16(D27IR, DIR_ROUTE(PIRQG, PIRQB, PIRQC, PIRQD)),
	RCBA_SET_REG_16(D26IR, DIR_ROUTE(PIRQC, PIRQF, PIRQC, PIRQD)),
	RCBA_SET_REG_16(D25IR, DIR_ROUTE(PIRQE, PIRQF, PIRQG, PIRQH)),
	RCBA_SET_REG_16(D22IR, DIR_ROUTE(PIRQA, PIRQB, PIRQC, PIRQD)),
	RCBA_SET_REG_16(D20IR, DIR_ROUTE(PIRQA, PIRQB, PIRQC, PIRQD)),

	/* Disable unused devices (board specific) */
	RCBA_RMW_REG_32(FD, ~0, PCH_DISABLE_ALWAYS),

	RCBA_END_CONFIG,
};

void mainboard_config_superio(void)
{
}
// what happened to these?
//	.wdbbar = 0x4000000,
//	.wdbsize = 0x1000,
// gone, see e8abb5ab8887969498f9953e76b7e0f4c68d3e47
void mainboard_romstage_entry(void)
{
	struct pei_data pei_data = {
		.pei_version = PEI_VERSION,
		.mchbar = (uintptr_t)DEFAULT_MCHBAR,
		.dmibar = (uintptr_t)DEFAULT_DMIBAR,
		.epbar = DEFAULT_EPBAR,
		.pciexbar = CONFIG_MMCONF_BASE_ADDRESS,
		.smbusbar = SMBUS_IO_BASE,
		.hpet_address = HPET_ADDR,
		.rcba = (uintptr_t)DEFAULT_RCBA,
		.pmbase = DEFAULT_PMBASE,
		.gpiobase = DEFAULT_GPIOBASE,
		.temp_mmio_base = 0xfed08000,
		.system_type = 5, /* ULT */
		.tseg_size = CONFIG_SMM_TSEG_SIZE,
		/* note that SPD addresses are left-shifted by 1. */
		.spd_addresses = { 0xa0, 0x00, 0xa4, 0x00 },
		.ec_present = 0,
		.gbe_enable = 0, // TODO
		// 0 = leave channel enabled
		// 1 = disable dimm 0 on channel
		// 2 = disable dimm 1 on channel
		// 3 = disable dimm 0+1 on channel
		.dimm_channel0_disabled = 2,
		.dimm_channel1_disabled = 2,
		.max_ddr3_freq = 1600,
		.usb2_ports = {
			/* Length, Enable, OCn#, Location */
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
			{ 0x0040, 1, USB_OC_PIN_SKIP, USB_PORT_BACK_PANEL },
		},
		.usb3_ports = {
			{ 1, USB_OC_PIN_SKIP },
			{ 1, USB_OC_PIN_SKIP },
			{ 1, USB_OC_PIN_SKIP },
			{ 1, USB_OC_PIN_SKIP },
			{ 1, USB_OC_PIN_SKIP },
			{ 1, USB_OC_PIN_SKIP },
		},
	};

	struct romstage_params romstage_params = {
		.pei_data = &pei_data,
		.gpio_map = &mainboard_gpio_map,
		.rcba_config = &rcba_config[0],
	};

	romstage_common(&romstage_params);
}
