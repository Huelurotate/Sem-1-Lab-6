#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main()
{
	int* arr = malloc(sizeof(int));
	check_alloc(arr);

	int menu_choice, is_sorted = 0, is_running = 1;
	int size = 0;
	int random_choice;

	srand(time(NULL));

	while (is_running)
	{
		print_menu();
		option_choice(&menu_choice);
		switch (menu_choice)
		{
		case 1:
			input(&arr, &size, &random_choice, &is_sorted);
			break;
		case 2:
			if (size != 0) 
				output(arr, size, random_choice);
			else 
				puts("\nThe array is empty.");
			break;
		case 3:
			if (size != 0 && !is_sorted)
				shell_sort(&arr, size, &is_sorted);
			else if (is_sorted)
				puts("\nThe array has already been sorted.");
			else
				puts("\nThe array is empty.");
			break;
		case 4:
			free_array(&arr, &size);
			is_running = 0;
		}
	}

	return 0;
}