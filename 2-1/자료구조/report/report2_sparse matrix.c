#include <stdio.h>
#pragma once
typedef struct {
	int row;
	int col;
	int value;
} term;

void smTranspose(term a[], term b[], term c[]) {
	int m, n, v, i, j, p;
	m = a[0].row;
	n = a[0].col;
	v = a[0].value;
	b[0].row = n;
	b[0].col = m;
	b[0].value = v;
	if (v > 0) {
		p = 1;
		for(i=0; i<n; i++) // 희소행렬 a의 열별로 전치 반복 수행
			for(j=1; j<=v;j++) // 0이 아닌 원소 수에 대해서만 반복 수행
				if (a[j].col == i) { //현재의 열에 속하는 원소가 있으면 b[]에 대입
					b[p].row = a[j].col;
					b[p].col = a[j].row;
					b[p].value = a[j].value;
					p++;
				}
	}

int main(void) {
	term a[] = { {8, 7, 10}, {0, 2, 2}, {0, 6, 12}, {1, 4, 7}, {2, 0, 23}, {3, 3, 31}, {4, 1, 14}, {4, 5, 25}, {5, 6, 6}, {6, 0, 52}, {7, 4, 11} };
	term b[sizeof(a) / sizeof(a[0])];

	term c[] = { {8, 7, 10}, {0, 5, 2}, {1, 2, 7}, {2, 6, 13}, {3, 0, 17}, {3, 3, 1}, {4, 5, 29}, {5, 2, 21}, {6, 0, 32}, {6, 6, 41}, {7, 4, 52} };
	// 희소행렬 c 추가
	int i;

	printf("<<희소행렬 a>>");
	for (i = 0; i <= a[0].value; i++)
		printf("\n[%3d, %3d, %3d ] ", a[i].row, a[i].col, a[i].value);

	smTranspose(a, b);

	printf("\n\n<<희소행렬 b>>");
	for (i = 0; i <= b[0].value; i++)
		printf("\n[%3d, %3d, %3d ]", b[i].row, b[i].col, b[i].value);

	printf("\n\n<<희소행렬 c>>"); 
	for (i = 0; i <= c[0].value; i++)
		printf("\n[%3d, %3d, %3d ] ", c[i].row, c[i].col, c[i].value);

	

	printf("\n\n<<희소행렬 a 와 희소행렬 c 의 합>>"); // 희소행렬 a + 희소행렬 c
	for (i = 0; i <= (a[i].value + c[i].value); i++)
		printf("\n[ %3d, %3d, %3d ]", a[i].row + c[i].row, a[i].col + c[i].col, a[i].value + c[i].value);
	
	return 0;
}
