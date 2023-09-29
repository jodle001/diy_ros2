//
// Created by jodle on 9/29/23.
//

#include <diy_serial_manager/serial_manager.hpp>
#include <utility>

namespace diy {
  namespace robot {

    SerialManager::SerialManager(const std::string& port_name) {
      try {
        ser_.setPort(port_name);
        ser_.setBaudrate(9600);  // Set this to your specific requirement
        serial::Timeout timeout = serial::Timeout::simpleTimeout(1000); // 1 second timeout
        ser_.setTimeout(timeout);
        ser_.open();
      } catch (serial::IOException& e) {
        std::cerr << "Unable to open port " << port_name << std::endl;
      }

      if(!ser_.isOpen()) {
        std::cerr << "Failed to open serial port" << std::endl;
      }
    }

    SerialManager::~SerialManager() {
      if(ser_.isOpen()) {
        ser_.close();
      }
    }

    bool SerialManager::read(SerialData& motion_data) {
      size_t bytesRead = ser_.read(data_received_.data(), ARRAY_SIZE);

      if(bytesRead == ARRAY_SIZE) {
        if(data_received_[0] != 253 || data_received_[14] != 254) {
          return false; // Incorrect packet format
        }

        for(int i = 1; i <= 6; ++i) {
          motion_data.joints[i-1].state.position = static_cast<double>(data_received_[i]);
        }

        for(int i = 7; i <= 9; ++i) {
          motion_data.digital_inputs[i-7].state = static_cast<bool>(data_received_[i]);
        }

        for(int i = 10; i <= 12; ++i) {
          motion_data.digital_outputs[i-10].state = static_cast<bool>(data_received_[i]);
        }

        motion_data.robotSpeed = static_cast<double>(data_received_[13]);
        // Assuming robotSpeed in byte format maps to a meaningful double representation.
        // If not, you might need to scale or adjust this value.

        return true;
      }
      return false;
    }

    void SerialManager::write(const SerialData& motion_data) {
      data_to_send_[0] = 253;
      for(int i = 1; i <= 6; ++i) {
        data_to_send_[i] = static_cast<uint8_t>(motion_data.joints[i-1].command.position);
      }
      for(int i = 7; i <= 9; ++i) {
        data_to_send_[i] = static_cast<uint8_t>(motion_data.digital_inputs[i-7].state);
      }
      for(int i = 10; i <= 12; ++i) {
        data_to_send_[i] = static_cast<uint8_t>(motion_data.digital_outputs[i-10].state);
      }
      data_to_send_[13] = static_cast<uint8_t>(motion_data.robotSpeed);
      // Again, assuming robotSpeed can be casted meaningfully to a byte.
      // If not, you might need to scale or adjust this value.

      data_to_send_[14] = 254;

      ser_.write(data_to_send_.data(), ARRAY_SIZE);
    }

  } // namespace robot
} // namespace diy