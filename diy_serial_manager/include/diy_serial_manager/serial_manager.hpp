//
// Created by jodle on 9/29/23.
//

#pragma once

#include <string>
#include <mutex>
#include <iostream>

#include <diy_serial_manager/utilities.hpp>
#include <serial/serial.h>

namespace diy
{
  namespace robot
  {
    class SerialManager
    {
    public:
      explicit SerialManager(const std::string&  port_name);
      ~SerialManager();

      // Position-related functions
      bool read(SerialData& motion_date);  // Read position from serial port
      void write(const SerialData& motion_data);  // Send position to serial port

    private:
      static const int ARRAY_SIZE = 15;
      std::array<uint8_t , ARRAY_SIZE> data_to_send_{};
      std::array<uint8_t , ARRAY_SIZE> data_received_{};
      serial::Serial ser_;

      // Add members for actual serial communication. Depending on the library used, this
      // might include file descriptors, configuration settings, buffers, etc.
    };
  }
}
