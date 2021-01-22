#include "open_event.h"
using std::string;

namespace mtm {

    OpenEvent::OpenEvent(const DateWrap &date, const string &event_name) : BaseEvent(date, event_name) {

    }

    OpenEvent *OpenEvent::clone() const {
        return (new OpenEvent(*this));
    }
}