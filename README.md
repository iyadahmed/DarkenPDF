# DarkenPDF
Increase the contrast of PDF files before printing,
it works by rasterizing the PDF and applying a contrast/brgihtness filter on top then re-exporting the PDF,
uses Cairo and Poppler

based on:  
* Rendering PDF to Cairo image surface: https://www.cairographics.org/cookbook/renderpdf/  
* Creating PDF from Cairo image surface: http://umencs.blogspot.com/2013/04/creating-pdf-in-cc-using-cairo-graphics.html

## How to build and use

### Step 1: Install build dependencies
**For Rocky 8 and Ubuntu you need to install Qt6 from the [online installer](https://www.qt.io/download-qt-installer)**

- Ubuntu:
    ```
    sudo apt install libpoppler-glib-dev libcairo-dev
    ```

- Rocky 8 (RHEL 8):
you need power tools repo enabled
    ```
    sudo dnf install cairo-devel poppler-glib-devel libffi-devel
    ```

- MSYS2:
    - UCRT:
        ```
        pacman -S --needed mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-cairo mingw-w64-ucrt-x86_64-poppler mingw-w64-ucrt-x86_64-qt-creator
        ```
    - MINGW64
        ```
        pacman -S --needed mingw-w64-x86_64-cmake mingw-w64-x86_64-cairo mingw-w64-x86_64-poppler mingw-w64-x86_64-qt-creator
        ```



### Step 2: Build using CMake
```sh
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build -j ${nproc}
```

### Step3: Darken your PDFs
Use CLI:
```
./DarkenPDF mypdf.pdf
```
or run GUI:
```
./DarkenPDF_GUI
```
