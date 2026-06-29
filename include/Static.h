//
// Created by awing on 6/29/26.
//

#ifndef GRAFCET_STATIC_H
#define GRAFCET_STATIC_H

#include "Grafcet.h"

bool check(const Grafcet::StateMachine& graph);

void exportToDot(std::ostream& out, const Grafcet::StateMachine& graph);

#endif //GRAFCET_STATIC_H
