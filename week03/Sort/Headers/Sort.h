#pragma once
#include<stdlib.h>
#include<time.h>
#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

/**
 *  @name        : void insertSort(int *a,int n);
 *  @description : 插入排序算法
 *  @param       : 数组指针 a, 数组长度 n
 */
void insertSort(int* a, int n) {
	for (int i = 1; i < n; i++) {
		int t = a[i];
		int j = i - 1;
		for (; j >=0; j--) {
			//后移
			if (a[j] > t) {
				a[j + 1] = a[j];
			}
			else 
				break;
		}
		//插入
		a[j + 1] = t;
	}
};


/**
 *  @name        : void MergeArray(int *a,int begin,int mid,int end,int *temp);
 *  @description : 归并排序（合并数组）
 *  @param       : 数组指针a，数组起点begin，数组中点mid，数组终点end，承载数组指针temp
 */
void MergeArray(int* a, int begin, int mid, int end, int* temp) {
	int i = begin;
	int j = begin;
	int k = mid;
	mid++;
	//合并数组
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
	//归并剩余项
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
 *  @description : 归并排序
 *  @param       : 数组指针a，数组起点begin，数组终点end，承载数组指针temp
 */
void MergeSort(int* a, int begin, int end, int* temp) {
	if (begin >= end)
		return;
	int mid = (end + begin) / 2;
	//拆分
	MergeSort(a, begin, mid, temp);
	MergeSort(a, mid+1, end, temp);
	//合并
	MergeArray(a, begin, mid, end, temp);
};


/**
 *  @name        : void QuickSort(int *a, int begin, int end);
 *  @description : 快速排序（递归版）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
void QuickSort_Recursion(int* a, int begin, int end) {
	if (begin >= end)
		return;
	int i = begin;
	int j = end;
	while (i < j) {
		//从后找小于a[begin]的元素对应的索引
		while (i < j) {
			if (a[j] < a[begin])
				break;
			j--;
		}
		//从前找大于a[begin]的元素对应的索引
		while (i < j) {
			if (a[i] > a[begin])
				break;
			i++;
		}
		//交换小于a[begin]的元素和大于a[begin]的元素
		if (i < j) {
		int t = a[i];
		a[i] = a[j];
		a[j] = t;		
		}
	}
	//基准数归位
	int t = a[begin];
	a[begin] = a[j];
	a[j] = t;
	//两边递归
	QuickSort_Recursion(a, begin, j);
	QuickSort_Recursion(a, j + 1, end);
};


/**
 *  @name        : void QuickSort(int *a,int size)
 *  @description : 快速排序（非递归版）
 *  @param       : 数组指针a，数组长度size
 */
void QuickSort(int* a, int size) {
	for (int i = 0; i < size;) {
		int t = i;
		int j = size - 1;
		while (t != j) {
			//从后找小于a[i]的元素对应的索引
			while (t < j) {
				if (a[j] < a[i])
					break;
				j--;
			}
			//从前找大于a[i]的元素对应的索引
			while (t < j) {
				if (a[t] > a[i])
					break;
				t++;
			}
			//交换
			if (t != j) {
				int temp = a[t];
				a[t] = a[j];
				a[j] = temp;
			}
		}
		//确定第i个元素
		if (t == i) {
			i++;
			continue;
		}
		//当前元素归位
		int p = a[t];
		a[t] = a[i];
		a[i] = p;
	}
};


/**
 *  @name        : void QuickSort(int *a, int begin, int end)
 *  @description : 快速排序（三枢轴优化）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
void Partition(int* a, int begin, int end) {
	if (begin >= end)
		return;
	//找基准
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
		//从后找小于a[n]的元素对应的索引
		while (i < j) {
			if (a[j] < a[n])
				break;
			j--;
		}
		//从前找大于a[n]的元素对应的索引
		while (i < j) {
			if (a[i] > a[n])
				break;
			i++;
		}
		//交换
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
	//两边递归
	Partition(a, begin, i);
	Partition(a, i + 1, end);
};


/**
 *  @name        : void CountSort(int *a, int size , int max)
 *  @description : 计数排序
 *  @param       : 数组指针a，数组长度size，数组最大值max
 */
void CountSort(int* a, int size, int max) {
	//记数表
	int* arr = (int*)malloc(sizeof(int)*(max+1));
	//初始化为0
	for (int i = 0; i < max + 1; i++)
		arr[i] = 0;
	//计数
	for (int i = 0; i < size; i++)
		arr[a[i]]++;
	int k = 0;
	//排序
	for (int i = 0;i <= max; i++){
		for (int j = 0; j < arr[i]; j++) {
			a[k] = i;
			k++;
		}
	}
};


/**
 *  @name        : void RadixCountSort(int *a,int size)
 *  @description : 基数计数排序
 *  @param       : 数组指针a，数组长度size
 */
void RadixCountSort(int* a, int size) {
	//找最大值
	int max = a[0];
	for (int i = 1; i < size; i++)
		if (a[i] > max)
			max = a[i];
	//计算最大值的长度
	int len = 0;
	while (max != 0) {
		max = max / 10;
		len++;
	}
	int t = 1;
	//循环最大值长度的次数
	for (int i = 0; i < len; i++) {
		//10个桶
		int* arr[10] = { NULL };
		//桶计数表
		int table[10] = { 0 };
		//生成桶
		for (int i = 0; i < 10; i++) {
			arr[i] = (int*)malloc(sizeof(int) * size);
			memset(arr[i], 0, size);
		}
		//入桶
		for (int j = 0; j < size; j++) {
		int p = a[j] / t % 10;
		arr[p][table[p]] = a[j];
		table[p]++;
		}
		t = t * 10;
		int d = 0;
		//出桶
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
 *  @description : 颜色排序
 *  @param       : 数组指针a（只含0，1，2元素），数组长度size
 */
void ColorSort(int* a, int size) {
	int p0 = 0;
	int p2 = size - 1;
	for (int p1 = 0; p1 < size;) {
		//用p1遍历数组，遇到1跳过
		if (a[p1] == 1) {
			p1++;
			continue;
		}
		//p1遍历到0的情况，与p0所在的元素互换
		if (a[p1] == 0) {
			int t = a[p1];
			a[p1] = a[p0];
			a[p0] = t;
			p0++;
			if (p0 > p1)
				p1++;
		}
		//p1遍历到2的情况，与p2所在的元素互换
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
 *  @name        : 自拟
 *  @description : 在一个无序序列中找到第K小的数
 *  @param       : 数组指针a，数组长度size
 */
//找第k小的数
int FindSmallNumber(int* a, int size, int k) {
	int low = 0;
	int hight = size - 1;
	//找到数组的第一个元素的基准位
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
	//数组第一个元素归位
	int t = a[0];
	a[0] = a[low];
	a[low] = t;
	//基准位为所求位
	if (low + 1 == k)
		return a[low];
	//所求位小于基准位
	else if (low + 1 > k) 
		return FindSmallNumber(&a[0],low+1 ,k);
	//所求位大于基准位
	else if (low + 1 < k) 
		return FindSmallNumber(&a[low + 1], size - low - 1, k - low - 1);
}


/**
 *  @name        : 自拟
 *  @description : 在一个无序序列中找到第K大的数
 *  @param       : 数组指针a，数组长度size
 */
//找第k大的数 == 找第size - k + 1 小的数
int FindBigNumber(int* a, int size, int k) {
	return FindSmallNumber(a, size, size - k + 1);
}


/**
 *  @name        : 自拟
 *  @description : 快排递归版随机
 *  @param       : 数组指针a，数组长度size
 */
//快排递归版随机
void QuickSort_Random(int* a, int size) {
	if (size == 0 || size == 1)
		return;
	srand((unsigned)time(NULL));
	int n = rand()%size;
	n = 0;
	int i = 0;
	int j = size -1;
	while (i != j ) {
		//从后找小于a[n]的元素对应的索引
		while (i < j ) {
			if (a[j] < a[n])
				break;
			j--;
		}
		//从前找大于a[n]的元素对应的索引
		while (i < j ) {
			if (a[i] > a[n])
				break;
			i++;
		}
		//交换
		if (i != j) {
			int t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	//记录基准位
	int index = 0;
	//基准位在随机位前
	if (i < n ) {
		index = i;
	}
	//基准位在随机位后
	if(i > n) {
		int t = a[j];
		a[j] = a[n];
		a[n] = t;
		index = j;
	}
	//基准位就在随机位
	if (i + 1 == n)
		index = n;
	//两边递归
	QuickSort_Random(&a[0], index +1);
	QuickSort_Random(&a[index +1], size - index -1);
};



#endif // QUEUE_H_INCLUDED


