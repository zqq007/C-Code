#include "sort.hpp"

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
    // printarray(a, sz);
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

static int getMid(int *a, int begin, int end)
{
    int mid = abs(end - begin) / 2 + begin;
    if (a[begin] < a[mid])
    {
        if (a[mid] < a[end])
        {
            return mid;
        }
        else if (a[end] < a[begin])
        {
            return begin;
        }
        else
        {
            return end;
        }
    }
    else
    {
        if (a[mid] > a[end])
        {
            return mid;
        }
        else if (a[begin] < a[end])
        {
            return begin;
        }
        else
        {
            return end;
        }
    }

    return mid;
}

int PartSort1(int *a, int left, int right)
{
    int mid = getMid(a, left, right);
    std::swap(a[left], a[mid]);

    int begin = left;
    int end = right;
    int key = begin;
    while (begin < end)
    {
        while (begin < end && a[end] >= a[key])
            --end;
        while (begin < end && a[begin] <= a[key])
            ++begin;

        std::swap(a[begin], a[end]);
    }
    std::swap(a[begin], a[key]);
    key = begin;

    return key;
}

int PartSort2(int *a, int left, int right)
{
    int mid = getMid(a, left, right);
    std::swap(a[left], a[mid]);

    int begin = left;
    int end = right;
    int key = a[begin];
    int hole = begin;
    while (begin < end)
    {
        while (begin < end && a[end] >= key)
            --end;
        std::swap(a[hole], a[end]);
        hole = end;
        while (begin < end && a[begin] <= key)
            ++begin;
        std::swap(a[begin], a[hole]);
        hole = begin;
    }
    a[hole] = key;
    return hole;
}

int PartSort3(int *a, int left, int right)
{
    int key = left;
    int pre = left;
    int cur = left + 1;
    while (cur < right)
    {
        while (cur < right && a[cur] < a[key])
        {
            ++pre;
            std::swap(a[pre], a[cur]);
        }
        ++cur;
    }
    std::swap(a[pre], a[key]);
    key = pre;
    return key;
}

void QuickSort(int *a, int left, int right)
{
    if (left >= right)
        return;

    // if less data is inserted,use insertion sort direclty
    if (right - left + 1 < 15)
    {
        InsertSort(a + left, right - left + 1);
        return;
    }
    else
    {
        // int key = PartSort1(a, left, right);
        // int key = PartSort2(a, left, right);
        int key = PartSort3(a, left, right);
        QuickSort(a, left, key - 1);
        QuickSort(a, key + 1, right);
        // printarray(a, right - left + 1);
    }
}

void QuickSortNonR(int *a, int left, int right)
{
    std::stack<int> st;
    st.push(right);
    st.push(left);

    while (!st.empty())
    {
        int begin = st.top();
        st.pop();

        int end = st.top();
        st.pop();

        int mid = PartSort2(a, begin, end);

        if (mid < end)
        {
            st.push(end);
            st.push(mid + 1);
        }
        if (begin < mid)
        {
            st.push(mid - 1);
            st.push(begin);
        }
    }
}

static void mergeSortHelper(int *a, int left, int right, int mid)
{
    int *arr = new int[right - left + 1];
    int cnt = left;
    while (cnt <= right)
    {
        arr[cnt] = a[cnt];
        cnt++;
    }
    int left_index = left;
    int right_index = mid + 1;
    int pos = left;

    while (left_index <= mid && right_index <= right)
    {
        if (a[left_index] < a[right_index])
            arr[pos++] = a[left_index++];
        else
            arr[pos++] = a[right_index++];
    }

    while (left_index <= mid)
        arr[pos++] = a[left_index++];
    while (right_index <= right)
        arr[pos++] = a[right_index++];

    int begin = left;
    while (begin <= right)
    {
        a[begin] = arr[begin];
        begin++;
    }
    delete[] arr;
    arr = nullptr;
}

static void mergeSort(int *a, int left, int right)
{
    if (left < right)
    {
        int mid = (right - left) / 2 + left;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        mergeSortHelper(a, left, right, mid);
    }
}

void MergeSort(int *a, int n)
{
    mergeSort(a, 0, n - 1);
}

void testSort()
{
    // #define RANDOM_NUM // Run the sorting algorithm with random values
#define CERTAIN_NUM // Run the sorting algorithm with certain values

#ifdef RANDOM_NUM
    srand(time(nullptr));

    int cnt = rand() % 20 + 1; // guaranteed greater than one
    // int cnt = 20;
    int n = cnt;
    int i = 0;
    int *a = new int[cnt];
    while (cnt--)
    {
        *(a + i) = rand() % 100;
        i++;
    }
#endif

#ifdef CERTAIN_NUM
    int a[] = {83, 63, 17, 51, 77, 9, 17, 58, 61, 32, 92, 51, 97, 86, 63, 53, 98, 14};
    int n = sizeof(a) / sizeof(a[0]);
#endif
    printf("before sorting:");
    printarray(a, n);
    printf("after sorting:");
    // int a[10] = {8, 4, 1, 2, 7, 5, 3, 6, 9, 10};
    // int n = sizeof(a) / sizeof(a[0]);
    // InsertSort(a, n);
    // ShellSort(a, n);
    // SelectSort(a, n);
    // HeapSort(a, n);
    // BubbleSort(a, n);
    // QuickSort(a, 0, n - 1);
    // QuickSortNonR(a, 0, n - 1);
    // QuickSortNonR(a, 0, n - 1);
    MergeSort(a, n);
    printarray(a, n);
#ifdef RANDOM_NUM
    delete[] a;
    a = nullptr;
#endif
}

int main()
{
    testSort();
    return 0;
}