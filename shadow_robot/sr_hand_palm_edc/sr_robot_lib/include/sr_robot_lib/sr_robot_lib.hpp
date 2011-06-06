/**
 * @file   sr_robot_lib.hpp
 * @author Ugo Cupcic <ugo@shadowrobot.com>
 * @date   Fri Jun  3 12:12:13 2011
 *
*
* Copyright 2011 Shadow Robot Company Ltd.
*
* This program is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the Free
* Software Foundation, either version 2 of the License, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program.  If not, see <http://www.gnu.org/licenses/>.
*
 * @brief This is a generic robot library for Shadow Robot's Hardware.
 *
 *
 */

#ifndef _SR_ROBOT_LIB_HPP_
#define _SR_ROBOT_LIB_HPP_

#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <vector>
#include <map>

#include <pr2_hardware_interface/hardware_interface.h>

namespace shadow_joints
{
  struct Motor
  {
    //the position of the motor in the motor array
    // coming from the hardware
    int motor_id;

    //actuator
    pr2_hardware_interface::Actuator* actuator;

    //Data we can read from the motor
    double encoder_position;
    double torque;

    double strain_gauge_left;
    double strain_gauge_right;
    double pwm;
    double flags;
    double current;
    double voltage;
    int can_msgs_received;
    int can_msgs_transmitted;

    int firmware_svn_revision;

    int force_control_p;
    int force_control_i;
    int force_control_d;
    int force_control_imax;
    int force_control_deadband;
  };

  struct Joint
  {
    //the index of the joint in the joint array
    // coming from the hardware
    int joint_id;

    double calibrated_position;

    bool has_motor;
    boost::shared_ptr<Motor> motor;
  };

  typedef std::map<std::string, boost::shared_ptr<Joint> > JointsMap;
}

namespace shadow_robot
{
  class SrRobotLib
  {
  public:
    SrRobotLib(std::vector<std::string> joint_names, std::vector<int> motor_ids,
               std::vector<int> joint_ids, std::vector<pr2_hardware_interface::Actuator*> actuators) {};
    ~SrRobotLib() {};

    shadow_joints::JointsMap joints_map;
    boost::mutex joints_map_mutex;

  protected:
    virtual void initialize_map(std::vector<std::string> joint_names,
                                std::vector<int> motor_ids,
                                std::vector<int> joint_ids,
                                std::vector<pr2_hardware_interface::Actuator*> actuators) = 0;
  };
}

/* For the emacs weenies in the crowd.
Local Variables:
   c-basic-offset: 2
End:
*/

#endif
