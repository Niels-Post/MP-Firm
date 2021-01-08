#include <core/communication/Response.hpp>
#include <cstddef>

Response::Response(uint8_t messageId, SuccessCode returnCode, uint8_t data_length, const uint8_t *dat, bool _broadcast)
        : message_id(messageId),
          successCode(returnCode), broadcast(_broadcast) {
    for (size_t i = 0; i < 4; i++) {
        data[i] = dat[i];
    }
}

Response::Response(SuccessCode returnCode, uint8_t data_length, const uint8_t *dat, bool _broadcast): Response(0, returnCode, data_length, dat, _broadcast) {

}

uint8_t Response::size() const {
    return 2 + data_size;
}
