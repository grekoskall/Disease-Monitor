#include <iostream>
#include <cstring>
#include "hashtable.h"

using namespace std;

BucketRecord::BucketRecord() : record_name(NULL), pointer(NULL){
}

BucketRecord::BucketRecord(char *name) : pointer(NULL){
  record_name = (char*)malloc(sizeof(char)*(strlen(name)+1));
  strcpy(record_name, name);
}

BucketRecord::BucketRecord(char *name, RBTree *point) : pointer(point){
  record_name = (char*)malloc(sizeof(char)*(strlen(name)+1));
  strcpy(record_name, name);
}

BucketRecord::~BucketRecord(){
  free(record_name);
  delete pointer;
}

char* BucketRecord::get_name(){
  return record_name;
}

RBTree* BucketRecord::get_tree(){
  return pointer;
}

void BucketRecord::set_name(const char* name){
  record_name = (char*)malloc(sizeof(char)*(strlen(name)+1));
  strcpy(record_name, name);
}

void BucketRecord::set_tree(RBTree *tree){
  pointer = tree;
}

Bucket::Bucket() : data(NULL), bucket_size(0), offset(0), next_bucket(NULL){
}

Bucket::Bucket(int size) : bucket_size(size), offset(0), next_bucket(NULL){
  if ( (size-sizeof(Bucket*)) <= 0){
    cout << "Impossible to create a bucket with negative size: bucket size given is too small." << endl;
    size = 520;
  }
  int no_of_entries = size%(sizeof(BucketRecord));
  data = (BucketRecord**)calloc(no_of_entries, sizeof(BucketRecord));
  for (int i = 0 ; i < no_of_entries ; i++){
    data[i] = new BucketRecord();
  }
}

Bucket::~Bucket(){
  int no_of_entries = bucket_size%(sizeof(BucketRecord));
  for(int i = 0 ; i < no_of_entries ; i++){
    delete data[i];
  }
  Bucket *temp;
  temp = next_bucket;
  while(temp != NULL){
      next_bucket = next_bucket->get_next();
      delete temp;
      temp = next_bucket;
  }
  free(data);
}

Bucket* Bucket::get_next(){
  return next_bucket;
}

int Bucket::get_offset(){
  return offset;
}

bool Bucket::add(const char *key, Record *record){
  bool result =  true;
  if(data == NULL){
    cout << "The bucket has not been initialized correctly" << endl;
    return false;
  }
  if(offset == 0){
    // This is the first record kept
    //cout << "CASE 1" << endl;
    RBTree *database = new RBTree;
    result = database->add(record->get_entryDate(), record);
    if(result == false ){
      cout << "Error while adding a first record to a new data tree." << endl;
      return result;
    }
    data[offset]->set_name(key);
    data[offset]->set_tree(database);
    offset++;
    return result;
  } else {
      // Search the bucket for a record with the same key
      //cout << "CASE 2" << endl;
      int flag = -1;
      for(int i = 0; i < offset; i++){
        if( strcmp(data[i]->get_name(), key) == 0){
          flag = i;
          break;
        }
      }
      if(flag > -1){
        // We found the record with the same key, so just add the record to the corrensponding structure
        //cout << "CASE 2 STEP 1" << endl;
        RBTree *database = data[flag]->get_tree();
        result = database->add(record->get_entryDate(), record);
        if(result == false){
          cout << "Error while adding a record to an existing data tree." << endl;
        }
        return result;
      } else {
        // There is no record with the same key. so we create one
        //cout << "CASE 2 STEP 2" << endl;
        if(next_bucket == NULL){
          // If this is the last bucket of the chain, then insert it here
          //cout << "CASE 2 STEP 2 BIT 1" << endl;
          int remaining_space = bucket_size%(sizeof(BucketRecord))-(offset+1);
          if(remaining_space < 0){
            // There is no space in this bucket --> add the record to the next
            //cout << "CASE 2 STEP 2 BIT 1 LOL 1" << endl;
            next_bucket = new Bucket(bucket_size);
            result = next_bucket->add(key, record);
            if( result == false ){
              cout << "Error while inserting to a next bucket." << endl;
            }
            return result;
          } else{
            // There is space in the bucket --> add the record here
            //cout << "CASE 2 STEP 2 BIT 1 LOL 2" << endl;

            RBTree *database =  new RBTree;
            result = database->add(record->get_entryDate(), record);
            if(result == false) {
              cout << "Error while adding a record to a new data tree." << endl;
              return result;
            }
            data[offset]->set_name(key);
            data[offset]->set_tree(database);
            offset++;
          }
        } else {
          // There are more buckers in the chain, so try to add to the next.
          //cout << "CASE 2 STEP 2 BIT 2" << endl;
          result = next_bucket->add(key, record);
          if (result == false){
            cout << "Error while inserting to a next bucket." << endl;
          }
          return result;
        }
      }
  }
  return result;
}

void Bucket::show(){
  if(offset == 0 ){
    cout << "EMPTY" << endl;
    return;
  }
  cout << "---------------" << endl;
  cout << "||SIZE\t:" << bucket_size << endl;
  cout << "||ITEMS\t:" << offset << endl;
  for(int i = 0; i < offset; i++){
    RBTree *database = data[i]->get_tree();
    cout << "||--DATA:" << data[i]->get_name() << endl;
    database->show();
    if(next_bucket == NULL){
      cout << "||--NEXT:" << "  NO" << endl;
    } else {
      cout << "||--NEXT:" << endl;
      next_bucket->show();
    }

  }
}

HashTable::HashTable() : entries(0), head(NULL){
}

HashTable::HashTable(int entries_num) : entries(entries_num){
  head = (Bucket**)calloc(entries_num, sizeof(Bucket));
  for(int i = 0 ; i < entries_num ; i++){
    head[i] = new Bucket();
  }
}

HashTable::HashTable(int entries_num, int bucket_size) : entries(entries_num){
  head = (Bucket**)calloc(entries_num, sizeof(Bucket));
  for(int i = 0 ; i < entries_num ; i++){
    head[i] = new Bucket(bucket_size);
  }
}

HashTable::~HashTable(){
  for(int i = 0 ; i < entries ; i++){
    delete head[i];
  }
  free(head);
}

bool HashTable::add(const char *key, Record *rec){
  int hash_position = hash(key);
  //cout << "Over : "  << hash_position << endl;
  return head[hash_position]->add(key, rec);
}

int HashTable::hash(const char *key){
  return (int)(*key)%entries;
}

void HashTable::show(){
  //cout << "Entries of hashtable: " << entries << endl;
  for (int i = 0 ; i < entries ; i++) {
    if(head[i]->get_offset() > 0 ){
      cout << "---Bucket no." << i << ": " << endl;
      head[i]->show();
    }
  }
}
