#include <device/device.h>
#include <drivers/intel/gma/int15.h>
#include <ec/acpi/ec.h>
#include <console/console.h>
#include <pc80/keyboard.h>

static void mainboard_init(struct device *dev)
{
	pc_keyboard_init(NO_AUX_DEVICE);
}

static void mainboard_enable(struct device *dev)
{
	dev->ops->init = mainboard_init;

	install_intel_vga_int15_handler(GMA_INT15_ACTIVE_LFP_INT_LVDS,
					GMA_INT15_PANEL_FIT_DEFAULT,
					GMA_INT15_BOOT_DISPLAY_DEFAULT, 0);
}

struct chip_operations mainboard_ops = {
	.enable_dev = mainboard_enable,
};
