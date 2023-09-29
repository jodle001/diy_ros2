//
// Created by jodle on 9/29/23.
//

#pragma once

#include <chrono>
#include <cmath>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include <diy_hardware_interface/visibility_control.hpp>
#include <diy_serial_manager/serial_manager.hpp>

#include <hardware_interface/handle.hpp>
#include <hardware_interface/hardware_info.hpp>
#include <hardware_interface/system_interface.hpp>
#include <hardware_interface/types/hardware_interface_return_values.hpp>
#include <hardware_interface/types/hardware_interface_type_values.hpp>
#include <rclcpp/macros.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp>
#include <rclcpp_lifecycle/state.hpp>

using hardware_interface::return_type;
using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

namespace diy_hardware_interface {

  class DIYSystemPositionOnlyHardware : public hardware_interface::SystemInterface {
  public:
    RCLCPP_SHARED_PTR_DEFINITIONS(DIYSystemPositionOnlyHardware)

    ROS2_CONTROL_DRIVER_PUBLIC
    CallbackReturn on_init(const hardware_interface::HardwareInfo& info) override;

    ROS2_CONTROL_DRIVER_PUBLIC
    std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

    ROS2_CONTROL_DRIVER_PUBLIC
    std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

    ROS2_CONTROL_DRIVER_PUBLIC
    CallbackReturn on_activate(const rclcpp_lifecycle::State& previous_state) override;

    ROS2_CONTROL_DRIVER_PUBLIC
    return_type read(const rclcpp::Time& time, const rclcpp::Duration& period) override;

    ROS2_CONTROL_DRIVER_PUBLIC
    return_type write(const rclcpp::Time& time, const rclcpp::Duration& period) override;
  private:
    std::unique_ptr<diy::robot::SerialManager> serial_manager_;
    diy::robot::SerialData serial_data_;

  }; // End of class

} // End of namespace diy_hardware_interface
