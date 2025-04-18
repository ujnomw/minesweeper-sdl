#pragma once

#include <SDL.h>

#include <map>
#include <vector>
class EventReceiver
{
   private:
    std::map<EventReceiver*, std::vector<Uint32>> d_children;

   public:
    EventReceiver() {}
    void SubscribeToEventTypes(EventReceiver* i_child, std::vector<Uint32> i_eventTypes)
    {
        d_children.emplace(i_child, i_eventTypes);
    }

    void SetParent(EventReceiver* i_parent, std::vector<Uint32> i_eventTypes)
    {
        i_parent->SubscribeToEventTypes(this, i_eventTypes);
    }

    bool IsChildSubscribedToEventType(EventReceiver* i_child, Uint32 i_eventType)
    {
        for (auto eventType : d_children[i_child])
        {
            if (eventType == i_eventType)
            {
                return true;
            }
        }
        return false;
    }
};