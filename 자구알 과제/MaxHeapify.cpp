#include <windows.h>
#include <stdio.h>

struct Heap
{
    Heap(int n) : size(n), capacity(n + 1)
    {
        element = new int[n + 1];
        ZeroMemory(element, capacity*sizeof(int));
    }
    ~Heap() { delete[] element; }
    int     size = 0;
    int     capacity = 0;
    int*    element = nullptr;
};

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
    MaxHeapify(heap, 1);
    PrintHeap(heap);
    delete heap;
}

Heap* MakeSampleHeap(int n)
{
    Heap* heap = new Heap(n);
    for (int i = 1; i <= n; ++i)
        heap->element[i] = (n + 2) - i;
    heap->element[1] = 1; // root노드만 maxheap 아니게 설정 (maxheapify 테스트를 위해)
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
