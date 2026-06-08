#include "task.h"

int main(void) {
        database_t *db = init_database();

        char buffer[512];
        int  arg;

        while (1) {
                if (scanf("%s", buffer) != 1) {
                        break;
                }

                int command = -1;
		
                if (strcmp(buffer, "list") == 0) {
                        list_tasks(db);
                        command = 4;
                } else if (strcmp(buffer, "clear") == 0) {
                        printf("Вы уверены, что хотите очистить все задачи? (y/n): ");
                        char confirm[10];
                        if (scanf("%s", confirm) == 1 && (strcmp(confirm, "y") == 0 || strcmp(confirm, "Y") 
						== 0 || strcmp(confirm, "yes") == 0)) {
                                clear_tasks(db);
                                save_database(db);
                        } else {
                                printf("Очистка отменена\n");
                        }
                        command = 5;
                } else if (strcmp(buffer, "help") == 0) {
                        help();
                        command = 6;
                } else if (strcmp(buffer, "exit") == 0) {
                	return 0;
		} else if (strcmp(buffer, "cld") == 0) {
                        cld();
                        command = 7;
                } else if (strcmp(buffer, "add") == 0) {
                        command = 0;
                } else if (strcmp(buffer, "done") == 0) {
                        command = 1;
                } else if (strcmp(buffer, "undone") == 0) {
                        command = 2;
                } else if (strcmp(buffer, "delete") == 0) {
                        command = 3;
                }
		
                if (command == -1) {
                        printf("неправильный синтаксис\n");
                } else {
                        int check_next;
                        while (1) {
                                do {
                                        check_next = getc(stdin);
                                } while (check_next == ' ');

                                if (check_next == '\n' || check_next == EOF) {
                                        break;
                                }

                                ungetc(check_next, stdin);
       
                                switch (command) {
                                        case 0:
                                                if (scanf(" %[^\n]", buffer) == 1) {
                                                        add_task(db, buffer);
                                                        save_database(db);
                                                }
                                                break;
                                        case 1:
                                                if (scanf("%d", &arg) == 1) {
                                                        if (done_task(db, arg) == -10) {
                                                                printf("задачи с номером %d нет\n", arg);
                                                        }
                                                        save_database(db);
                                                }
                                                break;
                                        case 2:
                                                if (scanf("%d", &arg) == 1) {
                                                        if (undone_task(db, arg) == -10) {
                                                                printf("задачи с номером %d нет\n", arg);
                                                        }
                                                        save_database(db);
                                                }
                                                break;
                                        case 3:
                                                if (scanf("%d", &arg) == 1) {
                                                        if (delete_task(db, arg) == -10) {
                                                                printf("задачи с номером %d нет\n", arg);
                                                        }
                                                        save_database(db);
                                                }
                                                break;
                                }
                                if (command == 0) {
                                        break;
                                }
                        }
                }
        }

        return 0;
}
