#include <stdio.h>
#include <vector>

void InsertionSort(int* arr, int length);
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

    for (auto& arr : arrList)
    {
        InsertionSort(arr.first, arr.second);
    }

    printf("\n[After Sorting] \n");
    for (auto& arr : arrList)
    {
        PrintArr(arr.first, arr.second);
    }

    getchar();
    return 0;
}


void InsertionSort(int* arr, int length)
{
    if (!arr)
        return;

    int idx = 0, subIdx = 0, key = 0;

    for (idx = 1; idx < length; ++idx)
    {
        key = arr[idx];
        subIdx = idx - 1;
        while (subIdx >= 0 && arr[subIdx] > key)
        {
            arr[subIdx + 1] = arr[subIdx];
            --subIdx;
        }
        arr[subIdx + 1] = key;
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

