#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <exception>

using std::exception;

namespace mtm {
    class Exception : public exception {};

    // DateWrap
    class NegativeDays : public Exception {};
    class InvalidDate : public Exception {};
    class InvalidStudent : public Exception {};
    class AlreadyRegistered : public Exception {};
    class AlreadyInvited : public Exception {};
    class NotRegistered : public Exception {};
    class RegistrationBlocked : public Exception {};
}

#endif