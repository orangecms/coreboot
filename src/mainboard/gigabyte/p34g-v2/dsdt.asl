/* SPDX-License-Identifier: GPL-2.0-only */

#define BRIGHTNESS_UP \_SB.PCI0.GFX0.INCB
#define BRIGHTNESS_DOWN \_SB.PCI0.GFX0.DECB
#define ACPI_VIDEO_DEVICE \_SB.PCI0.GFX0

#include <acpi/acpi.h>
DefinitionBlock(
	"dsdt.aml",
	"DSDT",
	ACPI_DSDT_REV_2,
	OEM_ID,
	ACPI_TABLE_CREATOR,
	0x20141018	// OEM revision
)
{
	/* Some generic macros */
	#include "acpi/platform.asl"

	/* Super I/O, EC */
	#include "acpi/superio.asl"
	#include "acpi/ec.asl"

	/* Thermal handler */
	#include "acpi/thermal.asl"

	/* global NVS and variables. */
	#include <southbridge/intel/lynxpoint/acpi/globalnvs.asl>

	#include <cpu/intel/common/acpi/cpu.asl>

	Device (\_SB.PCI0)
	{
		#include <northbridge/intel/haswell/acpi/hostbridge.asl>
		#include <drivers/intel/gma/acpi/default_brightness_levels.asl>
		#include <southbridge/intel/lynxpoint/acpi/pch.asl>
	}

	#include <southbridge/intel/common/acpi/sleepstates.asl>
}
