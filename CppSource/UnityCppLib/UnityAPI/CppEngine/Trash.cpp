#include "Trash.h"
#include <thread>
#include <list>

using namespace std;

namespace CppEngine {
    list<Object *> Trash::_trashBag;
    bool Trash::_running = false;

    thread Trash::_thread;
    sem_t Trash::_incinerateSemaphore;
    sem_t Trash::_addSemaphore;
    sem_t Trash::_mutex;

    void Trash::garbageDisposer() {
        do {
            sem_wait(&_addSemaphore);

            sem_wait(&_mutex);
            incinerate();
            sem_post(&_mutex);

            sem_post(&_incinerateSemaphore);
            this_thread::sleep_for(chrono::milliseconds(100));
        } while (_running);
    }

    void Trash::setup() {
        sem_init(&_incinerateSemaphore, 0, SEM_VALUE_MAX);
        sem_init(&_addSemaphore, 0, 0);
        sem_init(&_mutex, 0, 1);
        _running = true;
        _thread = thread(&garbageDisposer);
    }

    void Trash::add(Object *obj) {
        sem_wait(&_incinerateSemaphore);

        sem_wait(&_mutex);
        _trashBag.push_front(obj);
        sem_post(&_mutex);

        sem_post(&_addSemaphore);
    }

    void Trash::empty() {
        _running = false;
        _thread.join();

        sem_destroy(&_incinerateSemaphore);
        sem_destroy(&_addSemaphore);
        sem_destroy(&_mutex);

        incinerate();
    }

    void Trash::incinerate() {
        if (!_trashBag.empty()) {
            list<Object *>::iterator iterator = _trashBag.begin();
            for (int index = 0; index < _trashBag.size(); ++index) {
                advance(iterator, index);
                Object *obj = *iterator;
                Managed::destroy(obj->_instance.toPointer());
                delete obj;
            }
            _trashBag.clear();
        }
    }
}