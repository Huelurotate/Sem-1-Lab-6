#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main()
{
	int** arr = malloc(sizeof(int*));
	check_rows_alloc(arr);

	int menu_choice, is_sorted = 0, is_running = 1;
	int rows = 0;
	int random_choice;

	srand(time(NULL));

	while (is_running)
	{
		print_menu();
		option_choice(&menu_choice);
		switch (menu_choice)
		{
		case 1:
			input(&arr, &rows, &random_choice, &is_sorted);
			break;
		case 2:
			if (rows) output(arr, rows, random_choice);
			else puts("\nThe array is empty.");
			break;
		case 3:
			if (rows != 0 && !is_sorted)
				perform_calcs(arr, 0, rows - 1, &is_sorted);
			else if (is_sorted)
				puts("\nThe array's rows have already been sorted.");
			else
				puts("\nThe array is empty.");
			break;
		case 4:
			free_array(&arr, &rows);
			is_running = 0;
		}
	}

	return 0;
}