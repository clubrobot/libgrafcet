//
// Created by awing on 6/29/26.
//
#include "Static.h"

#include <map>
#include <ostream>

bool check(const Grafcet::StateMachine& graph) {
    std::pmr::map<const Grafcet::Node*, bool> visited;
    std::pmr::vector<const Grafcet::Node*> stack;
    const Grafcet::Node* startingNode = graph.getStartingNode();
    if (startingNode == nullptr) {
        return false;
    }
    stack.push_back(startingNode);
    do {
        const Grafcet::Node* currentNode = stack.back();
        stack.pop_back();
        if (!visited.contains(currentNode)) {
            visited[currentNode] = true;
            const auto* casted = dynamic_cast<const Grafcet::ActionNode*>(currentNode);
            if (currentNode->isTransition) {
                //vérifie que la transition existe
                if (!dynamic_cast<const Grafcet::Transition*>(currentNode)->condition()) { return false; }
            } else {
                //vérifie qu'une action existe
                if (!dynamic_cast<const Grafcet::ActionNode*>(currentNode)->actionFunction) { return false; }
            }
            for (const auto* child : currentNode->getChildren()) {
                stack.push_back(child);
                // Vérifie que deux noeuds d'action ne se suivent pas
                if (!currentNode->isTransition && !child->isTransition) {
                    return false;
                }
            }
        }
    } while (!stack.empty());
    return true;
}

void exportToDot(std::ostream &out, const Grafcet::StateMachine &graph) {
    out << "digraph {" << '\n';
    std::pmr::map<const Grafcet::Node*, bool> visited;
    std::pmr::vector<const Grafcet::Node*> stack;
    const Grafcet::Node* startingNode = graph.getStartingNode();
    unsigned int i = 0;
    if (startingNode == nullptr) { goto exit; }
    stack.push_back(startingNode);
    do {
        const Grafcet::Node* currentNode = stack.back();
        stack.pop_back();
        if (!visited.contains(currentNode)) {
            visited[currentNode] = true;
            std::pmr::string name = currentNode->name;
            if (name == "Node") {
                name = (currentNode->isTransition ? "transition_" : "action_") + std::to_string(i);
            }

            if (currentNode->isTransition) {
                out << "\t" << name << "[shape=diamond;label=" << name;
            } else {
                out << "\t" << name << "[shape=box;label=" << name;
            }
            if (currentNode->synchronize) {
                out << ";style=\"bold,filled\";fillcolor=lightblue;color=blue";
            }
            out << "]" << '\n';
            for (auto* child : currentNode->getChildren()) {
                i++;
                stack.push_back(child);
                std::pmr::string childName = child->name;
                if (childName == "Node") {
                    childName = (child->isTransition ? "transition_" : "action_") + std::to_string(i);
                    child->name = childName;
                }
                out << "\t" << name << "->" << childName << '\n';
            }
        }
    } while (!stack.empty());
exit:
    out << "}" << '\n';
}
