//
// Created by jodle on 9/29/23.
//

#include <diy_hardware_interface/diy_hardware_interface.hpp>

using namespace std::chrono_literals;

namespace diy_hardware_interface
{
  static constexpr size_t NUM_CONNECTION_TRIES = 100;
  static const rclcpp::Logger LOGGER = rclcpp::get_logger("DIYSystemPositionOnlyHardware");

  CallbackReturn DIYSystemPositionOnlyHardware::on_init(const hardware_interface::HardwareInfo& info)
  {
    if (hardware_interface::SystemInterface::on_init(info) != CallbackReturn::SUCCESS)
    {
      return CallbackReturn::ERROR;
    }

//    const auto rws_port = stoi(info_.hardware_parameters["rws_port"]);
//    const auto rws_ip = info_.hardware_parameters["rws_ip"];
//    const auto is_coupled = info_.hardware_parameters["j23_coupling"];
//
//    if (rws_ip == "None")
//    {
//      RCLCPP_FATAL(LOGGER, "RWS IP not specified");
//      return CallbackReturn::ERROR;
//    }
//
//    // Get robot controller description from RWS
//    abb::robot::RWSManager rws_manager(rws_ip, rws_port, "Default User", "robotics");
//    const auto robot_controller_description_ =
//        abb::robot::utilities::establishRWSConnection(rws_manager, "IRB1200", true);
//    RCLCPP_INFO_STREAM(LOGGER, "Robot controller description:\n"
//        << abb::robot::summaryText(robot_controller_description_));

    for (const hardware_interface::ComponentInfo& joint : info_.joints)
    {
      if (joint.command_interfaces.size() != 2)
      {
        RCLCPP_FATAL(LOGGER, "Joint '%s' has %zu command interfaces found. 2 expected.", joint.name.c_str(),
                     joint.command_interfaces.size());
        return CallbackReturn::ERROR;
      }

      if (joint.command_interfaces[0].name != hardware_interface::HW_IF_POSITION)
      {
        RCLCPP_FATAL(LOGGER, "Joint '%s' have %s command interfaces found as first command interface. '%s' expected.",
                     joint.name.c_str(), joint.command_interfaces[0].name.c_str(), hardware_interface::HW_IF_POSITION);
        return CallbackReturn::ERROR;
      }

      if (joint.command_interfaces[1].name != hardware_interface::HW_IF_VELOCITY)
      {
        RCLCPP_FATAL(LOGGER, "Joint '%s' have %s command interfaces found as second command interface. '%s' expected.",
                     joint.name.c_str(), joint.command_interfaces[1].name.c_str(), hardware_interface::HW_IF_VELOCITY);
        return CallbackReturn::ERROR;
      }

      if (joint.state_interfaces.size() != 2)
      {
        RCLCPP_FATAL(LOGGER, "Joint '%s' has %zu state interface. 2 expected.", joint.name.c_str(),
                     joint.state_interfaces.size());
        return CallbackReturn::ERROR;
      }

      if (joint.state_interfaces[0].name != hardware_interface::HW_IF_POSITION)
      {
        RCLCPP_FATAL(LOGGER, "Joint '%s' have %s state interface as first state interface. '%s' expected.",
                     joint.name.c_str(), joint.state_interfaces[0].name.c_str(), hardware_interface::HW_IF_POSITION);
        return CallbackReturn::ERROR;
      }

      if (joint.state_interfaces[1].name != hardware_interface::HW_IF_VELOCITY)
      {
        RCLCPP_FATAL(LOGGER, "Joint '%s' have %s state interface as first state interface. '%s' expected.",
                     joint.name.c_str(), joint.state_interfaces[1].name.c_str(), hardware_interface::HW_IF_VELOCITY);
        return CallbackReturn::ERROR;
      }
    }

//    urcl_ft_sensor_measurements_.resize(6);

    // Configure Serial
    RCLCPP_INFO(LOGGER, "Configuring DIY interface...");

    try
    {
      // TODO: FINISH Setting up SerialManager here
      const auto port_name = "/dev/ttyACM0";
      serial_manager_ = std::make_unique<diy::robot::SerialManager>(port_name);
    }
    catch (std::runtime_error& e)
    {
      RCLCPP_ERROR_STREAM(LOGGER, "Failed to initialize Serial connection");
      return CallbackReturn::ERROR;
    }

    if (!serial_manager_->isOpen()) {
      RCLCPP_ERROR_STREAM(LOGGER, "Failed to open serial port");
      return CallbackReturn::ERROR;
    }

    // TODO: This is where I left off

    return CallbackReturn::SUCCESS;
  }

  std::vector<hardware_interface::StateInterface> DIYSystemPositionOnlyHardware::export_state_interfaces()
  {
    std::vector<hardware_interface::StateInterface> state_interfaces;
//    for (auto& group : motion_data_.groups)
//    {
//      for (auto& unit : group.units)
//      {
//        for (auto& joint : unit.joints)
//        {
//          // TODO(seng): Consider changing joint names in robot description to match what comes
//          // from the ABB robot description to avoid needing to strip the prefix here
//          const auto pos1 = joint.name.find("joint");
//          std::string joint_name = joint.name.substr(pos1);
//          std::cout <<"Size of group.units is: " << group.units.size() << std::endl;
//          if(motion_data_.groups.size() >1){
//            if(std::string::npos == joint.name.find("rob")){
//              // in this situation we can't find "rob", meaning this is certainly an external axis mechanical group.
//              // So I guess we want to prefix this joint with "ext_"
//
//              joint_name = std::string("ext_") + std::string(joint_name);
//            }else{
//              const auto pos = joint.name.find("rob");
//              joint_name = joint.name.substr(pos);
//            }
//          }else{
//            joint_name = std::string("rob1_") + std::string(joint_name);
//          }
//
//          std::cout <<"Unstripped joint name: " << joint.name << std::endl;
//          std::cout <<"Stripped joint name: " << joint_name << std::endl;
//          state_interfaces.emplace_back(
//              hardware_interface::StateInterface(joint_name, hardware_interface::HW_IF_POSITION, &joint.state.position));
//          state_interfaces.emplace_back(
//              hardware_interface::StateInterface(joint_name, hardware_interface::HW_IF_VELOCITY, &joint.state.velocity));
//        }
//      }
//    }

//    for (auto& sensor : info_.sensors) {
//      for (uint j = 0; j < sensor.state_interfaces.size(); ++j) {
//        state_interfaces.emplace_back(hardware_interface::StateInterface(sensor.name, sensor.state_interfaces[j].name,
//                                                                         &urcl_ft_sensor_measurements_[j]));
//      }
//    }
    return state_interfaces;
  }

  std::vector<hardware_interface::CommandInterface> DIYSystemPositionOnlyHardware::export_command_interfaces()
  {
    std::vector<hardware_interface::CommandInterface> command_interfaces;
//    for (auto& group : motion_data_.groups)
//    {
//      for (auto& unit : group.units)
//      {
//        for (auto& joint : unit.joints)
//        {
//          // TODO(seng): Consider changing joint names in robot description to match what comes
//          // from the ABB robot description to avoid needing to strip the prefix here
//          const auto pos1 = joint.name.find("joint");
//          std::string joint_name = joint.name.substr(pos1);
//          if(motion_data_.groups.size() > 1){
//            if(std::string::npos == joint.name.find("rob")){
//              // in this situation we can't find "rob", meaning this is certainly an external axis mechanical group.
//              // So I guess we want to prefix this joint with "ext_"
//              joint_name = std::string("ext_") + std::string(joint_name);
//            }else{
//              const auto pos = joint.name.find("rob");
//              joint_name = joint.name.substr(pos);
//            }
//          }else{
//            joint_name = std::string("rob1_") + std::string(joint_name);
//          }
//
//          std::cout <<"Unstripped joint name: " << joint.name << std::endl;
//          std::cout <<"Stripped joint name: " << joint_name << std::endl;
//          command_interfaces.emplace_back(hardware_interface::CommandInterface(
//              joint_name, hardware_interface::HW_IF_POSITION, &joint.command.position));
//          command_interfaces.emplace_back(hardware_interface::CommandInterface(
//              joint_name, hardware_interface::HW_IF_VELOCITY, &joint.command.velocity));
//        }
//      }
//    }

    return command_interfaces;
  }

  CallbackReturn DIYSystemPositionOnlyHardware::on_activate(const rclcpp_lifecycle::State& /* previous_state */)
  {
//    size_t counter = 0;
//    RCLCPP_INFO(LOGGER, "Connecting to robot...");
//    while (rclcpp::ok() && ++counter < NUM_CONNECTION_TRIES)
//    {
//      // Wait for a message on any of the configured EGM channels.
//      if (egm_manager_->waitForMessage(500))
//      {
//        RCLCPP_INFO(LOGGER, "Connected to robot");
//        break;
//      }
//
//      RCLCPP_INFO(LOGGER, "Not connected to robot...");
//      if (counter == NUM_CONNECTION_TRIES)
//      {
//        RCLCPP_ERROR(LOGGER, "Failed to connect to robot");
//        return CallbackReturn::ERROR;
//      }
//      rclcpp::sleep_for(500ms);
//    }
//
//    egm_manager_->read(motion_data_);
//
//    RCLCPP_INFO(LOGGER, "ros2_control hardware interface was successfully started!");

    return CallbackReturn::SUCCESS;
  }

  return_type DIYSystemPositionOnlyHardware::read(const rclcpp::Time& time, const rclcpp::Duration& period)
  {
//    egm_manager_->read(motion_data_);
//
//    for (int i = 0; i < motion_data_.groups[0].egm_channel_data.input.mutable_measuredforce()->force_size(); i++) {
//      //RCLCPP_ERROR_STREAM(LOGGER, "force[" << motion_data_.groups[0].egm_channel_data.input.mutable_measuredforce()->force(i));
//      urcl_ft_sensor_measurements_[i] = motion_data_.groups[0].egm_channel_data.input.mutable_measuredforce()->force(i);
//    }
//    // TODO: (josh) I think that we're going to need to verify thta there aren't multiple IRB2400 or similar parallel link
//    // robots connected to the same controller via multimove. This would mean that we'd need to access more than just groups[0].
//    if(j23_coupling_){
//      motion_data_.groups[0].units[0].joints.at(2).state.position += J23_factor * motion_data_.groups[0].units[0].joints.at(1).state.position;
//      motion_data_.groups[0].units[0].joints.at(2).state.velocity += J23_factor * motion_data_.groups[0].units[0].joints.at(1).state.velocity;
//    }
    return return_type::OK;
  }

  return_type DIYSystemPositionOnlyHardware::write(const rclcpp::Time& time, const rclcpp::Duration& period)
  {

//    if(j23_coupling_){
////    RCLCPP_ERROR_STREAM(rclcpp::get_logger("temporary_trash"),"WRITE COUPLING");
//      motion_data_.groups[0].units[0].joints.at(2).command.position += (-1*J23_factor) * motion_data_.groups[0].units[0].joints.at(1).command.position;
//      motion_data_.groups[0].units[0].joints.at(2).command.velocity += (-1*J23_factor) * motion_data_.groups[0].units[0].joints.at(1).command.velocity;
//    }
//
////  for(uint i = 0; i < motion_data_.groups.size(); i++){
////    for(uint pp = 0; pp < motion_data_.groups[i].units.size(); pp++){
////
////    RCLCPP_ERROR_STREAM(rclcpp::get_logger("stupid"), "WRITING pos: " << motion_data_.groups[i].units[pp].joints[0].command.position << ", " <<
////    motion_data_.groups[i].units[pp].joints[1].command.position << ", " << motion_data_.groups[i].units[pp].joints[2].command.position <<  ", " <<
////    motion_data_.groups[i].units[pp].joints[3].command.position << ", " << motion_data_.groups[i].units[pp].joints[4].command.position << ", " <<
////    motion_data_.groups[i].units[pp].joints[5].command.position);
////    RCLCPP_ERROR_STREAM(rclcpp::get_logger("stupid"), "WRITING vel: " << motion_data_.groups[i].units[pp].joints[0].command.velocity << ", " <<
////    motion_data_.groups[i].units[pp].joints[1].command.velocity <<  ", " << motion_data_.groups[i].units[pp].joints[2].command.velocity << ", " <<
////    motion_data_.groups[i].units[pp].joints[3].command.velocity <<  ", " << motion_data_.groups[i].units[pp].joints[4].command.velocity << ", " <<
////    motion_data_.groups[i].units[pp].joints[5].command.velocity);
////    }
////  }
//    egm_manager_->write(motion_data_);
//    if(j23_coupling_){
////    RCLCPP_ERROR_STREAM(rclcpp::get_logger("temporary_trash"),"post-write re-COUPLING");
//      motion_data_.groups[0].units[0].joints.at(2).command.position += (J23_factor) * motion_data_.groups[0].units[0].joints.at(1).command.position;
//      motion_data_.groups[0].units[0].joints.at(2).command.velocity += (J23_factor) * motion_data_.groups[0].units[0].joints.at(1).command.velocity;
//    }
    return return_type::OK;
  }


}  // namespace abb_hardware_interface

#include "pluginlib/class_list_macros.hpp"

PLUGINLIB_EXPORT_CLASS(diy_hardware_interface::DIYSystemPositionOnlyHardware, hardware_interface::SystemInterface)
