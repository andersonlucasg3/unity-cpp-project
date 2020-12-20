#include "Trash.h"
#include <thread>
#include <list>

using namespace std;

namespace CppEngine {
    list<Object *> Trash::_trashBag;
    bool Trash::_running = false;

    thread Trash::_thread;
    sem_t *Trash::_incinerateSemaphore;
    sem_t *Trash::_addSemaphore;

    void Trash::garbageDisposer() {
        do {
            sem_wait(_addSemaphore);
            incinerate();
            sem_post(_incinerateSemaphore);
            this_thread::sleep_for(chrono::milliseconds(100));
        } while (_running);
    }

    void Trash::setup() {
        _incinerateSemaphore = sem_open("incinerate semaphore", O_CREAT);
        _addSemaphore = sem_open("add semaphore", O_CREAT);
        _running = true;
        _thread = thread(&garbageDisposer);
    }

    void Trash::add(Object *obj) {
        sem_wait(_incinerateSemaphore);
        _trashBag.push_front(obj);
        sem_post(_addSemaphore);
    }

    void Trash::empty() {
        _running = false;
        _thread.join();

        sem_close(_incinerateSemaphore);
        sem_close(_addSemaphore);

        incinerate();
    }

    void Trash::incinerate() {
        if (!_trashBag.empty()) {
            list<Object *>::iterator iterator = _trashBag.begin();
            for (int index = 0; index < _trashBag.size(); ++index) {
                advance(iterator, index);
                Object *obj = *iterator;
                delete obj;
            }
            _trashBag.clear();
        }
    }
}