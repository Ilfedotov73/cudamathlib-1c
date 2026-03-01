#include "test.h"
#include "rust.h"

#include "core.h"

#include "helper.h"

bool MatMul(const long lMethodNum, tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray, IMemoryManager* m_iMemory)
{
	// Получение параметров метода.
	std::string МатрицаА = get_method_param_as_utf8(paParams, 0);
	std::string МатрицаБ = get_method_param_as_utf8(paParams, 1);
	float ШиринаМатрицы = get_method_param_as_number(paParams, 2);

	int msize = ШиринаМатрицы * ШиринаМатрицы; // Размер квадртаной матрицы.

	float* ma = (float*)malloc(msize * sizeof(float)); // Матрица А.
	float* mb = (float*)malloc(msize * sizeof(float)); // Матрица Б.
	float* mmult = (float*)malloc(msize * sizeof(float)); // Выходная матрица.

	// Читаем входные матрицы как строки и заполняем массивы.
	helper::read_input(ma, МатрицаА, msize);
	helper::read_input(mb, МатрицаБ, msize);

	// Вычисляем произведение матрица ma на mb и записываем результат в mmult.
	matrixmath::matmul(mmult, ma, mb, ШиринаМатрицы);

	// Получаем результат mmult в формате строки для вывода.
	std::string mstr = helper::mat_to_str(mmult, msize, ШиринаМатрицы);

	// Преоборазуем в типа utf16.
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
	std::u16string utf16_result = converter.from_bytes(mstr);

	// Возврат значения в 1С.
	set_return_val_for_1c_as_utf16(pvarRetValue, utf16_result, m_iMemory);
	
	return true;
}