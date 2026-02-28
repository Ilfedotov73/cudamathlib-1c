#pragma once

#define BUILD_CUDA_MATRIXMATH
#include "exportlib.h"

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <string>

namespace matrixmath {
	__global__ void cudaMatMul(float* dev_result, float* dev_a, const float* dev_b, int width);
	EXP_CUDA_MATRIXMATH void matmul(float* result, const float* a, const float* b, int width);

	__global__ void cudaMatDet(float* dev_result, float* dev_mat, int width, int sarrusmatsize);
	EXP_CUDA_MATRIXMATH float matdet(const float* mat, int width);
}