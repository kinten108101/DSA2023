#include <iostream>
#include "./singlyLinkedList.h"

using namespace fuji;

class Polynomial;
class Term {
private:
    double coeff;   
    int exp;
    friend class Polynomial;
public:
    Term(double coeff = 0.0, int exp = 0) {
        this->coeff = coeff;
        this->exp = exp;
    }
    bool operator==(const Term& rhs) const {
        return this->coeff == rhs.coeff && this->exp == rhs.exp;
    }
    friend std::ostream & operator<<(std::ostream &os, const Term& term) {
        std::cout << std::endl;
        std::cout << "Term: " << "(" << term.coeff << " " << term.exp << ")";
        return os;
    }
};
class Polynomial {
private:
    SLinkedList<Term>* terms;
public:
    Polynomial() {
        this->terms = new SLinkedList<Term>();
    }
    ~Polynomial() {
        this->terms->clear();
    }
    void insertTerm(const Term& term);
    void insertTerm(double coeff, int exp);
    void print() {
        SLinkedList<Term>::Iterator it;
        std::cout << "[";
        for (it = this->terms->begin(); it != this->terms->end(); it++) {
            cout << (*it);
        }
        cout << endl << "]";
    }
};

void Polynomial::insertTerm(const Term& term) {
    // STUDENT ANSWER
    if (term.coeff == 0) return;
    SLinkedList<Term>::Iterator it;
    int result = -1;
    int idx = 0;
    // -1: not found
    // 0: found
    for (it = this->terms->begin(); it != this->terms->end(); it++, idx++) {
        if ((*it).exp == term.exp) {
            result = 0;
            break;
        } else if ((*it).exp < term.exp) {
            result = -1;
            break;
        }
    }
    if (result == -1) {
        this->terms->add(idx, term);
    } else if (result == 0) {
        (*it).coeff += term.coeff;
        if ((*it).coeff == 0) {
            this->terms->removeAt(idx);
        }
    }
}

void Polynomial::insertTerm(double coeff, int exp) {
    // STUDENT ANSWER
    Term term(coeff, exp);
    this->insertTerm(term);
}