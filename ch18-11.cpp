#include <iostream>
using namespace std;

#define LV 5

struct Node
{
  int value;
  int width[LV];
  Node *next[LV];
  
  Node(int val);
  ~Node();
};

Node::Node(int val):value{val}
{
  for (int i = 0; i < LV; i++ ) 
    {
      width[i] = 0;
      next[i] = nullptr;
    }
}

Node::~Node()
{
}

class Skiplist 
{
public:
  Node* head = nullptr;

  Skiplist() { head = nullptr;}
  Skiplist(initializer_list<int> lst);
  ~Skiplist();

  Node* getItem(int index);
  Node* insert(int value);
  void remove(int index);
  void print();

private:
  Node* current;
  int level;
  
  void upgrade();
};

Skiplist::Skiplist(initializer_list<int> lst)
{
  if( lst.size() == 0 ) return;

  head = new Node(*lst.begin());
  current = head;
  initializer_list<int>::iterator it;
  for (it = lst.begin()+1; it < lst.end(); it++)
    {
      Node* newnode = new Node(*it); 
      current->next[0] = newnode;
      current->width[0] = 1;
      current = newnode;
    }
  current->width[0] = 1;

  upgrade();
}

Skiplist::~Skiplist()
{
  while (head!=nullptr)
    {
      Node *d = head;
      head = head->next[0];
      delete d;
    }
}

Node *Skiplist::getItem(int index)
{
  Node *c = head;
  int level = LV - 1;
  int idx = index;
  while ( idx > 0 && c != nullptr)
    {
      while (c->width[level] > idx) level--;
      idx -= c->width[level]; 
      c = c->next[level];
    }
  return c;
}

Node *Skiplist::insert(int val)
{
  return nullptr;
}

void Skiplist::remove(int idx)
{
}

void Skiplist::upgrade()
{
    for (int i = 1; i < LV; i++)
    {
      Node *p1 = head;
      Node *p2 = head;
      int width = 0, index = 0;
      while (p2 != nullptr)
	{
      	  if ( index > 0 && index%2 == 0 ) 
	  {
	    p1->next[i] = p2;
	    p1 = p2;
	    width = 0;
	  }

	  index ++;
	  width += p2->width[i-1];
	  p1->width[i] = width;
	  p2 = p2->next[i-1];
	}

      p1->width[i] = width;
    }
}

void Skiplist::print()
{
  for ( int i = 0; i < LV; i++)
    {
      Node *c  = head;
      cout<<"level "<< i << " : ";
      while (c != nullptr)
	{
	  cout<< c->value<<':'<<c->width[i]<<' ';
	  c = c->next[i];
	}
      cout<<endl;
    }
}

int main()
{
  Skiplist *lst = new Skiplist({1,2,3,4,5});
  lst->print();
  for ( int i = 0; i < 5; i++){
    Node *n = lst->getItem(i);
    cout<<n->value<<endl;
  }

  delete(lst);

  return 0;
}
