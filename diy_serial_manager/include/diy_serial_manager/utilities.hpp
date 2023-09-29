//
// Created by jodle on 9/29/23.
//

#pragma once

#include <cmath>

#include "data_containers.hpp"

namespace diy
{
  namespace robot {

/**
 * \brief Various constant values.
 */
    struct Constants
        {
            /**
             * \brief Conversion value from radians to degrees.
             */
            static constexpr double RAD_TO_DEG{ 180.0 / M_PI };

            /**
             * \brief Conversion value from degrees to radians.
             */
            static constexpr double DEG_TO_RAD{ M_PI / 180.0 };

            /**
             * \brief Conversion value from millimeter to meter.
             */
            static constexpr double MM_TO_M{ 0.001 };

            /**
             * \brief Conversion value from meter to millimeter.
             */
            static constexpr double M_TO_MM{ 1000.0 };

            /**
             * \brief Identifier for if a mechanical unit has/is an integrated unit.
             *
             * Note: Using assignment initialization, instead of initializer list, due to compilation issue with MSVC:
             *       https://developercommunity.visualstudio.com/content/problem/447124/compilation-fails-with-brace-initializer-for-const.html
             */
            static constexpr char NO_INTEGRATED_UNIT[] = "NoIntegratedUnit";
        };

  } // namespace robot
} // namespace diy

