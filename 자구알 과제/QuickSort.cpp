#include <stdio.h>
#include <vector>
#include <time.h>

#define ARR_NUM_A 32
#define ARR_NUM_B 16
#define MAX_DATA_SIZE 20

int Partition(int* arr, int start, int end);
void QuickSort(int* arr, int start, int end);
void TestPartition();
void TestQuickSort();
bool CheckPartition(int* arr, int size, int pivot);
bool IsSorted(int* arr, int size);
void PrintArr(int* arr, int size);

int main()
{
    srand((unsigned int)time(NULL));
    TestPartition();
    TestQuickSort();
    getchar();
    return 0;
}

int Partition(int* arr, int start, int end)
{
    if (!arr)
        return -1;

    int pivotValue = arr[end];
    int endOfLow = start - 1;

    for (int checkPos = start; checkPos < end; ++checkPos)
    {
        if (arr[checkPos] <= pivotValue)
        {
            int temp = arr[++endOfLow];
            arr[endOfLow] = arr[checkPos];
            arr[checkPos] = temp;
        }
    }
    int temp = arr[++endOfLow];
    arr[endOfLow] = arr[end];
    arr[end] = temp;

    return endOfLow;
}

void QuickSort(int* arr, int start, int end)
{
    if (!arr || start >= end)
        return;

    int middle = Partition(arr, start, end);
    QuickSort(arr, start, middle - 1);
    QuickSort(arr, middle + 1, end);
}

void TestPartition()
{
    std::vector<std::pair<int*, int>> arrList;
    arrList.reserve(ARR_NUM_A + 2);
    
    // 1~32 크기의 배열을 차례로 생성하고 임의의 값 저장
    for (int i = 1; i <= ARR_NUM_A; ++i)
    {
        auto arr = new int[i];
        for (int j = 0; j < i; ++j)
            arr[j] = rand() % MAX_DATA_SIZE;
        arrList.push_back(std::pair<int*, int>(arr, i));
    }

    // 증가순서인 값 저장된 배열 추가
    auto arr = new int[ARR_NUM_A];
    for (int i = 0; i < ARR_NUM_A; ++i)
        arr[i] = i;
    arrList.push_back(std::pair<int*, int>(arr, ARR_NUM_A));

    // 감소순서인 값 저장된 배열 추가
    arr = new int[ARR_NUM_A];
    for (int i = 0; i < ARR_NUM_A; ++i)
        arr[i] = ARR_NUM_A - i;
    arrList.push_back(std::pair<int*, int>(arr, ARR_NUM_A));

    // partition 수행 후 체크
    for (auto& arr : arrList)
    {
        PrintArr(arr.first, arr.second);
        auto pivot = Partition(arr.first, 0, arr.second - 1);
        if (!CheckPartition(arr.first, arr.second, pivot))
            printf("error\n");
        PrintArr(arr.first, arr.second);
    }

    for (auto& arr : arrList)
        delete[] arr.first;
}

void TestQuickSort()
{
    std::vector<std::pair<int*, int>> arrList;
    arrList.reserve(ARR_NUM_B + 2);

    // 1~16 크기의 배열을 차례로 생성하고 임의의 값 저장
    for (int i = 1; i <= ARR_NUM_B; ++i)
    {
        auto arr = new int[i];
        for (int j = 0; j < i; ++j)
            arr[j] = rand() % MAX_DATA_SIZE;
        arrList.push_back(std::pair<int*, int>(arr, i));
    }

    // 증가순서인 값 저장된 배열 추가
    auto arr = new int[ARR_NUM_B];
    for (int i = 0; i < ARR_NUM_B; ++i)
        arr[i] = i;
    arrList.push_back(std::pair<int*, int>(arr, ARR_NUM_B));

    // 감소순서인 값 저장된 배열 추가
    arr = new int[ARR_NUM_B];
    for (int i = 0; i < ARR_NUM_B; ++i)
        arr[i] = ARR_NUM_B - i;
    arrList.push_back(std::pair<int*, int>(arr, ARR_NUM_B));

    // quickSort 수행 후 체크
    for (auto& arr : arrList)
    {
        PrintArr(arr.first, arr.second);
        QuickSort(arr.first, 0, arr.second - 1);
        if (!IsSorted(arr.first, arr.second))
            printf("error\n");
        PrintArr(arr.first, arr.second);
    }

    for (auto& arr : arrList)
        delete[] arr.first;
}

bool CheckPartition(int* arr, int size, int pivot)
{
    if (!arr || pivot < 0)  // 파티션 실패시 pivot이 -1을 받도록 되어있음
        return false;

    int pivotValue = arr[pivot];
    for (int i = 0; i < size; ++i)
    {
        if (i <= pivot)
        {
            if (arr[i] > pivotValue)
                return false;
        }
        else if (arr[i] <= pivotValue)
            return false;
    }
    return true;
}

bool IsSorted(int* arr, int size)
{
    if (!arr)
        size = 0;

    for (int idx = 0; idx < size - 1; ++idx)
    {
        if (arr[idx] > arr[idx + 1])
            return false;
    }
    return true;
}

void PrintArr(int* arr, int size)
{
    if (!arr)
        size = 0;

    printf("{");
    for (int i = 0; i < size; ++i)
    {
        printf("%d", arr[i]);
        if (i < size - 1)
            printf(",");
    }
    printf("}\n");
}

