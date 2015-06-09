/**
 *  @file camera_rpi2.h
 *  @brief Camera routines for the Raspberry Pi 2, modded for the EyeBot.
 *  These functions are not thread safe.   
 *  @author Jeremy Tan, 20933708 (HEXACOPTER GROUP)
 */

#ifndef _CAMERA_RPI_2_H
#define _CAMERA_RPI_2_H

/** Success code **/
#define CAM_SUCCESS 1
/** Failure code **/
#define CAM_FAILURE 0

typedef unsigned char BYTE;

/**
 * @brief The available camera modes.
 */
typedef enum CAMMode {
    /** Error code for invalid camera format. **/
    CAM_NONE,
    /** 160x120 frame, RGB format **/
    CAM_160_RGB,
    /** 320x240 frame, RGB format **/
    CAM_320_RGB,
    /** 640x480 frame, RGB format **/
    CAM_640_RGB,
    /** 1280x720 frame, RGB format **/
    CAM_1280_RGB,
    /** 1920x1080 frame, RGB format **/
    CAM_1920_RGB
} CAMMode;
 
/**
 *  @brief Initialise the camera. 
 *  
 *  @param [in] mode The mode to set the camera in
 *  @return Nonzero on success, zero on failure.
 *  
 *  @details Establishes the camera functions. This function must be called
 *           before any of the other camera functions.
 */
extern int CAMInit (CAMMode mode);

/**
 *  @brief Set the camera mode (e.g. format and resolution).
 *  
 *  @param [in] mode The camera mode to be set to
 *  @return Nonzero on success, zero on failure.
 *  
 *  @details Sets the camera mode. CAMInit must have been called previously.
 */
extern int CAMSetMode (CAMMode mode);

/**
 *  @brief Retrieves the current camera mode.
 *  
 *  @return The camera mode, or CAM_NONE on error.
 *  
 *  @details CAMInit must have been called previously.
 */
extern CAMMode CAMGetMode (void);

/**
 *  @brief Retrieve a camera frame into the provided buffer.
 *  
 *  @param [in] buf The buffer to copy the camera frame into. The supplied
 *                  buffer must be large enough to acommodate the size of the
 *                  image, as defined by the camera mode.
 *  @return Nonzero on success, zero on failure. On failure, the contents of buf
 *          is undefined.  
 *  
 *  @details Retrieves the current camera frame and copies it into the
 *           supplied buffer. CAMInit must have been called previously.
 */
extern int CAMGet (BYTE *buf);

/**
 *  @brief Stops and releases all camera structures.
 *  
 *  @return Nonzero on success, zero on failure.
 *  
 *  @details Releases all allocated memory and stops video capture.  
 */
extern int CAMRelease (void);

#endif /* _CAMERA_RPI_2_H */