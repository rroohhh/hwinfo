/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  component_array.h -- stores an array of equal components and their
  capatibilities
*/

#ifndef _COMPONENT_ARRAY_H
#define _COMPONENT_ARRAY_H

#include "component.h"
#include "capatibility.h"

struct ComponentArray {
    std::vector<Component *> components;
    std::vector<Capatibility> capatibilities;
};

#endif
