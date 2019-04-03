/* SPDX-License-Identifier: GPL-2.0-only */

Device(EC)
{
	Name (_HID, EISAID("PNP0C09"))
	Name (_UID, 0)
	Name (_GPE, 23)
	Device (BAT0)
	{
		Name (_HID, EisaId ("PNP0C0A") /* Control Method Battery */)  // _HID: Hardware ID
		Name (_UID, Zero)  // _UID: Unique ID
		Method (_STA, 0, NotSerialized)  // _STA: Status
		{
                        /* vendor:
                        If ((BNUM & One))
                        {
                              Return (0x1F)
                        }
                        Return (0x0B)
                        */
			Return (Zero)
		}
	}
}
