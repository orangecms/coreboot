Device(EC0)
{
	Name (_HID, EISAID("PNP0C09"))
	Name (_UID, 0)
	Name (_GPE, 23)
/* FIXME: EC support */
            Name (PENV, Zero)

            Method (ECRD, 1, Serialized)
            {
                Return (DerefOf (Arg0))
            }
            Method (ECWT, 2, Serialized)
            {
                Arg1 = Arg0
            }
            /*
            Method (ECMD, 1, Serialized)
            {
                If (ECON)
                {
                    While (CMDR)
                    {
                        Stall (0x14)
                    }

                    CMDR = Arg0
                }
            }
            */

            Device (BAT0)
            {
                Name (_HID, EisaId ("PNP0C0A") /* Control Method Battery */)  // _HID: Hardware ID
                Name (_UID, Zero)  // _UID: Unique ID
                Method (_STA, 0, NotSerialized)  // _STA: Status
                {
                    Return (Zero)
                }
            }
}
