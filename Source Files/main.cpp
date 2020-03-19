#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <getopt.h>
#include "record.h"
#include "linked_list.h"

using namespace std;

static struct option long_options[] = {
  {"h1", required_argument, NULL, 'h'},
  {"h2", required_argument, NULL, 't'},
  {NULL, 0, NULL, 0}
};

int main(int argc, char *argv[]){
  LinkedList ll;
  int dis_ht_noe, cou_ht_noe, bucket_size;
  char *records_file;

  //  Parser for the command line arguments
  int ch;
  while ((ch = getopt_long_only(argc, argv, "p:b:", long_options, NULL)) != -1){
    switch (ch) {
      case 'p':
        /* Passes the value of the patientRecordsFile given as argument after -p, to the variable records_file */
        cout << "Option -p with value: " << optarg << endl;
        records_file = (char*)malloc(strlen(optarg)+1);
        strcpy(records_file, optarg);
        //cout << strlen(records_file) << endl;
        //cout << strlen(optarg) << endl;
        break;
      case 'h':
        /* Passes the value of the diseaseHashtableNumOfEntries given as argument after -h1, to the variable dis_ht_noe */
        cout << "Option -h1 with value: " << optarg << endl;
        dis_ht_noe = atoi(optarg);
        //cout << dis_ht_noe << endl;
        break;
      case 't':
        /* Passes the value of the countryHashtableNumOfEntries given as argument after -h2, to the variable cou_ht_noe */
        cout << "Option -h2 with value: " << optarg << endl;
        cou_ht_noe = atoi(optarg);
        break;
      case 'b':
        /* Passes the value of the bucketSize given as argument after -b, to the variable bucket_size */
        cout << "Option -b with value: " << optarg << endl;
        bucket_size = atoi(optarg);
        break;
    }
  }

  ifstream file;
  file.open(records_file);
  string line;
  if(file.is_open()){
    while( getline(file, line) ){
        //cout << line << endl;
        istringstream ss(line);

        while(ss){

          string a, b, c, d, e, f, g;
          ss >> a >> b >> c >> d >> e >> f >> g;
          //cout << a << b << c << d << e << f << g << endl;
          ss.sync();

          Date *new_entryDate = new Date(f);
          Date *new_exitDate = new Date(g);
          if(*new_exitDate < *new_entryDate){
            // Record is invalid --> ignore
            cout << "Invalid record" << endl;
            delete new_entryDate;
            delete new_exitDate;
          } else {
            // Record is valid --> add to list
            Record  *new_record = new Record(stoi(a), b.c_str(), c.c_str(), d.c_str(), e.c_str(), new_entryDate, new_exitDate);
            if( ll.add(new_record) == false){
                // Record with the same ID already exists --> ignore
                delete new_record;
                cout << "Duplicate ID" << endl;
            }
          }
        }
    }
    file.close();
  } else {
    // Error while opening file
  }

  ll.print_list();

  free(records_file);
}
