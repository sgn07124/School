#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QSIZE 100
#ifndef max
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

typedef char element;

typedef struct treeNode {	// 연결 자료구조로 구성하기 위해 트리의 노드 정의
	char data;
	struct treeNode* left;  // 왼쪽 서브 트리에 대한 링크 필드
	struct treeNode* right; // 오른쪽 서브 트리에 대한 링크 필드
} treeNode;

typedef treeNode* element;
typedef struct QType {
	element queue[MAX_QSIZE];
	int front, rear;
}QType;

void init(QType* q) {
	q->front = 0; q->rear = 0;
}
int is_empty(QType* q) {
	return q->front == q->rear;
}
int is_full(QType* q){
	return (q->rear + 1) % MAX_QSIZE == q->front;
}
void enqueue(QType* q, element item) {
	if (is_full(q)) {
		printf("요소가 꽉 찼습니다. \n");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QSIZE;
	q->queue[q->rear] = item;
}
treeNode* dequeue(QType* q) {
	if (is_empty(q)) {
		printf("요소가 비었습니다.\n");
		exit(1);
	}
	else {
		q->front = (q->front + 1) % MAX_QSIZE;
		return q->queue[q->front];
	}
}


treeNode* readtree(void);
void	printtree(treeNode*);
treeNode* makeRootNode(char data, treeNode* leftNode, treeNode* rightNode);
void preorder(treeNode* root);
void inorder(treeNode* root);
void postorder(treeNode* root);
void levelorder(treeNode*);
int treeheight(treeNode*);

int main(void) {
	// (A*B-C/D) 수식 이진 트리 만들기
	treeNode* n1 = readtree(); // 예1: -(*(A,B),/(C,D)) 예2: A(B(D,E(,G)),C(F,))
	printtree(n1);

	printf("\n preorder : ");
	preorder(n1);

	printf("\n inorder : ");
	inorder(n1);

	printf("\n postorder : ");
	postorder(n1);

	printf("\n levelorder : ");
	levelorder(n1);

	int i = treeheight(n1);
	printf("\n tree height = %d", i);

	getchar();  return 0;
}

// 입력은 node(left_subtree,right_subtree)를 순환적으로 표현한 문자열이며
// 노드 데이터는 "문자 하나"를 가정
treeNode* readtree(void)
{
	char	c;
	treeNode* tmp;

	switch (c = getchar()) {
	case '(':
		fprintf(stderr, "Wrong input format(-1).\n");
		exit(-1);
	case ',':
	case ')':
		return(NULL);
	default:
		tmp = (treeNode*)malloc(sizeof(treeNode));
		tmp->data = c;
	}

	switch (c = getchar()) {
	case '(':
		tmp->left = readtree();
		tmp->right = readtree();
		getchar();	// scan ')'
		return(tmp);
	case ',':
	case ')':
	case '\n':
		tmp->left = NULL;
		tmp->right = NULL;
		return(tmp);
	default:
		fprintf(stderr, "Wrong input format(-2).\n");
		exit(-2);
	}
}

// node(left_subtree,right_subtree)의 순환적으로 표현한 문자열로 출력
void printtree(treeNode* root)
{
	treeNode* n7 = makeRootNode('D', NULL, NULL);
	treeNode* n6 = makeRootNode('C', NULL, NULL);
	treeNode* n5 = makeRootNode('B', NULL, NULL);
	treeNode* n4 = makeRootNode('A', NULL, NULL);
	treeNode* n3 = makeRootNode('/', n6, n7);
	treeNode* n2 = makeRootNode('*', n4, n5);
	treeNode* n1 = makeRootNode('-', n2, n3);
}

// data를 루트 노드로 하여 왼쪽 서브 트리와 오른쪽 서브 트리를 연결하는 연산
treeNode* makeRootNode(element data, treeNode* leftNode, treeNode* rightNode) {
	treeNode* root = (treeNode*)malloc(sizeof(treeNode));
	root->data = (char)data;
	root->left = leftNode;
	root->right = rightNode;
	return root;
}

// 이진 트리에 대한 전위 순회 연산
void preorder(treeNode* root) {
	if (root) {
		printf("%c", root->data);  //작업D
		preorder(root->left);       //작업L
		preorder(root->right);	 //작업R
	}
}

// 이진 트리에 대한 중위 순회 연산
void inorder(treeNode* root) {
	if (root) {
		inorder(root->left);        //작업L
		printf("%c", root->data); //작업D
		inorder(root->right);      //작업R
	}
}

// 이진 트리에 대한 후위 순회 연산
void postorder(treeNode* root) {
	if (root) {
		postorder(root->left);    //작업L
		postorder(root->right);  //작업R
		printf("%c", root->data); //작업D
	}
}

void levelorder(treeNode* root) {
	QType q;
	init(&q);
	if (root == NULL)
		return;
	enqueue(&q, root);
	while (!is_empty(&q)) {
		root = dequeue(&q);
		printf("%c ", root->data);
		if (root->left)
			enqueue(&q, root->left);
		if (root->right)
			enqueue(&q, root->right);
	}puts(" ");
}

int treeheight(treeNode* root) {
	int height = 0;
	if (root != NULL) {
		height = 1 + max(treeheight(root->left), treeheight(root->right));
	}
	return height;
}
