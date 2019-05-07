#pragma once

#include <stdio.h>
//��ӡ����
void PrintArray(int array[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}
//��������
void Swap(int array[], int i, int j) {
	int t = array[i];
	array[i] = array[j];
	array[j] = t;
}

/*
ʱ�临�Ӷ�:
	���		O(n��			����
	ƽ��		O(n^2)
	�		O(n^2)			����
�ռ临�Ӷ�:
	O(1)
�ȶ���: �ȶ�
*/
//��������
//ȡһ��i����ͷ��ʼ�������ҵ���һ����i������±��Ϊj��Ȼ��i���������Ѵӵ�һ����Ŀ�ʼ
//һֱ��i-1������ƶ�һ����λ��i�ᱻi-1���ǣ���Ȼ��i�ŵ�֮ǰj��λ��
//��j��ʼ�����ٴα���
void InsertSort(int array[], int size) {
	// һ�δ���һ������������Ҫѭ�� size ��
	// �ϸ������ϣ� size - 1 �ξ͹���
	// ���� [0, i - 1]
	// Ҫ���� [i]
	// ���� [i + 1, size - 1]
	for (int i = 0; i < size; i++) {
		// ���������������� [0, i - 1]
		// ��ǰ���Һ��ʵ�λ�ã���i��ĵ�һ����
		int j;
		for (j = i - 1; j >= 0 && array[j] > array[i]; j--) 
		{
		}
		//��ʱj+1���ǵ�һ�������������j

		if (j + 1 != i) {
			int key = array[i];//����i��������
			for (int k = i; k > j + 1; k--) {
				//�Ӻ���ǰ���ƣ���ǰһ�������Ƹ���һ��
				array[k] = array[k - 1];
			}
			array[j + 1] = key;//��key���뵽ԭ��j����λ�ú�
		}
	}
}
//��������
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
ʱ�临�Ӷ�:
	���	O(n)
	ƽ��	O(n^1.2-1.3)
	�	O(n^2)		�����������ֵĸ���
�ռ临�Ӷ�:
	O(1)
�ȶ���: ���ȶ�
*/


//ϣ�����򣨷�����ţ���ԭ���csdn�ղأ��˽�ԭ����
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
	int gap = size;//gapΪÿ�εĲ���
	while (1) {
		gap = gap / 3 + 1;
		// gap = gap / 2;

		InsertSortWithGap(array, size, gap);
		if (gap == 1) {
			break;
		}
	}
}


// ѡ������
// 1. ֱ��ѡ��
/*
ʱ�临�Ӷ�:	���ݲ�����		O(n^2)
�ռ临�Ӷ�: O(1)
�ȶ���: ���ȶ�
*/
void SelectSort(int array[], int size) {//Ѱ�����ķ����������η����
	for (int i = 0; i < size; i++) {
		// ���� [size - i, size - 1]
		// ���� [0, size - 1 - i]
		int maxIdx = 0;//���ֵ������ʼ��
		// Ҫ��������������������ֵ���±�
		for (int j = 0; j <= size - 1 - i; j++) {//Ѱ���������μ�С1
			if (array[j] >= array[maxIdx]) {//��ͷ��ʼ������ǰ��������Ѱ�ҵ�ǰ�������ֵ
				maxIdx = j;//����¼��ǰ�������ֵ���±�
			}
		}
		// maxIdx ��¼���������䲿�����������±�
		// ��������������һ��λ�õ������н���
		Swap(array, maxIdx, size - 1 - i);//��������ֵ��������ǰѰ����������
	}
}

// 2. ������
// ʱ�临�Ӷ� ���ݲ����� O(n * log(n))
// �ռ临�Ӷ� O(1)
// �ȶ���: ���ȶ�
void Heapify(int array[], int size, int index) {//�˴������
//���µ���
	/*
	1. �ж��ǲ���Ҷ��
	2. �ҵ����ĺ���
		1) û���Һ���
		2) �Һ���
			1) ���Ӵ�
			2) �Һ��Ӵ�
	3. ���ĺ��Ӻ͸��Ƚϣ�������Ƚϴ��˳�
	4. �������Ҽ�������
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
	// �����һ����Ҷ�ӽ�㣬һֱ�� 0�����ϵ����µ���
	for (int i = (size - 2) / 2; i >= 0; i--) {
		Heapify(array, size, i);
	}
}
void HeapSort(int array[], int size) {
	// �����
	CreateHeap(array, size);

	// һ�δ���һ����
	// ���� [0, size - 1 - i]
	// ���� [size - i, size - 1]
	for (int i = 0; i < size; i++) {
		// ������������������������һ����
		Swap(array, 0, size - 1 - i);
		// �ѵ����ʱ��ƻ���
		// ֻ�и��ĵط�
		// Ҫ��������ʣ�����򲿷ֵĳ��� size - 1 - i
		Heapify(array, size - 1 - i, 0);
	}
}

/*
ʱ�临�Ӷ�:
���: O(n)
ƽ��: O(n^2)
�: O(n^2)
�ռ临�Ӷ�: O(1)
�ȶ���: �ȶ�
*/
void BubbleSort(int array[], int size) {
	for (int i = 0; i < size; i++) {
		int isSorted = 1;
		// ���� [size - i, size - 1]
		// ���� [0, size - 1 - i]
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
��ȫ����
��ȫ����
��ȫ���
��ȫ���
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
#include "�߾��ȼ�ʱ.h"

void TestSpeed() {
	char * createNames[] = {
		"����",
		"����",
		"���",
		"���"
	};
	CreateFunc funcs[] = {
		CreateSorted,
		CreateReverse,
		CreateRandom,
		CreateEqual
	};

	char * sortNames[] = {
		"��������",
		"ѡ������",
		"ð������",
		"ϣ������",
		"  ������"
	};

	SortFunc sortFuncs[] = {
		InsertSort2,
		SelectSort,
		BubbleSort,
		ShellSort,
		HeapSort
	};

	�߾��ȼ�ʱ	��ʱ��;
	for (int i = 0; i < sizeof(funcs) / sizeof(CreateFunc); i++) {
		char * createName = createNames[i];
		CreateFunc	createFunc = funcs[i];
		for (int j = 0; j < sizeof(sortFuncs) / sizeof(SortFunc); j++) {
			SortFunc sortFunc = sortFuncs[j];
			char * name = sortNames[j];

			for (int k = 1; k < 20; k++) {
				int size = k * 5000;
				int *array = createFunc(size);
				��ʱ��.��ʼ();
				sortFunc(array, size);
				��ʱ��.����();
				free(array);

				printf("[%s] [%s] ������: %02d ǧ: ��ʱ: %.4f ����\n", name, createName, size / 1000, ��ʱ��.�������());
			}
	
		}
	}
}


void InsertSortBS(int array[], int size) {
	for (int i = 0; i < size; i++) {
		// ���� [0, i - 1] ����
		// ���� [i, size - 1] ����

		int left = 0;
		int right = i - 1;
		// [left, right] ����ұ�
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
		// left ��Ҫ�����λ�õ��±�
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
	// [0, begin - 1]	���� ��С����
	// [begin, end]		���� 
	// [end + 1, size - 1] ���� ������
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

		// ��С�����ŵ�����������ʼ
		// �������ŵ������������ĩβ
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