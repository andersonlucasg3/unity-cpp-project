#include "Trash.h"

using namespace std;

namespace CppEngine {
    queue<Object *> Trash::_trashBag;
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
        _trashBag.push(obj);
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
        while (!_trashBag.empty()) {
            Object *obj = _trashBag.front();
            _trashBag.pop();
            Managed::destroy(obj->_instance.toPointer());
            delete obj;
        }
    }
}