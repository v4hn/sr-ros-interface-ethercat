/**
* @file   motor_trace_buffer.h
* @author Ugo Cupcic <ugo@shadowrobot.com>
* @date   Tue Aug 23 11:39:25 2011
*
/* Copyright 2011 Shadow Robot Company Ltd.
*
* This program is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the Free
* Software Foundation version 2 of the License.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*
*
* @brief  Publishes the last second of the motor controller.
*
*
*/

#ifndef SR_EDC_ETHERCAT_DRIVERS_MOTOR_TRACE_BUFFER_H
#define SR_EDC_ETHERCAT_DRIVERS_MOTOR_TRACE_BUFFER_H

#include <sr_edc_ethercat_drivers/MotorTraceSample.h>
#include <sr_edc_ethercat_drivers/ActuatorInfo.h>
#include <sr_edc_ethercat_drivers/MotorTrace.h>

#include <realtime_tools/realtime_publisher.h>
#include <boost/thread/condition.hpp>  // Missing from realtime_publisher : wg-ros-pkg Ticket #4682
#include <boost/utility.hpp>
#include <string>
#include <vector>

namespace sr_edc_ethercat_drivers
{
/**
* \brief Class to buffer and publish previous 1-second of motor data
*
* Data is sampled with each cycle of realtime loop so that there
* is too much data to be published continuouly.  Instead of continuously
* publishing data, the trace buffers the previous X seconds of samples.
* Publishing can be triggered as result of event or request.
*/
class MotorTraceBuffer :
        private boost::noncopyable
{
public:
  explicit MotorTraceBuffer(unsigned trace_size);

  bool initialize(const sr_edc_ethercat_drivers::ActuatorInfo &actuator_info);

  void flagPublish(const std::string &reason, int level, int delay);

  void checkPublish();

  void sample(const sr_edc_ethercat_drivers::MotorTraceSample &s);

  void reset();

protected:
  unsigned trace_size_;  // !< size of trace vector
  unsigned trace_index_;  // !< index of most recent element in trace vector
  unsigned published_traces_;  // !< number of times motor trace has been published
  std::vector<sr_edc_ethercat_drivers::MotorTraceSample> trace_buffer_;
  realtime_tools::RealtimePublisher<sr_edc_ethercat_drivers::MotorTrace> *publisher_;
  int publish_delay_;
  int publish_level_;
  std::string publish_reason_;
};
}  // namespace sr_edc_ethercat_drivers

#endif  // SR_EDC_ETHERCAT_DRIVERS_MOTOR_TRACE_BUFFER_H
