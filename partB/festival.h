#ifndef _FESTIVAL_H_
#define _FESTIVAL_H_

#include "base_event.h"
#include "event_container.h"

namespace mtm {
    class Festival : public EventContainer{
    private:
        DateWrap festival_date;
    public:
        explicit Festival(const DateWrap& date);
        void add(const BaseEvent& event) override;
        Festival(const Festival& other) = default;
        ~Festival() override = default;
        Festival& operator=(const Festival& other) = default;
    };
}

#endif