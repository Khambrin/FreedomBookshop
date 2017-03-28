#ifndef USERLIST_H
#define USERLIST_H
#include "user.h"

class Userlist
{
    friend class UserlistIterator;
private:
    class nodo;
    class smartUp {
      public:
        nodo* punt;
        smartUp(nodo *p=0);
        smartUp(const smartUp&);
        ~smartUp();
        smartUp& operator=(const smartUp&);
        nodo& operator*() const;
        nodo* operator->() const;
        bool operator==(const smartUp&) const;
        bool operator!=(const smartUp&) const;
    };
    class nodo {
    public:
        User* info;
        smartUp next;
        int counter;
        nodo();
        nodo(User*, const smartUp&);
    };
    smartUp first;
    smartUp last;
public:
    class UserlistIterator {
        friend class Userlist;
    private:
        Userlist::smartUp point;
    public:
        bool operator==(UserlistIterator) const;
        bool operator!=(UserlistIterator) const;
        UserlistIterator& operator++();
        UserlistIterator operator++(int);
        User* operator*();
    };
    Userlist();
    UserlistIterator begin() const;
    UserlistIterator end() const;
    User* operator[](UserlistIterator) const;
    int size();
    bool Vuota() const;
    void push_front(User*);
    void push_back(User*);
    void pop_front();
    void pop_back();
    bool Contains(const User*);
    void Remove_user(QString);
    void Remove_user(UserlistIterator);
};

#endif // USERLIST_H
