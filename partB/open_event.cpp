#include "open_event.h"

namespace mtm {
    OpenEvent::OpenEvent(const DateWrap &date, const string& event_name, const int * participants, int participants_length)
            : BaseEvent(date,event_name,participants,participants_length) {

    }
}