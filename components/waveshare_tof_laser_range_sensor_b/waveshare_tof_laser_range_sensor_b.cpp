#include "waveshare_tof_laser_range_sensor_b.h"
#include "esphome/core/log.h"

namespace esphome {
namespace waveshare_tof_laser_range_sensor_b {

static const char *const TAG = "waveshare_tof_laser_range_sensor_b";

void WaveshareTOFLaserRangeSensorB::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Waveshare TOF Laser Range Sensor B...");
}

void WaveshareTOFLaserRangeSensorB::update() {
  const uint8_t TOF_HEADER[3] = {0x57, 0x00, 0xFF};
  const uint8_t TOF_LENGTH = 16;
  uint8_t data[32];

  while (this->available() >= 32) {
    this->read_array(data, 32);

    for (int i = 0; i <= 16; i++) {
      if (data[i] == TOF_HEADER[0] && data[i + 1] == TOF_HEADER[1] && data[i + 2] == TOF_HEADER[2]) {
        if (verify_checksum(&data[i], TOF_LENGTH)) {
          uint32_t distance = (uint32_t)data[i + 8] | ((uint32_t)data[i + 9] << 8) | ((uint32_t)data[i + 10] << 16);
          ESP_LOGD(TAG, "Distance: %u mm", distance);
          this->publish_state(distance);
          return;
        } else {
          ESP_LOGW(TAG, "Checksum failed");
        }
      }
    }
  }
}

bool WaveshareTOFLaserRangeSensorB::verify_checksum(const uint8_t *data, uint8_t len) {
  uint8_t checksum = 0;
  for (uint8_t i = 0; i < len - 1; i++) {
    checksum += data[i];
  }
  return checksum == data[len - 1];
}

void WaveshareTOFLaserRangeSensorB::dump_config() {
  ESP_LOGCONFIG(TAG, "Waveshare TOF Laser Range Sensor B:");
  LOG_SENSOR("", "Waveshare TOF Distance", this);
  LOG_UPDATE_INTERVAL(this);
}

}  // namespace waveshare_tof_laser_range_sensor_b
}  // namespace esphome
