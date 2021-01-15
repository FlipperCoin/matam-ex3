#include <exception>

using std::exception;

namespace mtm {
    class Exception : public exception {};

    // DateWrap
    class NegativeDays : public Exception {};
    class InvalidDate : public Exception {};

    // Events
    class InvalidStudent : public Exception {};
    class AlreadyRegistered : public Exception {};
    class NotRegistered : public Exception {};
    class EventAlreadyExists : public Exception {};
    class EventDoesNotExist : public Exception {};
    class RegistrationBlocked : public Exception {};
}