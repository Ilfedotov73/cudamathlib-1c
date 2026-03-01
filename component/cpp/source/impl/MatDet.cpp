
#include "test.h"
#include "rust.h"

#include "core.h"

#include "helper.h"

bool MatDet(const long lMethodNum, tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray, IMemoryManager* m_iMemory)
{
	//олучение параметров метода
	std::string Матрица = get_method_param_as_utf8(paParams, 0);
	float ШиринаМатрицы = get_method_param_as_number(paParams, 1);

	int msize = ШиринаМатрицы * ШиринаМатрицы;
	float* minp = (float*)malloc(msize * sizeof(float));

	helper::read_input(minp, Матрица, msize);

	float det = matrixmath::matdet(minp, ШиринаМатрицы);

	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
	std::u16string utf16_result = converter.from_bytes(std::to_string(det));

	// Возврат значения
	set_return_val_for_1c_as_utf16(pvarRetValue, utf16_result, m_iMemory);
	
	return true;
}