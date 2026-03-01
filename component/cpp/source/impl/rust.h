#pragma once
extern "C" const char* test__call_from_cpp(const char* addr, float f, bool b);
extern "C" const char* MatDet__call_from_cpp(const char* Матрица, float ШиринаМатрцы);
extern "C" const char* MatMul__call_from_cpp(const char* МатрицаА, const char* МатрицаБ, float ШиринаМатрицы);
extern "C" const char* free_mem_after_cpp(const char* ptr);