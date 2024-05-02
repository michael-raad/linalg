// time: k is length of list
// see linalg.h
struct llnode;

struct llist;

// list_create() returns an empty linked list
// effects: allocates memory
// time: O(1)
struct llist *list_create(void);

// add_front(mat, lst) adds a matrix to the front of a linked list
// requires: lst and mat are valid pointers
// effects: allocates memory (call remove_item or list_destroy)
// time: O(1)
void add_front(const struct matrix *mat, struct llist *lst);

// list_destroy(lst) frees all memory for lst if d = 1 and frees
//   memory for all nodes in lst if d = 0
// requires: lst is a valid pointer
//           d = 0 or d = 1
// effects: frees memory
// time: O(k)
void list_destroy(struct llist *lst, int d);

// list_length(lst) returns the length of lst
// requires: lst is a valid pointer
// time: O(k)
int list_length(const struct llist *lst);

// matrix_at(index, lst) returns the matrix at index in lst
// requires: lst is a valid pointer
// notes: 
//   if the index is less than 0, the function returns NULL
//   if the index is >= the list length, the fucntion returns NULL
//   in both cases, an error is produced to stderr
// effects: may produce output
// time: O(k)
struct matrix *matrix_at(int index, struct llist *lst);

// remove_item(index, lst) removes the node at index from lst
// requires: lst is a valid pointer
// notes: 
//   if the index is less than 0, the function returns
//   if the index is >= the list length, the fucntion returns
//   in both cases, an error is produced to stderr
// effects: may produce output
//          may free memory
// time: O(k)
void remove_item(int index, struct llist *lst);

// print_llist(lst) prints all matrices in lst
// requires: lst is a valid pointer
// effects: produces output
// time: O(knm)
void print_llist(struct llist *lst);