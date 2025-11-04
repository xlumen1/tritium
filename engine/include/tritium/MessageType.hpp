#include "api.hpp"

namespace tritium {
    enum class MessageType {
        REQUEST_DATA,
        SEND_DATA,
        SLEEP,
        WAKE,
        ACKNOWLEDGE
    };
} // namespace tritium

