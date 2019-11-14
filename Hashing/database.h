#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;


struct Node
{
  int ID;
  double sales;
  string f_name;
  string l_name;
  Node * next;
  Node(){ID = 0; sales = 0; f_name = " "; l_name = " "; next = NULL;}
  Node(int i, double s, string f, string l, Node * n){ID = i; sales = s; f_name = f; l_name = l; next = n;}
};

int myhash(string l_name);
void printMenu();

class Database
{

 private:
  Node ** table_name;
  Node ** tableID;
  int tableName_size;
  int tableName_used;
  int tableID_size;
  int tableID_used;
  int employee_count;
  string lowest_earner[2];
  string highest_earner[2];
  double sum, average, min, max;
  
 public:
  Database();
  void insert(int, double, string, string);
  void insertID(int, double, string, string);
  void print();
  bool remove(string);
  string * search_ID(int ID);
  Node * search_lastName(string l_name);
  double calcAverage();
  double sumAll();
  void report(ofstream &out);
  ~Database();
};
  

  
