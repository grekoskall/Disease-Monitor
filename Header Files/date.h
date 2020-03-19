#ifndef _DATE_H
#define _DATE_H
class Date{
  private:
    char* date;
  public:
    Date();
    Date(char*);
    Date(std::string);
    Date(int, int, int);
    ~Date();

    bool operator > (Date &);
    bool operator < (Date &);
    char* get_date();
  };

#endif
