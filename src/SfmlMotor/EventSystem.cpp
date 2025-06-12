#include "pch.h"
#include "EventSystem.h"
#include <algorithm>

void EventSystem::subscribe(const std::string& eventType, const EventCallback& callback) {
    m_subscribers[eventType].push_back(callback);
}

void EventSystem::unsubscribe(const std::string& eventType, const EventCallback& callback) {
    auto it = m_subscribers.find(eventType);
    if (it != m_subscribers.end()) {
        auto& callbacks = it->second;
        callbacks.erase(
            std::remove_if(callbacks.begin(), callbacks.end(),
                [&](const EventCallback& cb) {
                    return cb.target<void(Event*)>() == callback.target<void(Event*)>();
                }),
            callbacks.end()
        );
    }
}

void EventSystem::emit(const std::string& eventType, Event* event) {
    auto it = m_subscribers.find(eventType);
    if (it != m_subscribers.end()) {
        auto callbacks = it->second;
        for (const auto& callback : callbacks) {
            callback(event);
        }
    }
}