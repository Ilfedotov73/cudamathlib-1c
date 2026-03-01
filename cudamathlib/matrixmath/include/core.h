#pragma once

#define BUILD_CUDA_MATRIXMATH
#include "exportlib.h"

#include <string>

namespace matrixmath {
	EXP_CUDA_MATRIXMATH void matmul(float* result, const float* a, const float* b, int width);
	EXP_CUDA_MATRIXMATH float matdet(const float* mat, int width);
}