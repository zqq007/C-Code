#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void printarray(int *a, int sz);

void InsertSort(int *a, int sz);

void ShellSort(int *a, int sz);

// 选择排序
void SelectSort(int *a, int n);

// 堆排序
void AdjustDwon(int *a, int n, int root);
void HeapSort(int *a, int n);

// 冒泡排序
void BubbleSort(int *a, int n);

// 快速排序递归实现
// 快速排序hoare版本
int PartSort1(int *a, int left, int right);
// 快速排序挖坑法
int PartSort2(int *a, int left, int right);
// 快速排序前后指针法
int PartSort3(int *a, int left, int right);
void QuickSort(int *a, int left, int right);

// 快速排序 非递归实现
void QuickSortNonR(int *a, int left, int right);

// 归并排序
void MergeSort(int *a, int n);