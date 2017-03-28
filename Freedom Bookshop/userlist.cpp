#include "userlist.h"
#include "premium_user.h"

//metodi di Userlist

Userlist::Userlist():first(0),last(0)
{

}

Userlist::UserlistIterator Userlist::begin() const
{
    UserlistIterator aux;
    aux.point=first;
    return aux;
}

Userlist::UserlistIterator Userlist::end() const
{
    UserlistIterator aux;
    aux.point=0;
    return aux;
}

User* Userlist::operator[](Userlist::UserlistIterator it) const
{
    return (it.point)->info;
}

int Userlist::size()
{
    Userlist::UserlistIterator it;
    int count=0;
    for (it=this->begin(); it!=this->end();it++){
        count++;
    }
    return count;
}

bool Userlist::Vuota() const
{
    return first==0;
}

void Userlist::push_front(User* User)
{
    first=new nodo(User,first);
    if(!last.punt) {
        last=new nodo(User,0);
    }
}

void Userlist::push_back(User* User)
{
    if(!first.punt){
        first=new nodo(User,0);
        last=first;
    } else if(last.punt==first.punt){
        last=new nodo(User,0);
        first->next=last;
    } else {
        last->next=new nodo(User, 0);
        last=last->next;
    }
}

void Userlist::pop_front()
{
    first=first->next;
}

void Userlist::pop_back()
{
    UserlistIterator it=this->begin();
    while(it.point->next!=last){
        it++;
    }
    last=it.point;
}

bool Userlist::Contains(const User *user)
{
    UserlistIterator it=this->begin();
    while(it.point.punt->info!=user){
        it++;
    }
    if(it.point.punt!=0){
        return true;
    }
    else {
        return false;
    }

}

void Userlist::Remove_user(QString codice)
{
    smartUp p=first;
    smartUp prec;
    smartUp q;
    smartUp original = first;
    first=0;
    if(p!=0){
        Premium_user* user=dynamic_cast<Premium_user*>(p->info);
        while(p!=0 && !(user->GetCodice_carta()==codice)){
            q = new nodo(p->info,p->next);
            if(prec==0) {
                first=q;
            } else {
                prec->next=q;
            }
            prec = q;
            p = p->next;
            if(p!=0){
                user=dynamic_cast<Premium_user*>(p->info);
            }
        }
    }
    if(p==0) {
        first=original;
    } else if (prec==0) {
        first=p->next;
    } else {
        prec->next=p->next;
        if(prec->next==0) {
        last=prec;
        }
    }
}

void Userlist::Remove_user(Userlist::UserlistIterator iteratore)
{
    if(iteratore==this->begin()) {
        first=first->next;
    } else {
        UserlistIterator it;
        UserlistIterator prec;
        for(it=this->begin(); it!=this->end(); it++){
            if(iteratore==it){
                prec.point.punt->next=it.point.punt->next;
                delete *it;
            } if (it==this->begin()) {
                prec=this->begin();
            } else {
                prec++;
            }
        }
    }
}

//metodi di smartUp

Userlist::smartUp::smartUp(nodo *p):punt(p)
{
    if(punt) {punt->counter++;}
}

Userlist::smartUp::smartUp(const Userlist::smartUp &p):punt(p.punt)
{
    if(punt) {punt->counter++;}
}

Userlist::smartUp::~smartUp()
{
    if(punt) {
        punt->counter--;
        if(punt->counter==0) {
            delete punt;
        }
    }
}

Userlist::smartUp &Userlist::smartUp::operator=(const Userlist::smartUp &p)
{
    if(this != &p) {
        Userlist::nodo* s=punt;
        punt=p.punt;
        if(punt) punt->counter++;
        if(s) {
            s->counter--;
            if(s->counter == 0) {
                delete s;
            }
        }
    }
    return *this;
}

Userlist::nodo &Userlist::smartUp::operator*() const
{
    return *punt;
}

Userlist::nodo *Userlist::smartUp::operator->() const
{
    return punt;
}

bool Userlist::smartUp::operator==(const Userlist::smartUp &p) const
{
    return punt==p.punt;
}

bool Userlist::smartUp::operator!=(const Userlist::smartUp &p) const
{
    return punt!=p.punt;
}

//metodi di nodo

Userlist::nodo::nodo():counter(0) {}

Userlist::nodo::nodo(User* User, const Userlist::smartUp &p):info(User), next(p), counter(0) {}


//metodi di UserlistIterator

bool Userlist::UserlistIterator::operator==(Userlist::UserlistIterator it) const
{
    return point==it.point;
}

bool Userlist::UserlistIterator::operator!=(Userlist::UserlistIterator it) const
{
    return point!=it.point;
}

Userlist::UserlistIterator &Userlist::UserlistIterator::operator++()
{
    if(point.punt) {
        point=point->next;
    }
    return *this;
}

Userlist::UserlistIterator Userlist::UserlistIterator::operator++(int)
{
    UserlistIterator aux=*this;
    if(point.punt) {
        point=point->next;
    }
    return aux;
}

User* Userlist::UserlistIterator::operator *()
{
    return point->info;
}
