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

#ifndef REGISTRATIONDUMP_FIX_H
#define REGISTRATIONDUMP_FIX_H
#define _BSD_SOURCE
#include <libfreenect/libfreenect.h>
#include <libfreenect/libfreenect_registration.h>
#include <endian.h>
#include "registration.h"


int freenect_apply_registration_to_buffer(freenect_registration* reg, uint8_t* input_packed, uint16_t* output_mm);

#endif //REGISTRATIONDUMP_FIX_H
