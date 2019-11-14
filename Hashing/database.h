#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>
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
  Node ** table;
  int size;
  int used;
  double sum, average;
  
 public:
  Database();
  void insert(int, double, string, string);
  void print();
  bool remove(string);
  string * search_ID(int ID);
  Node * search_lastName(string l_name);
  ~Database();
};
  

  
