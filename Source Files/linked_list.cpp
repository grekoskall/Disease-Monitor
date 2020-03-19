#include <iostream>
#include "linked_list.h"

using namespace std;

Node::Node() : data(NULL), next(NULL){
}

Node::Node(Record *rec) : data(rec), next(NULL){
}

Node::Node(Record *rec, Node *nex) : data(rec), next(nex){
}

Node::~Node(){
  delete data;
}

int Node::get_recordID(){
  return data->get_recordID();
}

void Node::set_data(Record *dat){
  data = dat;
}

Node* Node::get_next(){
  return next;
}

void Node::set_next(Node *new_next){
  next = new_next;
}

void Node::print_node(){
  data->print_record();
}

LinkedList::LinkedList() : head(NULL){
}

LinkedList::LinkedList(Record *record){
  Node *node = new Node(record);
  this->add(node);
}

LinkedList::LinkedList(Node *node) : head(node){
}

LinkedList::~LinkedList(){
  if(head == NULL){
  } else {
    Node *temp;
    temp = head;
    while(head != NULL){
      head = temp->get_next();
      delete temp;
      temp = head;
    }
  }
}

bool LinkedList::add(Node *new_node){
  if( this->check_double_record( new_node->get_recordID()) ){
    return false;
  }
  new_node->set_next(head);
  head = new_node;
  return true;
}

bool LinkedList::add(Record *new_record){
  if( this->check_double_record( new_record->get_recordID()) ){
    return false;
  }
  Node *new_node = new Node(new_record, head);
  head = new_node;
  return true;
}

bool LinkedList::check_double_record(int recId){
  Node *temp;
  temp = head;

  while(temp != NULL){
    if(temp->get_recordID() == recId){
      return true;
    }
    temp = temp->get_next();
  }
  return false;
}

void LinkedList::print_list(){
  Node *temp;
  temp = head;
  cout << "\t\t- PRINTING LIST -" << endl;
  while(temp != NULL){
    temp->print_node();
    temp = temp->get_next();
  }
  cout << "\t\t- END OF LIST -" << endl;
}
