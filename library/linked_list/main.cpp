#include <cstdio>

extern void test_list();
extern void test_stack();
extern void test_queue();

int main()
{
	printf("\n*** [List]\n");
	test_list();

	printf("\n*** [Stack]\n");
	test_stack();

	printf("\n*** [Queue]\n");
	test_queue();

	return 0;
}