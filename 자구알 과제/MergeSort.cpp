#include <stdio.h>
#include <stdint.h>
#include <vector>

void MergeSort(int *arr, int *bufferArr, int begin, int last);
void Merge(int *arr, int *bufferArr, int firstBegin, int firstLast, int secondLast);
void CopyBlock(int* begin, int* last, int* buff);
bool IsSorted(int* arr, int length);
void PrintArr(int* arr, int length);

int main()
{
    std::vector<std::pair<int*, int>> arrList;
    arrList.reserve(10);

    int* arr0 = nullptr;                        // 원소 0개
    int arr1[] = { 1 };                         // 원소 1개
    int arr2[] = { 7, 3 };                      // 원소 2개
    int arr3[] = { 1, 2, 3, 4, 5 };             // 증가순
    int arr4[] = { 5, 4, 3, 2, 1 };             // 감소순
    int arr5[] = { 2, 4, 7, 5, 8, 0 };          // 랜덤
    int arr6[] = { 3, 3, 3, 3, 3, 3 };          // 동일한 숫자
    int arr7[] = { 3, 6, 5, 8, 3, 3, 9, 0 };    // 랜덤 & 동일한 숫자
    int arr8[20];                               // 원소 20개
    for (int i = 0; i < 20; ++i)
    {
        arr8[i] = 20 - i;
    }
    arrList.push_back(std::pair<int*, int>(arr0, 0));
    arrList.push_back(std::pair<int*, int>(arr1, _countof(arr1)));
    arrList.push_back(std::pair<int*, int>(arr2, _countof(arr2)));
    arrList.push_back(std::pair<int*, int>(arr3, _countof(arr3)));
    arrList.push_back(std::pair<int*, int>(arr4, _countof(arr4)));
    arrList.push_back(std::pair<int*, int>(arr5, _countof(arr5)));
    arrList.push_back(std::pair<int*, int>(arr6, _countof(arr6)));
    arrList.push_back(std::pair<int*, int>(arr7, _countof(arr7)));
    arrList.push_back(std::pair<int*, int>(arr8, _countof(arr8)));


    printf("[Before Sorting] \n");
    for (auto& arr : arrList)
    {
        PrintArr(arr.first, arr.second);
    }

    int buff[256] = { 0, };
    for (auto& arr : arrList)
    {
        MergeSort(arr.first, buff, 0, arr.second - 1);
    }
    memset(buff, 0, 256);

    printf("\n[After Sorting] \n");
    for (auto& arr : arrList)
    {
        PrintArr(arr.first, arr.second);
    }

    getchar();
    return 0;
}


void MergeSort(int *arr, int *bufferArr, int begin, int last)
{
    if (!arr || !bufferArr)
        return;

    if (begin < last)
    {
        int middle = begin + (last - begin) / 2;
        MergeSort(arr, bufferArr, begin, middle);
        MergeSort(arr, bufferArr, middle + 1, last);
        Merge(arr, bufferArr, begin, middle, last);
    }
}

void Merge(int *arr, int *bufferArr, int firstBegin, int firstLast, int secondLast)
{
    if (!arr || !bufferArr)
        return;

    int idx = 0, arr1Idx = 0, arr2Idx = 0;

    CopyBlock(arr + firstBegin, arr + secondLast + 1, bufferArr + firstBegin);

    arr1Idx = firstBegin;
    arr2Idx = firstLast + 1;

    for (idx = firstBegin; idx <= secondLast; ++idx)
    {
        if (arr1Idx > firstLast)
            arr[idx] = bufferArr[arr2Idx++];
        else if (arr2Idx > secondLast)
            arr[idx] = bufferArr[arr1Idx++];
        else if (bufferArr[arr1Idx] < bufferArr[arr2Idx])
            arr[idx] = bufferArr[arr1Idx++];
        else
            arr[idx] = bufferArr[arr2Idx++];
    }
}

void CopyBlock(int* begin, int* last, int* buff)
{
    if (!begin || !last || !buff)
        return;

    while (begin <= last)
    {
        *buff = *begin;
        buff++;
        begin++;
    }
}

bool IsSorted(int* arr, int length)
{
    if (!arr)
        length = 0;

    for (int idx = 0; idx < length - 1; ++idx)
    {
        if (arr[idx] > arr[idx + 1])
            return false;
    }
    return true;
}

void PrintArr(int* arr, int length)
{
    if (!arr)
        length = 0;

    if (IsSorted(arr, length))
        printf("Sort O : ");
    else
        printf("Sort X : ");

    printf("{");
    for (int i = 0; i < length; ++i)
    {
        printf("%d", arr[i]);
        if (i < length - 1)
            printf(",");
    }
    printf("}\n");
}
