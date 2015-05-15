# CameraRPI2
Camera functions for RPi2 and Eyebot

Instructions:

1. Load the camera driver on startup. Edit `/etc/modules` by appending the line:
  
  ~~~~~
  bcm2835-v4l2
  ~~~~~
  
  Restart the Pi.
2. Using gcc directly:
    
  ~~~~~
  gcc -std=c99 -Wall -pedantic `pkg-config --cflags opencv` *.c `pkg-config --libs opencv` -lm -o camtest
  ~~~~~
  
  Using cmake:
  
  ~~~~~
  cmake .
  make
  ~~~~~
3. Testing:

  ~~~~~
  ./camtest
  ~~~~~
