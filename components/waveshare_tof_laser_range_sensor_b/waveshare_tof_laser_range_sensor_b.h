#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace waveshare_tof_laser_range_sensor_b {

class WaveshareTOFLaserRangeSensorB : public uart::UARTDevice, public PollingComponent, public sensor::Sensor {
 public:
  WaveshareTOFLaserRangeSensorB() = default;

  void setup() override;
  void update() override;
  void dump_config() override;

 protected:
  bool verify_checksum(const uint8_t *data, uint8_t len);
};

}  // namespace waveshare_tof_laser_range_sensor_b
}  // namespace esphome
