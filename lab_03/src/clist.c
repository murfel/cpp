#include "../include/clist.h"

void init_list(struct intrusive_list * l, struct intrusive_node * node) {
    l->head->next = node;
    l->head->prev = node;

    node->next = l->head;
    node->prev = l->head;
}


void add_node(struct intrusive_list * l, struct intrusive_node * node) {
    l->head->next->prev = node;
    l->head->next = node;

    node->prev = l->head;
    node->next = l->head;
}


void remove_node(struct intrusive_list * l, struct intrusive_node * node) {
    node->next->prev = node->prev;
    node->prev->next = node->next;
}


int get_length(struct intrusive_list * l) {
    int ctr = 0;
    struct intrusive_node * node = l->head;
    while (node->next != l->head) {
        node = node->next;
        ctr++;
    }
    return ctr;
}
