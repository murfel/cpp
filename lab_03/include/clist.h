struct intrusive_node {
  struct intrusive_node* next;
  struct intrusive_node* prev;
};

struct intrusive_list {
  struct intrusive_node* head;
};

typedef struct intrusive_list intrusive_list_t;

void init_list(struct intrusive_list * l, struct intrusive_node * node);
void add_node(struct intrusive_list * l, struct intrusive_node * node);
void remove_node(struct intrusive_list * l, struct intrusive_node * node);

int get_length(struct intrusive_list * l);
