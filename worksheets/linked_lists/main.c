#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"

struct book_ *root;

int main() {
  root = malloc(sizeof(struct book_));  
  root->next = NULL; 

  struct book_ *book;
  book = create_book("ABC 123", "Joe Bloggs", 1);
  add_book(book);
  book = create_book("DEF 456", "Joe Bloggs", 3);
  add_book(book);
  book = create_book("GHJ 789", "Joe Bloggs", 2);
  add_book(book);

  print_list();
  printf("\nFinding book 2\n");
  print_node(3);

  return 0;
}

void print_node(long isbn) {
  struct book_ *conductor;
  conductor = root->next;

  while (conductor != NULL ) {
    if(conductor->isbn == isbn){
      printf("%s", conductor->title);
      printf(" %s", conductor->author);
      printf(" %ld\n", conductor->isbn);
    }
    conductor = conductor->next; 
  }
}

void add_book(struct book_ *book){
  struct book_ *conductor;
  conductor = root;
  while((conductor->next != NULL) && (conductor->next->isbn < book->isbn)) {
    conductor = conductor->next;
  }
  book->next = conductor->next;
  conductor->next = book;
}

struct book_ *create_book(char title[50], char author[30], long isbn) {
  struct book_ *book;
  book = (struct book_ *) malloc(sizeof(struct book_ ));  
  strcpy(book->title, title);
  strcpy(book->author, author);
  book->isbn = isbn;
  book->next = NULL;
  return book;
}

void print_list() {
  printf("List of books, but ISBN\n");
  struct book_ *conductor;
  conductor = root->next;
  while (conductor != NULL ) {
      printf("%s", conductor->title);
      printf(" %s", conductor->author);
      printf(" %ld\n", conductor->isbn);
      conductor = conductor->next;
  }
}
