#include <exception>
#ifndef _EXCEPTIONS_
#define _EXCEPTIONS_

namespace mtm {
    class Exception : public std::exception {};

    // DateWrap
    class NegativeDays : public Exception {};
    class InvalidDate : public Exception {};

    // Events
    class InvalidStudent : public Exception {};
    class AlreadyRegistered : public Exception {};
    class AlreadyInvited : public Exception {};
    class NotRegistered : public Exception {};
    class EventAlreadyExists : public Exception {};
    class EventDoesNotExist : public Exception {};
    class RegistrationBlocked : public Exception {};
    class DateMismatch : public Exception {};
    class NotSupported : public Exception {};
    class InvalidNumber : public Exception {};
    class InvalidInterval : public Exception {};

}

#endif