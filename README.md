# Determining the Suitability of Hashing Algorithms for Password Security Using GPU Acceleration - Ross Gray CS408 

<p>This repository holds code that is part of my submission for CS408. The hashing algorithms contained are for research purposes only.  <br><br>
They should not be used for any real world applications, and have not been tested to the level of standard implementations.  <br><br>
<b>This code has been written and tested in Linux and may not be compatible with windows. The binaries provided are compiled for linux.  <br><br>
Therefore, it is highly recommended that linux is used to run the binaries or compile the code.</b>

<h2> Navigating the project's directory </h2>
<p> All of the code related to the project is stored in the "src" directory. The subdirectories inside each contain a single hashing algorithm implementation.  <br>
the ones containing cuda code have cuda in added to the name of the directory. Inside each of the implementation folders you will find bin folders containing the compiled binaries  <br>
for that specific implementation. </p>

<h2> Running and compiling code </h2>
<p> I have added compiled binaries in the bin folder of each implementation. These should run without any problems on any linux machine, for the regular C++ code. The cuda implementations require  <br>
a NVIDIA GPU to run. The cuda code was developed using a NVIDIA Geforce GTX 2060 super. Any GPU with the same architecture (Turing) should be able to run the compiled binaries without issue.  <br><br>

<h3> Turing GPUs </h3>
    -GeForce MX series
        -GeForce MX450 Laptop
        -GeForce MX550 Laptop
    -GeForce 16 series    GeForce MX series
        -GeForce MX450 Laptop
        -GeForce MX550 Laptop
    -GeForce 16 series
        -GeForce GTX 1630
        -GeForce GTX 1650 Laptop
        -GeForce GTX 1650
        -GeForce GTX 1650 Super
        -GeForce GTX 1650 Ti Laptop
        -GeForce GTX 1660
        -GeForce GTX 1660 Super
        -GeForce GTX 1660 Ti Laptop
        -GeForce GTX 1660 Ti
    -GeForce 20 series
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
    -Nvidia Quadro
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
    -Nvidia Tesla
        -Tesla T4
