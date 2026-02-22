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

void input(int** arr, int* size, int* choice, int* flag)
{
	if (*size != 0)
	{
		free_array(arr, size);
		*flag = 0;
	}

	random_choice(choice);

	if (*choice)
		random_input(arr, size);
	else
		manual_input(arr, size);
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

void manual_input(int** arr, int* size)
{
	getchar();

	puts("Enter the elements into the array(Enter - stop):");
	while (1)
	{
		char char_input = getchar();

		if (char_input == '\n')
			return;

		ungetc(char_input, stdin);

		int value;
		while (scanf_s("%d", &value) != 1 || value < MIN_INPUT || value > MAX_INPUT)
		{
			puts("Invalid Input.");
			rewind(stdin);
		}

		getchar();

		*arr = realloc(*arr, (*size + 1) * sizeof(int));
		check_alloc(*arr);
		(*arr)[*size] = value;
		(*size)++;
	}
}

void random_input(int** arr, int* size)
{
	int random_size = (rand() % (MAX_RAND_SIZE - MIN_RAND_SIZE + 1)) + MIN_RAND_SIZE;
	*arr = realloc(*arr, random_size * sizeof(int));
	check_alloc(*arr);
	*size = random_size;

	for (int i = 0; i < random_size; i++)
		(*arr)[i] = (rand() % (RAND_MAX - RAND_MIN + 1)) + RAND_MIN;
}

void output(int* arr, int size, int random_choice)
{
	if (random_choice)
		puts("\nThe array is filled with random integers:");
	else
		puts("\nYou have filled the array with integers:");
	for (int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	puts("");
}

void shell_sort(int** arr, int size, int* flag)
{
	int beginning, is_found = 0;

	find_first_positive(*arr, size, &beginning, &is_found);
	if (!is_found)
	{
		puts("\nThe array has no positive integers.");
		return;
	}

	int new_size = size - beginning;
	for (int gap = new_size / 2; gap >= 1; gap /= 2)
	{
		for (int i = beginning + gap; i < size; i++)
		{
			int placeholder = (*arr)[i];
			int j = i;

			while (j >= (beginning + gap) && (*arr)[j - gap] > placeholder)
			{
				(*arr)[j] = (*arr)[j - gap];
				j -= gap;
			}

			(*arr)[j] = placeholder;
		}
	}

	puts("\nAll integers after the first positive were sorted.");
	*flag = 1;
}

void find_first_positive(int* arr, int size, int* index, int* flag) 
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > 0)
		{
			*index = i + 1;
			*flag = 1;
			break;
		}
	}
}

void check_alloc(int* arr)
{
	if (arr == NULL)
	{
		puts("Memory allocation error.");
		exit(1);
	}
}

void free_array(int** arr, int* size)
{
	free(*arr);
	*arr = NULL;
	*size = 0;
}
