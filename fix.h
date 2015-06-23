//
// Created by dtenty on 17/06/15.
//

#ifndef REGISTRATIONDUMP_FIX_H
#define REGISTRATIONDUMP_FIX_H
#define _BSD_SOURCE
#include <libfreenect/libfreenect.h>
#include <libfreenect/libfreenect_registration.h>
#include <endian.h>

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

int freenect_apply_registration_to_buffer(freenect_registration* reg, uint8_t* input_packed, uint16_t* output_mm);

#endif //REGISTRATIONDUMP_FIX_H
