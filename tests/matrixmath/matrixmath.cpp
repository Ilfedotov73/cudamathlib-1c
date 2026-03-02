#include <iostream>

#include "assert.h"
#include "core.h"

#define WIDTH 4
#define N 16

void test1();
void test2();

int main()
{
	std::cerr << "Start of testing the matrixmath base on CUDA." << '\n';
	test1();
	test2();
}

void print_info(float* mat)
{
	for (int i = 0; i < N; ++i) {
		if (((i + 1) / WIDTH) > 8) {
			std::cerr << "..." << '\n';
			std::cerr << "Look at the input file." << '\n';
		}
		std::cerr << mat[i] << ' ';
		if ((i + 1) % WIDTH == 0) { std::cout << '\n'; }
	}
	std::cerr << '\n';
}

void test2()
{
	std::cerr << "Test2: the matrixmath::matdet(...) function:" << '\n';

	float mat[N] = { 1.0, -2.0, -3.0, 4.0,
					 5.0, 6.0, 7.0, 8.0,
					 0.0, 1.0, -1.0, -2.0,
					 0.0, 4.0, 0.0, 4.0 };

	std::cerr << "The input matrix:" << '\n';
	print_info(mat);

	float det = matrixmath::matdet(mat, WIDTH);
	std::cout << det << '\n';

	assert(det == -376);
	std::cerr << "TEST COMPLETED" << '\n';
}

void test1()
{
	std::cerr << "Test1: the matrixmath::matmul(...) function:" << '\n';

	float m_a[N] = { 2.0, 2.0, 2.0, 2.0,
					 3.0, 3.0, 3.0, 3.0,
					 4.0, 4.0, 4.0, 4.0,
					 0.0, 0.0, 0.0, 0.0 };

	std::cerr << "The input matrix A:" << '\n';
	print_info(m_a);

	float m_b[N] = { 1.0, -2.0, -3.0, 4.0,
					 5.0, 6.0, 7.0, 8.0,
					 0.0, 1.0, -1.0, -2.0,
					 0.0, 4.0, 0.0, 4.0 };

	std::cerr << "The input matrix B:" << '\n';
	print_info(m_b);

	float m_c_test[N] = { 12.0, 18.0, 6.0, 28.0,
						  18.0, 27.0, 9.0, 42.0,
						  24.0, 36.0, 12.0, 56.0,
						  0.0, 0.0, 0.0, 0.0 };

	std::cerr << "The answer:" << '\n';
	print_info(m_c_test);

	float m_c[N];
	matrixmath::matmul(m_c, m_a, m_b, WIDTH);

	for (int i = 0; i < N; ++i) {
		std::cout << m_c[i] << ' ';
		if ((i + 1) % WIDTH == 0) { std::cout << '\n'; }
		assert(m_c[i] == m_c_test[i]);
	}
	std::cerr << "TEST COMPLETED" << '\n';
}