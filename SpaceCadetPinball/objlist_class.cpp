#include  "pch.h""
#include "objlist_class.h"
#include <cstdlib>
// v1 from Ida

objlist_class::objlist_class(int SizeInt, int growSize)
{
	ListPtr = objlist_new(SizeInt);
	GrowSize = growSize;
}

objlist_class::~objlist_class()
{
	if (ListPtr)
		free(ListPtr);
}

void objlist_class::Add(void* value)
{
	if (this->ListPtr->Count == this->ListPtr->Size)
		Grow();
	objlist_add_object(ListPtr, (int)value);
}

void objlist_class::Grow()
{
	this->ListPtr = objlist_grow(this->ListPtr, this->GrowSize);
}

int objlist_class::Delete(int value)
{
	return objlist_delete_object(ListPtr, value);
}


objlist_struct1* objlist_class::objlist_new(int sizeInt)
{
	objlist_struct1* result = (objlist_struct1 *)malloc(4 * sizeInt + 12);
	if (!result)
		return result;
	result->Count = 0;
	result->Size = sizeInt;
	return result;
}

int objlist_class::objlist_add_object(objlist_struct1* ptrToStruct, int value)
{
	int addIndex = ptrToStruct->Count;
	if (addIndex >= ptrToStruct->Size)
		return 0;
	ptrToStruct->Array[addIndex] = value;
	return ++ptrToStruct->Count;
}

objlist_struct1* objlist_class::objlist_grow(objlist_struct1* ptrToStruct, int growSize)
{
	objlist_struct1* resultPtr = ptrToStruct;
	if (!ptrToStruct)
		return resultPtr;
	int newSizeInt = growSize + ptrToStruct->Count;
	if (newSizeInt <= ptrToStruct->Size)
		return resultPtr;
	objlist_struct1* resultPtr2 = (objlist_struct1 *)realloc(ptrToStruct, 4 * newSizeInt + 12);
	if (!resultPtr2)
		return resultPtr;
	resultPtr = resultPtr2;
	resultPtr2->Size = growSize + resultPtr2->Count;
	return resultPtr;
}

int objlist_class::objlist_delete_object(objlist_struct1* ptrToStruct, int value)
{
	int count = ptrToStruct->Count;
	int index = count - 1;
	if (count - 1 < 0)
		return 0;
	for (int* i = &ptrToStruct->Array[index]; *i != value; --i)
	{
		if (--index < 0)
			return 0;
	}
	//ptrToStruct->Array[index] = *(&ptrToStruct->Count + count);
	ptrToStruct->Array[index] = ptrToStruct->Array[count - 1];
	--ptrToStruct->Count;
	return 1;
}
