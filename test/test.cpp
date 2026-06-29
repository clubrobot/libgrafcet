//
// Created by awing on 6/29/26.
//
#include <cassert>
#include <iostream>

#include "Grafcet.h"
#include "Static.h"

using namespace Grafcet;
using namespace std;
int main() {
    auto an1 = ActionNode();
    an1.actionFunction = []{cout << "Action 1" << '\n';};

    auto t1 = Transition();
    t1.condition = []{return true;};
    an1.addChild(&t1);

    auto an2 = ActionNode();
    an2.actionFunction = []{cout << "Action 2" << '\n';};
    t1.addChild(&an2);

    auto an3 = ActionNode();
    an3.actionFunction = []{cout << "Action 3" << '\n';};
    t1.addChild(&an3);

    auto t2 = Transition();
    t2.condition = []{return true;};
    an2.addChild(&t2);
    an3.addChild(&t2);
    t2.synchronize = true;

    auto t3 = Transition();
    t3.condition = []{return true;};
    t2.addChild(&t3);

    auto graph = StateMachine(&an1);

    assert(check(graph));
    exportToDot(std::cout, graph);
}