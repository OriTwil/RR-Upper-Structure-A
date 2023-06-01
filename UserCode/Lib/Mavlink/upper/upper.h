/** @file
 *  @brief MAVLink comm protocol generated from upper.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_UPPER_H
#define MAVLINK_UPPER_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_UPPER.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#undef MAVLINK_THIS_XML_HASH
#define MAVLINK_THIS_XML_HASH 8042156609761386349

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{11, 95, 28, 28, 0, 0, 0}, {209, 219, 25, 25, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_UPPER

// ENUM DEFINITIONS



// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_chassis_to_upper.h"
#include "./mavlink_msg_joystick_air.h"

// base include


#undef MAVLINK_THIS_XML_HASH
#define MAVLINK_THIS_XML_HASH 8042156609761386349

#if MAVLINK_THIS_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_CHASSIS_TO_UPPER, MAVLINK_MESSAGE_INFO_JOYSTICK_AIR}
# define MAVLINK_MESSAGE_NAMES {{ "CHASSIS_TO_UPPER", 11 }, { "JOYSTICK_AIR", 209 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_UPPER_H
