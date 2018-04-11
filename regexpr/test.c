/*
** EPITECH PROJECT, 2017
** test.c for template
** File description:
** description
*/

#include <stdbool.h>

unsigned void uv;
signed void sv;
void v;

unsigned char uc;
signed char sc;
char c;

unsigned short us;
signed short ss;
short s;

unsigned int ui;
signed int si;
int i;

unsigned long ul;
signed long sl;
long l;

int signed const long ld;

unsigned float uf;
signed float sf;
float f;

unsigned double ud;
signed double sd;
double d;

unsigned bool ub;
signed bool sb;
bool b;

#include <stdio.h>
int main()
{
	printf("%ld\n", sizeof(int));
	printf("%ld\n", sizeof(int long));
	printf("%ld\n", sizeof(long int));
	printf("%ld\n", sizeof(long));
	printf("%ld\n", sizeof(long long));
}
