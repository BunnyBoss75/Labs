#include "pch.h"
#include <iostream>
#include <string.h>
using namespace std;
int main() {
	system("chcp 1251");
	setlocale(LC_ALL, "Russian");
	int i, n, j, flag = 0;
	char s[1000], send[1000];
	send[999] = '\0';
	s[999] = '\0';
	char month[12][15] = { " января ", " февраля ", " марта ", " апреля ", " мая ", " июня ", " июля ", " августа ", " сентября ", " октября ", " ноября ", " декабря " };
	char* s1;
	char d[11];
	_strset_s(send, '\0');
	_strset_s(s, '\0');
	cin.getline(s, 1000);
	for (i = 0; i < 1000; i++) {
		flag = 0;
		s1 = &s[i];
		if (strlen(s1) < 10)
			break;
		for (j = 0; j < 10; j++)
			if (!((s1[j] - '0' < 10 && s1[j] - '0' > -1 && j != 2 && j != 5) || ((j == 2 || j == 5) && s1[j] == '.'))) {
				flag = 1;
				strncat_s(send, sizeof(send), s1, 1);
				break;
			}
		if (flag == 1)
			continue;
		strncpy_s(d, sizeof(d), s1, 10);
		strncat_s(send, d, 2);
		n = (s1[3] - '0') * 10 + s1[4] - '0';
		if (n == 0 || n > 12)
			strcat_s(send, " < неверный номер месяца > ");
		else
			strcat_s(send, month[n - 1]);
		strncat_s(send, &d[6], 4);
		i += 9;
	}

	strncat_s(send, sizeof(send), s1, 9);
	printf("%s\n", send);
}