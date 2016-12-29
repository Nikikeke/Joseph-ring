#include <iostream>
#include <cstring>
#include <string>

using namespace std;

unsigned int total[400];
unsigned int num1[200];
unsigned int num2[200];


int main()
{
	memset(total, 0, sizeof(total));
	string str1, str2;
	cin >> str1 >> str2;
	int len, index;
	len = str1.length();
	index = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		num1[index++] = str1[i] - '0';
	}
	len = str2.length();
	index = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		num2[index++] = str2[i] - '0';
	}

	for (unsigned int i = 0; i<str1.length(); i++)
	{
		for (unsigned int j = 0; j<str2.length(); j++)
		{
			total[i + j] += num1[i] * num2[j];
		}
	}
	for (int i = 0; i<400; i++)
	{
		if (total[i] >= 10)
		{
			total[i + 1] += total[i] / 10;
			total[i] %= 10;
		}
	}
	bool flag = false;
	for (int i = 399; i >= 0; i--)
	{
		if (flag || total[i])
		{
			flag = true;
			cout << total[i];
		}
	}

	if (!flag)
	{
		cout << "0";
	}

	return 0;
}