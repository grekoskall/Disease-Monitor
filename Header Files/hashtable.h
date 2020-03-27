#ifndef _HASH_TABLE_
#define _HASH_TABLE_
#include "record.h"
#include "trees.h"

class BucketRecord{
  private:
    char *record_name;
    RBTree *pointer;
  public:
    BucketRecord();
    BucketRecord(char*);
    BucketRecord(char*, RBTree*);
    ~BucketRecord();

    char* get_name();
    RBTree* get_tree();
    void set_name(const char*);
    void set_tree(RBTree*);
};

class Bucket{
  private:
    BucketRecord  **data;
    int bucket_size;
    int offset;
    Bucket *next_bucket;
  public:
    Bucket();
    Bucket(int);
    ~Bucket();

    Bucket *get_next();
    int get_offset();

    bool add(const char *, Record *);

    void show();
};

class HashTable{
  private:
    int entries;
    Bucket **head;
  public:
    HashTable();
    HashTable(int );
    HashTable(int, int);
    ~HashTable();

    bool add(const char *, Record *);

    int hash(const char *);

    void show();
};

#endif
