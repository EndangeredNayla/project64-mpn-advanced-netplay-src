#pragma once

#include "stdafx.h"

#include "packet.h"

class connection: public std::enable_shared_from_this<connection> {
public:
    connection(asio::io_service& io_s);
    void read(std::function<void(packet& p)> read_handler);
    void send(const packet& p, bool flush = true);
    void flush();

protected:
    asio::ip::tcp::socket socket;

    virtual void handle_error(const asio::error_code& error);

private:
    uint8_t packet_size_buffer[2];

    std::vector<uint8_t> output_buffer;
    bool is_writing = false;
};
