/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/device.h>
#include <device/pnp.h>
#include <superio/conf_mode.h>

#include "it8587e.h"

static void it8587e_init(struct device *dev)
{
}

static struct device_operations ops = {
	.read_resources   = pnp_read_resources,
	.set_resources    = pnp_set_resources,
	.enable_resources = pnp_enable_resources,
	.enable           = pnp_alt_enable,
	.init             = it8587e_init,
	.ops_pnp_mode     = &pnp_conf_mode_870155_aa,
};

static struct pnp_info pnp_dev_info[] = {
	{ NULL, IT8587E_UART1, PNP_IO0 | PNP_IRQ0, 0x0ff8, },
	{ NULL, IT8587E_UART2, PNP_IO0 | PNP_IRQ0, 0x0ff8, },
	{ NULL, IT8587E_SWUC, PNP_IO0 | PNP_IRQ0, 0xfff0, },
	/* Documentation: Unused */
	{ NULL, IT8587E_KBCM, PNP_IRQ0, },
	/* Documentation: Program io0 = 0x60 and io1 = 0x64 */
	{ NULL, IT8587E_KBCK, PNP_IO0 | PNP_IO1 | PNP_IRQ0, 0x07ff, 0x07ff, },
	{ NULL, IT8528E_IR, PNP_IO0 | PNP_IRQ0, 0xfff8, },
	{ NULL, IT8587E_SMFI, PNP_IO0 | PNP_IRQ0, 0xfff0, },
	/* Documentation: Program io0 = 0x70-0x73 */
	{ NULL, IT8587E_RTCT, PNP_IO0 | PNP_IO1 | PNP_IO2 | PNP_IO3 | PNP_IRQ0,
		0xfffe, 0xfffe, 0xfffe, 0xfffe},
	/* Documentation: Program io0 = 0x62 and io1 = 0x66 */
	{ NULL, IT8587E_PMC1, PNP_IO0 | PNP_IO1 | PNP_IRQ0, 0x07ff, 0x07ff },
	/* Documentation: Program io0 = 0x68 and io1 = 0x6c */
	{ NULL, IT8587E_PMC2, PNP_IO0 | PNP_IO1 | PNP_IRQ0, 0x07fc, 0x07fc },
	/* Documentation: Program io0 = 0x6a and io1 = 0x6e */
	{ NULL, IT8587E_PMC3, PNP_IO0 | PNP_IO1 | PNP_IRQ0, 0x07ff, 0x07ff },
	{ NULL, IT8587E_PMC4, PNP_IO0 | PNP_IO1 | PNP_IRQ0, 0x07ff, 0x07ff },
	{ NULL, IT8587E_PMC5, PNP_IO0 | PNP_IO1 | PNP_IRQ0, 0x07ff, 0x07ff },
	{ NULL, IT8587E_SSPI, PNP_IO0 | PNP_IRQ0, 0xfff8 },
	{ NULL, IT8587E_PECI, PNP_IO0, 0xfff8 },
};

static void enable_dev(struct device *dev)
{
	pnp_enable_devices(dev, &ops, ARRAY_SIZE(pnp_dev_info), pnp_dev_info);
}

struct chip_operations superio_ite_it8587e_ops = {
	CHIP_NAME("ITE IT8587E Super I/O")
	.enable_dev = enable_dev,
};
