#include "Trash.h"

using namespace std;

namespace CppEngine {
    queue<Object *> Trash::_trashBag;
    bool Trash::_running = false;

    thread Trash::_thread;
    sem_t *Trash::_incinerateSemaphore;
    sem_t *Trash::_addSemaphore;
    sem_t *Trash::_mutex;

    void Trash::garbageDisposer() {
        do {
            sem_wait(_addSemaphore);

            sem_wait(_mutex);
            incinerate();
            sem_post(_mutex);

            sem_post(_incinerateSemaphore);
            this_thread::sleep_for(chrono::milliseconds(100));
        } while (_running);
    }

    void Trash::setup() {
        static string_c incinerateSem = "incinerate semaphore";
        static string_c addSem = "add semaphore";
        static string_c mutexSem = "mutex semaphore";
        _incinerateSemaphore = sem_open(incinerateSem, O_CREAT);
        _addSemaphore = sem_open(addSem, O_CREAT);
        _mutex = sem_open(mutexSem, O_CREAT);
        sem_unlink(incinerateSem);
        sem_unlink(addSem);
        sem_unlink(mutexSem);
        _running = true;
        _thread = thread(&garbageDisposer);
    }

    void Trash::add(Object *obj) {
        sem_wait(_incinerateSemaphore);

        sem_wait(_mutex);
        _trashBag.push(obj);
        sem_post(_mutex);

        sem_post(_addSemaphore);
    }

    void Trash::empty() {
        _running = false;
        _thread.join();

        sem_close(_incinerateSemaphore);
        sem_close(_addSemaphore);
        sem_close(_mutex);

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