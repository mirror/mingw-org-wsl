/**
 * @file cfg.h
 * @copy 2012 MinGW.org project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
 * PnP Configuration Manager shared definitions between user mode and
 * kernel mode code
 */

#ifndef __CFG_H
#define __CFG_H
#pragma GCC system_header

#ifdef __cplusplus
extern "C" {
#endif

#define CM_PROB_NOT_CONFIGURED		  				0x00000001
#define CM_PROB_DEVLOADER_FAILED            0x00000002
#define CM_PROB_OUT_OF_MEMORY               0x00000003
#define CM_PROB_ENTRY_IS_WRONG_TYPE         0x00000004
#define CM_PROB_LACKED_ARBITRATOR           0x00000005
#define CM_PROB_BOOT_CONFIG_CONFLICT        0x00000006
#define CM_PROB_FAILED_FILTER               0x00000007
#define CM_PROB_DEVLOADER_NOT_FOUND         0x00000008
#define CM_PROB_INVALID_DATA                0x00000009
#define CM_PROB_FAILED_START                0x0000000A
#define CM_PROB_LIAR                        0x0000000B
#define CM_PROB_NORMAL_CONFLICT             0x0000000C
#define CM_PROB_NOT_VERIFIED                0x0000000D
#define CM_PROB_NEED_RESTART                0x0000000E
#define CM_PROB_REENUMERATION               0x0000000F
#define CM_PROB_PARTIAL_LOG_CONF            0x00000010
#define CM_PROB_UNKNOWN_RESOURCE            0x00000011
#define CM_PROB_REINSTALL                   0x00000012
#define CM_PROB_REGISTRY                    0x00000013
#define CM_PROB_VXDLDR                      0x00000014
#define CM_PROB_WILL_BE_REMOVED             0x00000015
#define CM_PROB_DISABLED                    0x00000016
#define CM_PROB_DEVLOADER_NOT_READY         0x00000017
#define CM_PROB_DEVICE_NOT_THERE            0x00000018
#define CM_PROB_MOVED                       0x00000019
#define CM_PROB_TOO_EARLY                   0x0000001A
#define CM_PROB_NO_VALID_LOG_CONF           0x0000001B
#define CM_PROB_FAILED_INSTALL              0x0000001C
#define CM_PROB_HARDWARE_DISABLED           0x0000001D
#define CM_PROB_CANT_SHARE_IRQ              0x0000001E
#define CM_PROB_FAILED_ADD                  0x0000001F
#define CM_PROB_DISABLED_SERVICE          	0x00000020
#define CM_PROB_TRANSLATION_FAILED        	0x00000021
#define CM_PROB_NO_SOFTCONFIG             	0x00000022
#define CM_PROB_BIOS_TABLE                	0x00000023
#define CM_PROB_IRQ_TRANSLATION_FAILED    	0x00000024
#define CM_PROB_FAILED_DRIVER_ENTRY       	0x00000025
#define CM_PROB_DRIVER_FAILED_PRIOR_UNLOAD	0x00000026
#define CM_PROB_DRIVER_FAILED_LOAD          0x00000027
#define CM_PROB_DRIVER_SERVICE_KEY_INVALID  0x00000028
#define CM_PROB_LEGACY_SERVICE_NO_DEVICES   0x00000029
#define CM_PROB_DUPLICATE_DEVICE            0x0000002A
#define CM_PROB_FAILED_POST_START           0x0000002B
#define CM_PROB_HALTED                      0x0000002C
#define CM_PROB_PHANTOM                     0x0000002D
#define CM_PROB_SYSTEM_SHUTDOWN             0x0000002E
#define CM_PROB_HELD_FOR_EJECT              0x0000002F
#define CM_PROB_DRIVER_BLOCKED              0x00000030
#define CM_PROB_REGISTRY_TOO_LARGE        	0x00000031

#define LCPRI_FORCECONFIG                 0x00000000
#define LCPRI_BOOTCONFIG                  0x00000001
#define LCPRI_DESIRED                     0x00002000
#define LCPRI_NORMAL                      0x00003000
#define LCPRI_LASTBESTCONFIG              0x00003FFF
#define LCPRI_SUBOPTIMAL                  0x00005000
#define LCPRI_LASTSOFTCONFIG              0x00007FFF
#define LCPRI_RESTART                     0x00008000
#define LCPRI_REBOOT                      0x00009000
#define LCPRI_POWEROFF                    0x0000A000
#define LCPRI_HARDRECONFIG                0x0000C000
#define LCPRI_HARDWIRED                   0x0000E000
#define LCPRI_IMPOSSIBLE                  0x0000F000
#define LCPRI_DISABLED                    0x0000FFFF
#define MAX_LCPRI                         0x0000FFFF

#define DN_ROOT_ENUMERATED	0x00000001	/* Was enumerated by ROOT */
#define DN_DRIVER_LOADED	0x00000002	/* Has Register_Device_Driver */
#define DN_ENUM_LOADED		0x00000004	/* Has Register_Enumerator */
#define DN_STARTED		0x00000008	/* Is currently configured */
#define DN_MANUAL		0x00000010	/* Manually installed */
#define DN_NEED_TO_ENUM		0x00000020	/* May need reenumeration */
#define DN_NOT_FIRST_TIME	0x00000040	/* Has received a config */
#define DN_HARDWARE_ENUM	0x00000080	/* Enum generates hardware ID */
#define DN_LIAR			0x00000100	/* Lied about can reconfig once */
#define DN_HAS_MARK		0x00000200	/* Not CM_Create_DevNode lately */
#define DN_HAS_PROBLEM		0x00000400	/* Need device installer */
#define DN_FILTERED		0x00000800	/* Is filtered */
#define DN_MOVED		0x00001000	/* Has been moved */
#define DN_DISABLEABLE		0x00002000	/* Can be rebalanced */
#define DN_REMOVABLE		0x00004000	/* Can be removed */
#define DN_PRIVATE_PROBLEM	0x00008000	/* Has a private problem */
#define DN_MF_PARENT		0x00010000	/* Multi function parent */
#define DN_MF_CHILD		0x00020000	/* Multi function child */
#define DN_WILL_BE_REMOVED	0x00040000	/* Devnode is being removed */

typedef enum _PNP_VETO_TYPE {
  PNP_VetoTypeUnknown,
  PNP_VetoLegacyDevice,
  PNP_VetoPendingClose,
  PNP_VetoWindowsApp,
  PNP_VetoWindowsService,
  PNP_VetoOutstandingOpen,
  PNP_VetoDevice,
  PNP_VetoDriver,
  PNP_VetoIllegalDeviceRequest,
  PNP_VetoInsufficientPower,
  PNP_VetoNonDisableable,
  PNP_VetoLegacyDriver
} PNP_VETO_TYPE, *PPNP_VETO_TYPE;

#ifdef __cplusplus
}
#endif

#endif /* __CFG_H */
