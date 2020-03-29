#ifndef L_ITEM_H
#define L_ITEM_H
#include "record.h"

class LNode{
  private:
    Record *record;
    LNode *next_node;
  public:
    LNode();
    LNode(Record *);
    ~LNode();

    void set_record(Record *);
    void set_next(LNode *);

    Record* get_record();
    LNode* get_next();
};

class LNTree{
  private:
    LNode *head;
  public:
    LNTree();
    LNTree(LNode *);
    LNTree(Record *);
    ~LNTree();

    void add(Record *);

    void num_current_patients();
};

class LItem{
  private:
    char *name;
    int amount;
    LItem *next_item;
  public:
    LItem();
    LItem(char *);
    ~LItem();

    void set_name(char *);
    void set_next(LItem *);

    char* get_name();
    LItem* get_next();
    int get_amount();

    void increase_amount();
};

// This class is for manipulating items inside the tree.
class LLTree{
  private:
    LItem *head;
  public:
    LLTree();
    LLTree(LItem *);
    LLTree(char *);
    ~LLTree();

    void add(LItem *);
    void add(char *);
    void remove(LItem *);

    void topk_diseases(int);
    void topk_countries(int);
};

#endif
