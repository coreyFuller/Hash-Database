
#include "database.h"

int string_hash(string s, int tableName_size){
 unsigned int i, h = 0;
  for (i=0; i<s.length(); i++)
    h = (h * 2917 + (unsigned int)s[i]) % tableName_size;
  return h;
}

int ID_hash(int ID, int tableID_size){return ID % tableID_size;}

Database::Database()
{
    tableName_size = 4;
    tableID_size = min = 10000;
    tableID_used = tableName_used = 0;
    sum = average = employee_count = max = 0;
    table_name = new Node *[tableName_size];
    for(int i = 0 ; i < tableName_size; i++){
        table_name[i] = NULL;
    }
    tableID = new Node*[tableID_size];
    for(int i = 0; i < tableID_size ;i++)
    {
      tableID[i] = NULL;
    }
}

void Database::report(ofstream &out)
{
  out << "Annual Report" << endl << endl;
  out << "Total Annual Sales: $" << sum << endl;
  out << "Average Sale per Employee: $" << average << endl << endl;
  out << "Highest earner: " << highest_earner[0] << " " << highest_earner[1] << "(+20%)" << endl;
  out << "Employees to recieve a 5% bonus on next pay period: " << endl;
  for(int i = 0; i < tableName_size; i++)
    {
      for(Node * temp = table_name[i]; temp; temp = temp->next)
	{
	  if(temp->sales >= average){out << "-" << temp->f_name << " " << temp->l_name << endl;}
	}
    }
  out << endl << "Lowest earner: " << lowest_earner[0] << " " << lowest_earner[1] << endl;
  remove(lowest_earner[1]);
  out << lowest_earner[0] <<  " " << lowest_earner[1] << " removed from the company database." << endl;
}

void Database::insert(int ID,double sales, string f_name, string l_name)
{
     if(tableName_used == tableName_size)
     {
     tableName_size *= 2;
     Node ** newTable = new Node *[tableName_size]; 
     for (int k = 0; k < tableName_size; k++) {
      newTable[k] = NULL; 
    }
    for(int i = 0; i < tableName_used; i++){
      Node * temp = table_name[i]; 
        while(temp) { 
          newTable[string_hash(temp->l_name, tableName_size)] = new Node(temp->ID, temp->sales, temp->f_name, temp->l_name, newTable[string_hash(temp->l_name, tableName_size)]); 
          temp = temp->next;
        }
    }

    for (int j = 0; j < tableName_used; j++) {    
    Node * temp = table_name[j];
      while(temp) {
      table_name[j] = temp->next;   
      delete temp; 
      temp = table_name[j];
      }
    }
    delete [] table_name;
    table_name = newTable;
  }
   int h = string_hash(l_name, tableName_size);
   table_name[h] = new Node(ID, sales, f_name, l_name, table_name[h]);
   if(sales > max){max = sales; highest_earner[0] = f_name; highest_earner[1] = l_name;}
   if(sales < min){min = sales; lowest_earner[0] = f_name; lowest_earner[1] = l_name;}
   employee_count++;
}

 void Database::insertID(int ID, double sales, string f_name, string l_name)
 {
   if(tableID_used == tableID_size)
     {
     tableID_size *= 2;
     Node ** newTable = new Node *[tableID_size]; 
     for (int k = 0; k < tableID_size; k++) {
      newTable[k] = NULL; 
    }
    for(int i = 0; i < tableName_used; i++){
      Node * temp = tableID[i]; 
        while(temp) { 
          newTable[ID_hash(temp->ID, tableID_size)] = new Node(temp->ID, temp->sales, temp->f_name, temp->l_name, newTable[ID_hash(temp->ID, tableID_size)]); 
          temp = temp->next;
        }
    }

    for (int j = 0; j < tableID_used; j++) {    
    Node * temp = tableID[j];
      while(temp) {
      tableID[j] = temp->next;   
      delete temp; 
      temp = tableID[j];
      }
    }
    delete [] tableID;
    tableID = newTable;
     }
    int h = ID_hash(ID, tableID_size);
    tableID[h] = new Node(ID, sales, f_name, l_name, tableID[h]);
 }

void Database::print() 
{
for(int i = 0; i < tableName_size; i++)
{
    for(Node * temp = table_name[i]; temp; temp = temp->next)
    {
        cout << "Employee " << temp->ID <<  ": " << temp->f_name << " " << temp->l_name << endl;
        cout << "Total Sales: $" << temp->sales << endl << endl;
    }
}
}

Node * Database::search_lastName(string l_name)
{
    int h = string_hash(l_name, tableName_size);
    for(Node * temp = table_name[h]; temp; temp = temp->next)
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
   int h = string_hash(s, tableName_size);
    if(table_name[h]->l_name == s)
    {  
    temp = table_name[h];
    table_name[h] = table_name[h]->next;
    delete temp;
    return true;
    }
  else {
    for(Node * current =table_name[h]; current; temp = current, current = current->next) {
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
   int h = ID_hash(ID, tableID_size);
   for(Node * temp = tableID[h]; temp; temp = temp->next)
   {
    if(temp->ID == ID)
    {
    cout << "Employee " << temp->ID << ": " << temp->f_name << " " << temp->l_name << endl; 
    cout << "Total Sales: " <<  temp->sales << endl;
    name[0] = temp->f_name; name[1] = temp->l_name;
    return name;
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
  cout << "[6] Print Database Menu" << endl;
  cout << "[0] Exit and print Annual Report" << endl << endl;
}

Database::~Database()
{
  for (int i=0; i<tableName_size; i++) 
  {
    while (table_name[i] != NULL) 
    {
      Node *temp = table_name[i];
      table_name[i] = table_name[i]->next;
      delete temp;
    }
  }
  delete [] table_name;
}

double Database::sumAll()
{
  for(int i = 0; i < tableName_size;i++)
  {
    for(Node * temp = table_name[i]; temp; temp = temp->next){sum += temp->sales;}
  }
  return sum;
}
double Database::calcAverage(){average = sum / employee_count; return average;}
