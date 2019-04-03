/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/azalia_device.h>

const u32 cim_verb_data[] = {
	0x80862807, /* Codec Vendor / Device ID: Intel */
	0x80860101, /* Subsystem ID */

	0x00000004, /* Number of 4 dword sets */
	/* NID 0x01: Subsystem ID.  */
	AZALIA_SUBVENDOR(0x0, 0x80860101),

	/* NID 0x05.  */
	AZALIA_PIN_CFG(0x0, 0x05, 0x18560010),

	/* NID 0x06.  */
	AZALIA_PIN_CFG(0x0, 0x06, 0x18560010),

	/* NID 0x07.  */
	AZALIA_PIN_CFG(0x0, 0x07, 0x18560010),
};

const u32 pc_beep_verbs[0] = {};

AZALIA_ARRAY_SIZES;
