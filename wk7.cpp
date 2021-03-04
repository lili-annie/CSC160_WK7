
#include <iostream>

using namespace std;

int* myFunction() {
  int* myArray = new int[5];
  return myArray;
}


int main() {

  int num[5];
  num[0] = 43;
  num[1] = 44;
  cout << num[0] << ", " << num[1] << endl;

  int size;
  cout << "enter size:";
  cin >> size;
  cout << size << endl;

  // int *other_num = (int*)malloc(size*sizeof(int));
  int* other_num = new int[size];
  other_num[0] = 43;
  other_num[1] = 44;
  cout << "other num " << other_num[0] << ", " << other_num[1] << endl;

  delete [] other_num;

  char ch = 'a';
  char *c_str = new char[3];

  c_str[0] = 'a';
  c_str[1] = 'b';
  c_str[2] = '\0';

  cout << c_str << endl;

}