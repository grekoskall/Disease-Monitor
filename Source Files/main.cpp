#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <getopt.h>
#include "linked_list.h"
#include "hashtable.h"
#include "trees.h"

using namespace std;

static struct option long_options[] = {
  {"h1", required_argument, NULL, 'h'},
  {"h2", required_argument, NULL, 't'},
  {NULL, 0, NULL, 0}
};

int main(int argc, char *argv[]){
  LinkedList ll; // Linked list that will hold the records

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
  // Now we have all command line arguments passed to variables inside main
  // We can now create the data structures
  HashTable disease_ht(dis_ht_noe, bucket_size);
  //cout << dis_ht_noe << bucket_size << endl;
  HashTable country_ht(cou_ht_noe, bucket_size);

  ifstream file;
  file.open(records_file);
  string line;
  if(file.is_open()){
    while( getline(file, line) ){
        //cout << line << endl;
        istringstream ss(line);

        while(ss){
          // a=recordID, b=patient First name, c=patient Last name, d=disease, e=country, f=Entry date, g=Exit date
          string a, b, c, d, e, f, g;
          ss >> a >> b >> c >> d >> e >> f >> g;
          //cout << a << b << c << d << e << f << g << endl;
          ss.sync();

          Date *new_entryDate = new Date(f);
          Date *new_exitDate = new Date(g);
          if(*new_entryDate > *new_exitDate){
            // Record is invalid --> ignore
            cout << "Invalid record" << endl;
            delete new_entryDate;
            delete new_exitDate;
          } else {
            // Record is valid --> add to list
            Record  *new_record = new Record(stoi(a), b.c_str(), c.c_str(), e.c_str(), d.c_str(), new_entryDate, new_exitDate);

            if( ll.add(new_record) == false){
                // Record with the same ID already exists --> ignore
                delete new_record;
                cout << "Duplicate ID" << endl;
            }
            // Record is now added to the linked list

            // Now add the data to the hashtables and update the corrensponding trees
            disease_ht.add(d.c_str(), new_record);
            //cout << "and out" << endl;
            country_ht.add(e.c_str(), new_record);
          }
        }
    }
    file.close();
  } else {
    // Error while opening file
  }

  ll.print_list();

  cout << "\t- DISEASE HT -" << endl;
  disease_ht.show();
  cout << "\t- END OF HT -" << endl;
  //cout << endl;
  cout << "\t- COUNTRY HT -" << endl;
  country_ht.show();
  cout << "\t- END OF HT -" << endl;
  //cout << endl;

  string str;
  string exit_str = ("/exit");
  string gds_str = ("/globalDiseaseStats");
  string df_str = ("/diseaseFrequency");
  string topkd_str = ("/topk-Diseases");
  string topkc_str = ("/topk-Countries");
  string ipr_str = ("/insertPatientRecord");
  string rpe_str = ("/recordPatientExit");
  string ncp_str = ("/numCurrentPatients");
  while(str.compare(exit_str) != 0){
    cout << " - Please enter your command -" << endl;
    getline(cin, str);
    istringstream ss(str);
    string str;
    getline(ss, str, ' ');

    if(str.compare(gds_str) == 0){
      // /globalDiseaseStats [date1 date2]
      // For every disease, print the number of hits, during the period between date1 and date2 if they are defined.
      string date1;
      if(getline(ss, date1, ' ')){
        // this means there was a second argument, hopefully date1
        string date2;
        if(getline(ss, date2, ' ')){
          // since date1 was given, the user must have specified date2
          Date *new_date1 = new Date(date1.c_str());
          Date *new_date2 = new Date(date2.c_str());

          if(*new_date1 > *new_date2){
            // Dates are invalid
            cout << "Error: the dates given don't add up." << endl;
          } else {
            // Dates are valid, proceed with presenting data.
            disease_ht.global_disease_stats(new_date1, new_date2);
          }
        } else {
          cout << "Error: no second date given." << endl;
        }
      } else {
        // general case without any date limitations.
        disease_ht.global_disease_stats();
      }
    } else if(str.compare(df_str) == 0){
      // /diseaseFrequency virusName [country] date1 date2
      // NO [country] : for the disease virusName, print the number of hits, during the period between date1 and date2.
      // WITH [country] : for the disease virusName, print the number of hits but for the country given, during the period between date1 and date2.
      string virusName;
      if(getline(ss, virusName, ' ')){
        // this means that virusName was given as a second argument
        string a, b, c, d;
        getline(ss, a, ' ');
        getline(ss, b, ' ');
        getline(ss, c, ' ');
        if(getline(ss, d, ' ')){
          // There was a country argument given.
          Date *new_date1 = new Date(c.c_str());
          Date *new_date2 = new Date(d.c_str());
          if(*new_date1 > *new_date2){
            cout << "Error: the dates given don't add up." << endl;
          } else {
            disease_ht.disease_frequency(new_date1, new_date2, a.c_str(), b.c_str());
          }
        } else {
          // There wasn't a country argument given.
          Date *new_date1 = new Date(b.c_str());
          Date *new_date2 = new Date(c.c_str());
          if(*new_date1 > *new_date2){
            cout << "Error: the dates given don't add up." << endl;
          } else {
            disease_ht.disease_frequency(new_date1, new_date2, a.c_str());
          }
        }
      } else {
        cout << "Error: no second argument given: virusName." << endl;
      }
    } else if(str.compare(topkd_str) == 0){
      // /topk-Diseases k country [date1 date2]
      // Prints for the country given the viruses that have the top k number of hits, during the period between date1 and date2 if defined.
      string k, country, date1;
      getline(ss, k, ' ');
      getline(ss, country, ' ');
      if(getline(ss, date1, ' ')){
        // Means that the first date is defined, therefore the second must also be defined.
        string date2;
        if(getline(ss, date2, ' ')){
          // Means that a second date was given.
          Date *new_date1 = new Date(date1.c_str());
          Date *new_date2 = new Date(date2.c_str());
          if(*new_date1 > *new_date2){
            cout << "Error: the dates given don't add up." << endl;
          } else{
            country_ht.topk_diseases(atoi(k.c_str()), country.c_str(), new_date1, new_date2);
          }
        } else {
          // A second date wasn't given.
          cout << "Error: no second date given." << endl;
        }
      } else {
        // Means that dates are not defined.
        country_ht.topk_diseases(atoi(k.c_str()), country.c_str());
      }
    } else if(str.compare(topkc_str) == 0){
      // /topk-Diseases k disease [date1 date2]
      // Prints for the disease the countries that have the top k number of hits.
      string k, country, date1;
      getline(ss, k, ' ');
      getline(ss, country, ' ');
      if(getline(ss, date1, ' ')){
        // Means that the first date is defined, therefore the second must also be defined.
        string date2;
        if(getline(ss, date2, ' ')){
          // Means that a second date was given.
          Date *new_date1 = new Date(date1.c_str());
          Date *new_date2 = new Date(date2.c_str());
          if(*new_date1 > *new_date2){
            cout << "Error: the dates given don't add up." << endl;
          } else {
            disease_ht.topk_countries(atoi(k.c_str()), country.c_str(), new_date1, new_date2);
          }
        } else {
          // A second date wasn't given.
          cout << "Error: no second date given." << endl;
        }
      } else {
        // Means that dates are not defined.
        disease_ht.topk_countries(atoi(k.c_str()), country.c_str());
      }
    } else if(str.compare(ipr_str) == 0){
      // /insertPatientRecord recordID patientFirstName patientLastName diseaseID countryID entryDate [exitDate]
      // insert in the system the new record with its attributes. the exitDate attribute is optional.
      string recordID;
      if(!getline(ss, recordID, ' ')){
        cout << "Error: no recordID given." << endl;
      } else {
        string patientFirstName;
        if(!getline(ss, patientFirstName, ' ')){
          cout << "Error: no patient first name given." << endl;
        } else {
          string patientLastName;
          if(!getline(ss, patientLastName, ' ')){
            cout << "Error: no patient last name given." << endl;
          } else {
            string diseaseID;
            if(!getline(ss, diseaseID, ' ')){
              cout << "Error: no diseaseID given." << endl;
            } else {
              string countryID;
              if(!getline(ss, countryID, ' ')){
                cout << "Error: no countryID given." << endl;
              } else {
                string entryDate;
                if(!getline(ss, entryDate, ' ')){
                  cout << "Error: no entryDate given." << endl;
                } else {
                  string exitDate;
                  if(!getline(ss, exitDate, ' ')){
                    // Exit date wasn't given --> it will default to: "-"
                    Date *entry_date = new Date(entryDate);
                    Date *exit_date = new Date();

                    Record *new_record = new Record(atoi(recordID.c_str()), patientFirstName.c_str(), patientLastName.c_str(), countryID.c_str(), diseaseID.c_str(), entry_date, exit_date);
                    if( ll.add(new_record) == false){
                        // Record with the same ID already exists --> ignore
                        delete new_record;
                        cout << "Duplicate ID" << endl;
                    }
                    disease_ht.add(diseaseID.c_str(), new_record);
                    country_ht.add(countryID.c_str(), new_record);
                  } else {
                    // Exit date was given
                    Date *entry_date = new Date(entryDate);
                    Date *exit_date = new Date(exitDate);

                    Record *new_record = new Record(atoi(recordID.c_str()), patientFirstName.c_str(), patientLastName.c_str(), countryID.c_str(), diseaseID.c_str(), entry_date, exit_date);
                    if( ll.add(new_record) == false){
                        // Record with the same ID already exists --> ignore
                        delete new_record;
                        cout << "Duplicate ID" << endl;
                    }
                    disease_ht.add(diseaseID.c_str(), new_record);
                    country_ht.add(countryID.c_str(), new_record);
                  }
                }
              }
            }
          }
        }
      }
    } else if(str.compare(rpe_str) == 0){
      // /recordPatientExit recordID exitDate
      // Add the exitDate to the record with ID recordID.
      string recordID;
      if(!getline(ss, recordID, ' ')){
        cout << "Error: no recordID given." << endl;
      } else {
        string exitDate;
        if(!getline(ss, exitDate, ' ')){
          cout << "Error: no exitDate given." << endl;
        } else {
          Date *exit_date = new Date(exitDate);
          // All arguments were given.
          if( ll.record_patient_exit(atoi(recordID.c_str()), exit_date) == false){
            cout << "The recordID given does not exist." << endl;
          } else {
            cout << "Records' exitDate updated." << endl;
          }
        }
      }
    } else if(str.compare(ncp_str) == 0){
      // /numCurrentPatients [disease]
      // WITH disease : prints the number of patients that are still hospitalized with the disease.
      // NO disease : prints for every disease the number of patients that are still hospitalized.
      string diseaseID;
      if(!getline(ss, diseaseID, ' ')){
        // no diseaseID given.
        disease_ht.num_current_patients();
      } else {
        disease_ht.num_current_patients(diseaseID.c_str());
      }
    }
  }
  free(records_file);
}
