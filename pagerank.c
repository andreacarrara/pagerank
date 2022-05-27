#include <stdio.h>
#include <math.h>

// CONSTANTS
#define MAX_PAGES 100 // Integer in [MIN_PAGES, +inf)
#define MIN_PAGES 2 // Integer in [2, MAX_PAGES]
#define WEIGHT 0.15 // Real in (0, 1), best at 0.15
#define ERROR 0.0001 // Real in (0, +inf), best at 0.0001

// PROTOTYPES
int get_num_pages();
void init_link_matrix(int num_pages, float link_matrix[][num_pages]);
void scalar_multiplication(float *matrix, int num_rows, int num_cols, float scalar);
void column_multiplication(float *matrix, int num_rows, int num_cols, float *column);
void addition(float *matrix1, float *matrix2, int num_rows, int num_cols);
float norm(float *column, int num_rows);
void print_standings(float score_column[], int num_pages);

int main() {
	// INPUT
	printf("Let's start by creating a model of the web.\n");
	int num_pages = get_num_pages();
	float link_matrix[num_pages][num_pages];
	init_link_matrix(num_pages, link_matrix);

	// CONVERGENCE LOOP

	// Initialize mean column and score column
	float mean_column[num_pages], score_column[num_pages];
	for (int i = 0; i < num_pages; i++) {
		float entry = 1 / (float) num_pages;
		mean_column[i] = entry;
		score_column[i] = entry;
	}

	// Weigh link matrix and mean column
	scalar_multiplication(link_matrix[0], num_pages, num_pages, 1 - WEIGHT);
	scalar_multiplication(mean_column, num_pages, 1, WEIGHT);

	float score_norm;
	do {
		// Store score column before operations
		float score_diff[num_pages];
		for (int i = 0; i < num_pages; i++)
			score_diff[i] = score_column[i];

		// Multiply score column by weighted link matrix
		column_multiplication(link_matrix[0], num_pages, num_pages, score_column);

		// Add weighted mean column to score column
		addition(score_column, mean_column, num_pages, 1);

		// Subtract previous score column from score column
		scalar_multiplication(score_diff, num_pages, 1, -1);
		addition(score_diff, score_column, num_pages, 1);

		// Calculate norm of the difference
		score_norm = norm(score_diff, num_pages);

		// Repeat until score norm is smaller than error
	} while (score_norm > ERROR);

	// OUTPUT
	printf("Here are the standings:\n");
	print_standings(score_column, num_pages);
}

// INPUT

// Get number of pages
int get_num_pages() {
	int num_pages;
	do {
		printf("How many pages does your web have? ");
		scanf("%d", &num_pages);
		if (num_pages < MIN_PAGES)
			printf("Your web has too few pages, try %d or more.\n", MIN_PAGES);
		else if (num_pages > MAX_PAGES)
			printf("Your web has too many pages, try %d or less.\n", MAX_PAGES);
	} while (num_pages < MIN_PAGES || num_pages > MAX_PAGES);
	return num_pages;
}

// Initialize link matrix
void init_link_matrix(int num_pages, float link_matrix[][num_pages]) {
	// Set all entries to 0
	for (int i = 0; i < num_pages; i++)
		for (int j = 0; j < num_pages; j++)
			link_matrix[i][j] = 0;

	// Links
	for (int i = 0; i < num_pages; i++) {
		// Number of links
		int num_links;
		do {
			printf("How many links does page %d have? ", i + 1);
			scanf("%d", &num_links);
			if (num_links < 1)
				printf("Page %d has too few links, try 1 or more.\n", i + 1);
			else if (num_links > num_pages - 1)
				printf("Page %d has too many links, try %d or less.\n", i + 1, num_pages - 1);
		} while (num_links < 1 || num_links > num_pages - 1);

		// Linked pages
		for (int j = 0; j < num_links; j++) {
			int page_num;
			do {
				printf("%d. What page does page %d link? ", j + 1, i + 1);
				scanf("%d", &page_num);
				if (page_num < 1 || page_num > num_pages)
					printf("Page %d does not exist, try again.\n", page_num);
				else if (page_num == i + 1)
					printf("A page can't link itself, try again.\n");
				else if (link_matrix[page_num - 1][i])
					printf("Page %d already links page %d, try again.\n", i + 1, page_num);
			} while (page_num < 1 || page_num > num_pages || page_num == i + 1 || link_matrix[page_num - 1][i]);
			
			// Set entry
			link_matrix[page_num - 1][i] = 1 / (float) num_links;
		}
	}
}

// MATRIX OPERATIONS

// Multiply matrix by scalar
// Product stored in the matrix
void scalar_multiplication(float *matrix, int num_rows, int num_cols, float scalar) {
	int num_entries = num_rows * num_cols;
	for (int i = 0; i < num_entries; i++)
		*matrix++ *= scalar;
}

// Multiply matrix by column
// Product stored in the column
// Column must have num_cols rows
void column_multiplication(float *matrix, int num_rows, int num_cols, float *column) {
	float product[num_cols];
	for (int i = 0; i < num_rows; i++) {
		float sum = 0;
		float *temp = column;
		for (int j = 0; j < num_cols; j++)
			sum += *matrix++ * *temp++;
		product[i] = sum;
	}

	// Copy entries in the column
	for (int i = 0; i < num_cols; i++)
		*column++ = product[i];
}

// Sum two matrices
// Sum stored in the first matrix
// Matrices must have the same dimensions
void addition(float *matrix1, float *matrix2, int num_rows, int num_cols) {
	int num_entries = num_rows * num_cols;
	for (int i = 0; i < num_entries; i++)
		*matrix1++ += *matrix2++;
}

// Return Euclidean norm of column
float norm(float *column, int num_rows) {
	float sum = 0;
	for (int i = 0; i < num_rows; i++)
		sum += pow(*column++, 2);
	return sqrt(sum);
}

// OUTPUT

// Print standings
void print_standings(float score_column[], int num_pages) {
	for (int i = 0; i < num_pages; i++) {
		float max_score = 0;
		int page_num;
		for (int j = 0; j < num_pages; j++)
			if (score_column[j] > max_score) {
				max_score = score_column[j];
				page_num = j;
			}
		score_column[page_num] = 0;
		printf("%d. Page %d: %f\n", i + 1, page_num + 1, max_score);
	}
}
