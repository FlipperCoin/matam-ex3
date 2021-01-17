#include "festival.h"
#include "exceptions.h"

namespace mtm {

    void Festival::add(const BaseEvent& event) {
        if (this->festival_date != event.getDate())
            throw DateMismatch();

        if (events_num == events_max){
            this->resizeListEvents();
        }
        events[events_num++] = event.clone();
        this->sort();
    }

    void Festival::resizeListEvents() {
        BaseEvent* *temp = new BaseEvent*[events_max + LIST_RESIZE];
        events_max += LIST_RESIZE;
        for (int i = 0; i < events_num; i++) {
            temp[i] = events[i];
        }
        delete[] events;
        events = temp;
    }

}