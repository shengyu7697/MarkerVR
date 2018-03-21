# MarkerVR
This is a Marker-based Tracking System for VR/AR Applications.  

## Develop Environment
* Linux
* [OpenCV 3.3.1](https://github.com/opencv/opencv/archive/3.3.1.zip)
* [OpenCV's extra modules 3.3.1](https://github.com/opencv/opencv_contrib/archive/3.3.1.zip)

## How to Build

#### Get Source Code
一次全部下載 (包含所有的 submodule)  
```
git clone https://github.com/shengyu7697/MarkerVR.git --recursive
```
or  
分次下載 (先下主程式再下載 submodule)  
```
git clone https://github.com/shengyu7697/MarkerVR.git
cd MarkerVR
git submodule init
git submodule update
```
#### Build
```
cd MarkerVR
./gen_makefile.sh
cd build
make -j8
```
