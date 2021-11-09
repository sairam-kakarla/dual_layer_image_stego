# DILS
Parallel Dual Layer Image Steganography for pgm images.
# Developers
  - [Lakshmi Sairam Kakarla](https://github.com/sairam-kakarla)
  - [K Uday](https://github.com/udayreddy-ux)
  - [Maddukuri Nivas](https://github.com/Nani54325)
# Source Code
 - ```src/read_pgm.c``` Contains functions to load the grayscale values from pgm file into memory.
 - ```src/write_pgm.c``` Contains functions to create a pgm file from grascale values in memory.
 - ```src/encode_in_pgm.c``` Contains functions of implementing parallel encoding.
 - ```src/decode_from_pgm.c```
 - ```src/PGM.h``` Header file for project.
 - ```src/bit_operations.c``` Contains functions to extract bit information and to generate random secret for testing.

# Tasks
- [x] I/O of PGM Files.  
      -> Read pixel array from PGM Images.  
      -> Write pixel array to PGM Images.   
- [x] Serial Encode.  
      -> Layer One Generation.  
      -> Intermediate Layer Generation.  
      -> Final Layer Generation.
- [ ] Serial Decode.
- [ ] Parallel Encode.
- [ ] Parallel Decode.
- [ ] Benchmark.

# Execution
**Requires GCC Compiler**
**Requires openmp**
-```sudo apt install libomp-dev``` for installing openMp.
- clone the repo in working directory
- ```cd dual_layer_image_stego``` to change to the project directory.
- ```cd src```  to change to the source code directory.
- ```make``` to make the application
- ```./main``` to run the application
