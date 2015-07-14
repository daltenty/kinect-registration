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

#include <libfreenect/libfreenect_registration.h>
#include "serialization.h"
#include <malloc.h>
#include <unistd.h>


void serialize_registration(std::ofstream &fd, freenect_registration *registration) {
    fd << "<?xml version=\"1.0\" ?>\n<configuration>\n";
        // serialize fixed portions of struct
    //write(fd, registration,sizeof(freenect_reg_info)+sizeof(freenect_reg_pad_info)+sizeof(freenect_zero_plane_info)+sizeof(double));
    serialize_freenect_reg_info(fd, registration->reg_info);
    serialize_freenect_reg_pad_info(fd,registration->reg_pad_info);
    serialize_freenect_zero_plane_info(fd,registration->zero_plane_info);

    // serialize pointers
    //write(fd, registration->raw_to_mm_shift,sizeof(uint16_t) * DEPTH_MAX_RAW_VALUE);
    //write(fd,registration->depth_to_rgb_shift,sizeof( int32_t) * DEPTH_MAX_METRIC_VALUE);

    //write(fd,registration->registration_table,sizeof(int32_t)*640*480*2);
    fd << "</configuration>" << std::endl;
}

//void deserialize_registration(int fd, freenect_registration *registration) {
//    // serialize fixed portions of struct
//    read(fd, registration,sizeof(freenect_reg_info)+sizeof(freenect_reg_pad_info)+sizeof(freenect_zero_plane_info)+sizeof(double));
//
//    registration->raw_to_mm_shift    = (uint16_t*)malloc( sizeof(uint16_t) * DEPTH_MAX_RAW_VALUE );
//    registration->depth_to_rgb_shift = (int32_t*)malloc( sizeof( int32_t) * DEPTH_MAX_METRIC_VALUE );
//    registration->registration_table = (int32_t (*)[2])malloc( sizeof( int32_t) * DEPTH_X_RES * DEPTH_Y_RES * 2 );
//
//    // serialize pointers
//    read(fd, registration->raw_to_mm_shift,sizeof(uint16_t));
//    read(fd,registration->depth_to_rgb_shift,sizeof(int32_t));
//
//    read(fd,registration->registration_table,sizeof(int32_t)*640*480*2);
//}

void serialize_freenect_reg_info(std::ofstream &fd, freenect_reg_info reg_info) {
    write_property(fd , "reg_info.dx",reg_info.dx_center); // not used by mapping algorithm

    write_property(fd , "reg_info.ax",reg_info.ax);
    write_property(fd , "reg_info.bx",reg_info.bx);
    write_property(fd , "reg_info.cx",reg_info.cx);
    write_property(fd , "reg_info.dx",reg_info.dx);

    write_property(fd , "reg_info.dx",reg_info.dx_start);

    write_property(fd , "reg_info.ay",reg_info.ay);
    write_property(fd , "reg_info.by",reg_info.by);
    write_property(fd , "reg_info.cy",reg_info.cy);
    write_property(fd , "reg_info.dy",reg_info.dy);

    write_property(fd , "reg_info.dy",reg_info.dy_start);

    write_property(fd , "reg_info.dx",reg_info.dx_beta_start);
    write_property(fd , "reg_info.dy",reg_info.dy_beta_start);

    write_property(fd , "reg_info.rollout",reg_info.rollout_blank); // not used by mapping algorithm
    write_property(fd , "reg_info.rollout",reg_info.rollout_size);  // not used by mapping algorithm

    write_property(fd , "reg_info.dx",reg_info.dx_beta_inc);
    write_property(fd , "reg_info.dy",reg_info.dy_beta_inc);

    write_property(fd , "reg_info.dxdx",reg_info.dxdx_start);
    write_property(fd , "reg_info.dxdy",reg_info.dxdy_start);
    write_property(fd , "reg_info.dydx",reg_info.dydx_start);
    write_property(fd , "reg_info.dydy",reg_info.dydy_start);

    write_property(fd , "reg_info.dxdxdx",reg_info.dxdxdx_start);
    write_property(fd , "reg_info.dydxdx",reg_info.dydxdx_start);
    write_property(fd , "reg_info.dxdxdy",reg_info.dxdxdy_start);
    write_property(fd , "reg_info.dydxdy",reg_info.dydxdy_start);

    write_property(fd , "reg_info.back",reg_info.back_comp1); // not used by mapping algorithm

    write_property(fd , "reg_info.dydydx",reg_info.dydydx_start);

    write_property(fd , "reg_info.back",reg_info.back_comp2); // not used by mapping algorithm

    write_property(fd , "reg_info.dydydy",reg_info.dydydy_start);

}

void serialize_freenect_reg_pad_info(std::ofstream &fd, freenect_reg_pad_info reg_pad_info) {

}

void serialize_freenect_zero_plane_info(std::ofstream &fd, freenect_zero_plane_info zero_plane_info) {

}

void write_property(std::ofstream &fd, const char *name, int value) {
    fd << "<property>\n";
    fd << "\t<name>" << name << "</name>\n";
    fd << "\t<value>" << value << "</value>\n";
    fd << "</property>\n";
}
