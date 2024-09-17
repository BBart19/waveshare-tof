#include "waveshare_tof_laser_range_sensor_b.h"
#include "esphome/core/log.h"

namespace esphome {
namespace waveshare_tof_laser_range_sensor_b {

static const char *const TAG = "waveshare_tof_laser_range_sensor_b";

void WaveshareTOFLaserRangeSensorB::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Waveshare TOF Laser Range Sensor B...");
}

void WaveshareTOFLaserRangeSensorB::loop() {
  const uint8_t TOF_HEADER[3] = {0x57, 0x00, 0xFF};
  uint8_t TOF_data[32] = {0};
  uint8_t TOF_LENGTH = 16;
  uint32_t TOF_distance = 0;

  while (this->available() >= 32) {
    this->read_array(TOF_data, 32);

    for (int j = 0; j <= 16; j++) {
      if ((TOF_data[j] == TOF_HEADER[0] && TOF_data[j + 1] == TOF_HEADER[1] && TOF_data[j + 2] == TOF_HEADER[2]) &&
          (verify_checksum(&TOF_data[j], TOF_LENGTH))) {
        TOF_distance = (TOF_data[j + 8]) | (TOF_data[j + 9] << 8) | (TOF_data[j + 10] << 16);
        this->publish_state(TOF_distance);
        break;
      }
    }
  }
}

bool WaveshareTOFLaserRangeSensorB::verify_checksum(uint8_t data[], uint8_t len) {
  uint8_t checksum = 0;

  for (uint8_t k = 0; k < len - 1; k++) {
    checksum += data[k];
  }

  return checksum == data[len - 1];
}

void WaveshareTOFLaserRangeSensorB::dump_config() {
  ESP_LOGCONFIG(TAG, "Waveshare TOF Laser Range Sensor B:");
  LOG_SENSOR("", "Waveshare TOF Distance", this);
}

}  // namespace waveshare_tof_laser_range_sensor_b
}  // namespace esphome

