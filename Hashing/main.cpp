#include "database.h"

int main(int argc, char * argv[]) {

  srand(time(0));
  ifstream input("data.txt");
  ofstream output("report.txt");
  Database D;
  int ID = 0, choice = -1;
  double sales = 0;
  string f_name, l_name;

  while(input >> ID >> sales >> f_name >> l_name){
    D.insert(ID, sales, f_name, l_name);
    D.insertID(ID, sales, f_name, l_name);
  }
  
  printMenu();
  while(choice != 0)
  {
    cout << "Enter a menu command: ";
    cin >> choice;
    switch(choice)
    { 
    cout << choice;
    case 1:
      D.print();
      break;
    case 2:
      cout << "Enter employee first name: "; cin >> f_name;
      cout << "Enter employee last name: "; cin >> l_name;
      cout << "Enter employee sales: "; cin >> sales;
      D.insert(rand() % 100 + 1, sales, f_name, l_name);
      break;
    case 3:
    cout << "Enter the last name of an Employee to remove: ";
    cin >> l_name; 
    if(!D.remove(l_name)) cout << "Employee not in the database." << endl;
      break;
    case 4:
      cout << "Enter the last name of an employee to search for: ";
      cin >> l_name;
      D.search_lastName(l_name);
      break;
    case 5:
    cout << "Enter the ID of an employee to search for: ";
    cin >> ID;
    if(!D.search_ID(ID)) cout << "Employee not in the database." << endl;
      break;
    case 6:
      cout << endl;
      printMenu();
      break;
    case 0:
      break;
    default:
      cout << "Not a valid command." << endl;
    }
  } 
  D.sumAll(); D.calcAverage(); D.report(output);
  return 0;
}
