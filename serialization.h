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
#ifndef REGISTRATIONDUMP_SERIALIZATION_H
#define REGISTRATIONDUMP_SERIALIZATION_H

#include <libfreenect/libfreenect_registration.h>
#include <fstream>
#include "registration.h"

// NOTE: this is really dirty and depends on libfreenect internals
// git-version: 89f77f6d2c

void serialize_registration(std::ofstream &fd, freenect_registration *registration);
void serialize_freenect_reg_info(std::ofstream &fd,freenect_reg_info reg_info);
void serialize_freenect_reg_pad_info(std::ofstream &fd, freenect_reg_pad_info    reg_pad_info);
void serialize_freenect_zero_plane_info(std::ofstream &fd, freenect_zero_plane_info zero_plane_info);\
void write_property(std::ofstream &fd, const char *name, int value);

//void deserialize_registration(int fd, freenect_registration *registration);

#endif //REGISTRATIONDUMP_SERIALIZATION_H
