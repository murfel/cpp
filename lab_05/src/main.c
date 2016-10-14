#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/position.h"

typedef void (*op_t)(intrusive_node*, int*);

void apply(intrusive_list *lst, op_t op, int* temp) {
    intrusive_node *head = &lst->head;
    intrusive_node *node = head->next;

    for (; node != head; node = node->next) {
        op(node, temp);
    }
}

void count_nodes(intrusive_node * node, int* temp) {
    (*temp)++;
}

void print_node(intrusive_node * node, int* temp) {
    position_node *pnode = get_position(node);
    printf("[%d, %d] ", pnode->x, pnode->y);
}

int main(int argc, char *argv[]) {
    size_t int_size = 3;

    intrusive_list list;
    intrusive_list* l = &list;
    init_list(l);

    if (strcmp(argv[1], "loadtext") == 0) {
        FILE *f = fopen(argv[2], "r");
        int x;
        int y;
        while (fscanf(f, "%d %d", &x, &y) != EOF) {
            add_position(l, x, y);
        }
    }
    else if (strcmp(argv[1], "loadbin") == 0) {
        // не забыть проверить на баги и если надо отдебажить
        FILE *f = fopen(argv[2], "rb");
        int x = 0;
        int y = 0;
        while (fread(&x, int_size, 1, f) != 0) {
        //while (!feof(f)) {
            //void * x = calloc(1, int_size);
            //void * y = calloc(1, int_size);

            //fread(&x, int_size, 1, f);
            fread(&y, int_size, 1, f);
            add_position(l, x, y);
            //free(x);
            //free(y);
        }
    }
    else {
        printf("Invalid argument: %s\n", argv[1]);
        return 1;
    }

    if (argc == 3)
        return 0;



    if (strcmp(argv[3], "savetext") == 0) {
        FILE *f = fopen(argv[4], "w");

        intrusive_node *head = &l->head;
        intrusive_node *node = head->next;
        position_node *pnode;

        for (; node != head; node = node->next) {
            pnode = get_position(node);
            fprintf(f, "%d %d\n", pnode->x, pnode->y);
        }
    }
    else if (strcmp(argv[3], "savebin") == 0) {
        FILE *f = fopen(argv[4], "w");

        intrusive_node *head = &l->head;
        intrusive_node *node = head->next;
        position_node *pnode;

        int x = 0;
        int y = 0;

        for (; node != head; node = node->next) {
            pnode = get_position(node);
            x = pnode->x;
            y = pnode->y;

            fwrite(&x, 3, 1, f);
            fwrite(&y, 3, 1, f);
        }

    }
    else if (strcmp(argv[3], "print") == 0) {
        // пока работает без спецификации формата
        int temp;
        apply(l, print_node, &temp);
        printf("\n");
    }
    else if (strcmp(argv[3], "count") == 0) {
        int temp = 0;
        apply(l, count_nodes, &temp);
        printf("%d\n", temp);
    }
    else {
        printf("Invalid argument: %s\n", argv[3]);
        return 1;
    }

    //show_all_positions(l);
    return 0;
}
