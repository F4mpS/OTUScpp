#include "async.h"

namespace async {

handle_t connect(std::size_t bulk) {
    return new Moderator(bulk);
}

void receive(handle_t handle, const char *data, std::size_t size) {
    handle->ReadBuffer(data, size);
}

void disconnect(handle_t handle) {
    handle->EndReceiving();
}

}
