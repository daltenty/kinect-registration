/*
 * This file is part of the OpenKinect Project. http://www.openkinect.org
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

#include <iostream>
#include <libfreenect/libfreenect.h>
#include <libfreenect/libfreenect_registration.h>
#include <unistd.h>
#include <fcntl.h>


using namespace std;

int main() {
    freenect_context *ctx;
    freenect_device *dev;
    int outputfile=open("registration.raw", O_CREAT|O_WRONLY|O_TRUNC);

    if (!outputfile)
        perror("Error openning output file");

    if (freenect_init(&ctx,NULL))
        perror("Cannot get context");

    freenect_select_subdevices(ctx, (freenect_device_flags)(FREENECT_DEVICE_MOTOR | FREENECT_DEVICE_CAMERA));

    if (freenect_open_device(ctx,&dev,0)) {
        perror("Error opening device");
    }

    freenect_registration reg=freenect_copy_registration(dev);
    write(outputfile, &reg,sizeof(reg));
    freenect_destroy_registration(&reg);
    close(outputfile);

    freenect_close_device(dev);




    return 0;
}