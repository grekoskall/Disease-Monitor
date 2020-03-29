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

    void global_disease_stats();
    void global_disease_stats(Date *, Date *);

    void disease_frequency(Date *, Date *, const char *);
    void disease_frequency(Date *, Date *, const char *, const char *);

    void topk_diseases(int);
    void topk_diseases(int, Date *, Date *);

    void topk_countries(int);
    void topk_countries(int, Date *, Date *);

    void num_current_patients_1();  // Prints all the recrods
    void num_current_patients_2();  // Pritns the number of records
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
    void global_disease_stats();
    void global_disease_stats(Date *, Date *);

    void disease_frequency(Date *, Date *, const char *);
    void disease_frequency(Date *, Date *, const char *, const char *);

    void topk_diseases(int, const char *);
    void topk_diseases(int, const char *, Date *, Date *);

    void topk_countries(int, const char *);
    void topk_countries(int, const char *, Date *, Date *);

    void num_current_patients();
    void num_current_patients(const char *);
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
    void global_disease_stats();
    void global_disease_stats(Date *, Date *);

    void disease_frequency(Date *, Date *, const char *);
    void disease_frequency(Date *, Date *, const char *, const char *);

    void topk_diseases(int, const char *);
    void topk_diseases(int, const char *, Date *, Date *);

    void topk_countries(int, const char *);
    void topk_countries(int, const char *, Date *, Date *);

    void num_current_patients();
    void num_current_patients(const char*);
};

#endif
