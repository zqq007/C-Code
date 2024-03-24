#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>

void printarray(int *arr, int sz)
{
    for (int i = 0; i < sz; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*插入排序*/
void InsertSort(int *a, int sz)
{
    for (int i = 0; i < sz - 1; ++i)
    {
        int index = i;
        int val = a[i + 1];
        while (index >= 0)
        {
            if (a[index] > val)
            {
                a[index + 1] = a[index];
                index--;
            }
            else
                break;
        }
        a[index + 1] = val;
    }
    printarray(a, sz);
}

/*希尔排序*/
void ShellSort(int *a, int sz)
{
    int gap = sz;
    while (gap > 1)
    {
        gap = gap / 3 + 1; // 保证gap不为0
        for (int i = 0; i < sz - gap; ++i)
        {
            int index = i;
            int value = a[i + 1];
            if (a[index] > value)
            {
                while (index >= 0)
                {
                    if (a[index] > value)
                    {
                        a[index + 1] = a[index];
                        --index;
                    }
                    else
                        break;
                }
            }
            a[index + 1] = value;
        }
    }
    printarray(a, sz);
}

void SelectSort(int *a, int n)
{
    int begin = 0, end = n - 1;
    while (begin < end)
    {
        int min_index = begin;
        int max_index = end;
        for (int i = begin; i <= end; ++i)
        {
            if (a[i] > a[max_index])
                max_index = i;
            if (a[i] < a[min_index])
                min_index = i;
        }
        std::swap(a[min_index], a[begin]);
        if (max_index == begin)
            max_index = min_index;
        std::swap(a[max_index], a[end]);
        begin++;
        end--;
    }
    printarray(a, n);
}

void AdjustDwon(int *a, int n, int root)
{
    int child = root * 2 + 1;
    while (child < n)
    {
        if (child + 1 < n && a[child] < a[child + 1])
            child++;
        if (a[child] > a[root])
        {
            std::swap(a[child], a[root]);
            root = child;
            child = root * 2 + 1;
        }
        else
            break;
    }
}

void HeapSort(int *a, int n)
{
    for (int i = (n - 1 - 1) / 2; i >= 0; --i)
    {
        AdjustDwon(a, n, i);
    }
    int end = n - 1;
    while (end > 0)
    {
        std::swap(a[0], a[end]);
        AdjustDwon(a, end, 0);
        end--;
    }
    printarray(a, n);
}

void BubbleSort(int *a, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 1; j < n - i; j++)
        {
            /* code */
            if (a[j] < a[j - 1])
            {
                std::swap(a[j], a[j - 1]);
            }
        }
    }
    printarray(a, n);
}

void testSort()
{
    int a[10] = {8, 4, 1, 2, 7, 5, 3, 6, 9, 10};
    int n = sizeof(a) / sizeof(a[0]);
    // InsertSort(a, n);
    // ShellSort(a, n);
    // SelectSort(a, n);
    // HeapSort(a, n);
    BubbleSort(a, n);
}

int main()
{
    testSort();
    return 0;
}