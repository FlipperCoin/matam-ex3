#include <exception>

using std::exception;

namespace mtm {
    class Exception : public exception {};

    class NegativeDays : public Exception {};
}