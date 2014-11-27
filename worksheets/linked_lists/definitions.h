struct book_ {
  char title[50];
  char author[30];
  long isbn;
  struct book_ *next;
};

void add_book(struct book_ *book);
struct book_ *create_book(char title[50], char author[30], long isbn);
void print_list();
void print_node(long isbn);
