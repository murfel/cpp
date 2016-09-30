#include "../include/clist.h"

struct position_node {
  int x, y;
  struct intrusive_node * node;
};

void remove_position(struct intrusive_list * l, int x, int y) { // removes all (x, y) pairs
     ;
}

void add_positon(struct intrusive_list * l, int x, int y) {
     ;
}

void show_all_positions(struct intrusive_list * l) {
     ;
}

void remove_all_positions(struct intrusive_list * l) {
     ;
}

int main() {
  /* usage

     intrusive_list_t l;
     init_list(&l);

     add_positon(&l, 10, 10);
     add_positon(&l, 20, 20);

     show_all_positions(&l);
*/
     return 0;

}
