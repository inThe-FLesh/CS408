nvcc -gencode arch=compute_75,code=sm_75 -rdc=true base64.cu BCrypt.cu -o BCrypt
./BCrypt
