#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PAGES 100 // Integer in [2, +inf)
#define M 0.15 // Real in (0, 1)

void scalar_multiplication(int order, float matrix[][order], float scalar);

int main() {

	// INPUT
	printf("Welcome to PageRank!\n");
	printf("Let's start by creating a model of the web.\n");

	// Number of pages
	int num_pages = 2;
	do {
		if (num_pages < 2)
			printf("Your web have too few pages, try 2 or more.\n");
		else if (num_pages > MAX_PAGES)
			printf("Your web have too many pages, try %d or less.\n", MAX_PAGES);
		printf("How many pages does your web have? ");
		scanf("%d", &num_pages);
	} while (num_pages < 2 || num_pages > MAX_PAGES);

	// Initialize link matrix
	float link_matrix[num_pages][num_pages];
	memset(link_matrix, 0, sizeof(link_matrix));

	// Links
	for (int i = 0; i < num_pages; i++) {

		// Number of links
		int num_links = 1;
		do {
			if (num_links < 1)
				printf("Page %d have too few links, try 1 or more.\n", i + 1);
			else if (num_links > num_pages - 1)
				printf("Page %d have too many links, try %d or less.\n", i + 1, num_pages - 1);
			printf("How many links does page %d have? ", i + 1);
			scanf("%d", &num_links);
		} while (num_links < 1 || num_links > num_pages - 1);

		// Pages linked
		for (int j = 0; j < num_links; j++) {
			int page_num = 1, has_repeated = false;
			do {
				if (page_num < 1 || page_num > num_pages)
					printf("Page %d does not exist, try again.\n", page_num);
				else if (page_num == i + 1 && has_repeated)
					printf("A page can't link to itself, try again.\n");
				printf("%d. What page does page %d link to? ", j + 1, i + 1);
				scanf("%d", &page_num);
				has_repeated = true;
			} while (page_num < 1 || page_num == i + 1 || page_num > num_pages);

			// Update link matrix
			link_matrix[page_num - 1][i] = 1 / (float) num_links;
		}
	}

	// ALGORITHM
	scalar_multiplication(num_pages, link_matrix, M);

	// DEBUGGING

	// Print link matrix
	for (int i = 0; i < num_pages; i++) {
		for (int j = 0; j < num_pages; j++)
			printf("%.2f\t", link_matrix[i][j]);
		printf("\n");
	}
}

// MATRIX OPERATIONS

// Multiply matrix by scalar
void scalar_multiplication(int order, float matrix[][order], float scalar) {
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			matrix[i][j] *= scalar;
}
