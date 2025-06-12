#pragma once
#include "Event.h"
#include <functional>
#include <map>
#include <vector>
#include <string>

class EventSystem {
public:
    using EventCallback = std::function<void(Event*)>;

    void subscribe(const std::string& eventType, const EventCallback& callback);
    void unsubscribe(const std::string& eventType, const EventCallback& callback);
    void emit(const std::string& eventType, Event* event);

private:
    std::map<std::string, std::vector<EventCallback>> m_subscribers;

    // Fonction utilitaire pour comparer deux callbacks
    bool areCallbacksEqual(const EventCallback& a, const EventCallback& b);
};