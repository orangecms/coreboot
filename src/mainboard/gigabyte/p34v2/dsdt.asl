/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2009 coresystems GmbH
 * Copyright (C) 2012 Google Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#define BRIGHTNESS_UP \_SB.PCI0.GFX0.INCB
#define BRIGHTNESS_DOWN \_SB.PCI0.GFX0.DECB
#define ACPI_VIDEO_DEVICE \_SB.PCI0.GFX0

#include <arch/acpi.h>
DefinitionBlock(
	"dsdt.aml",
	"DSDT",
	0x02,		// DSDT revision: ACPI 2.0 and up
	OEM_ID,
	ACPI_TABLE_CREATOR,
	0x20141018	// OEM revision
)
{
	/* Some generic macros */
	#include "acpi/platform.asl"

	/* Thermal handler */
	// TODO: #include "acpi/thermal.asl"

	#include <cpu/intel/common/acpi/cpu.asl>
	#include <southbridge/intel/lynxpoint/acpi/platform.asl>

	/* global NVS and variables. */
	#include <southbridge/intel/lynxpoint/acpi/globalnvs.asl>
	#include <southbridge/intel/lynxpoint/acpi/sleepstates.asl>

	Device (\_SB.PCI0)
	{
		#include <northbridge/intel/haswell/acpi/haswell.asl>
		#include <drivers/intel/gma/acpi/default_brightness_levels.asl>
		#include <southbridge/intel/lynxpoint/acpi/pch.asl>
	}
}
