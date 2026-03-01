#include "../include/core.h"

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>

typedef unsigned int uint32;

__global__ void cudaMatMul(float* dev_result, float* dev_a, const float* dev_b, int width)
{
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int col = blockIdx.x * blockDim.x + threadIdx.x;

	if (row < width && col < width) {
		float sum = 0.0f;
		for (int i = 0; i < width; ++i) {
			sum += dev_a[row * width + i] * dev_b[i * width + col];
		}
		dev_result[row * width + col] = sum;
	}
}

EXP_CUDA_MATRIXMATH void matrixmath::matmul(float* result, const float* a, const float* b, int width)
{
	uint32 size = width * width * sizeof(float);

	float* dev_a = 0;
	float* dev_b = 0;
	float* dev_result = 0;

	cudaMalloc((void**)&dev_a, size);
	cudaMalloc((void**)&dev_b, size);
	cudaMalloc((void**)&dev_result, size);

	cudaMemcpy(dev_a, a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, size, cudaMemcpyHostToDevice);

	uint32 th = 32;
	uint32 bl = (width + th - 1) / th;

	dim3 threads(th, th);
	dim3 blocks(bl, bl);

	cudaMatMul<<<blocks, threads>>>(dev_result, dev_a, dev_b, width);
	cudaDeviceSynchronize();

	cudaMemcpy(result, dev_result, size, cudaMemcpyDeviceToHost);

	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_result);

	cudaDeviceReset();
}

__global__ void cudaMatDet(float* dev_result, float* dev_mat, int width, int sarrusmatsize)
{
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int col = blockIdx.x * blockDim.x + threadIdx.x;

	if (row < width && col < width) {
		int idx = row * (2 * width - 1) + col;
		int step;

		float mult = dev_mat[idx];
		if (row == 0) {
			step = 2 * width;
			idx += step;
			for (int i = 1; i < width && idx < sarrusmatsize; ++i) {
				mult *= dev_mat[idx];
				idx += step;
			}
			dev_result[col] = mult;
		}
		else if (row == width - 1) {
			step = (2 * width - 2);
			idx -= step;
			for (int i = row - 1; i >= 0 && idx >= 0; --i) {
				mult *= dev_mat[idx];
				idx -= step;
			}
			dev_result[col + width] = mult;
		}
	}
}

EXP_CUDA_MATRIXMATH float matrixmath::matdet(const float* mat, int width)
{
	uint32 sarrusmatsize = (width * width) + (width * width - width);

	float* dev_mat = 0;
	float* dev_result = 0;

	cudaMalloc((void**)&dev_mat, sarrusmatsize * sizeof(float));
	cudaMallocManaged((void**)&dev_result, 2 * width * sizeof(float));

	cudaMemcpy(dev_mat, mat, sarrusmatsize * sizeof(float), cudaMemcpyHostToDevice);

	uint32 th = 32;
	uint32 bl = (width + th - 1) / th;

	dim3 threads(th, th);
	dim3 blocks(bl, bl);

	cudaMatDet<<<blocks, threads>>>(dev_result, dev_mat, width, sarrusmatsize);
	cudaDeviceSynchronize();

	float det = 0.0f;
	for (int i = 0, s = 2 * width; i < s; ++i) {
		if (i >= width) { det += dev_result[i] * -1; }
		else { det += dev_result[i]; }
	}

	cudaFree(dev_mat);
	cudaFree(dev_result);

	cudaDeviceReset();
	return det;
}