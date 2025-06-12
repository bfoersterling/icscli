#include "list_handling.h"
#include "date_time_handling.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_list(struct event *head) {
	while (head != NULL) {
		printf("%s\n", head->start_date);
		printf("%s\n", head->end_date);
		printf("%s\n", head->summary);
		head = head->next;
	}
}

void sorted_insert(struct event** head, char start_date[], char end_date[], char summary[]) {
	struct event *new_node = malloc(sizeof(struct event));
	strcpy((*new_node).start_date, start_date);
	strcpy((*new_node).end_date, end_date);
	strcpy((*new_node).summary, summary);

	if (*head == NULL || strcmp((*head)->start_date, new_node->start_date) >= 0) {
		new_node->next = *head;
		*head = new_node;
	}
	else {
		// Locate the node before the point of insertion
		struct event* current = *head;
		while (current->next!=NULL && strcmp(current->next->start_date, new_node->start_date) < 0)
			current = current->next;

		new_node->next = current->next;
		current->next = new_node;
	}
}

void free_list(struct event *head)
{
	struct event* tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

// print_upcoming() also prints ongoing events
// because you usually also want to see those
void print_upcoming(struct event *head, char current_date[], int show_all_events) {
	int i = 0;
	while (head != NULL) {
		if (strcmp(head->end_date, current_date) >= 0) {
			pretty_print_date_time(head->start_date);
			print_end_date(head->end_date, head->start_date);
			printf("\nSUMMARY: %s\n", head->summary);

			if (!show_all_events) {
				i++;
				if (i > 4)
					break;
			}

			if (head->next != NULL)
				printf("\n");
		}

		head = head->next;
	}
}
