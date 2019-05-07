#pragma once

#include <stdio.h>
//打印函数
void PrintArray(int array[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}
//交换函数
void Swap(int array[], int i, int j) {
	int t = array[i];
	array[i] = array[j];
	array[j] = t;
}

/*
时间复杂度:
	最好		O(n）			有序
	平均		O(n^2)
	最坏		O(n^2)			逆序
空间复杂度:
	O(1)
稳定性: 稳定
*/
//插入排序
//取一个i，从头开始遍历，找到第一个比i大的数下标记为j，然后将i拷贝出，把从第一个大的开始
//一直到i-1都向后移动一个单位（i会被i-1覆盖），然后将i放到之前j的位置
//从j开始往后再次遍历
void InsertSort(int array[], int size) {
	// 一次处理一个数，所以需要循环 size 次
	// 严格意义上， size - 1 次就够了
	// 有序 [0, i - 1]
	// 要处理 [i]
	// 无序 [i + 1, size - 1]
	for (int i = 0; i < size; i++) {
		// 遍历整个有序区间 [0, i - 1]
		// 向前查找合适的位置（比i大的第一数）
		int j;
		for (j = i - 1; j >= 0 && array[j] > array[i]; j--) 
		{
		}
		//此时j+1才是第一个大的数，并非j

		if (j + 1 != i) {
			int key = array[i];//将第i个数备份
			for (int k = i; k > j + 1; k--) {
				//从后向前复制，将前一个数复制给后一个
				array[k] = array[k - 1];
			}
			array[j + 1] = key;//将key插入到原先j所在位置后
		}
	}
}
//插入排序
void InsertSort2(int array[], int size) {
	for (int i = 0; i < size; i++) {
		int key = array[i];
		int j;
		for (j = i - 1; j >= 0 && array[j] > key; j--) {
			array[j + 1] = array[j];
		}

		array[j + 1] = key;
	}
}

/*
时间复杂度:
	最好	O(n)
	平均	O(n^1.2-1.3)
	最坏	O(n^2)		减少最坏情况出现的概率
空间复杂度:
	O(1)
稳定性: 不稳定
*/


//希尔排序（分组插排），原理见csdn收藏，了解原理即可
void InsertSortWithGap(int array[], int size, int gap) {
	for (int i = 0; i < size; i++) {
		int key = array[i];
		int j;
		for (j = i - gap; j >= 0 && array[j] > key; j -= gap) {
			array[j + gap] = array[j];
		}

		array[j + gap] = key;
	}
}
void ShellSort(int array[], int size) {
	int gap = size;//gap为每次的步长
	while (1) {
		gap = gap / 3 + 1;
		// gap = gap / 2;

		InsertSortWithGap(array, size, gap);
		if (gap == 1) {
			break;
		}
	}
}


// 选择排序
// 1. 直接选择
/*
时间复杂度:	数据不敏感		O(n^2)
空间复杂度: O(1)
稳定性: 不稳定
*/
void SelectSort(int array[], int size) {//寻找最大的放最后，再找其次放最后
	for (int i = 0; i < size; i++) {
		// 有序 [size - i, size - 1]
		// 无序 [0, size - 1 - i]
		int maxIdx = 0;//最大值变量初始化
		// 要查找整个无序区间的最大值的下标
		for (int j = 0; j <= size - 1 - i; j++) {//寻找区间依次减小1
			if (array[j] >= array[maxIdx]) {//从头开始遍历当前查找区间寻找当前区间最大值
				maxIdx = j;//并记录当前区间最大值的下标
			}
		}
		// maxIdx 记录着无序区间部分最大的数的下标
		// 和无序区间的最后一个位置的数进行交换
		Swap(array, maxIdx, size - 1 - i);//将这个最大值放在它当前寻找区间的最后
	}
}

// 2. 堆排序
// 时间复杂度 数据不敏感 O(n * log(n))
// 空间复杂度 O(1)
// 稳定性: 不稳定
void Heapify(int array[], int size, int index) {//此处建大堆
//向下调整
	/*
	1. 判断是不是叶子
	2. 找到最大的孩子
		1) 没有右孩子
		2) 右孩子
			1) 左孩子大
			2) 右孩子大
	3. 最大的孩子和根比较，如果根比较大，退出
	4. 交换并且继续调整
	*/
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	if (left >= size) { return; }
	int max = left;
	if (right < size && array[right] > array[left]) {
		max = right;
	}
	if (array[index] >= array[max]) {
		return;
	}

	Swap(array, max, index);

	Heapify(array, size, max);
}

void CreateHeap(int array[], int size) {
	// 从最后一个非叶子结点，一直到 0，不断的向下调整
	for (int i = (size - 2) / 2; i >= 0; i--) {
		Heapify(array, size, i);
	}
}
void HeapSort(int array[], int size) {
	// 建大堆
	CreateHeap(array, size);

	// 一次处理一个数
	// 无序 [0, size - 1 - i]
	// 有序 [size - i, size - 1]
	for (int i = 0; i < size; i++) {
		// 交换最大的数和无序区间的最后一个数
		Swap(array, 0, size - 1 - i);
		// 堆的性质被破坏了
		// 只有根的地方
		// 要调整的是剩余无序部分的长度 size - 1 - i
		Heapify(array, size - 1 - i, 0);
	}
}

/*
时间复杂度:
最好: O(n)
平均: O(n^2)
最坏: O(n^2)
空间复杂度: O(1)
稳定性: 稳定
*/
void BubbleSort(int array[], int size) {
	for (int i = 0; i < size; i++) {
		int isSorted = 1;
		// 有序 [size - i, size - 1]
		// 无序 [0, size - 1 - i]
		for (int j = 0; j < size - 1 - i; j++) {
			if (array[j] > array[j + 1]) {
				Swap(array, j, j + 1);
				isSorted = 0;
			}
		}

		if (isSorted == 1) {
			break;
		}
	}
}


#include <stdlib.h>
/*
完全有序
完全逆序
完全随机
完全相等
*/
int * CreateSorted(int size) {
	int *array = (int *)malloc(sizeof(int)* size);
	for (int i = 0; i < size; i++) {
		array[i] = i;
	}

	return array;
}

int * CreateReverse(int size) {
	int *array = (int *)malloc(sizeof(int)* size);
	for (int i = 0; i < size; i++) {
		array[i] = size - i;
	}

	return array;
}

int * CreateRandom(int size) {
	int *array = (int *)malloc(sizeof(int)* size);
	for (int i = 0; i < size; i++) {
		array[i] = rand() % size;
	}

	return array;
}

int * CreateEqual(int size) {
	int *array = (int *)malloc(sizeof(int)* size);
	for (int i = 0; i < size; i++) {
		array[i] = size;
	}

	return array;
}

typedef int *(*CreateFunc)(int);
typedef void(*SortFunc)(int *, int);
#include "高精度计时.h"

void TestSpeed() {
	char * createNames[] = {
		"有序",
		"逆序",
		"随机",
		"相等"
	};
	CreateFunc funcs[] = {
		CreateSorted,
		CreateReverse,
		CreateRandom,
		CreateEqual
	};

	char * sortNames[] = {
		"插入排序",
		"选择排序",
		"冒泡排序",
		"希尔排序",
		"  堆排序"
	};

	SortFunc sortFuncs[] = {
		InsertSort2,
		SelectSort,
		BubbleSort,
		ShellSort,
		HeapSort
	};

	高精度计时	计时器;
	for (int i = 0; i < sizeof(funcs) / sizeof(CreateFunc); i++) {
		char * createName = createNames[i];
		CreateFunc	createFunc = funcs[i];
		for (int j = 0; j < sizeof(sortFuncs) / sizeof(SortFunc); j++) {
			SortFunc sortFunc = sortFuncs[j];
			char * name = sortNames[j];

			for (int k = 1; k < 20; k++) {
				int size = k * 5000;
				int *array = createFunc(size);
				计时器.开始();
				sortFunc(array, size);
				计时器.结束();
				free(array);

				printf("[%s] [%s] 数据量: %02d 千: 耗时: %.4f 毫秒\n", name, createName, size / 1000, 计时器.间隔毫秒());
			}
	
		}
	}
}


void InsertSortBS(int array[], int size) {
	for (int i = 0; i < size; i++) {
		// 有序 [0, i - 1] 有序
		// 无序 [i, size - 1] 无序

		int left = 0;
		int right = i - 1;
		// [left, right] 左闭右闭
		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (array[mid] == array[i]) {
				left = mid + 1;
			}
			else if (array[mid] < array[i]) {
				left = mid + 1;
			}
			else {
				right = mid - 1;
			}
		}
		// left 是要插入的位置的下标
		int key = array[i];
		for (int k = i; k > left; k--) {
			array[k] = array[k - 1];
		}

		array[left] = key;
	}
}


void SelectSortOP(int array[], int size) {
	int begin = 0;
	int end = size - 1;
	// [0, begin - 1]	有序 最小的数
	// [begin, end]		无序 
	// [end + 1, size - 1] 有序 最大的数
	while (begin <= end) {
		int min = begin;
		int max = begin;
		for (int i = begin; i <= end; i++) {
			if (array[i] > array[max]) {
				max = i;
			}

			if (array[i] < array[min]) {
				min = i;
			}
		}

		// 最小的数放到无序区间的最开始
		// 最大的数放到无序区间的最末尾
		Swap(array, min, begin);
		if (max == begin) {
			max = min;
		}
		Swap(array, max, end);

		begin++;
		end--;
	}
}

void Test() {
	int array[] = { 9, 4, 3, 7, 2, 5, 8, 8, 7, 1, 3 };
	int size = sizeof(array) / sizeof(int);

	PrintArray(array, size);
	SelectSortOP(array, size);
	PrintArray(array, size);
}