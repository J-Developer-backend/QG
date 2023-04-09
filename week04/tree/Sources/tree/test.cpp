#include<stdio.h>
#include<string.h>
#include "tree.h"

char input[1024] = "";
BinarySortTree bst;
BinarySortTreePtr BST = &bst;

// ‰»Î ˝æ›¥¶¿Ì
bool checkInput(char* s, int* data) {
	//◊÷∑˚¥Æπ˝∂ÃªÚπ˝≥§
	if (strlen(s) == 0 || strlen(s) > 11)
		return false;
	int index = 1;
	int i = 0;
	//∑˚∫≈∂œ∂®
	if (s[0] == '-') {
		i++;
		index = -1;
	}
	long temp = 0;
	//ºÏ≤È∫œ¿Ì–‘
	for (; s[i] != '\0'; i++) {
		if (s[i] > '9' || s[i] < '0')
			return false;
		//¿€º∆«Û∫Õ
		temp = temp * 10 + s[i] - '0';
	}
	//≈–∂œ∑∂Œß «∑Ò∫œ¿Ì
	if (temp >= 2147483648 || temp < -2147483648)
		return false;
	*data = (int)(temp * index);
	return true;
}

//visit∫Ø ˝
void visit(NodePtr p) {
	if (p != NULL)
		printf("%d\n", p->value);
}

//≤‚ ‘BST_init
void testBST_init() {
	printf("test BST_init function\n");
	printf("Status:%d\n",BST_init(BST));
}

//≤‚ ‘BST_insert
void testBST_insert() {
	printf("test BST_insert function\n");
	ElemType value = 0;
	do {
		printf("please input the value you want to insert\n");
		gets_s(input);
	} while (!checkInput(input, &value));
	printf("Status:%d\n", BST_insert(BST,value));
}

//≤‚ ‘BST_delete
void testBST_delete() {
	printf("test BST_delete function\n");
	ElemType value = 0;
	do {
		printf("please input the value you want to delete\n");
		gets_s(input);
	} while (!checkInput(input, &value));
	printf("Status:%d\n", BST_delete(BST, value));
}

//≤‚ ‘BST_search
void testBST_search() {
	printf("test BST_search function\n");
	ElemType value = 0;
	do {
		printf("please input the value you want to search\n");
		gets_s(input);
	} while (!checkInput(input, &value));
	printf("Status:%d\n", BST_search(BST, value));
}

//≤‚ ‘BST_preorderI
void testBST_preorderI() {
	printf("test BST_preorderI function\n");
	printf("Status:%d\n", BST_preorderI(BST,visit));
}

//≤‚ ‘BST_preorderR
void testBST_preorderR() {
	printf("test BST_preorderR function\n");
	printf("Status:%d\n", BST_preorderR(BST, visit));
}

//≤‚ ‘BST_inorderI
void testBST_inorderI() {
	printf("test BST_inorderI function\n");
	printf("Status:%d\n", BST_inorderI(BST, visit));
}

//≤‚ ‘BST_inorderR
void testBST_inorderR() {
	printf("test BST_inorderR function\n");
	printf("Status:%d\n", BST_inorderR(BST, visit));
}

//≤‚ ‘BST_postorderI
void testBST_postorderI() {
	printf("test BST_postorderI function\n");
	printf("Status:%d\n", BST_postorderI(BST, visit));
}

//≤‚ ‘BST_postorderR
void testBST_postorderR() {
	printf("test BST_postorderR function\n");
	printf("Status:%d\n", BST_postorderR(BST, visit));
}

//≤‚ ‘BST_levelOrder
void testBST_levelOrder() {
	printf("test BST_levelOrder function\n");
	printf("Status:%d\n", BST_levelOrder(BST, visit));
}

//∫Ø ˝≤‚ ‘
void testFunction(int commend) {
	switch (commend) {
	case 1: {
		testBST_init();
		break;
	}
	case 2: {
		testBST_insert();
		break;
	}
	case 3: {
		testBST_delete();
		break;
	}
	case 4: {
		testBST_search();
		break;
	}
	case 5: {
		testBST_preorderI();
		break;
	}
	case 6: {
		testBST_preorderR();
		break;
	}
	case 7: {
		testBST_inorderI();
		break;
	}
	case 8: {
		testBST_inorderR();
		break;
	}
	case 9: {
		testBST_postorderI();
		break;
	}
	case 10: {
		testBST_postorderR();
		break;
	}
	case 11: {
		testBST_levelOrder();
		break;
	}
	case 12: {
		exit(0);
	}
	}
	system("pause");
	system("cls");
}

//≤‚ ‘≤Àµ•
void testMenu() {
	while (true) {
		printf("1.BST_init\n");
		printf("2.BST_insert\n");
		printf("3.BST_delete\n");
		printf("4.BST_search\n");
		printf("5.BST_preorderI\n");
		printf("6.BST_preorderR\n");
		printf("7.BST_inorderI\n");
		printf("8.BST_inorderR\n");
		printf("9.BST_postorderI\n");
		printf("10.BST_postorderR\n");
		printf("11.BST_levelOrder\n");
		printf("12.exit\n");
		int commend = -1;
		do {
			printf("please input the commend:\n");
			gets_s(input);
		} while (!checkInput(input, &commend));
		system("cls");
		testFunction(commend);
	}
}

int main() {
	testMenu();
}