#pragma once
#include<stdlib.h>
#include<time.h>
#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

/**
 *  @name        : void insertSort(int *a,int n);
 *  @description : ���������㷨
 *  @param       : ����ָ�� a, ���鳤�� n
 */
void insertSort(int* a, int n) {
	for (int i = 1; i < n; i++) {
		int t = a[i];
		int j = i - 1;
		for (; j >=0; j--) {
			//����
			if (a[j] > t) {
				a[j + 1] = a[j];
			}
			else 
				break;
		}
		//����
		a[j + 1] = t;
	}
};


/**
 *  @name        : void MergeArray(int *a,int begin,int mid,int end,int *temp);
 *  @description : �鲢���򣨺ϲ����飩
 *  @param       : ����ָ��a���������begin�������е�mid�������յ�end����������ָ��temp
 */
void MergeArray(int* a, int begin, int mid, int end, int* temp) {
	int i = begin;
	int j = begin;
	int k = mid;
	mid++;
	//�ϲ�����
	while (begin <= k && mid <= end) {
		if (a[begin] > a[mid]) {
			temp[i] = a[mid];
			mid++;
		}
		else {
			temp[i] = a[begin];
			begin++;
		}
		i++;
	}
	//�鲢ʣ����
	while (begin <= k) {
		temp[i] = a[begin];
		i++;
		begin++;
	}
	while (mid <= end) {
		temp[i] = a[mid];
		i++;
		mid++;
	}
	while (j <= end) {
		a[j] = temp[j];
		j++;
	}
};


/**
 *  @name        : void MergeSort(int *a,int begin,int end,int *temp);
 *  @description : �鲢����
 *  @param       : ����ָ��a���������begin�������յ�end����������ָ��temp
 */
void MergeSort(int* a, int begin, int end, int* temp) {
	if (begin >= end)
		return;
	int mid = (end + begin) / 2;
	//���
	MergeSort(a, begin, mid, temp);
	MergeSort(a, mid+1, end, temp);
	//�ϲ�
	MergeArray(a, begin, mid, end, temp);
};


/**
 *  @name        : void QuickSort(int *a, int begin, int end);
 *  @description : �������򣨵ݹ�棩
 *  @param       : ����ָ��a���������begin�������յ�end
 */
void QuickSort_Recursion(int* a, int begin, int end) {
	if (begin >= end)
		return;
	int i = begin;
	int j = end;
	while (i < j) {
		//�Ӻ���С��a[begin]��Ԫ�ض�Ӧ������
		while (i < j) {
			if (a[j] < a[begin])
				break;
			j--;
		}
		//��ǰ�Ҵ���a[begin]��Ԫ�ض�Ӧ������
		while (i < j) {
			if (a[i] > a[begin])
				break;
			i++;
		}
		//����С��a[begin]��Ԫ�غʹ���a[begin]��Ԫ��
		if (i < j) {
		int t = a[i];
		a[i] = a[j];
		a[j] = t;		
		}
	}
	//��׼����λ
	int t = a[begin];
	a[begin] = a[j];
	a[j] = t;
	//���ߵݹ�
	QuickSort_Recursion(a, begin, j);
	QuickSort_Recursion(a, j + 1, end);
};


/**
 *  @name        : void QuickSort(int *a,int size)
 *  @description : �������򣨷ǵݹ�棩
 *  @param       : ����ָ��a�����鳤��size
 */
void QuickSort(int* a, int size) {
	for (int i = 0; i < size;) {
		int t = i;
		int j = size - 1;
		while (t != j) {
			//�Ӻ���С��a[i]��Ԫ�ض�Ӧ������
			while (t < j) {
				if (a[j] < a[i])
					break;
				j--;
			}
			//��ǰ�Ҵ���a[i]��Ԫ�ض�Ӧ������
			while (t < j) {
				if (a[t] > a[i])
					break;
				t++;
			}
			//����
			if (t != j) {
				int temp = a[t];
				a[t] = a[j];
				a[j] = temp;
			}
		}
		//ȷ����i��Ԫ��
		if (t == i) {
			i++;
			continue;
		}
		//��ǰԪ�ع�λ
		int p = a[t];
		a[t] = a[i];
		a[i] = p;
	}
};


/**
 *  @name        : void QuickSort(int *a, int begin, int end)
 *  @description : ���������������Ż���
 *  @param       : ����ָ��a���������begin�������յ�end
 */
void Partition(int* a, int begin, int end) {
	if (begin >= end)
		return;
	//�һ�׼
	if (a[begin] > a[(begin + end) / 2]) {
		int t = a[begin];
		a[begin] = a[(begin + end) / 2];
		a[(begin + end) / 2] = t;
	}
	if (a[(begin + end) / 2] > a[end]) {
		int t = a[(begin + end) / 2];
		a[(begin + end) / 2] = a[end];
		a[end] = t;
	}
	if (a[begin] < a[(begin + end) / 2]) {
		int t = a[begin];
		a[begin] = a[(begin + end) / 2];
		a[(begin + end) / 2] = t;
	}
	int i = begin;
	int j = end;
	int n = begin;
	while (i != j) {
		//�Ӻ���С��a[n]��Ԫ�ض�Ӧ������
		while (i < j) {
			if (a[j] < a[n])
				break;
			j--;
		}
		//��ǰ�Ҵ���a[n]��Ԫ�ض�Ӧ������
		while (i < j) {
			if (a[i] > a[n])
				break;
			i++;
		}
		//����
		if (i != j) {
			int t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	if (i != n) {
		int t = a[i];
		a[i] = a[n];
		a[n] = t;
	}
	//���ߵݹ�
	Partition(a, begin, i);
	Partition(a, i + 1, end);
};


/**
 *  @name        : void CountSort(int *a, int size , int max)
 *  @description : ��������
 *  @param       : ����ָ��a�����鳤��size���������ֵmax
 */
void CountSort(int* a, int size, int max) {
	//������
	int* arr = (int*)malloc(sizeof(int)*(max+1));
	//��ʼ��Ϊ0
	for (int i = 0; i < max + 1; i++)
		arr[i] = 0;
	//����
	for (int i = 0; i < size; i++)
		arr[a[i]]++;
	int k = 0;
	//����
	for (int i = 0;i <= max; i++){
		for (int j = 0; j < arr[i]; j++) {
			a[k] = i;
			k++;
		}
	}
};


/**
 *  @name        : void RadixCountSort(int *a,int size)
 *  @description : ������������
 *  @param       : ����ָ��a�����鳤��size
 */
void RadixCountSort(int* a, int size) {
	//�����ֵ
	int max = a[0];
	for (int i = 1; i < size; i++)
		if (a[i] > max)
			max = a[i];
	//�������ֵ�ĳ���
	int len = 0;
	while (max != 0) {
		max = max / 10;
		len++;
	}
	int t = 1;
	//ѭ�����ֵ���ȵĴ���
	for (int i = 0; i < len; i++) {
		//10��Ͱ
		int* arr[10] = { NULL };
		//Ͱ������
		int table[10] = { 0 };
		//����Ͱ
		for (int i = 0; i < 10; i++) {
			arr[i] = (int*)malloc(sizeof(int) * size);
			memset(arr[i], 0, size);
		}
		//��Ͱ
		for (int j = 0; j < size; j++) {
		int p = a[j] / t % 10;
		arr[p][table[p]] = a[j];
		table[p]++;
		}
		t = t * 10;
		int d = 0;
		//��Ͱ
		for (int k = 0; k < 10; k++) {
			for (int g = 0; g < table[k]; g++) {
				a[d] = arr[k][g];
				d++;
			}
		}
	}
};


/**
 *  @name        : void ColorSort(int *a,int size)
 *  @description : ��ɫ����
 *  @param       : ����ָ��a��ֻ��0��1��2Ԫ�أ������鳤��size
 */
void ColorSort(int* a, int size) {
	int p0 = 0;
	int p2 = size - 1;
	for (int p1 = 0; p1 < size;) {
		//��p1�������飬����1����
		if (a[p1] == 1) {
			p1++;
			continue;
		}
		//p1������0���������p0���ڵ�Ԫ�ػ���
		if (a[p1] == 0) {
			int t = a[p1];
			a[p1] = a[p0];
			a[p0] = t;
			p0++;
			if (p0 > p1)
				p1++;
		}
		//p1������2���������p2���ڵ�Ԫ�ػ���
		else if (a[p1] == 2) {
			int t = a[p1];
			a[p1] = a[p2];
			a[p2] = t;
			p2--;
		}
		if (p1 >= p2)
			break;
	}
};


/**
 *  @name        : ����
 *  @description : ��һ�������������ҵ���KС����
 *  @param       : ����ָ��a�����鳤��size
 */
//�ҵ�kС����
int FindSmallNumber(int* a, int size, int k) {
	int low = 0;
	int hight = size - 1;
	//�ҵ�����ĵ�һ��Ԫ�صĻ�׼λ
	while (low != hight) {
		while (low < hight) {
			if (a[hight] < a[0])
				break;
			hight--;
		}
		while (low < hight) {
			if (a[low] > a[0])
				break;
			low++;
		}
		if(low!=hight){
			int t = a[low];
			a[low] = a[hight];
			a[hight] = t;
		}
	}
	//�����һ��Ԫ�ع�λ
	int t = a[0];
	a[0] = a[low];
	a[low] = t;
	//��׼λΪ����λ
	if (low + 1 == k)
		return a[low];
	//����λС�ڻ�׼λ
	else if (low + 1 > k) 
		return FindSmallNumber(&a[0],low+1 ,k);
	//����λ���ڻ�׼λ
	else if (low + 1 < k) 
		return FindSmallNumber(&a[low + 1], size - low - 1, k - low - 1);
}


/**
 *  @name        : ����
 *  @description : ��һ�������������ҵ���K�����
 *  @param       : ����ָ��a�����鳤��size
 */
//�ҵ�k����� == �ҵ�size - k + 1 С����
int FindBigNumber(int* a, int size, int k) {
	return FindSmallNumber(a, size, size - k + 1);
}


/**
 *  @name        : ����
 *  @description : ���ŵݹ�����
 *  @param       : ����ָ��a�����鳤��size
 */
//���ŵݹ�����
void QuickSort_Random(int* a, int size) {
	if (size == 0 || size == 1)
		return;
	srand((unsigned)time(NULL));
	int n = rand()%size;
	n = 0;
	int i = 0;
	int j = size -1;
	while (i != j ) {
		//�Ӻ���С��a[n]��Ԫ�ض�Ӧ������
		while (i < j ) {
			if (a[j] < a[n])
				break;
			j--;
		}
		//��ǰ�Ҵ���a[n]��Ԫ�ض�Ӧ������
		while (i < j ) {
			if (a[i] > a[n])
				break;
			i++;
		}
		//����
		if (i != j) {
			int t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	//��¼��׼λ
	int index = 0;
	//��׼λ�����λǰ
	if (i < n ) {
		index = i;
	}
	//��׼λ�����λ��
	if(i > n) {
		int t = a[j];
		a[j] = a[n];
		a[n] = t;
		index = j;
	}
	//��׼λ�������λ
	if (i + 1 == n)
		index = n;
	//���ߵݹ�
	QuickSort_Random(&a[0], index +1);
	QuickSort_Random(&a[index +1], size - index -1);
};



#endif // QUEUE_H_INCLUDED


