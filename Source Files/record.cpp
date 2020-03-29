#include <iostream>
#include <cstring>
#include "record.h"

using namespace std;

Record::Record() : recordID(0), patientFirstName(NULL), patientLastName(NULL), diseaseID(NULL), country(NULL), entryDate(NULL), exitDate(NULL){
}

Record::Record(int r_id) : recordID(r_id), patientFirstName(NULL), patientLastName(NULL), diseaseID(NULL), country(NULL), entryDate(NULL), exitDate(NULL){
}

Record::Record(int r_id, const char* p_firstName) : recordID(r_id), patientLastName(NULL), diseaseID(NULL), country(NULL), entryDate(NULL), exitDate(NULL){
  patientFirstName = (char*)malloc(sizeof(char)*(strlen(p_firstName)+1));
  strcpy(patientFirstName, p_firstName);
}

Record::Record(int r_id, const char* p_firstName, const char* p_lastName) : recordID(r_id), diseaseID(NULL), country(NULL), entryDate(NULL), exitDate(NULL){
  patientFirstName = (char*)malloc(sizeof(char)*(strlen(p_firstName)+1));
  strcpy(patientFirstName, p_firstName);

  patientLastName = (char*)malloc(sizeof(char)*(strlen(p_lastName)+1));
  strcpy(patientLastName, p_lastName);
}

Record::Record(int r_id, const char* p_firstName, const char* p_lastName, const char* p_country) : recordID(r_id), diseaseID(NULL), entryDate(NULL), exitDate(NULL){
  patientFirstName = (char*)malloc(sizeof(char)*(strlen(p_firstName)+1));
  strcpy(patientFirstName, p_firstName);

  patientLastName = (char*)malloc(sizeof(char)*(strlen(p_lastName)+1));
  strcpy(patientLastName, p_lastName);

  country = (char*)malloc(sizeof(char)*(strlen(p_country)+1));
  strcpy(country, p_country);
}

Record::Record(int r_id, const char* p_firstName, const char* p_lastName, const char* p_country, const char* p_disease) : recordID(r_id), entryDate(NULL), exitDate(NULL){
  patientFirstName = (char*)malloc(sizeof(char)*(strlen(p_firstName)+1));
  strcpy(patientFirstName, p_firstName);

  patientLastName = (char*)malloc(sizeof(char)*(strlen(p_lastName)+1));
  strcpy(patientLastName, p_lastName);

  country = (char*)malloc(sizeof(char)*(strlen(p_country)+1));
  strcpy(country, p_country);

  diseaseID = (char*)malloc(sizeof(char)*(strlen(p_disease)+1));
  strcpy(diseaseID, p_disease);
}

Record::Record(int r_id, const char* p_firstName, const char* p_lastName, const char* p_country, const char* p_disease, Date *p_entryDate) : recordID(r_id), entryDate(p_entryDate), exitDate(new Date){
  patientFirstName = (char*)malloc(sizeof(char)*(strlen(p_firstName)+1));
  strcpy(patientFirstName, p_firstName);

  patientLastName = (char*)malloc(sizeof(char)*(strlen(p_lastName)+1));
  strcpy(patientLastName, p_lastName);

  country = (char*)malloc(sizeof(char)*(strlen(p_country)+1));
  strcpy(country, p_country);

  diseaseID = (char*)malloc(sizeof(char)*(strlen(p_disease)+1));
  strcpy(diseaseID, p_disease);
}

Record::Record(int r_id, const char* p_firstName, const char* p_lastName, const char* p_country, const char* p_disease, Date *p_entryDate, Date *p_exitDate) : recordID(r_id), entryDate(p_entryDate), exitDate(p_exitDate){
  patientFirstName = (char*)malloc(sizeof(char)*(strlen(p_firstName)+1));
  strcpy(patientFirstName, p_firstName);

  patientLastName = (char*)malloc(sizeof(char)*(strlen(p_lastName)+1));
  strcpy(patientLastName, p_lastName);

  country = (char*)malloc(sizeof(char)*(strlen(p_country)+1));
  strcpy(country, p_country);

  diseaseID = (char*)malloc(sizeof(char)*(strlen(p_disease)+1));
  strcpy(diseaseID, p_disease);
}

Record::~Record(){
  free(patientFirstName);
  free(patientLastName);
  free(country);
  free(diseaseID);
  delete entryDate;
  delete exitDate;
}

int Record::get_recordID(){
  return recordID;
}

Date* Record::get_entryDate(){
  return entryDate;
}

char* Record::get_country(){
  return country;
}

char* Record::get_disease(){
  return diseaseID;
}

void Record::set_exit_date(Date *new_exit_date){
  delete exitDate;
  exitDate = new_exit_date;
}

void Record::print_record(){
  cout << "----RECORD\t: " << recordID << endl;
  cout << "||  NAME\t: " << patientFirstName << " " << patientLastName << endl;
  cout << "||  DISEASE\t: " << diseaseID << endl;
  cout << "||  ENTRY\t: " << entryDate->get_date() << endl;
  cout << "||  EXIT\t: " << exitDate->get_date() << endl;
}
