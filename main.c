#include <stdio.h>
#include "cantalloc.h"

int	main(void)
{
	char	*str;
	int	*array;

	str = cantalloc(sizeof(char) * 5);
	str[0] = 'c';
	str[1] = 'i';
	str[2] = 'a';
	str[3] = 'o';
	str[4] = 0;
	printf("%s\n", str);

	array = cantalloc(sizeof(int) * 5);
	array[0] = 54;
	array[1] = 42;
	array[2] = 7;
	array[3] = 8965;
	array[4] = 0;
	for (int i = 0; i < 5; ++i)
		printf("%d ", array[i]);
	printf("\n");

	array = ccantalloc(sizeof(int), 5);
	for (int i = 0; i < 5; ++i)
		printf("%d ", array[i]);
	printf("\n");

	cantalloc_clean();

	return(0);
}
