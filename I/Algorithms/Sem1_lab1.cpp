#include "pch.h"
#include <iostream>
using namespace std;
int main() {
	int i, i1, i2;
	printf("\311");
	for (i = 0; i < 8; i++) {
		for (i1 = 0; i1 < 5; i1++)
			printf("\315");
		if (i < 7)
			printf("\321");
	}
	printf("\273\n");
	for (i = 0; i < 255;) {
		printf("\272");
		for (i1 = 0; i1 < 8; i++) {
			if (i == 10)
				printf("10:\\n");
			else if (i == 27)
				printf(" 27: ");
			else if (i == 7)
				printf(" 7:\\a");
			else if (i == 9)
				printf(" 9:\\t");
			else if (i == 8)
				printf(" 8:\\b");
			else if (i == 13)
				printf("13:\\r");
			else
				printf("%3d:%c", i, i);
			i1++;
			if (i1 != 8)
				printf("\263");
		}
		printf("\272\n");
		if (i < 255) {
			printf("\307");
			for (i2 = 0; i2 < 8; i2++) {
				for (i1 = 0; i1 < 5; i1++)
					printf("\304");
				if (i2 < 7)
					printf("\305");
			}
			printf("\266\n");
		}
	}
	printf("\310");
	for (i = 0; i < 8; i++) {
		for (i1 = 0; i1 < 5; i1++)
			printf("\315");
		if (i < 7)
			printf("\317");
	}
	printf("\274\n");
	system("pause");
}