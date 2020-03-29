#include <iostream>
#include <cstring>
#include "trees.h"


using namespace std;

TreeNode::TreeNode() : key(NULL), value(NULL), left(NULL), right(NULL), parent(NULL), size(1), color(NO){
}

TreeNode::TreeNode(Date *date, Record *record) : key(date), value(record), left(NULL), right(NULL), parent(NULL), size(1), color(NO){
}

TreeNode::~TreeNode(){
}

TreeNode* TreeNode::get_left(){
  return left;
}

TreeNode* TreeNode::get_right(){
  return right;
}

TreeNode* TreeNode::get_parent() {
  if(key == NULL){
    return NULL;
  } else {
    return parent;
  }
}

TreeNode* TreeNode::get_grandparent(){
  if(parent == NULL){
    return NULL;
  } else {
    return parent->get_parent();
  }
}

TreeNode* TreeNode::get_sibling(){
  TreeNode *temp = get_parent();
  if(temp == NULL){
    return NULL;
  }
  if(this == temp->get_left()){
    return temp->get_right();
  } else {
    return temp->get_left();
  }
}

TreeNode* TreeNode::get_uncle(){
  TreeNode *temp = get_parent();
  return temp->get_sibling();
}

Date* TreeNode::get_key(){
  return key;
}

enum color_t TreeNode::get_color(){
  return color;
}

int TreeNode::get_size(){
  return size;
}

char* TreeNode::get_country(){
  return value->get_country();
}

char* TreeNode::get_disease(){
  return value->get_disease();
}

Record* TreeNode::get_record(){
  return value;
}

void TreeNode::set_right(TreeNode* node){
  right = node;
}

void TreeNode::set_left(TreeNode* node){
  left = node;
}

void TreeNode::set_parent(TreeNode* node){
  parent = node;
}

void TreeNode::set_color(enum color_t col){
  color = col;
}

void TreeNode::set_size(int s){
  size = s;
}

void TreeNode::increase_size(){
  size++;
}

void TreeNode::rotate_left(){
  TreeNode *nnew = right;
  TreeNode *temp = get_parent();

  if(nnew == NULL){
    cout << "Error while trying to rotate left" << endl;
    // Since the leafs of a red-black tree are empty, they cannot become internal nodes.
    return;
  }

  right = nnew->get_left();
  nnew->set_left(this);
  parent = nnew;
  // Handle other child/parent pointers
  if (right != NULL){
    right->set_parent(this);
  }

  // Initially n could be the root.
  if(temp != NULL){
    if(this == temp->get_left()){
      temp->set_left(nnew);
    } else if ( this == temp->get_right() ){
      temp->set_right(nnew);
    }
  }
  nnew->set_parent(temp);
}

void TreeNode::rotate_right(){
  TreeNode *nnew = left;
  TreeNode *temp = get_parent();

  if(nnew == NULL){
    cout << "Error while trying to rotate right" << endl;
    // Since the leaves of a red-black tree are empty, they cannon become internal nodes.
    return;
  }

  left = nnew->get_right();
  nnew->set_right(this);
  parent = nnew;

  // Handle other child/parent pointers
  if ( left != NULL ){
    left->set_parent(this);
  }

  // Initially n could be the root
  if(temp != NULL){
    if (this == temp->get_left()){
      temp->set_left(nnew);
    } else if ( this == temp->get_right() ){
      temp->set_right(nnew);
    }
  }
  nnew->set_parent(temp);
}

TreeNode* TreeNode::insert(TreeNode *node){
  if(node == NULL){
    cout << "Not a valid node given to insert" << endl;
    return NULL;
  }
  // Insert new TreeNode into the current tree
  insert_recurse(this, node);

  // Repair the tree in case any of the red-black properties have been violated.
  insert_repair_tree(node);

  // Find the new root to return
  TreeNode *temp = node;
  while(temp->get_parent() != NULL){
    temp = temp->get_parent();
  }
  return temp;
}

void TreeNode::insert_recurse(TreeNode *root, TreeNode *node){
  // Recursively descend the tree until a leaf is found.
  if ( root != NULL ){
    if ( (*node->get_key()) < (*root->get_key()) ){
      if ( root->get_left() != NULL ){
        insert_recurse(root->get_left(), node);
        root->increase_size();
        return;
      } else {
        root->increase_size();
        root->set_left(node);
      }
    } else {
      // node->key >= root->key
      if ( root->get_right() != NULL){
        insert_recurse(root->get_right(), node);
        root->increase_size();
        return;
      } else {
        root->increase_size();
        root->set_right(node);
      }
    }
  }

  // Insert new TreeNode node.
  node->set_parent(root);
  node->set_left(NULL);
  node->set_right(NULL);
  node->set_color(RED);
  node->set_size(1);
}

void TreeNode::insert_repair_tree(TreeNode *node){
  if ( node->get_parent() == NULL){
    insert_case1(node);
  } else if ( node->get_parent()->get_color() == BLACK){
    insert_case2(node);
  } else if ( node->get_uncle() != NULL && node->get_uncle()->get_color() == RED){
    insert_case3(node);
  } else {
    insert_case4(node);
  }
}

void TreeNode::insert_case1(TreeNode *node){
  node->set_color(BLACK);
}

void TreeNode::insert_case2(TreeNode *node){
  // Do nothing since the tree is still valid.
  return;
}

void TreeNode::insert_case3(TreeNode *node){
  node->get_parent()->set_color(BLACK);
  node->get_uncle()->set_color(BLACK);
  node->get_grandparent()->set_color(RED);
  insert_repair_tree(node->get_grandparent());
}

void TreeNode::insert_case4(TreeNode *node){
  TreeNode *temp = node->get_parent();
  TreeNode *t_temp = node->get_grandparent();

  if ( node == temp->get_right() && temp == t_temp->get_left() ){
    temp->rotate_left();
    node = node->get_left();
  } else if ( node == temp->get_left() && temp == t_temp->get_right() ){
    temp->rotate_right();
    node = node->get_right();
  }

  insert_case4_step2(node);
}

void TreeNode::insert_case4_step2(TreeNode *node){
  TreeNode *temp = node->get_parent();
  TreeNode *t_temp = node->get_grandparent();

  if ( node == temp->get_left() ){
    t_temp->rotate_left();
  } else {
    t_temp->rotate_right();
  }

  temp->set_color(BLACK);
  t_temp->set_color(RED);
}

void TreeNode::show(){
  cout << "||-ENTRY: " << key->get_date() << endl;
}

RBTree::RBTree() : root(NULL), type(NULL){
}

RBTree::RBTree(TreeNode *t_root) : root(t_root), type(NULL){
  // For test purposes only, need to rewrite the destructor
}

RBTree::RBTree(Date *date, Record *record) : type(NULL){
  root = new TreeNode(date, record);
}

RBTree::~RBTree(){
  delete_recurse(root);
}

bool RBTree::add(Date *key_date, Record *new_record){
  TreeNode *new_node = new TreeNode(key_date, new_record);

  root = root->insert(new_node);
  return true;
}

void RBTree::show(){
  print_tree(root);
}

void RBTree::print_tree(TreeNode *node){
  if(node == NULL){
    return;
  }
  print_tree(node->get_left());
  //cout << "done left" << endl;
  node->show();
  print_tree(node->get_right());
}

void RBTree::delete_recurse(TreeNode *node){
  if(node == NULL){
    return ;
  }
  TreeNode* temp_r = node->get_right();
  TreeNode* temp_l = node->get_left();
  delete node;
  delete_recurse(temp_r);
  delete_recurse(temp_l);
}

void RBTree::global_disease_stats(){
  cout << "||--No. of recorded hits: " << root->get_size() << endl;
}

void RBTree::global_disease_stats(Date *date1, Date *date2){
  cout << "||--No. of recorded hits: " << global_disease_stats(date1, date2, root) << endl;
}

int RBTree::global_disease_stats(Date *date1, Date *date2, TreeNode *node){
  if(node == NULL){
    return 0;
  }
  Date *dd = node->get_key();
  if(*date1 > *dd){
    // means that starting date is after the date of the node.
    // try to go to the right subtree and do the same.
    return global_disease_stats(date1, date2, node->get_right());
  } else if(*dd > *date2){
    // means that ending date is before the date of the node.
    return global_disease_stats(date1, date2, node->get_left());
  } else{
    // means that the node date is between the date1 and date2
    return node->get_size();
  }
}

void RBTree::disease_frequency(Date *date1, Date *date2, const char *country){
  cout << "||--No. of recorder hits: " << disease_frequency(date1, date2, country, root);
}

int RBTree::disease_frequency(Date *date1, Date *date2, const char *country, TreeNode *node){
  static int result = 0;
  if(node == NULL){
    return 0;
  }
  Date *dd = node->get_key();
  if(*date1 > *dd){
    return disease_frequency(date1, date2, country, node->get_right());
  } else if (*dd > *date2){
    return disease_frequency(date1, date2, country, node->get_left());
  } else {
    if(strcmp(country, node->get_country()) == 0){
      result++;
    }
    disease_frequency(date1, date2, country, node->get_right());
    disease_frequency(date1, date2, country, node->get_left());
  }
  return result;
}

void RBTree::topk_diseases(int k){
  LLTree *ll = new LLTree();
  topk_diseases(root, ll);
  ll->topk_diseases(k);
  delete ll;
}

void RBTree::topk_diseases(TreeNode *node, LLTree *ll){
  if(node == NULL){
    return;
  } else {
    ll->add(node->get_disease());
    topk_diseases(node->get_right(), ll);
    topk_diseases(node->get_left(), ll);
  }
}

void RBTree::topk_diseases(int k, Date *date1, Date *date2){
  LLTree *ll = new LLTree();
  topk_diseases(root, ll, date1, date2);
  ll->topk_diseases(k);
  delete ll;
}

void RBTree::topk_diseases(TreeNode *node, LLTree *ll, Date *date1, Date *date2){
  if(node == NULL){
    return;
  }
  Date *dd = node->get_key();
  if(*date1 > *dd){
    return;
  } else if(*dd > *date2){
    return;
  } else {
    ll->add(node->get_disease());
    topk_diseases(node->get_right(), ll, date1, date2);
    topk_diseases(node->get_left(), ll, date1, date2);
  }
}

void RBTree::topk_countries(int k){
  LLTree *ll = new LLTree();
  topk_countries(root, ll);
  delete ll;
}

void RBTree::topk_countries(TreeNode *node, LLTree *ll){
  if(node == NULL){
    return;
  } else {
    ll->add(node->get_country());
    topk_countries(node->get_right(), ll);
    topk_countries(node->get_left(), ll);
  }
}

void RBTree::topk_countries(int k, Date *date1, Date *date2){
  LLTree *ll = new LLTree();
  topk_countries(root, ll, date1, date2);
  ll->topk_countries(k);
  delete ll;
}

void RBTree::topk_countries(TreeNode *node, LLTree *ll, Date *date1, Date *date2){
  if(node == NULL){
    return;
  }
  Date *dd = node->get_key();
  if(*date1 > *dd){
    return;
  } else if(*dd > *date2){
    return;
  } else {
    ll->add(node->get_country());
    topk_countries(node->get_right(), ll, date1, date2);
    topk_countries(node->get_left(), ll, date1, date2);
  }
}

void RBTree::num_current_patients_1(){
  LNTree *ln = new LNTree();
  num_current_patients_1(root, ln);
  ln->num_current_patients();
  delete ln;
}

void RBTree::num_current_patients_1(TreeNode *node, LNTree *ln){
  if(node == NULL){
    return;
  } else {
    if(strcmp(node->get_key()->get_date(), "-") == 0){
      ln->add(node->get_record());
    }
    num_current_patients_1(node->get_right(), ln);
    num_current_patients_1(node->get_left(), ln);
  }
}

void RBTree::num_current_patients_2(){
  cout << num_current_patients_2(root) << " still hospitalized."  << endl;
}

int RBTree::num_current_patients_2(TreeNode *node){
  static int patients = 0;
  if(strcmp(node->get_key()->get_date(), "-") == 0){
    patients++;
  }
  num_current_patients_2(node->get_right());
  num_current_patients_2(node->get_left());
  return patients;
}
