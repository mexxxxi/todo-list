#include "task.h"

database_t *init_database(void) {
        database_t *db = (database_t *)malloc(sizeof(database_t));

        FILE *f = fopen("db.txt", "r+");
        if (f != NULL) {
                fscanf(f, "%d", &db->size);
                db->capacity = db->size * 2;
                db->tasks = (task_t *)malloc(sizeof(task_t) * db->capacity);
		
                char arg2[512];
                int arg1, arg3;
                for (int i = 0; i < db->size; i++) {
                        if (fscanf(f, "%d %d %[^\n]", &arg1, &arg3, arg2) == 3) {
                                db->tasks[i].number = arg1;
                                db->tasks[i].status = arg3;

                                db->tasks[i].name = (char *)malloc((strlen(arg2) + 1) * sizeof(char));
                                strncpy(db->tasks[i].name, arg2, strlen(arg2) + 1);
                        }
                }
        }
        else {
                f = fopen("db.txt", "w+");

                db->size = 0;
                db->capacity = 100;
                db->tasks = (task_t *)malloc(sizeof(task_t) * db->capacity);
        }

        fclose(f);

        return db;
}

int add_task(database_t *db, const char *name) {
        if (db == NULL)
                return -1;
        else if (name == NULL) 
                return -2;

        if (db->capacity - db->size < 10) {
                db->tasks = (task_t *)realloc(db->tasks, sizeof(task_t) * (db->size + 100));
                db->capacity += 100;
        }

        int index = db->size;
        db->tasks[index].name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
        strncpy(db->tasks[index].name, name, strlen(name) + 1);
        int max_number = -1;
        for (int i = 0; i < db->size; i++) {
                if (db->tasks[i].number > max_number) {
                        max_number = db->tasks[i].number;
                }
        }
        db->tasks[index].number = max_number + 1;
        db->tasks[index].status = TODO;
        db->size++;

        return 0;
}

int done_task(database_t *db, const int number) {
        if (db == NULL)
                return -1;

        int flag = 0;
        for (int i = 0; i < db->size; i++) {
                if (db->tasks[i].number == number) {
                        db->tasks[i].status = DONE;
                        flag = 1;
                        break;
                }
        }
	
        if (flag == 0)
                return -10;

        return 0;
}

int undone_task(database_t *db, const int number) {
        if (db == NULL)
                return -1;

        int flag = 0;
        for (int i = 0; i < db->size; i++) {
                if (db->tasks[i].number == number) {
                        db->tasks[i].status = TODO;
                        flag = 1;
                        break;
                }
        }

        if (flag == 0)
                return -10;

        return 0;
}

int delete_task(database_t *db, const int number) {
        if (db == NULL)
                return -1;

        int index = -1;
        for (int i = 0; i < db->size; i++) {
                if (db->tasks[i].number == number) {
                        index = i;
                        break;
                }
        }

        if (index == -1)
                return -10;

        free(db->tasks[index].name);

        for (int i = index; i < db->size - 1; i++) {
                db->tasks[i] = db->tasks[i + 1];
        }

        db->size--;

        return 0;
}

int list_tasks(const database_t *db) {
        if (db == NULL)
                return -1;

        printf("============================================================\n");
        printf(" number |                   name                   | status\n");
        printf("============================================================\n");

        if (db->size == 0) {
                printf("                           ~ пусто ~\n");
                printf("============================================================\n");
                return 0;
        }

        for (int i = 0; i < db->size; i++) {
                if (db->tasks[i].number == -1)
                        continue;
                printf(" %-6d | %-40s | %-6s\n", db->tasks[i].number, db->tasks[i].name, 
                                db->tasks[i].status == 0 ? "TODO" : "DONE");
        }
	
        printf("============================================================\n");

        return 0;
}

int clear_tasks(database_t *db) {
        if (db == NULL)
                return -1;

        db->size = 0;

        return 0;
}

void help(void) {
        printf("комманды:\n\n");

        printf("  add <...>\n");
        printf("  |--добавить задачу в базу данных\n\n");

        printf("  done <...> <...> ...\n");
        printf("  |--отметить задачу выполненной\n");
        printf("  |--аргументов может быть несколько\n\n");

        printf("  undone <...> <...> ...\n");
        printf("  |--отметить задачу не выполненной\n");
        printf("  |--аргументов может быть несколько\n\n");

        printf("  delete <...> <...> ...\n");
        printf("  |--удалить задачу\n");
        printf("  |--аргументов может быть несколько\n\n");

        printf("  list\n");
        printf("  |--вывести список задач\n\n");
        
        printf("  clear\n");
        printf("  |--очистить список задач\n");
        printf("  |--потребуется подтверждение\n\n");

	printf("  cld\n");
        printf("  |--очистить экран\n");
}

void cld(void) {
        system("clear");
}

int save_database(const database_t *db) {
        if (db == NULL)
                return -1;

        FILE *f = fopen("db.txt", "w");
        if (f == NULL) {
                printf("Ошибка: не удалось открыть файл db.txt для записи!\n");
                return -2;
        }

        fprintf(f, "%d\n", db->size);
	
        for (int i = 0; i < db->size; i++) {
                fprintf(f, "%d %d %s\n", db->tasks[i].number, db->tasks[i].status, db->tasks[i].name);
        }

        fclose(f);
        return 0;
}
