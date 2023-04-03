#pragma once
#ifndef XUANZUO_H_INCLUDED
#define XUANZUO_H_INCLUDED

//冒泡优化1
void BubblSort1(int* a, int size) {
	int p1 = size;
	int p2 = size;
	for(int i = 0;i<size;i++){
		//记录发生交换的最大索引，减少遍历深度和次数
		p2 = p1;
		for (int j = 0; j < size - i - 1 && j < p2; j++) {
			if (a[j] > a[j + 1]) {
				int t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
				p1 = j;
			}
		}
		if (p1 == 0)
			break;
	}
}

//冒泡优化2
void BubblSort2(int* a, int size) {
	int d = 1;
	for (int i = 0; i < size; i++) {
		//验证在否次排序中是否已经排好
		d = 0;
		for (int j = 0; j < size - i - 1 ; j++) {
			if (a[j] > a[j + 1]) {
				int t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
				d = 1;
			}
		}
		if (d == 0)
			break;
	}

}

//冒泡优化3
void BubblSort3(int* a, int size) {
	for (int i = 0; i < size/2; i++) {
		for (int j = i,k = size -i - 1; j < size - i - 1; j++,k--) {
			//遍历一次，排两个数
			if (a[j] > a[j + 1]) {
				int t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
			if (a[k] < a[k - 1]) {
				int t = a[k];
				a[k] = a[k - 1];
				a[k - 1] = t;
			}
		}
	}
}



#endif



