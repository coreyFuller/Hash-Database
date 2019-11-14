#include "database.h"

int myhash(string s, int size){

 unsigned int i, h = 0;
  for (i=0; i<s.length(); i++)
    h = (h * 2917 + (unsigned int)s[i]) % size;
  return h;
}

Database::Database()
{
    size = 4;
    sum = average = 0;
    table = new Node *[size];
    for(int i = 0 ; i < size; i++){
        table[i] = NULL;
    }
    used = 0;
}

void Database::insert(int ID,double sales, string f_name, string l_name)
{
     if(used == size)
     {
     size *= 2;
     Node ** newTable = new Node *[size]; 
     for (int k = 0; k < size; k++) {
      newTable[k] = NULL; 
    }
    for(int i = 0; i < used; i++){
      Node * temp = table[i]; 
        while(temp) { 
          newTable[myhash(temp->l_name, size)] = new Node(temp->ID, temp->sales, temp->f_name, temp->l_name, newTable[myhash(temp->l_name, size)]); // copies elements to new table
          temp = temp->next;
        }
    }

    for (int j = 0; j < used; j++) {    
    Node * temp = table[j];
      while(temp) {
      table[j] = temp->next;   
      delete temp;     // deallocates the old table
      temp = table[j];
      }
    }
    delete [] table;
    table = newTable;
  }

   int h = myhash(l_name, size);
   table[h] = new Node(ID, sales, f_name, l_name, table[h]);
}

void Database::print() 
{

for(int i = 0; i < size; i++)
{
    for(Node * temp = table[i]; temp; temp = temp->next)
    {
        cout << "Employee " << temp->ID <<  ": " << temp->f_name << " " << temp->l_name << endl;
        cout << "Total Sales: $" << temp->sales << endl << endl;
    }
}
}

Node * Database::search_lastName(string l_name)
{
    int h = myhash(l_name, size);
    for(Node * temp = table[h]; temp; temp = temp->next)
    {
        if(temp->l_name == l_name)
        {
          cout << "Employee " << temp->ID << ": " << temp->f_name << " " << temp->l_name << endl; 
          cout << "Total Sales: " <<  temp->sales << endl;
          return temp;
        }
    }
    return NULL;
}

 bool Database::remove(string s)
 {
   Node * temp = NULL;
   int h = myhash(s, size);
    if(table[h]->l_name == s)
    {  
    temp = table[h];
    table[h] = table[h]->next;
    delete temp;
    return true;
    }
  else {
    for(Node * current =table[h]; current; temp = current, current = current->next) {
      if(current->l_name == s) {
        temp->next = current->next;
        delete current;
        return true;
      }
    }
  }
  return false;
 }
 string * Database::search_ID(int ID)
 {
   string * name = new string[2];
   for(int i = 0; i<size; i++)
   {
     for(Node * temp = table[i]; temp; temp = temp->next)
     {
       if(temp->ID == ID)
       {
          cout << "Employee " << temp->ID << ": " << temp->f_name << " " << temp->l_name << endl; 
          cout << "Total Sales: " <<  temp->sales << endl;
          name[0] = temp->f_name; name[1] = temp->l_name;
          return name;
       }
     }
   }
   return NULL;
 }

void printMenu()
{
  cout << "DATABASE MENU:" << endl;
  cout << "[1] Print Current Directory" << endl;
  cout << "[2] Add New Employee Data" << endl;
  cout << "[3] Remove Employee from Directory" << endl;
  cout << "[4] Search by Last Name" << endl;
  cout << "[5] Search by ID" << endl;
  cout << "[0] Exit and print Annual Report" << endl << endl;
}

Database::~Database()
{
  for (int i=0; i<size; i++) 
  {
    while (table[i] != NULL) 
    {
      Node *temp = table[i];
      table[i] = table[i]->next;
      delete temp;
    }
  }
  delete [] table;
}