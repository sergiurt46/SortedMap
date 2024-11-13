#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
    //Θ(1)
	this->current = m.head;
}

void SMIterator::first(){
    //Θ(1)
	this->current = this->map.head;
}

void SMIterator::next(){
    //Θ(1)
    if (!valid()){
        throw exception();
    } else {
        this->current = this->current->next();
    }
}


bool SMIterator::valid() const{
    //Θ(1)
    return (this->current!=nullptr);
}

TElem SMIterator::getCurrent() const{
    //Θ(1)
    TElem e(this->current->key(), this->current->element());
    if (!valid()){
        throw exception();
    } else {
        return e;
    }
}


