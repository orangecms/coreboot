# Note: From here on down, we are socket-centric. Socket choice determines
# what other CPU files are included.
#
# Therefore: ONLY include Makefile.inc from socket directories!

subdirs-$(CONFIG_CPU_INTEL_FIRMWARE_INTERFACE_TABLE) += fit
subdirs-$(CONFIG_CPU_INTEL_SOCKET_441) += socket_441
subdirs-$(CONFIG_CPU_INTEL_SOCKET_BGA956) += socket_BGA956
subdirs-$(CONFIG_CPU_INTEL_SOCKET_FCBGA559) += socket_FCBGA559
subdirs-$(CONFIG_CPU_INTEL_SOCKET_M) += socket_m
subdirs-$(CONFIG_CPU_INTEL_SOCKET_P) += socket_p
subdirs-$(CONFIG_CPU_INTEL_SOCKET_MPGA604) += socket_mPGA604
subdirs-$(CONFIG_NORTHBRIDGE_INTEL_NEHALEM) += model_2065x
subdirs-$(CONFIG_NORTHBRIDGE_INTEL_SANDYBRIDGE) += model_206ax
subdirs-$(CONFIG_NORTHBRIDGE_INTEL_IVYBRIDGE) += model_206ax
subdirs-$(CONFIG_NORTHBRIDGE_INTEL_HASWELL) += haswell
subdirs-$(CONFIG_NORTHBRIDGE_INTEL_FSP_RANGELEY) += fsp_model_406dx
subdirs-$(CONFIG_CPU_INTEL_SLOT_1) += slot_1
subdirs-$(CONFIG_CPU_INTEL_SOCKET_LGA775) += socket_LGA775
