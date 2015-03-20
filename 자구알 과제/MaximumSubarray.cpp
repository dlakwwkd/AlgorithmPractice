#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <windows.h>

struct ArrInfo
{
    ArrInfo(int l, int h, int max)
    : low(l), high(h), maxSum(max){}
    int low;
    int high;
    int maxSum;
};

ArrInfo IterateFindMaximumSubArray(int* arr, int low, int high);
ArrInfo FindMaximumSubArray(int* arr, int low, int high);
ArrInfo FindMaxCrossingSubArray(int* arr, int low, int mid, int high);
void    PrintArr(int* arr, int length, ArrInfo subArr);

int main()
{
    std::vector<std::pair<int*, int>> arrList;
    arrList.reserve(10);

    int* arr0 = nullptr;    // 원소 0개
    int arr1[] = { 1 };     // 원소 1개
    int arr2[] = { 3, 7 };  // 원소 2개
    int arr3[] = { 1, -4, 3, 8 }; // 원소 4개
    int arr4[] =
    {   1, 2, -3, 4, 5,
        -1, -2, -3, -4, -5,
        9, 8, 7, 6, 5,
        -9, -8, -7, -6, -5 }; // 원소 20개

    arrList.push_back(std::pair<int*, int>(arr0, 0));
    arrList.push_back(std::pair<int*, int>(arr1, _countof(arr1)));
    arrList.push_back(std::pair<int*, int>(arr2, _countof(arr2)));
    arrList.push_back(std::pair<int*, int>(arr3, _countof(arr3)));
    arrList.push_back(std::pair<int*, int>(arr4, _countof(arr4)));

    printf("[ n^2 ]\n");
    for (auto& arr : arrList)
    {
        auto arrInfo = IterateFindMaximumSubArray(arr.first, 0, arr.second);
        PrintArr(arr.first, arr.second, arrInfo);
    }
    printf("\n[ nlgn ]\n");
    for (auto& arr : arrList)
    {
        auto arrInfo = FindMaximumSubArray(arr.first, 0, arr.second);
        PrintArr(arr.first, arr.second, arrInfo);
    }
    getchar();
    return 0;
}

ArrInfo IterateFindMaximumSubArray(int* arr, int low, int high)
{
    if (!arr)
        return ArrInfo(0, 0, 0);

    int maxSum = arr[0];
    int maxSumLeft = 0;
    int maxSumRight = 0;
    for (int idx = 0; idx < high; ++idx)
    {
        int curSum = 0;
        for (int i = idx; i < high; ++i)
        {
            curSum += arr[i];
            if (curSum > maxSum)
            {
                maxSum = curSum;
                maxSumLeft = idx;
                maxSumRight = i;
            }
        }
    }
    return ArrInfo(maxSumLeft, maxSumRight, maxSum);
}

ArrInfo FindMaximumSubArray(int* arr, int low, int high)
{
    if (!arr)
        return ArrInfo(0, 0, 0);
    if (high == low)
        return ArrInfo(low, high, arr[low]);

    int mid = low + (high - low) / 2;
    ArrInfo leftArr = FindMaximumSubArray(arr, low, mid);
    ArrInfo rightArr = FindMaximumSubArray(arr, mid + 1, high);
    ArrInfo crossArr = FindMaxCrossingSubArray(arr, low, mid, high);

    if (leftArr.maxSum >= rightArr.maxSum && leftArr.maxSum >= crossArr.maxSum)
        return leftArr;
    else if (rightArr.maxSum >= leftArr.maxSum && rightArr.maxSum >= crossArr.maxSum)
        return rightArr;
    else
        return crossArr;
}

ArrInfo FindMaxCrossingSubArray(int* arr, int low, int mid, int high)
{
    if (!arr)
        return ArrInfo(0, 0, 0);

    int leftSum = INTMAX_MIN;
    int maxLeft = mid;
    int sum = 0;
    for (int i = mid; i >= low; --i)
    {
        sum += arr[i];
        if (sum > leftSum)
        {
            leftSum = sum;
            maxLeft = i;
        }
    }
    int rightSum = INTMAX_MIN;
    int maxRight = mid + 1;
    sum = 0;
    for (int i = mid + 1; i <= high; ++i)
    {
        sum += arr[i];
        if (sum > rightSum)
        {
            rightSum = sum;
            maxRight = i;
        }
    }
    return ArrInfo(maxLeft, maxRight, leftSum + rightSum);
}

void PrintArr(int* arr, int length, ArrInfo subArr)
{
    if (!arr)
        length = 0;

    printf("maxSum : %d \t {", subArr.maxSum);
    for (int i = 0; i < length; ++i)
    {
        if (i == subArr.low)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

        printf("%d", arr[i]);
        
        if (i == subArr.high)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        if (i < length - 1)
            printf(",");
    }
    printf("}\n");
}
