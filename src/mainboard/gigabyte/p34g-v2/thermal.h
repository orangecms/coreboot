/* SPDX-License-Identifier: GPL-2.0-only */

// taken from Samsung / lumpy
#ifndef P34V2_THERMAL_H
#define P34V2_THERMAL_H

/* Fan is OFF */
#define FAN4_THRESHOLD_OFF 0
#define FAN4_THRESHOLD_ON 0

/* Fan is at LOW speed */
#define FAN3_THRESHOLD_OFF 40
#define FAN3_THRESHOLD_ON 44

/* Fan is at MEDIUM speed */
#define FAN2_THRESHOLD_OFF 44
#define FAN2_THRESHOLD_ON 48

/* Fan is at HIGH speed */
#define FAN1_THRESHOLD_OFF 48
#define FAN1_THRESHOLD_ON 54

/* Fan is at FULL speed */
#define FAN0_THRESHOLD_OFF 54
#define FAN0_THRESHOLD_ON 78

/* Temperature which OS will shutdown at */
#define CRITICAL_TEMPERATURE 100

/* Temperature which OS will throttle CPU */
#define PASSIVE_TEMPERATURE 80

/* Tj_max value for calculating PECI CPU temperature */
#define MAX_TEMPERATURE 100

#endif
