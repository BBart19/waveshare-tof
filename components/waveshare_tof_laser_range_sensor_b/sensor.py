import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import (
    STATE_CLASS_MEASUREMENT,
    ICON_ARROW_EXPAND_VERTICAL,
    DEVICE_CLASS_DISTANCE,
    UNIT_MILLIMETER,
)

CODEOWNERS = ["@BBart19"]
DEPENDENCIES = ["uart"]

waveshare_ns = cg.esphome_ns.namespace("waveshare_tof_laser_range_sensor_b")
WaveshareTOFLaserRangeSensorB = waveshare_ns.class_(
    "WaveshareTOFLaserRangeSensorB", sensor.Sensor, cg.PollingComponent, uart.UARTDevice
)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        unit_of_measurement=UNIT_MILLIMETER,
        icon=ICON_ARROW_EXPAND_VERTICAL,
        accuracy_decimals=0,
        state_class=STATE_CLASS_MEASUREMENT,
        device_class=DEVICE_CLASS_DISTANCE,
    )
    .extend(cv.polling_component_schema("1s"))
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend({cv.GenerateID(): cv.declare_id(WaveshareTOFLaserRangeSensorB)})
)

async def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    await uart.register_uart_device(var, config)
