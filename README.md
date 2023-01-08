How to build and use

Step 1: Install build dependencies
```
sudo apt install libpoppler-glib-dev libcairo-dev
```

Step 2: Build using CMake
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

Step3: Darken your PDFs
```
./DarkenPDF mypdf.pdf
```
