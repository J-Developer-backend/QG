#pragma once
#ifndef XUANZUO_H_INCLUDED
#define XUANZUO_H_INCLUDED

//ð���Ż�1
void BubblSort1(int* a, int size) {
	int p1 = size;
	int p2 = size;
	for(int i = 0;i<size;i++){
		//��¼����������������������ٱ�����Ⱥʹ���
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

//ð���Ż�2
void BubblSort2(int* a, int size) {
	int d = 1;
	for (int i = 0; i < size; i++) {
		//��֤�ڷ���������Ƿ��Ѿ��ź�
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

//ð���Ż�3
void BubblSort3(int* a, int size) {
	for (int i = 0; i < size/2; i++) {
		for (int j = i,k = size -i - 1; j < size - i - 1; j++,k--) {
			//����һ�Σ���������
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



