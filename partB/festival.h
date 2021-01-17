#ifndef _FESTIVAL_H_
#define _FESTIVAL_H_

#include "base_event.h"
#include "event_container.h"

namespace mtm {
    class Festival : public EventContainer{
    private:
        DateWrap festival_date;
    public:
        explicit Festival(const DateWrap& date) : festival_date(date), EventContainer(){
        };
        void add(const BaseEvent& event) override;
        void resizeListEvents();
    };
}

#endif