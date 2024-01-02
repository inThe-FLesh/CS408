nvcc sha256Cuda.cu computation.cu preprocessing.cu -arch=compute_75 -code=sm_75 -o main --expt-relaxed-constexpr
./main
