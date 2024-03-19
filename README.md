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
<p> I have added compiled binaries in the bin folder of each implementation. These should run without any problems on any linux machine, for the regular C++ code.  <br> The cuda implementations require  <br>
a NVIDIA GPU to run. The cuda code was developed using a NVIDIA Geforce GTX 2060 super. Any GPU with the same architecture (Turing) should be able to run the compiled binaries without issue.  <br><br>

<h3> Turing GPUs </h3>
<ul>
    <li>GeForce MX450 Laptop</li>
    <li>GeForce MX550 Laptop</li>
    <li>GeForce GTX 1630</li>
    <li>GeForce GTX 1650 Laptop</li>
    <li>GeForce GTX 1650</li>
    <li>GeForce GTX 1650 Super</li>
    <li>GeForce GTX 1650 Ti Laptop</li>
    <li>GeForce GTX 1660</li>
    <li>GeForce GTX 1660 Super</li>
    <li>GeForce GTX 1660 Ti Laptop</li>
    <li>GeForce GTX 1660 Ti</li>
    <li>GeForce RTX 2060 Laptop</li>
    <li>GeForce RTX 2060</li>
    <li>GeForce RTX 2060 Super</li>
    <li>GeForce RTX 2070 Laptop</li>
    <li>GeForce RTX 2070</li>
    <li>GeForce RTX 2070 Super Laptop</li>
    <li>GeForce RTX 2070 Super</li>
    <li>GeForce RTX 2080 Laptop</li>
    <li>GeForce RTX 2080</li>
    <li>GeForce RTX 2080 Super Laptop</li>
    <li>GeForce RTX 2080 Super</li>
    <li>GeForce RTX 2080 Ti</li>
    <li>Titan RTX</li>
    <li>Quadro RTX 3000 Laptop</li>
    <li>Quadro RTX 4000 Laptop</li>
    <li>Quadro RTX 4000</li>
    <li>Quadro RTX 5000 Laptop</li>
    <li>Quadro RTX 5000</li>
    <li>Quadro RTX 6000 Laptop</li>
    <li>Quadro RTX 6000</li>
    <li>Quadro RTX 8000</li>
    <li>Quadro T1000 Laptop</li>
    <li>Quadro T2000 Laptop</li>
    <li>T400</li>
    <li>T400 4GB</li>
    <li>T500 Laptop</li>
    <li>T600 Laptop</li>
    <li>T600</li>
    <li>T1000</li>
    <li>T1000 8GB</li>
    <li>T1200 Laptop</li>
    <li>Tesla T4</li>
</ul>

<p> Using any of these GPUs to run or compile the code should work without issue.  <br><br>
with other GPUs running the build scripts provided should produce a working binary.  <br>
this can be done by running > bash build.sh > in the terminal when in the implementation's root directory.</p.

