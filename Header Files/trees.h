#ifndef _WBST_H_
#define _WBST_H_
#include "record.h"
#include "l_item.h"

enum color_t { BLACK, RED, NO};

// TreeNode is like a tree structure
class TreeNode{
  private:
    Date *key;
    Record *value;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    int size;
    enum color_t color;
  public:
    TreeNode();
    TreeNode(Date *, Record *);
    ~TreeNode();

    TreeNode* get_left();
    TreeNode* get_right();
    TreeNode* get_parent();
    TreeNode* get_grandparent();
    TreeNode* get_sibling();
    TreeNode* get_uncle();

    Date* get_key();
    enum color_t get_color();
    int get_size();
    char* get_country();
    char* get_disease();
    Record* get_record();

    void set_right(TreeNode *);
    void set_left(TreeNode *);
    void set_parent(TreeNode *);
    void set_color(enum color_t);

    void set_size(int);
    void increase_size();

    void rotate_left();
    void rotate_right();

    TreeNode* insert(TreeNode *);
    void insert_recurse(TreeNode *, TreeNode *);
    void insert_repair_tree(TreeNode *);

    void insert_case1(TreeNode *);
    void insert_case2(TreeNode *);
    void insert_case3(TreeNode *);
    void insert_case4(TreeNode *);
    void insert_case4_step2(TreeNode *);

    void show();
};

// RBTree is a class for manipulating trees (of type TreeNode)
class RBTree{
  private:
    char *type;
    TreeNode *root;
  public:
    RBTree();
    RBTree(TreeNode *);
    RBTree(Date *, Record *);
    ~RBTree();

    bool add(Date *, Record *);

    void show();
    void print_tree(TreeNode *);
    void delete_recurse(TreeNode*);

    void global_disease_stats();
    void global_disease_stats(Date *, Date *);
    int global_disease_stats(Date *, Date *, TreeNode *);

    void disease_frequency(Date *, Date *, const char *);
    int disease_frequency(Date *, Date *, const char *, TreeNode *);

    void topk_diseases(int);
    void topk_diseases(TreeNode *, LLTree *);
    void topk_diseases(int, Date *, Date *);
    void topk_diseases(TreeNode *, LLTree *, Date *, Date *);

    void topk_countries(int);
    void topk_countries(TreeNode *, LLTree *);
    void topk_countries(int, Date *, Date *);
    void topk_countries(TreeNode *, LLTree *, Date *, Date *);

    void num_current_patients_1();
    void num_current_patients_1(TreeNode *, LNTree *);
    void num_current_patients_2();
    int num_current_patients_2(TreeNode *);

};


#endif
