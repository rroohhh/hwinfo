/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  config.h -- hwinfo configuration
*/

#ifndef _CONFIG_H
#define _CONFIG_H

#include "component.h"
#include "aggregator.h"
#include "nodes.h"

DECLARE_COMPONENT(battery, "alarm", "capacity", "capacity_level", "cycle_count",
                  "energy_full", "energy_full_design", "energy_now",
                  "manufacturer", "model_name", "power_now", "present",
                  "serial_number", "status", "technology", "type",
                  "voltage_min_design", "voltage_now")
DECLARE_NODES(battery, "/sys/class/power_supply/BAT0",
              "/sys/class/power_supply/BAT1")

DECLARE_COMPONENT(backlight, "actual_brightness", "bl_power", "brightness",
                  "max_brightness", "type")
DECLARE_NODES(backlight, "/sys/class/backlight/intel_backlight")


// DECLARE_COMPONENT(battery, "capacity", "capacity_level", "cycle_count")
// DECLARE_NODES(battery, "/sys/class/power_supply/BAT0",
//               "/sys/class/power_supply/BAT1")

#endif
