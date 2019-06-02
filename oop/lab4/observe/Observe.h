#include <vector>
#include <algorithm>

#ifndef OBSERVE_H
#define OBSERVE_H

enum ObserveEvent {
    CHANGE,
};

class Observable;

class Observer {
public:
    virtual void receive(ObserveEvent) = 0;
};

class Observable {
public:
    void subscribe(Observer* observer) {
        observers.push_back(observer);
    }

    void unsubscribe(Observer* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it == observers.end()) {
            return;
        }

        observers.erase(it);
    }

protected:
    void notify(ObserveEvent event) const {
        for (Observer* observer : observers) {
            observer->receive(event);
        }
    }

private:
    std::vector<Observer*> observers;
};

#endif // OBSERVE_H
