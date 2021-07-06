#include <iostream>
#include <fstream>
#include "list.h"

template <typename T>
typename list<T>::iterator find(list<T>& theList,const T& item) {
  typename list<T>::iterator iter = theList.begin();
  while(iter != theList.end()) {
    if(*iter == item)
      return iter;
    iter++;
  }
  return iter;
}

int main() {
  list<int> l;

  std::ifstream in;
  in.open("data.txt");

  // Read a list of data items from the file
  // and insert them in the list.
  int x;
  while(in >> x)
    l.push_back(x);
  in.close();

  // Find all of the numbers from 1 to 19 that do not
  // appear in the list, and print them.
  for(int n = 1;n < 20;n++) {
    if(find(l,n) == l.end())
      std::cout << n << std::endl;
  }
  std::cout << std::endl;

  // Remove all numbers of the form 1 + 3*k from the list
  for(int n = 1;n < 20;n = n + 3) {
    list<int>::iterator itr = find(l,n);
    if(itr != l.end())
      l.erase(itr);
  }

  // Print the final form of the list
  for(list<int>::iterator itr = l.begin();itr != l.end();itr++)
    std::cout << *itr << std::endl;

  return 0;
}
