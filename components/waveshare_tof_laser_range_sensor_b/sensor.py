import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome import automation
from esphome.const import *


CODEOWNERS = ["@BBart19"]
DEPENDENCIES = ["uart"]

waveshare_tof_laser_range_sensor_b_ns = cg.esphome_ns.namespace("waveshare_tof_laser_range_sensor_b")
WaveshareTOFLaserRangeSensorB = waveshare_tof_laser_range_sensor_b_ns.class_(
    "WaveshareTOFLaserRangeSensorB", sensor.Sensor, cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = sensor.sensor_schema(
    WaveshareTOFLaserRangeSensorB,
    unit_of_measurement=UNIT_MILLIMETER,
    icon=ICON_ARROW_EXPAND_VERTICAL,
    accuracy_decimals=0,
    state_class=STATE_CLASS_MEASUREMENT,
    device_class=DEVICE_CLASS_DISTANCE,
).extend(uart.UART_DEVICE_SCHEMA)


async def to_code(config):
    var = await cg.get_variable(config[CONF_ID])
    await sensor.register_sensor(var, config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

