#include "../src/date_time_handling.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
	// 1
	char* pdt = pretty_date_time("20251215T080000Z");

	assert(!strcmp(pdt, "2025-12-15 08:00:00"));

	free(pdt);

	// 2
	char* pdt2 = pretty_date_time("20251215T080000");

	assert(!strcmp(pdt2, "2025-12-15 08:00:00"));

	free(pdt2);

	// 3
	char* pdt3 = pretty_date_time("");

	assert(!strcmp(pdt3, ""));

	free(pdt3);

	// 4
	char* pdt4 = pretty_date_time("20251215");

	assert(!strcmp(pdt4, "2025-12-15"));

	free(pdt4);

	// 5
	char current_date[] = "20240710T103000";

	printf("current_date: %s\n", current_date);
	printf("strlen(current_date): %ld\n\n", strlen(current_date));

	pretty_print_date_time(current_date);

	printf("\n\ncurrent_date: %s\n", current_date);
	printf("strlen(current_date): %ld\n", strlen(current_date));

	pretty_print_date_time("20251215T080000Z");
	printf("\n");

	return 0;
}
