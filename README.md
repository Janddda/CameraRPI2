# CameraRPI2
Camera functions for RPi2 and Eyebot

Instructions:

1. Load the camera driver on startup. Edit `/etc/modules` by appending the line:
  
  ~~~~~
  bcm2835-v4l2
  ~~~~~
  
  Restart the Pi.
2. Ensure that a **standard** installation of OpenCV is installed:

  ~~~~~
  sudo apt-get update
  sudo apt-get upgrade
  sudo apt-get install libopencv-dev
  ~~~~~
  
3. Using gcc directly:
    
  ~~~~~
  gcc -std=c99 -Wall -pedantic `pkg-config --cflags opencv` *.c `pkg-config --libs opencv` -lm -o camtest
  ~~~~~
  
  Using cmake:
  
  ~~~~~
  cmake .
  make
  ~~~~~
4. Testing:

  ~~~~~
  ./camtest
  ~~~~~

## Known issues
There is a bug in the OpenCV library as bundled with raspbian, which causes the function `cvCreateCameraCapture` to return a non-NULL value, even on failure. This means that if the camera is already being used, `CAMInit` will segfault.
