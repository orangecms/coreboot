/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2011 The Chromium OS Authors. All rights reserved.
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

// Thermal Zone

External (\PPKG, MethodObj)

#define HAVE_THERMALZONE
Scope (\_TZ)
{
        Name (ETMD, One)
	ThermalZone (THRM)
	{
		Name (_TC1, 0x02)
		Name (_TC2, 0x05)

		// Ignore critical temps for the first few reads
		// at boot to prevent unexpected shutdown
		Name (IRDC, 4)
		Name (CRDC, 0)

		// Thermal zone polling frequency: 10 seconds
		Name (_TZP, 100)

		// Thermal sampling period for passive cooling: 2 seconds
		Name (_TSP, 20)

		// Convert from Degrees C to 1/10 Kelvin for ACPI
		Method (CTOK, 1) {
			// 10th of Degrees C
			Multiply (Arg0, 10, Local0)

			// Convert to Kelvin
			Add (Local0, 2732, Local0)

			Return (Local0)
		}

		// Threshold for OS to shutdown
		Method (_CRT, 0, Serialized)
		{
			Return (CTOK (\TCRT))
		}

		// Threshold for passive cooling
		Method (_PSV, 0, Serialized)
		{
			Return (CTOK (\TPSV))
		}

		// Processors used for passive cooling
		Method (_PSL, 0, Serialized)
		{
			Return (\PPKG ())
		}

		Method (_AC0) {
			If (LLessEqual (\FLVL, 0)) {
				Return (CTOK (\F0OF))
			} Else {
				Return (CTOK (\F0ON))
			}
		}

		Method (_AC1) {
			If (LLessEqual (\FLVL, 1)) {
				Return (CTOK (\F1OF))
			} Else {
				Return (CTOK (\F1ON))
			}
		}

		Method (_AC2) {
			If (LLessEqual (\FLVL, 2)) {
				Return (CTOK (\F2OF))
			} Else {
				Return (CTOK (\F2ON))
			}
		}

		Method (_AC3) {
			If (LLessEqual (\FLVL, 3)) {
				Return (CTOK (\F3OF))
			} Else {
				Return (CTOK (\F3ON))
			}
		}

		Method (_AC4) {
			If (LLessEqual (\FLVL, 4)) {
				Return (CTOK (\F4OF))
			} Else {
				Return (CTOK (\F4ON))
			}
		}
	}
}
