# Determining the Suitability of Hashing Algorithms for Password Security Using GPU Acceleration 
## - Ross Gray CS408 

This repository holds code that is part of my submission for CS408. The hashing algorithms contained are for research purposes only.
They should not be used for any real world applications, and have not been tested to the level of standard implementations. 
This code has been written and tested in Linux and may not be compatible with windows. The binaries provided are compiled for linux. 
Therefore, it is highly recommended that linux is used to run the binaries or compile the code.

## Navigating the project's directory
All of the code related to the project is stored in the "src" directory. The subdirectories inside each contain a single hashing algorithm implementation. 
the ones containing cuda code have cuda in added to the name of the directory. Inside each of the implementation folders you will find bin folders containing the compiled binaries 
for that specific implementation. 

## Running and compiling code
I have added compiled binaries in the bin folder of each implementation. These should run without any problems on any linux machine, for the regular C++ code.
The cuda implementations require  a NVIDIA GPU to run. The cuda code was developed using a NVIDIA Geforce GTX 2060 super. Any GPU with the same architecture (Turing) should be able to run the compiled binaries without issue. 

### Turing GPUs 
    -GeForce MX450 Laptop
    -GeForce MX550 Laptop
    -GeForce GTX 1630
    -GeForce GTX 1650 Laptop
    -GeForce GTX 1650
    -GeForce GTX 1650 Super
    -GeForce GTX 1650 Ti Laptop
    -GeForce GTX 1660
    -GeForce GTX 1660 Super
    -GeForce GTX 1660 Ti Laptop
    -GeForce GTX 1660 Ti
    -GeForce RTX 2060 Laptop
    -GeForce RTX 2060
    -GeForce RTX 2060 Super
    -GeForce RTX 2070 Laptop
    -GeForce RTX 2070
    -GeForce RTX 2070 Super Laptop
    -GeForce RTX 2070 Super
    -GeForce RTX 2080 Laptop
    -GeForce RTX 2080
    -GeForce RTX 2080 Super Laptop
    -GeForce RTX 2080 Super
    -GeForce RTX 2080 Ti
    -Titan RTX
    -Quadro RTX 3000 Laptop
    -Quadro RTX 4000 Laptop
    -Quadro RTX 4000
    -Quadro RTX 5000 Laptop
    -Quadro RTX 5000
    -Quadro RTX 6000 Laptop
    -Quadro RTX 6000
    -Quadro RTX 8000
    -Quadro T1000 Laptop
    -Quadro T2000 Laptop
    -T400
    -T400 4GB
    -T500 Laptop
    -T600 Laptop
    -T600
    -T1000
    -T1000 8GB
    -T1200 Laptop
    -Tesla T4

Using any of these GPUs to run or compile the code should work without issue.
with other GPUs running the build scripts provided should produce a working binary. 
this can be done by running `bash build.sh` in the terminal when in the implementation's root directory.

**IMPORTANT**
to be able to compile cuda code you must have the cuda drivers installed, your GPUs driver, the cuda development toolkit, and / or nvcc. 
compiling without specifying your architecture can cause issues with code executing on the GPU. 

to specify architecture you would open a bash terminal in the folder of the algorithm you wish to compile and run this command:

```nvcc -gencode arch=compute_<YOUR ARCHITECTURE NUMBER>,code=sm_<YOUR ARCHITECTURE NUMBER> -rdc=true base64.cu BCrypt.cu -o BCrypt```

this example uses the BCrypt cuda project as its compile target

