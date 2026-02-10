#define MAX_INPUT 9999
#define MIN_INPUT -9999
#define MAX_RAND_SIZE 20
#define MIN_RAND_SIZE 1
#define RAND_MAX 50
#define RAND_MIN -50

void print_menu();
void option_choice(int* choice);

void input(int** arr, int* size, int* choice, int* flag);
void random_choice(int* choice);
void manual_input(int** arr, int* size);
void random_input(int** arr, int* size);

void output(int* arr, int size, int random_choice);

void shell_sort(int** arr, int size, int* flag);
void find_first_positive(int* arr, int size, int* index, int* flag);

void check_alloc(int* arr);
void free_array(int** arr, int* size);