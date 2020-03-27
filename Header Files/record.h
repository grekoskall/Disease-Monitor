#ifndef _RECORD_H
#define _RECORD_H
#include "date.h"

class Record {
  private:
    int recordID;
    char* patientFirstName;
    char* patientLastName;
    char* diseaseID;
    char* country;
    Date *entryDate;
    Date *exitDate;
  public:
    Record();
    Record(int);
    Record(int, const char* p_firstName);
    Record(int, const char* p_firstName, const char* p_lastName);
    Record(int, const char* p_firstName, const char* p_lastName, const char* p_country);
    Record(int, const char* p_firstName, const char* p_lastName, const char* p_country, const char* p_disease);
    Record(int, const char* p_firstName, const char* p_lastName, const char* p_country, const char* p_disease, Date* p_entryDate);
    Record(int, const char* p_firstName, const char* p_lastName, const char* p_country, const char* p_disease, Date* p_entryDate, Date* p_exitDate);
    ~Record();

    int get_recordID();
    Date* get_entryDate();
    void print_record();
};

#endif
