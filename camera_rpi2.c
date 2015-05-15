/**
 *  @file camera_rpi2.c
 *  @brief Camera routines for the Raspberry Pi 2, modded for the EyeBot.
 *  Can be compiled with:
 *  gcc -std=c99 -Wall -pedantic `pkg-config --cflags opencv` *.c `pkg-config --libs opencv`  
 *  @author Jeremy Tan, 20933708 (HEXACOPTER GROUP) 
 */

#include "camera_rpi2.h"
#include <stdlib.h>
#include <cv.h>
#include <opencv2/highgui/highgui_c.h>

/* Globals */
/** The OpenCv capture object. **/
static CvCapture *g_capture = NULL;
/** The current camera mode. **/
static CAMMode g_mode = CAM_NONE;

int CAMInit (CAMMode mode) {
    if (g_capture == NULL) {
        g_capture = cvCreateCameraCapture(-1);
        if (g_capture == NULL) {
            return CAM_FAILURE;
        }
    }
    cvSetCaptureProperty(g_capture, CV_CAP_PROP_CONVERT_RGB, 1);
    return CAMSetMode(mode);
}

int CAMSetMode (CAMMode mode) {
    int width, height, realwidth, realheight;
    
    if (g_capture == NULL) {
        return CAM_FAILURE;
    }
    
    switch (mode) {
        case CAM_160_RGB:
            width = 160, height = 120;
        break;
        case CAM_320_RGB:
            width = 320, height = 240;
        break;
        case CAM_640_RGB:
            width = 640, height = 480;
        break;
        case CAM_1280_RGB:
            width = 1280, height = 720;
        break;
        case CAM_1920_RGB:
            width = 1920, height = 1080;
        break;
        case CAM_NONE: default:
            return CAM_FAILURE;
    }
    
    cvSetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_WIDTH, width);
    cvSetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_HEIGHT, height);
    realwidth = (int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_WIDTH);
    realheight = (int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_HEIGHT);
    
    if (realwidth != width || realheight != height) {
        g_mode = CAM_NONE;
        return CAM_FAILURE;
    }
    
    g_mode = mode;
    return CAM_SUCCESS;
}

CAMMode CAMGetMode (void) {
    return g_mode;
}

int CAMGetFrame (BYTE *buf) {
    if (g_mode != CAM_NONE && g_capture != NULL) {
        IplImage *frame = cvQueryFrame(g_capture);
        if (frame != NULL) {
            //cvShowImage("TEST", frame);
            //cvWaitKey(10);
            memcpy(buf, frame->imageData, frame->imageSize);
            return CAM_SUCCESS;
        }
    }
    return CAM_FAILURE;
}

int CAMRelease (void) {
    if (g_capture) {
        cvReleaseCapture(&g_capture);
        g_capture = NULL;
    }
    g_mode = CAM_NONE;
    return CAM_SUCCESS;
}