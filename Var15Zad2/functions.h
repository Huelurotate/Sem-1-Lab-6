#define MAX_INPUT 9999
#define MIN_INPUT -9999
#define RAND_MAX 50
#define RAND_MIN -50
#define RAND_SIZE_MAX 10
#define RAND_SIZE_MIN 1

void print_menu();
void option_choice(int* choice);

void input(int*** arr, int* rows, int* choice, int* flag);
void random_choice(int* choice);
void manual_input(int*** arr, int* rows);
void random_input(int*** arr, int* rows);

void output(int** arr, int rows, int random_choice);

void perform_calcs(int** arr, int start, int end, int* flag);
void merge_sort(int** arr, int left, int right);
void merge(int** arr, int start, int middle, int end);
int row_product(int* row);

void check_rows_alloc(int** arr);
void check_cols_alloc(int* arr);
void free_array(int*** arr, int* rows);