/*
 * Copyright (c) 2015 David Tenty <dtenty@ryerson.ca>, Adrian Popescu <dapopesc@ryerson.ca>
 *
 * Parts of this file originally part of the OpenKinect Project. http://www.openkinect.org
 *
 * Copyright (c) 2011 individual OpenKinect contributors. See the CONTRIB file
 * for details.
 *
 * This code is licensed to you under the terms of the Apache License, version
 * 2.0, or, at your option, the terms of the GNU General Public License,
 * version 2.0. See the APACHE20 and GPL2 files for the text of the licenses,
 * or the following URLs:
 * http://www.apache.org/licenses/LICENSE-2.0
 * http://www.gnu.org/licenses/gpl-2.0.txt
 *
 * If you redistribute this file in source form, modified or unmodified, you
 * may:
 *   1) Leave this header intact and distribute it under the same terms,
 *      accompanying it with the APACHE20 and GPL20 files, or
 *   2) Delete the Apache 2.0 clause and accompany it with the GPL2 file, or
 *   3) Delete the GPL v2 clause and accompany it with the APACHE20 file
 * In all cases you must keep the copyright notice intact and include a copy
 * of the CONTRIB file.
 *
 * Binary distributions must follow the binary distribution requirements of
 * either License.
 */

#ifndef REGISTRATIONDUMP_REGISTRATION_H
#define REGISTRATIONDUMP_REGISTRATION_H

// from registration.c
#define REG_X_VAL_SCALE 256 // "fixed-point" precision for double -> int32_t conversion

#define S2D_PIXEL_CONST 10
#define S2D_CONST_OFFSET 0.375

#define DEPTH_SENSOR_X_RES 1280
#define DEPTH_MIRROR_X 0

#define DEPTH_MAX_METRIC_VALUE FREENECT_DEPTH_MM_MAX_VALUE
#define DEPTH_NO_MM_VALUE      FREENECT_DEPTH_MM_NO_VALUE
#define DEPTH_MAX_RAW_VALUE    FREENECT_DEPTH_RAW_MAX_VALUE
#define DEPTH_NO_RAW_VALUE     FREENECT_DEPTH_RAW_NO_VALUE

#define DEPTH_X_OFFSET 1
#define DEPTH_Y_OFFSET 1
#define DEPTH_X_RES 640
#define DEPTH_Y_RES 480

#endif //REGISTRATIONDUMP_REGISTRATION_H
