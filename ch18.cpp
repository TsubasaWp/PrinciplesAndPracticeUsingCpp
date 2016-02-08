//
//  main.cpp
//  PPPUC
//
//  Created by Tsubasa on 1/30/16.
//  Copyright (c) 2016 tsu. All rights reserved.
//

#include <iostream>
using namespace std;

class Vector
{
  int sz;
  double * elem;
public:
  Vector(int s): sz{s}, elem{new double[s]}
  {
    for(int i = 0; i < sz; i++) elem[i] = 0;
  }

  Vector(initializer_list<double> lst): sz{(int)lst.size()},elem{new double[lst.size()]}
  {
    copy(lst.begin(),lst.end(),elem);
  }
  
  Vector(const Vector&);

  Vector& operator=(const Vector&);

  ~Vector(){delete[] elem;}
  void Set(int, double);
  void Print();
};

void Vector::Set(int index, double value)
{
  if (index >= sz) return;
  elem[index] = value;
}

void Vector::Print()
{
  for (int i = 0; i < sz; i++)
    {
      cout<<(elem[i])<<endl;
    }
}

Vector::Vector(const Vector& arg)
  :sz(arg.sz),elem(new double[arg.sz])
{
  copy(arg.elem,arg.elem+arg.sz,elem);
}

Vector& Vector::operator=(const Vector& arg)
{
  double *d = new double[arg.sz];
  copy(arg.elem,arg.elem+arg.sz,d);
  delete[] elem;
  elem = d;
  sz = arg.sz;
  return *this;
}

// exc 1
char *strup(const char* a)
{
  int sz = 0;
  while ( a[sz] != 0 )  sz++;
  
  char * res = new char[sz+1];
  for(int i = 0; i <= sz; i++) res[i] = *a+i;

  return res;
}


// exc 2
int findx(const char *s, const char *x)
{
  int i = 0;
  int j = 0;
  while ( s[i++] != 0 )
    {
      if ( s[i] == x[0])
	{
	  j = 0;
	  while ( s[i+j] == x[j] && x[j] != 0 ) j++;
	  if ( x[j] == 0 ) return i;
	}
    }
  return -1;
}

// exc 3
int strcmp(const char *s1, const char *s2)
{
  int i = 0;
  while( !( s1[i] == 0 && s2[i] == 0 ))
    {
      if ( s1[i] != s2[i] ) return (s1[i] < s2[i]) ? -1 : 1;
      i++;
    }
  return 0;
}

// exc 5
string cat_dot(const string &a, const string &b)
{
  return a + "." + b;
}

// exc 7
char *c_cat_dot(const char*a, const char*b)
{
  char *res = new char[strlen(a)+strlen(b)+1];  
  int i = 0;
  while (a[i] != 0) {
      res[i] = a[i];
      ++i;
  }
  int j = 0;
  res[i]='.';
  while (b[j] != 0){
    res[i+j+1] = b[j];
    ++j;
  }
  return res;
}

// exc 8
int palindrome(const string &a)
{
  string rev = a;
  int n = a.size();
  for ( int i = 0; i <= n/2; i++)
    {
      rev[i] = a[n-1];
    }
  return rev.compare(a);
}

// exc 9
void print_order(void *a , void *b)
{
  if ( a < b ) cout << "downward"<<endl;
  else if ( a > b ) cout << "upward" << endl;
  else cout << "equal" << endl;
}

void mem_layout()
{
  int a,b;
  cout << "the order of stack is ";
  print_order (&a, &b);
  int *p1 = new int[1];
  int *p2 = new int[1];  
  cout << "the order of free-store is ";
  print_order(p1,p2);
}

// exc 11 - 12
// will be implementing in a seperate file.








// ==============================
int main(int argc, const char * argv[]) {
  mem_layout();

  return 0;
}
