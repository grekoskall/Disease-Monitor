#include <iostream>
#include <cstring>
#include "date.h"

using namespace std;

Date::Date(){
  date = (char*)malloc(sizeof(char)+1);
  strcpy(date, "-");
}

Date::Date(char* d_date){
  date = (char*)malloc(sizeof(char)*(strlen(d_date)+1));
  strcpy(date, d_date);
}

Date::Date(string d_date){
  date = (char*)malloc(sizeof(char)*(d_date.length()+1));
  strcpy(date, d_date.c_str());
}

Date::Date(int day, int month, int year){
    string d_date = to_string(day) + "-" + to_string(month) + "-" + to_string(year);
    date = (char*)malloc(sizeof(char)*(d_date.length()+1));
    strcpy(date, d_date.c_str());
}

Date::~Date(){
  free(date);
}

bool Date::operator > (Date &c2){
  char *c_date = (char*)malloc(sizeof(char)*(strlen(c2.get_date())+1));
  strcpy(c_date, c2.get_date());
  if( strcmp(c_date, "-") == 0){
    free(c_date);
    return false;
  }
  char* t_date = (char*)malloc(sizeof(char)*(strlen(this->get_date())+1));
  strcpy(t_date, date);

  char *t_day;
  t_day = strtok(t_date, "-");

  char *t_month;
  t_month = strtok(NULL, "-");
  char *t_year;
  t_year = strtok(NULL, "-");

  char *c_day;
  c_day = strtok(c_date, "-");
  char *c_month;
  c_month = strtok(NULL, "-");
  char *c_year;
  c_year = strtok(NULL, "-");

  if (strcmp(t_year, c_year) == 1) {
    free(t_date);
    free(c_date);
    return true;
  } else if ((strcmp(t_year, c_year) == 0) && (strcmp(t_month, c_month) == 1)){
    free(t_date);
    free(c_date);
    return true;
  } else if ((strcmp(t_year, c_year) == 0) && (strcmp(t_month, c_month) == 0) && (strcmp(t_day, c_day) == 1)){
    free(t_date);
    free(c_date);
    return true;
  } else {
    free(t_date);
    free(c_date);
    return false;
  }
}

bool Date::operator <(Date &c2){
  char *t_date = (char*)malloc(sizeof(char)*(strlen(this->get_date())+1));
  strcpy(t_date, this->get_date());
  if( strcmp(t_date, "-") == 0){
    free(t_date);
    return false;
  }
  free(t_date);
  return !(*this > c2);
}
char* Date::get_date(){
  return date;
}
