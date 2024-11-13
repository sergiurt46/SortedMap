#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

Node::Node(TValue e,TKey k,PNod prev, PNod next) {
    //Θ(1)
    this->e = e;
    this->k = k;
    this->previousNode = prev;
    this->nextNode = next;

}

TValue Node::element() {
    //Θ(1)
    if (this != nullptr) {
        return this->e;
    }
}

TKey Node::key() {
    //Θ(1)
    if (this != nullptr) {
        return this->k;
    }
}

PNod Node::next() {
    //Θ(1)
    if (this != nullptr) {
        return this->nextNode;
    }
}

PNod Node::prev() {
    //Θ(1)
    if (this != nullptr) {
        return this->previousNode;
    }
}

SortedMap::SortedMap(Relation r) {
    //Θ(1)
	head = nullptr;
    this->rel = r;
}

TValue SortedMap::add(TKey k, TValue v) {
    // Best case: Θ(1) - when the map is empty or the new key is smaller than the current head key
    // Worst case: ω(n) - when the new key is larger than all existing keys, and it needs to be inserted at the end
    // Average case: O(n) - when the new key falls somewhere in between the existing keys

    PNod p = this->head;

    if (search(k) != NULL_TVALUE) {
        while (p != nullptr) {
            if (p->key() == k) {
                TValue old = p->element();
                p->e = v;
                return old;
            } else {
                p = p->next();
            }
        }
    } else {
        Node* newNode = new Node(v, k, nullptr, nullptr);

        if (this->head == nullptr || rel(k, this->head->key())) {
            newNode->nextNode = this->head;
            if (this->head != nullptr) {
                this->head->previousNode = newNode;
            }
            this->head = newNode;
        } else {
            while (p->next() != nullptr && rel(p->next()->key(), k)) {
                p = p->next();
            }

            newNode->nextNode = p->next();
            if (p->next() != nullptr) {
                p->next()->previousNode = newNode;
            }
            p->nextNode = newNode;
            newNode->previousNode = p;
        }
    }

    return NULL_TVALUE;
}


TValue SortedMap::search(TKey k) const {
    // Best case: Θ(1) - when the key is found at the head
    // Worst case: ω(n) - when the key is not found or located at the end of the map
    // Average case: O(n) - when the key is located somewhere in between the map
    PNod p = this->head;
    while (p!=nullptr){
        if (p->key()==k){
            return p->element();
        } else {
            p = p->next();
        }
    }
	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
    // Best case: Θ(1) - when the key to remove is at the head
    // Worst case: ω(n) - when the key to remove is located at the end of the map
    // Average case: O(n) - when the key to remove is located somewhere in between the map

    PNod p = this->head;
    if(search(k) != NULL_TVALUE) {
        while(p != nullptr) {
            if(p->key() == k) {
                TValue value = p->element();
                PNod prevNode = p->prev();
                PNod nextNode = p->next();
                if (prevNode != nullptr) {
                    prevNode->nextNode = nextNode;
                } else {
                    this->head = nextNode;
                }
                if (nextNode != nullptr) {
                    nextNode->previousNode = prevNode;
                }
                delete p;
                return value;
            } else {
                p = p->next();
            }
        }
    }
    return NULL_TVALUE;
}


int SortedMap::size() const {
    //Θ(n)
	int nr = 0;
    PNod p = this->head;
    while (p!= nullptr)
    {
        nr++;
        p = p->next();
    }
	return nr;
}

bool SortedMap::isEmpty() const {
    //Θ(1)
	return (this->head == nullptr);
}

SMIterator SortedMap::iterator() const {
    //Θ(1)
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
    //Θ(n)
    while (head != nullptr) {
        PNod p = head;
        head = head->nextNode;
        delete p;
    }
}

TValue SortedMap::mostFrequent() const {
    // Best case: Θ(n) - when the Map is empty
    // Worst case: ω(n)
    // Average case: O(n)
    if(this->head == nullptr)
        return NULL_TVALUE;
    else
    {
        TValue b[101], mostFreq;
        int a[101], i = 0, max = 0;
        PNod p = this->head;
        while(p!=nullptr)
        {
            int ok = 0;
            for(int j=1; j <= i ;j++)
                if(b[j] == p->element())
                {
                    a[j] ++;
                    ok = 1;
                }
            if(ok == 0)
            {
                i++;
                a[i]++;
                b[i] = p->element();

            }
            p = p->next();
        }

        for(int j = 1; j <= i; j++)
        {
            if(a[j] > max)
            {
                max = a[j];
                mostFreq = b[j];
            }
        }
        return mostFreq;
    }

}
