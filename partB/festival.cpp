#include "festival.h"
#include "exceptions.h"

namespace mtm {
    void Festival::add(const BaseEvent& event) {
        if (this->festival_date != event.getDate())
            throw DateMismatch();
        events.add(SharedPointer<BaseEvent>(event.clone()));
        sort();
    }

    Festival::Festival(const DateWrap &date)  : EventContainer(), festival_date(date) {

    }
}