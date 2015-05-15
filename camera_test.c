/**
 *  @file camera_test.c
 *  @brief Testing routines for camera functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include "camera_rpi2.h"

int main(int argc, char *argv[]) {
    FILE *fp = fopen("test.rgb", "wb");
    size_t bufsiz = 640*480*3;
    BYTE buf[bufsiz];
    
    if (fp == NULL) {
        perror("Cannot open test.rgb");
        return 1;
    }
    
    if (CAMInit(CAM_640_RGB) != CAM_SUCCESS) {
        printf("Could not initialise camera.\n");
        return 1;
    }
    
    printf("Camera mode: %d\n", CAMGetMode());
    for (int i = 0; i < 50; i++) {
        if (CAMGetFrame(buf) != CAM_SUCCESS) {
            printf("Failed to capture camera frame. (%d)\n", i+1);
        } else {
            printf("Got frame %d\n", i+1);
        }
    }
    
    printf("Saving frame to test.rgb\n");
    fwrite(buf, 1, bufsiz, fp);
    
    printf("Done.\n");
    CAMRelease();
    fclose(fp);
}