//
// Created by jodle on 9/29/23.
//

#ifndef BUILD_DATA_CONTAINERS_HPP
#define BUILD_DATA_CONTAINERS_HPP

#include <string>
#include <vector>

namespace diy {
  namespace robot {

    struct SerialData {
      /**
       * \brief State of a joint.
       */
      struct JointState {
        /**
         * \brief Position in [radians] or [m].
         */
        double position;

        // TODO: Unfortunately the controller is not yet build to take velocity commands
//
//        /**
//         * \brief Velocity in [radians/s] or [m/s] (this is only intended for EGM).
//         */
//        double velocity;
//
//        /**
//         * \brief Effort in [Nm] or [N] (this is only used as a placeholder).
//         */
//        double effort;
      };

      /**
       * \brief Command for a joint (this is only intended for EGM).
       */
      struct JointCommand {
        /**
         * \brief Position in [radians] or [m].
         */
        double position;

//        /**
//         * \brief Velocity in [radians/s] or [m/s].
//         */
//        double velocity;
      };

      /**
       * \brief Motion data for a joint.
       */
      struct Joint {
        /**
         * \brief The joint's (standardized) name.
         */
        std::string name;

        /**
         * \brief Indicator for rotational or linear motion.
         */
        bool rotational;

        /**
         * \brief Lower limit in [radians] or [m].
         */
        double lower_limit;

        /**
         * \brief Upper limit in [radians] or [m].
         */
        double upper_limit;

        /**
         * \brief State of the joint.
         */
        JointState state;

        /**
         * \brief Command for the joint.
         */
        JointCommand command;
      };

      /**
       * \brief Digital input data.
       */
      struct DigitalInput {
        bool state;
      };

      /**
       * \brief Digital output data.
       */
      struct DigitalOutput {
        bool state;
      };

      // List of joints.
      std::vector<Joint> joints;

      // Digital inputs.
      std::vector<DigitalInput> digital_inputs;

      // Digital outputs.
      std::vector<DigitalOutput> digital_outputs;

      /**
       * \brief Robot speed.
       */
      double robotSpeed;

      /**
       * \brief Packet received indicator.
       */
      bool packetReceived;
    };

  } // namespace robot

} // namespace diy
#endif //BUILD_DATA_CONTAINERS_HPP
