#include <windows.h>
#include <stdio.h>
#include <algorithm>

struct Heap
{
    Heap(int n) : size(n), capacity(n + 1)
    {
        element = new int[capacity];
        ZeroMemory(element, capacity*sizeof(int));
    }
    ~Heap() { delete[] element; }
    void Resize()
    {
        int* temp = new int[capacity * 2];
        ZeroMemory(temp, capacity * 2 * sizeof(int));
        memcpy(temp, element, capacity*sizeof(int));
        delete[] element;
        element = temp;
        capacity *= 2;
    }
    int     size = 0;
    int     capacity = 0;
    int*    element = nullptr;
};

void    BuildMaxHeap(Heap* heap);                   // 실습 3
void    HeapSort(Heap* heap);                       // 실습 4
bool    ExtractMax(Heap* heap, OUT int& maxValue);  // 실습 5
void    IncreaseKey(Heap* heap, int pos, int key);  // 실습 6
void    MaxHeapInsert(Heap* heap, int key);         // 실습 6

void    MaxHeapify(Heap* heap, int pos);
void    TestHeapify();
Heap*   MakeSampleHeap(int n);
bool    IsMaxHeap(Heap* heap, int pos);
void    PrintHeap(Heap* heap);

int main()
{
    TestHeapify();
    getchar();
    return 0;
}

void BuildMaxHeap(Heap* heap) // 실습 3
{
    heap->size = heap->capacity - 1;
    for (int i = heap->size / 2; i > 0; --i)
        MaxHeapify(heap, i);
}

void HeapSort(Heap* heap) // 실습 4
{
    BuildMaxHeap(heap);
    for (int i = heap->size; i > 1; --i)
    {
        int temp = heap->element[1];
        heap->element[1] = heap->element[i];
        heap->element[i] = temp;
        heap->size--;
        MaxHeapify(heap, 1);
    }
    heap->size = heap->capacity - 1;
}

bool ExtractMax(Heap* heap, OUT int& maxValue)  // 실습 5
{
    if (!heap || heap->size < 1)
        return false;

    maxValue = heap->element[1];
    heap->element[1] = heap->element[heap->size];
    heap->size--;
    MaxHeapify(heap, 1);
    return true;
}

void IncreaseKey(Heap* heap, int pos, int key)  // 실습 6
{
    if (!heap || pos > heap->size || key < heap->element[pos])
        return;

    heap->element[pos] = key;
    int parent = pos / 2;
    while (pos > 1 && heap->element[parent] < heap->element[pos])
    {
        int temp = heap->element[pos];
        heap->element[pos] = heap->element[parent];
        heap->element[parent] = temp;
        pos = parent;
        parent /= 2;
    }
}

void MaxHeapInsert(Heap* heap, int key) // 실습 6
{
    if (!heap)
        return;
    if (++heap->size >= heap->capacity)
        heap->Resize();

    heap->element[heap->size] = INT_MIN;
    IncreaseKey(heap, heap->size, key);
    printf("\n InsertValue : %d", key);
}

void MaxHeapify(Heap* heap, int pos)
{
    if (!heap || pos > heap->size)
        return;

    int left = pos * 2;
    int right = left + 1;
    int largest = 0;

    if (left <= heap->size && heap->element[left] > heap->element[pos])
        largest = left;
    else largest = pos;
    if (right <= heap->size && heap->element[right] > heap->element[largest])
        largest = right;

    if (largest != pos)
    {
        int temp = heap->element[pos];
        heap->element[pos] = heap->element[largest];
        heap->element[largest] = temp;
        MaxHeapify(heap, largest);
    }
}

void TestHeapify()
{
    Heap* heap = MakeSampleHeap(20);
    PrintHeap(heap);

    HeapSort(heap);
    PrintHeap(heap);

    BuildMaxHeap(heap);
    int value = 0;
    if (ExtractMax(heap, value))
        printf("\n ExtractValue : %d", value);
    else printf("extract Failed!\n");
    PrintHeap(heap);

    MaxHeapInsert(heap, 30);
    PrintHeap(heap);

    MaxHeapInsert(heap, 0);
    PrintHeap(heap);

    MaxHeapInsert(heap, 15);
    PrintHeap(heap);
    delete heap;
}

Heap* MakeSampleHeap(int n)
{
    Heap* heap = new Heap(n);
    for (int i = 1; i <= n; ++i)
        heap->element[i] = (n + 1) - i;
    return heap;
}

bool IsMaxHeap(Heap* heap, int pos)
{
    if (!heap || pos > heap->size)
        return true;

    int left = pos * 2;
    int right = left + 1;

    if (left <= heap->size && heap->element[left] > heap->element[pos])
        return false;
    if (right <= heap->size && heap->element[right] > heap->element[pos])
        return false;

    return IsMaxHeap(heap, left) && IsMaxHeap(heap, right);
}

void PrintHeap(Heap* heap)
{
    if (!heap)
        return;

    printf("\n Heap size : %d, capacity : %d, ", heap->size, heap->capacity);
    if (IsMaxHeap(heap, 1))
        printf("MaxHeap : Ok \n");
    else
        printf("MaxHeap : No \n");

    int newline = 1;
    int space = 1;
    while (space < heap->size)
        space = space * 2 + 1;
    for (int i = 1; i <= heap->size; ++i)
    {
        for (int j = 0; j < space; ++j)
            printf(" ");

        printf("%2d", heap->element[i]);

        for (int j = 0; j < space; ++j)
            printf(" ");

        if (i == newline)
        {
            newline = newline * 2 + 1;
            space /= 2;
            printf("\n");
        }
    }
    printf("\n");
}



