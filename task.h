#ifndef TASK_H
#define TASK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct task_s {
	char *name;
	int number;
	enum {
		TODO,	/* не выполнено */
		DONE	/*  выполнено  */
	} status;
} task_t;

typedef struct database_s {
	task_t *tasks;
	int size;
	int capacity;
} database_t; 

database_t *init_database(void);

int add_task(database_t *db, const char *name);

int done_task  (database_t *db, const int number);
int undone_task(database_t *db, const int number);
int delete_task(database_t *db, const int number);

int list_tasks (const database_t *db);
int clear_tasks(database_t *db);

void help(void);
void cld (void);

int save_database(const database_t *db);
#endif /* TASK_H */
