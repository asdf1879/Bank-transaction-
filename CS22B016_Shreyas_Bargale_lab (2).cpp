// CS22B016 Shreyas Bargale
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#include <limits.h>
class Nodes {
public:
  int accno, currbal;
  Nodes *next;
  // Node *prev;

  Nodes(int d) {
    accno = d;
    currbal = 1000;
    next = nullptr;
  }
};

class Noded {
public:
  int accnod, value;
  char c;
  Noded *next;
  Noded *prev;

  Noded() {
    next = NULL;
    prev = NULL;
  }
  Noded(int d, char n, int v) {
    accnod = d;
    value = v;
    c = n;
    next = nullptr;
    prev = NULL;
  }
};

class sll {
private:
  Nodes *first;
  Nodes *last;
  int len;

public:
  sll() {
    first = NULL;
    len = 0;
  }
  int retlen() { return len; }
  void insert(int d) {
    Nodes *addednode = new Nodes(d);
    if (first == NULL) {
      first = addednode;
      len++;
      last = first;
    } else {
      Nodes *temp = first;
      while (temp->next != NULL) {
        temp = temp->next;
      }
      temp->next = addednode;
      len++;
      last = addednode;
    }
  }
  void print() {
    Nodes *temp = first;
    while (temp != last) {
      cout << temp->currbal << " ";
      temp = temp->next;
    }
    cout << last->currbal << endl;
  }
  int find(int acc) {
    Nodes *temp = first;
    while (temp != last) {
      if (temp->accno == acc) {
        return 1;
      }
      temp = temp->next;
    }
    if (last->accno == acc) {
      return 1;
    }
    return 0;
  }

  void changebalance(int d, int acc) {
    // cout<<"d "<<d<<" acc "<<acc<<endl;
    Nodes *temp = first;
    while (temp!=NULL&&temp->accno != acc) {
      temp = temp->next;
      
    }
      if(temp!=NULL)
    temp->currbal += d;
    // cout << acc << endl << temp->currbal << endl;
  }

  void gfunc() {
    int X;
    cin >> X;
    int count = 0;
    Nodes *temp = first;

    while (temp != NULL) {
      if (temp->currbal >= X) {
        count++;
      }
      temp = temp->next;
    }
    cout << count << endl;
  }

  void vfunc() {
    int X;
    cin >> X;
    Nodes *temp = first;

    while (temp != NULL) {
      if (temp->accno == X) {
        cout << temp->currbal<<endl;
        return;
      }
      temp = temp->next;
    }
  }

  void mfunc() {
    Nodes *temp = first;
    int max = INT_MIN;
    while (temp != NULL) {
      if (temp->currbal > max) {
        max = temp->currbal;
      }
      temp = temp->next;
    }
    temp = first;
    vector<int> k;
    while (temp != NULL) {
      if (temp->currbal == max) {
        k.push_back(temp->accno);
      }
      temp = temp->next;
    }
    sort(k.begin(), k.end());
    for (int i = 0; i < k.size(); i++) {
      cout << k[i]<<" ";
    }
      cout<<endl;
  }
};

class dll {
private:
  Noded *head;
  Noded *tail;
  Noded *cursor;
  int trans;

  int curpos = 0;

public:
  Noded *gcursor() { return cursor; }
  int cursposp() { return curpos; }
  int gtrans() { return trans; }
  dll() {
    head = new Noded();
    tail = new Noded();
    head->next = tail;
    tail->prev = head;
    cursor = head;
    // cout<<"objectcheck";
    trans = 0;
    // len=0;
  }
  void insert(int d, char c, int v) {
    Noded *addednode = new Noded(d, c, v);
    tail->prev->next = addednode;
    addednode->prev = tail->prev;
    addednode->next = tail;
    tail->prev = addednode;
    trans++;
  }
  //   int nooftransactions(){
  //   Noded * temp=head;
  //   int x=0;
  //   while(temp->next!=tail){
  //     x++;
  //     temp=temp->next;
  //   }
  //   return x;
  // }

  void print() {
    Noded *temp = head;
    temp = temp->next;
    while (temp != tail) {
      cout << temp->accnod << " " << temp->c << " " << temp->value << endl;
      temp = temp->next;
    }
  }

  void Fprocess(sll &acc) {
    int X;
    cin >> X;
    cursor = cursor->next;
    curpos++;
    X--;
    while (cursor != tail && X >= 0) {
      // cout<<cursor->accnod<<endl;
      X--;
      int change;
      if (cursor->c == 'W') {
        change = 0 - cursor->value;
      } else if (cursor->c == 'D') {
        change = cursor->value;
      }
      acc.changebalance(change, cursor->accnod);
      cursor = cursor->next;
      curpos++;
    }
      cursor=cursor->prev;
    if (cursor == tail) {
      cursor = tail->prev;
    }
     // cout<<cursor->accnod<<endl;
  }

  void Rprocess(sll &acc) {
    // print();
    int Y;
    cin >> Y;
    if (cursor == head) {
      return;
    }
    // cout<<cursor->accnod<<endl;
    for(int i=0;i<Y;i++) {
      if(cursor==head){
        return;
      }
      int change;
      if (cursor->c == 'W') {
        change = cursor->value;
      } else if (cursor->c == 'D') {
        change = 0 - cursor->value;
      }
      // cout<<cursor->accnod<<" this will be deleted\n";
      acc.changebalance(change, cursor->accnod);
      cursor = cursor->prev;
      curpos--;
    }
    
    // cout<<cursor->accnod<<endl;
  }

  void idkprocess(sll &acc) {
    int account, value;
    char q;
    cin >> account >> q >> value;
    int k;
    // cout<<"test";
    cin >> k;
    // cout<<"test";
    Noded *temp = new Noded(account, q, value);
    if (k > trans) {
      // cout << "hey";
      return;
    }
    trans++;
    Noded *it = head;
    it = head->next;
    int i = 1;
    for (; i < k; i++) {
      it = it->next;
      // cout<<"h";
    }
      temp->next=it->next;
    it->next = temp;
    // cout<<"a";
    temp->prev = it;
    // cout<<"b";
   
    (temp->next)->prev = temp;
    // cout<<"c";
    Noded * t=head;
    t=t->next;
    int l=1;

  while(t!=NULL&&t!=cursor){
    t=t->next;
    l++;
  }
    
    if (k < l) {
      int change;
      if (temp->c == 'W') {
        change = 0 - temp->value;
      } else if (temp->c == 'D') {
        change = temp->value;
      }
      acc.changebalance(change, temp->accnod);
      // cout<<"hello";
    }
  }

  void cfunc(sll &acc) {
    cursor = cursor->next;
    curpos++;
    // X--;
    while (cursor != tail) {
      // cout<<cursor->accnod<<endl;
      // X--;
      int change;
      if (cursor->c == 'W') {
        change = 0 - cursor->value;
      } else if (cursor->c == 'D') {
        change = cursor->value;
      }
      acc.changebalance(change, cursor->accnod);
      cursor = cursor->next;
      curpos++;
    }
    if (cursor == tail) {
      cursor = tail->prev;
    }
  }

  void sfunc(sll &acc) {
    int Y;
    cin >> Y;
    if (acc.find(Y) != 1) {
      return;
    }
    Noded *temp = head;
    
    while (temp != cursor && temp != tail) {
        temp = temp->next;
        if (temp->accnod == Y) {
        cout << temp->accnod << " " << temp->c << " " << temp->value<<endl;
      }
        // temp=temp->next;
    }
    // if (temp == cursor) {
    //   if (temp->accnod == Y) {
    //     cout << temp->accnod << " " << temp->c << " " << temp->value << endl;
    //   }
    // }
  }

  void dfunc(sll &acc) {
    int A;
    cin >> A;
    int M;
    cin >> M;
      
      // cout<<M<<endl;
    Noded *cursort = cursor;
    if (M > 0) {
      cursort = cursort->next;
      while (cursort != tail && M > 0) {
        if (cursort->accnod == A) {
          Noded *del = cursort;
          M--;
          (del->prev)->next = del->next;
          (del->next)->prev = del->prev;
          delete del;
          trans--;
        }
        cursort = cursort->next;
      }
    } else if(M<0) {
      cursort = cursort->prev;
      while (cursort != head && M < 0) {
        if (cursort->accnod == A) {
          Noded *del = cursort;
          M++;
          (del->prev)->next = del->next;
          (del->next)->prev = del->prev;
          int change;
          if (del->c == 'W') {
            change = del->value;
          } else if (del->c == 'D') {
            change = 0 - del->value;
          }
          acc.changebalance(change, del->accnod);
            // cout<<del->accnod<<endl;
         // cout<<"hello"<<endl;
          delete del;
          trans--;
        }
        cursort = cursort->prev;
      }
    }
  }
};

int main() {
  int C;
  cin >> C;

  sll accounts;
  dll transactions;
  for (int i = 0; i < C; i++) {
    int x;
    cin >> x;
    accounts.insert(x);
  }

  // cout<<accounts.find(100);

  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    int acc, v;
    char q;
    cin >> acc >> q >> v;
    // cout<<q;
    if (accounts.find(acc)) {
      transactions.insert(acc, q, v);
    }
  }
  string s;
  cin >> s;
  while (s != "END") {
    if (s == "F") {
      transactions.Fprocess(accounts);
    } else if (s == "R") {
      transactions.Rprocess(accounts);
    } else if (s == "I") {
      transactions.idkprocess(accounts);
    } else if (s == "C") {
      transactions.cfunc(accounts);
    } else if (s == "D") {
      transactions.dfunc(accounts);
    } else if (s == "S") {
      transactions.sfunc(accounts);
    } else if (s == "G") {
      accounts.gfunc();
    } else if (s == "M") {
      accounts.mfunc();
    } else if (s == "V") {
      accounts.vfunc();
    }
    cin >> s;
  }

  // transactions.Fprocess(accounts);
  // transactions.idkprocess(accounts);
  // transactions.Rprocess(accounts,5);
  // transactions.print();
}