#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace waveshare_tof_laser_range_sensor_b {

class WaveshareTOFLaserRangeSensorB : public Component, public sensor::Sensor {
 public:
  WaveshareTOFLaserRangeSensorB(int rx_pin, int tx_pin) : rx_pin_(rx_pin), tx_pin_(tx_pin) {}

  void setup() override;
  void loop() override;
  void dump_config() override;

 protected:
  bool verify_checksum(uint8_t data[], uint8_t len);
  int rx_pin_;
  int tx_pin_;
};

}  // namespace waveshare_tof_laser_range_sensor_b
}  // namespace esphome
