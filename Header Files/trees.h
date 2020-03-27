#ifndef _WBST_H_
#define _WBST_H_
#include "record.h"

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

    void set_right(TreeNode *);
    void set_left(TreeNode *);
    void set_parent(TreeNode *);
    void set_color(enum color_t);

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
};

#endif
