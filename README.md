## How to Build

#### Get Source Code
一次全部下載 (包含所有的 submodule)  
```
git clone https://github.com/shengyu7697/ArUcoMarker.git --recursive
```
or  
分次下載 (先下主程式再下載 submodule)  
```
git clone https://github.com/shengyu7697/ArUcoMarker.git
cd ArUcoMarker
git submodule init
git submodule update
```
#### Build
```
cd ArUcoMarker
./gen_makefile.sh
cd build
make -j8
```
