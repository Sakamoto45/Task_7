#pragma once
#include <iostream>
#include <time.h>
#include <iomanip>

#define EPS 1e-9
#define INF 1e9


using namespace std;

class queue_unit {
public:
    int id;
    double entry_time;
    queue_unit* next; //перед
    queue_unit* prev; //после

    queue_unit(int _id, double _entry_time) {
        id = _id;
        entry_time = _entry_time;
        next = NULL;
        prev = NULL;
    }
};

class queue {
public:

    queue_unit* head;
    queue_unit* tail;
    int length;

    queue() {
        head = NULL;
        tail = NULL;
        length = 0;
    }

    void push(int _id, double _entry_time) {

        length++;
        if (tail == NULL) {

            queue_unit* tempptr = new queue_unit(_id, _entry_time);
            tail = tempptr;
            head = tempptr;
        } else {

            queue_unit* tempptr = new queue_unit(_id, _entry_time);
            tail->prev = tempptr;
            tempptr->next = tail;
            tail = tempptr;
        }
    }

    void add(queue_unit* _unit) {

        length++;
        if (tail == NULL) {

            tail = _unit;
            head = _unit;
        } else {

            tail->prev = _unit;
            _unit->next = tail;
            tail = _unit;
        }
    }

    queue_unit* pop() {

        if (head == NULL) {
            cout << "error: queue is empty" << endl;
            return NULL;
        } else {
            length--;
            queue_unit* tempptr = head;
            head = head->prev;
            if (head != NULL) {
                head->next = NULL;
            } else {
                tail = NULL;
            }
            tempptr->prev = NULL;
            return tempptr;
        }
    }

    void print() {
        queue_unit* tempptr = head;
        cout << "queue: ";
        while (tempptr != NULL) {
            cout << tempptr->id << " ";
            tempptr = tempptr->next;
        }
        cout << ".  " << endl;
    }

    bool is_empty() {
        return head == NULL;
    }
};

class AO {
public:
    queue_unit* in_process;

    AO() {
        in_process = NULL;
    }

    bool is_empty() {
        return in_process == NULL;
    }

    void push(queue_unit* _unit) {

        if (is_empty()) {
            in_process = _unit;
        } else {
            cout << "error: AO isn't empty" << endl;
        }
    }

    queue_unit* pop() {

        if (is_empty()) {
            cout << "error: AO is empty" << endl;
            return NULL;
        } else {
            queue_unit* temp = in_process;
            in_process = NULL;
            return temp;
        }
    }

    void print() {
        cout << "AO: " << (in_process != NULL ? in_process->id : 0) << ".  ";
    }
};
