#include <iostream>
#include <cstring>
#include "l_item.h"

using namespace std;

LNode::LNode() : record(NULL) {
}

LNode::LNode(Record *rec) : record(rec) {
}

LNode::~LNode(){
}

void LNode::set_record(Record *rec){
  record = rec;
}

void LNode::set_next(LNode *node){
  if(next_node != NULL){
    delete next_node;
  }
  next_node = node;
}

Record* LNode::get_record(){
  return record;
}

LNode* LNode::get_next(){
  return next_node;
}

LNTree::LNTree(){
  head = new LNode();
}

LNTree::LNTree(LNode *node) : head(node){
}

LNTree::LNTree(Record *record){
  head = new LNode(record);
}

LNTree::~LNTree(){
  LNode *temp = head;
  while(temp != NULL){
    head = head->get_next();
    delete temp;
    temp  = head;
  }
}

void LNTree::add(Record *record){
  LNode *new_node = new LNode(record);
  if(head == NULL){
    head = new_node;
    return;
  }
  LNode *temp = head;
  while(temp->get_next() != NULL){
    temp = temp->get_next();
  }
  temp->set_next(new_node);
}

void LNTree::num_current_patients(){
  if(head == NULL) {
    cout << "No patients are hospitalized." << endl;
    return;
  }
  cout << "|--Patients that are still hospitalized:" << endl;
  LNode *temp;
  temp = head;
  while(temp != NULL){
    temp->get_record()->print_record();
    temp = temp->get_next();
  }
}

LItem::LItem() : name(NULL), amount(0), next_item(NULL){
}

LItem::LItem(char *item) : amount(1), next_item(NULL){
  name = (char*)malloc(sizeof(char)*(strlen(item)+1));
  strcpy(name, item);
}

LItem::~LItem(){
  free(name);
}

void LItem::set_name(char *item){
  if(name != NULL){
    free(name);
  }
  name = (char*)malloc(sizeof(char)*(strlen(item)+1));
  strcpy(name, item);
}

void LItem::set_next(LItem *next){
  if(next_item != NULL){
    delete next_item;
  }
  next_item = next;
}

char* LItem::get_name(){
  return name;
}

LItem* LItem::get_next(){
  return next_item;
}

int LItem::get_amount(){
  return amount;
}

void LItem::increase_amount(){
  amount++;
}

LLTree::LLTree() : head(NULL){
}

LLTree::LLTree(LItem *item) : head(item){
}

LLTree::LLTree(char *name){
  head = new LItem(name);
}

LLTree::~LLTree(){
  LItem *temp;
  temp = head;
  while(temp != NULL){
    head = temp->get_next();
    delete temp;
    temp = head;
  }
}

void LLTree::add(LItem *item){
  if(head == NULL){
    head = item;
    head->set_next(NULL);
  } else {
    LItem *temp = head;
    while(temp->get_next() != NULL){
      if(strcmp(temp->get_name(), item->get_name()) == 0){
        temp->increase_amount();
        return;
      }
      temp = temp->get_next();
    }
    if(strcmp(temp->get_name(), item->get_name()) == 0){
      temp->increase_amount();
      return;
    } else {
      temp->set_next(item);
    }
  }
}

void LLTree::add(char *name){
  if(head == NULL){
    head = new LItem(name);
    return;
  }
  LItem *temp = head;
  while(temp->get_next() != NULL){
    if(strcmp(name, temp->get_name()) == 0){
      temp->increase_amount();
      return;
    }
    temp = temp->get_next();
  }
  if(strcmp(name, temp->get_name()) == 0){
    temp->increase_amount();
    return;
  } else {
    LItem *item = new LItem(name);
    temp->set_next(item);
  }
}

void LLTree::remove(LItem *item){
  if(head == item){
    LItem *temp = head;
    head = head->get_next();
    delete temp;
  } else {
    LItem *previous = head;
    LItem *current = head->get_next();

    while(current != NULL){
      if(current == item){
        previous->set_next(current->get_next());
        delete current;
        break;
      } else {
        previous = current;
        current = current->get_next();
      }
    }
    cout << "Error: didn't find the item to remove." << endl;
  }
}

void LLTree::topk_diseases(int k){
  for(int i = 0; i < k; i++){
    if(head == NULL){
      return;
    }
    int max = head->get_amount();
    LItem *item = head;
    LItem *temp = head->get_next();
    while(temp != NULL){
      if(temp->get_amount() > max){
        max = temp->get_amount();
        item = temp;
      }
      temp = temp->get_next();
    }
    cout << "Top " << i+1 << " disease: " << item->get_name() << ", hits: " << item->get_amount() << endl;
    remove(item);
  }
}

void LLTree::topk_countries(int k){
  for(int i = 0; i < k; i++){
    if(head == NULL){
      return;
    }
    int max = head->get_amount();
    LItem *item = head;
    LItem *temp = head->get_next();
    while(temp != NULL){
      if(temp->get_amount() > max){
        max = temp->get_amount();
        item = temp;
      }
      temp = temp->get_next();
    }
    cout << "Top " << i+1 << " country: " << item->get_name() << ", hits: " << item->get_amount() << endl;
    remove(item);
  }
}
