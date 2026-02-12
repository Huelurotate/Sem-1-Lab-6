#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void print_menu()
{
	puts("\n      MENU\n"
		"Choose an option:\n"
		"1 - Input Data\n"
		"2 - Output Data\n"
		"3 - Perform Calculations\n"
		"4 - Exit Program");
}

void option_choice(int* choice)
{
	while (scanf_s("%d", choice) != 1 || \
		(*choice != 1 && *choice != 2 && *choice != 3 && *choice != 4))
	{
		puts("Invalid Input.");
		rewind(stdin);
	}
}

void input(int*** arr, int* rows, int* choice, int* flag)
{
	if (*rows != 0)
	{
		free_array(arr, rows);
		*flag = 0;
	}

	random_choice(choice);

	if (*choice)
		random_input(arr, rows);
	else
		manual_input(arr, rows);
}

void random_choice(int* choice)
{
	printf("\nFill the array with random numbers?(1 - yes, 0 - no): ");
	while (scanf_s("%d", choice) != 1 || (*choice != 0 && *choice != 1))
	{
		puts("Invalid Input.");
		rewind(stdin);
	}
}

void manual_input(int*** arr, int* rows)
{
	getchar();

	while (1)
	{
		int col = 0;

		printf("\nEnter the elements for row number %d(Enter - stop):\n", (*rows + 1));

		while (1)
		{
			int ch_input = getchar();

			if (ch_input == '\n')
			{
				if (col == 0)
				{
					return;
				}
				else
				{
					(*arr)[*rows] = realloc((*arr)[*rows], (col + 1) * sizeof(int));
					check_cols_alloc((*arr)[*rows]);
					(*arr)[*rows][col] = INT_MAX;

					break;
				}
			}

			ungetc(ch_input, stdin);

			int value;
			while (scanf_s("%d", &value) != 1 || value < MIN_INPUT || value > MAX_INPUT)
			{
				puts("Invalid Input.");
				rewind(stdin);
			}

			getchar();

			(*arr)[*rows] = realloc((*arr)[*rows], (col + 1) * sizeof(int));
			check_cols_alloc((*arr)[*rows]);
			(*arr)[*rows][col] = value;
			col++;
		}

		*arr = realloc(*arr, (*rows + 1) * sizeof(int*));
		check_rows_alloc(*arr);
		(*rows)++;
	}
}

void random_input(int*** arr, int* rows)
{
	int row_size = (rand() % (RAND_SIZE_MAX - RAND_SIZE_MIN + 1)) + RAND_SIZE_MIN;
	*rows = row_size;
	*arr = realloc(*arr, row_size * sizeof(int*));
	check_rows_alloc(*arr);

	for (int i = 0; i < row_size; i++)
	{
		int col_size = (rand() % (RAND_SIZE_MAX - RAND_SIZE_MIN + 1)) + RAND_SIZE_MIN;
		int* current_row = malloc((col_size + 1) * sizeof(int));
		check_cols_alloc(current_row);

		for (int j = 0; j < col_size; j++)
		{
			current_row[j] = (rand() % (RAND_MAX - RAND_MIN + 1)) + RAND_MIN;
		}

		current_row[col_size] = INT_MAX;
		(*arr)[i] = current_row;
	}
}

void output(int** arr, int rows, int random_choice)
{
	if (random_choice)
		puts("\nThe array is filled with random integers:");
	else
		puts("\nYou have filled the array with integers:");
	for (int i = 0; i < rows; i++)
	{
		if (arr[i] == NULL) continue;
		for (int j = 0; arr[i][j] != INT_MAX; j++)
		{
			printf("%5d", arr[i][j]);
		}
		puts("");
	}
}

void perform_calcs(int** arr, int start, int end, int* flag)
{
	merge_sort(arr, start, end);
	*flag = 1;
	puts("\nThe array's rows have been sorted.");
}

void merge_sort(int** arr, int start, int end)
{
	if (start < end)
	{
		int middle = (start + end) / 2;

		merge_sort(arr, start, middle);
		merge_sort(arr, middle + 1, end);
		merge(arr, start, middle, end);
	}
}

void merge(int** arr, int start, int middle, int end)
{
	int current_size = end - start + 1;

	int** temp_arr = malloc(current_size * sizeof(int*));
	check_rows_alloc(temp_arr);

	int i = start;
	int j = middle + 1;
	int k = 0;


	while (i <= middle && j <= end)
	{
		if (row_product(arr[i]) <= row_product(arr[j]))
			temp_arr[k] = arr[i++];
		else
			temp_arr[k] = arr[j++];
		k++;
	}

	while (i <= middle)
		temp_arr[k++] = arr[i++];

	while (j <= end)
		temp_arr[k++] = arr[j++];

	for (int p = 0; p < current_size; p++)
		arr[start + p] = temp_arr[p];

	free(temp_arr);
}

int row_product(int* row)
{
	int total = 1;
	int has_negative = 0;
	
	for (int i = 0; row[i] != INT_MAX; i++)
	{
		if (row[i] < 0)
		{
			total *= row[i];
			has_negative = 1;
		}
	}

	if (!has_negative)
		return 0;

	return total;
}

void check_rows_alloc(int** arr)
{
	if (arr == NULL)
	{
		puts("Memory allocation error.");
		exit(1);
	}
}

void check_cols_alloc(int* arr)
{
	if (arr == NULL)
	{
		puts("Memory allocation error.");
		exit(1);
	}
}

void free_array(int*** arr, int* rows)
{
	for (int i = 0; i < *rows; i++)
		free((*arr)[i]);
	free(*arr);
	*arr = NULL;
	*rows = 0;
}
