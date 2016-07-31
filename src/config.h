/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  config.h -- hwinfo configuration
*/

#ifndef _CONFIG_H
#define _CONFIG_H

#include "component.h"
#include "aggregator.h"
#include "nodes.h"

DECLARE_COMPONENT(battery, "capacity", "capacity_level", "cycle_count")
DECLARE_NODES(battery, "/sys/class/power_supply/BAT0","/sys/class/power_supply/BAT1")
DECLARE_AGGREGATION(battery, "capacity", sum)

#endif
