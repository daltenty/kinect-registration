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

#include "fix.h"
#include <iostream>

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>



using namespace std;

int freenect_apply_registration_to_buffer(freenect_registration* reg, uint16_t* input_unpacked, uint16_t* output_mm)
{
    // set output buffer to zero using pointer-sized memory access (~ 30-40% faster than memset)
    size_t i, *wipe = (size_t*)output_mm;
    for (i = 0; i < DEPTH_X_RES * DEPTH_Y_RES * sizeof(uint16_t) / sizeof(size_t); i++) wipe[i] = DEPTH_NO_MM_VALUE;


    uint32_t target_offset = DEPTH_Y_RES * reg->reg_pad_info.start_lines;
    uint32_t x,y,source_index = 0;

    for (y = 0; y < DEPTH_Y_RES; y++) {
        for (x = 0; x < DEPTH_X_RES; x++) {

            // get the value at the current depth pixel, convert to millimeters
            uint16_t metric_depth = reg->raw_to_mm_shift[ input_unpacked[source_index++] ];

            // so long as the current pixel has a depth value
            if (metric_depth == DEPTH_NO_MM_VALUE) continue;
            if (metric_depth >= DEPTH_MAX_METRIC_VALUE) continue;

            // calculate the new x and y location for that pixel
            // using registration_table for the basic rectification
            // and depth_to_rgb_shift for determining the x shift
            uint32_t reg_index = DEPTH_MIRROR_X ? ((y + 1) * DEPTH_X_RES - x - 1) : (y * DEPTH_X_RES + x);
            uint32_t nx = (reg->registration_table[reg_index][0] + reg->depth_to_rgb_shift[metric_depth]) / REG_X_VAL_SCALE;
            uint32_t ny =  reg->registration_table[reg_index][1];

            // ignore anything outside the image bounds
            if (nx >= DEPTH_X_RES) continue;

            // convert nx, ny to an index in the depth image array
            uint32_t target_index = (DEPTH_MIRROR_X ? ((ny + 1) * DEPTH_X_RES - nx - 1) : (ny * DEPTH_X_RES + nx)) - target_offset;

            // get the current value at the new location
            uint16_t current_depth = output_mm[target_index];

            // make sure the new location is empty, or the new value is closer
            if ((current_depth == DEPTH_NO_MM_VALUE) || (current_depth > metric_depth)) {
                output_mm[target_index] = metric_depth; // always save depth at current location

#ifdef DENSE_REGISTRATION
					// if we're not on the first row, or the first column
					if ((nx > 0) && (ny > 0)) {
						output_mm[target_index - DEPTH_X_RES    ] = metric_depth; // save depth at (x,y-1)
						output_mm[target_index - DEPTH_X_RES - 1] = metric_depth; // save depth at (x-1,y-1)
						output_mm[target_index               - 1] = metric_depth; // save depth at (x-1,y)
					} else if (ny > 0) {
						output_mm[target_index - DEPTH_X_RES] = metric_depth; // save depth at (x,y-1)
					} else if (nx > 0) {
						output_mm[target_index - 1] = metric_depth; // save depth at (x-1,y)
					}
				#endif
            }
        }
    }
    return 0;
}

int copy_header(char *str, FILE *out)
{
    char c;
    int offset=0;

    while (1) {
        c=*str;
        fputc(c,out);
        str++; offset++;
        if (c == '\n')
            break;
    }

    return offset;
}

static int get_data_size(FILE *fp)
{
    int orig = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int out = ftell(fp);
    fseek(fp, orig, SEEK_SET);
    return out;
}

void die (const char* str) {
    cerr << str << endl;
    abort();
}

int main(int argc,char *argv[]) {
    if (argc != 3) {
        die("Wrong args");
    }

    freenect_context *ctx;
    freenect_device *dev;
    FILE *inputfile=fopen(argv[1],"r");
    FILE *outputfile=fopen(argv[2], "w");
    char *buffer;
    uint16_t *new_img,*old_img;
    unsigned int bufsize;


    if (!inputfile)
        die("Error openning output file");

    if (!outputfile)
        die("Error openning output file");

    if (freenect_init(&ctx,NULL))
        die("Cannot get context");

    freenect_select_subdevices(ctx, (freenect_device_flags)(FREENECT_DEVICE_MOTOR | FREENECT_DEVICE_CAMERA));

    if (freenect_open_device(ctx,&dev,0)) {
        die("Error opening device");
    }

    freenect_registration reg=freenect_copy_registration(dev);

    //load_image
    bufsize = get_data_size(inputfile);
    buffer = (char *)malloc(bufsize);
    if (fread(buffer, bufsize, 1,inputfile ) != 1) {
        printf("Error: Couldn't read entire file.\n");
        return -1;
    }
    fclose(inputfile);

    int offset=copy_header(buffer,outputfile);


    // register stuff
    old_img=reinterpret_cast<uint16_t *>(buffer+offset);
    new_img=reinterpret_cast<uint16_t *>(malloc(bufsize-offset));
    cout << "Got " << (bufsize - offset)/2 << "pixels" << endl;

    freenect_apply_registration_to_buffer(&reg,old_img,new_img);

    for (int i=0; i < (bufsize-offset)/2;i++) {
        *(new_img+i)=htobe16(*(new_img+i));
    }

    fwrite(new_img,sizeof(uint16_t),(bufsize-offset)/2,outputfile);

    freenect_destroy_registration(&reg);
    free(buffer);

    fclose(outputfile);

    freenect_close_device(dev);




    return 0;
}
