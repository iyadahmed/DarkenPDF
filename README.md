# How to build and use

## Step 1: Install build dependencies
Ubuntu:
```
sudo apt install libpoppler-glib-dev libcairo-dev
```
MSYS2:
```
pacman -S mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-cairo mingw-w64-ucrt-x86_64-poppler
```

## Step 2: Build using CMake
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

## Step3: Darken your PDFs
```
./DarkenPDF mypdf.pdf
```
