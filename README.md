# DarkenPDF
Increase the contrast of PDF files before printing,
it works by rasterizing the PDF and applying a contrast/brgihtness filter on top then re-exporting the PDF,
uses Cairo and Poppler

## How to build and use

### Step 1: Install build dependencies
Ubuntu:
```
sudo apt install libpoppler-glib-dev libcairo-dev
```
MSYS2:
```
pacman -S mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-cairo mingw-w64-ucrt-x86_64-poppler
```
Rocky 8 (RHEL 8):
you need power tools repo enabled
```
sudo dnf install cairo-devel poppler-glib-devel libffi-devel
```

### Step 2: Build using CMake
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

### Step3: Darken your PDFs
```
./DarkenPDF mypdf.pdf
```
