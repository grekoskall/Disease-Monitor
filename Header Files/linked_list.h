#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H
#include "record.h"

class Node{
  private:
    Record *data;
    Node *next;

  public:
    Node();
    Node(Record *);
    Node(Record *, Node *);
    ~Node();

    int get_recordID();

    void set_data(Record *);
    Node* get_next();
    void set_next(Node *);

    void print_node();
};

class LinkedList{
  private:
      Node *head;

  public:
      LinkedList();
      LinkedList(Record *);
      LinkedList(Node *);
      ~LinkedList();

      bool add(Node *);
      bool add(Record *);

      bool check_double_record(int);

      void print_list();
};

#endif
