#ifndef EXP_CUDA_MATRIXMATH
	#ifndef BUILD_CUDA_MATRIXMATH
		#pragma comment(lib, "cumatrixmath.lib")
		#define EXP_CUDA_MATRIXMATH __declspec(dllimport)
#else
		#define EXP_CUDA_MATRIXMATH __declspec(dllexport)
	#endif
#endif