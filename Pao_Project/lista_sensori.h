#ifndef LISTA_SENSORI_H
#define LISTA_SENSORI_H

template<class T>
class Lista_Sensori{
    friend class Iterator;
private:
    class Nodo{
    public:
        T info;
        Nodo* prev;
        Nodo* next;
        Nodo(const T& t=T(),Nodo* p=nullptr,Nodo* n=nullptr):info(t),prev(p),next(n){}
        bool operator==(const Nodo& n) const{return info==n.info;}
        bool operator!=(const Nodo& n) const{return info!=n.info;}
    };
    Nodo* first;
    Nodo* last;
    unsigned int dimensione;
    static void distruggi(Nodo* n){
        if(n!=nullptr){
            distruggi(n->next);
            delete n;
        }
    }
    static Nodo* copia(Nodo* f, Nodo*& l){
        if(f==nullptr) return l=nullptr;
        Nodo* tmp=new Nodo(f->info->clone());
        Nodo* p=tmp;
        while(f->next!=nullptr){
            p->next=new Nodo(f->next->info->clone(), p);
            f=f->next;
            p=p->next;
        }
        l=p;
        return  tmp;
    }
public:
    class Iterator{
        friend class Lista_Sensori<T>;
    private:
        Nodo* now;
    public:
        Iterator(Nodo* attuale =nullptr):now(attuale){}
        T& operator*() const{return now->info;}
        T* operator->() const{return &(now->info);}
        bool operator!=(const Iterator& it) const{return now!=it.now;}
        bool operator==(const Iterator& it) const{return now!=it.now;}
        Iterator& operator++(){
            if(now!=nullptr) {
                now=now->next;
            }
            return *this;
        }
        Iterator operator++(int){
            Iterator ausiliario(*this);
            if(now!=nullptr) {
                now=now->next;
            }
            return ausiliario;
        }
        Iterator& operator--(){
            if(now!=nullptr){
                now=now->prev;
            }
            return *this;
        }
        Iterator operator--(int){
            Iterator ausiliario(*this);
            if (now!=nullptr) {
                now=now->prev;
            }
            return ausiliario;
        }
    };
    class Const_Iterator{
        friend class Lista_Sensori<T>;
    private:
        const Nodo* now;
    public:
        Const_Iterator(Nodo* attuale =nullptr):now(attuale){}
        const T& operator*() const{return now->info;}
        const T* operator->() const{return &(now->info);}
        bool operator!=(const Const_Iterator& cit) const{return now!=cit.now;}
        bool operator==(const Const_Iterator& cit) const{return now!=cit.now;}
        Const_Iterator& operator++(){
            if(now!=nullptr) {
                now=now->next;
            }
            return *this;
        }
        Const_Iterator operator++(int){
            Const_Iterator ausiliario(*this);
            if(now!=nullptr) {
                now=now->next;
            }
            return ausiliario;
        }
        Const_Iterator& operator--(){
            if(now!=nullptr){
                now=now->prev;
            }
            return *this;
        }
        Const_Iterator operator--(int){
            Const_Iterator ausiliario(*this);
            if (now!=nullptr) {
                now=now->prev;
            }
            return ausiliario;
        }
    };
    Lista_Sensori(Nodo* f=nullptr,Nodo* l=nullptr,int dim =0):first(f),last(l),dimensione(dim<0 ? 0 : dim){}
    ~Lista_Sensori(){
        distruggi(first);
    }
    Lista_Sensori<T>& operator=(const Lista_Sensori<T>& ls){
        if(this!=&ls){
            distruggi(first);
            first=nullptr;
            last=nullptr;
            copia(ls.first,last);
            ls.dimensione=dimensione;
        }
        return *this;
    }
    Lista_Sensori<T>(const Lista_Sensori<T>& ls):first(nullptr),last(nullptr),dimensione(ls.dimensione){
        copia(ls.first,last);
    }
    unsigned int Size() const{
        return dimensione;
    }
    bool Is_Empty() const{
        return (dimensione==0 || first==nullptr);
    }
    T& operator[](unsigned int i) const{
        if(i<dimensione){
            Nodo* temp=first;
            bool esci=false;
            for (unsigned int j=0; j<dimensione && !esci; ++j) {
                if (j==i){
                    esci=true;
                }else{
                    temp=temp->next;
                }
            }
            return (temp->info);
        }else{//manca un messaggio d'errore
            i=dimensione-1;
            return operator[](i);
        }
    }
    Iterator begin() const{
        return Iterator(first);
    }
    Iterator end() const{
        return Iterator();
    }
    Const_Iterator cbegin() const{
        return Const_Iterator(first);
    }
    Const_Iterator cend() const{
        return Const_Iterator();
    }
    void Insert_Front(const T& t){
        if(first==nullptr){
            first=last=new Nodo(t);
            dimensione=1;
        }else{
            first->prev=new Nodo(t,nullptr,first);
            first=first->prev;
            dimensione++;
        }
    }
    void Insert_Back(const T& t){
        if(last==nullptr){
            last=first=new Nodo(t);
            dimensione=1;
        }else{
            last=new Nodo(t, last, nullptr);
            last->prev->next=last;
            dimensione++;
        }
    }
    void clear(){
        delete first;
        dimensione=0;
        first=last=nullptr;
    }
    void Pop_Front(){
        if(first!=nullptr){
            Nodo* n=first;
            first=first->next;
            if(first!=nullptr) first->prev=nullptr;
            else last=nullptr;
            n->next=nullptr;
            delete n;
            dimensione--;
        }
    }
    void Pop_Back(){
        if(first!=nullptr){
            Nodo* n=last;
            last=last->prev;
            if(last!=nullptr) last->next=nullptr;
            else first=nullptr;
            delete n;
            dimensione--;
        }
    }
    Iterator Search(const T& t){
        for(Iterator it=begin();it!=end() && *it!=t;it++)
            return it;
    }
    Const_Iterator Search_Only_Read(const T& t) const{
        for(Const_Iterator cit=cbegin();cit!=cend() && *cit!=t;cit++)
            return cit;
    }
    bool Search_Bool(const T& t){
        if(first!=nullptr){
            for(Iterator it=begin();it!=end();it++){
                if(*it==t){
                    return true;
                }
            }
        }
        return false;
    }
    T& Front() const{
        return first->info;
    }
    T& Back() const{
        return last->info;
    }
    void Erase(const T& t){
        if(first!=nullptr){
            if(t==first->info){
                Pop_Front();
                return;
            }
            Nodo* ausiliario=first;
            while(ausiliario!=nullptr && ausiliario->info!=t){
                ausiliario=ausiliario->next;
            }
            if(ausiliario==last){
                Pop_Back();
                return;
            }
            if(ausiliario!=nullptr){
                ausiliario->prev->next=ausiliario->next;
                ausiliario->next->prev=ausiliario->prev;
                ausiliario->next=nullptr;
                delete ausiliario;
                dimensione--;
            }
        }
    }
};
#endif // LISTA_SENSORI_H
