#include <iostream>
using namespace std;

template<typename T>
class Vector
{
  int sz;
  T * elem;
  int space;

public:
  Vector(): sz{0}, space{0}, elem{nullptr} {}

  Vector(int s): sz{s}, space{s},elem{new T[s]}
  {
    for(int i = 0; i < sz; i++) elem[i] = 0;
  }

  Vector(initializer_list<T> lst): sz{(int)lst.size()},space{(int)lst.size()},elem{new T[lst.size()]}
  {
    copy(lst.begin(),lst.end(),elem);
  }
  
  Vector(const Vector&);
  ~Vector(){delete[] elem;}

  Vector& operator=(const Vector&);
  T operator[](int i);

  void set(int, T);
  int size() { return sz;}
  void print();
  void reserve(int newalloc);
  void resize(int newsize);
  void push_back(T value);
};

template<typename T>
void Vector<T>::reserve(int newalloc)
{
  if (newalloc < space) return;
  T *p = new T[newalloc];
  for (int i = 0; i < sz; i++) p[i] = elem[i];
  delete[] elem;
  elem = p;
  space = newalloc;
}

template<typename T>
void Vector<T>::resize(int newsize)
{
  if (newsize < space) return;
  reserve(newsize);
  for (int i = sz; i < newsize; i++) elem[i] = 0;
  sz = newsize;
}

template<typename T>
void Vector<T>::push_back(T value)
{
  if ( space == 0 ) reserve(8);
  if ( space == sz) reserve(2*space);
  elem[sz] = value;
  sz ++;
}

template<typename T>
void Vector<T>::set(int index, T value)
{
  if (index >= sz) return;
  elem[index] = value;
}

template<typename T>
void Vector<T>::print()
{
  for (int i = 0; i < sz; i++)
    {
      cout<<(elem[i])<<endl;
    }
}

template<typename T>
Vector<T>::Vector(const Vector<T>& arg)
  :sz(arg.sz),elem(new T[arg.sz])
{
  copy(arg.elem,arg.elem+arg.sz,elem);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& arg)
{
  T *d = new T[arg.sz];
  copy(arg.elem,arg.elem+arg.sz,d);
  delete[] elem;
  elem = d;
  space = sz = arg.sz;
  return *this;
}

template<typename T>
T Vector<T>::operator[](int i)
{
  return elem[i];
}

// exc 1
// 定义f(), 将两个Vector<T>相加
// to-resolve: 判定T可以进行加法运算?
template<typename T>
void f1(Vector<T>& v1, Vector<T>& v2)
{
  for (int i = 0; i < v1.size(); i++) 
    {
      if ( i < v2.size() ) v1.set(i, v1[i] + v2[i]);
    }
}

// exc 2
// 定义f2(), 将Vector<T> 与Vector<U>相乘 
template<typename T,typename U>
void f2(Vector<T>& v1, Vector<U>& v2)
{
  for (int i = 0; i < v1.size(); i++) 
    {
      if ( i < v2.size() ) v1.set(i, v1[i] * v2[i]);
    }
}

// exc 3
// write a template class Pair that can be hold a pair of value of any type.
// implatment set_value() and get_value()
template<typename K, typename V >
class Pair{
  Vector<K> keys;
  Vector<V> values;

public:
  Pair() {};
  ~Pair();

  void set_value( const K&, V );
  V& get_value( const K&);
  void print();
};

template<typename K, typename V >
Pair<K,V>::~Pair()
{
}

template<typename K, typename V >
void Pair<K,V>::set_value(const K& key, V val )
{
  keys.push_back(key);
  values.push_back(val);
}

template<typename K, typename V >
V& Pair<K,V>::get_value(const K& key)
{
  for ( int i = 0; i < keys.size(); i++)
    {
      if ( key == keys[i]) return values[i];
    }
}

template<typename K, typename V >
void Pair<K,V>::print()
{
  keys.print();
  values.print();
}

// exc 4
// modify class Link from $17.9.3 to be a template with the type of value as the template argument


int main()
{
  Pair<int,double> p;
  p.set_value(1, 2.3);
  p.print();
  return 0;
}

