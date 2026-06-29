//
// Created by awing on 09/05/2026.
//
/**
 * @file Node.h
 * @ingroup grafcet
 * @brief Représentation d'un noeud du grafcet
 */
#ifndef TEAM2026_NODE_H
#define TEAM2026_NODE_H

#include <vector>
#include <memory_resource>
#include <string>

namespace Grafcet {
    class StateMachine;

    /**
     * @class Node
     * @brief Représente un noeud dans le graphcet
     * Un noeud peut être un noeud d'action ou un noeud de transition. Il contient
     * une liste de parent & d'enfant afin de pouvoir parcourir le graphe,
     */
    class Node {
    public:
        /**
         *
         * @param parent Une liste de parents pour le noeud
         * @param child Une liste d'enfants pour le noeud
         */
        explicit Node(const std::pmr::vector<Node*> &parent = {}, const std::pmr::vector<Node*> &child = {}) : parent(parent), children(child) {}
        virtual ~Node() = default;
        /// @brief vérifie si le noeud est activé
        virtual bool enabled() = 0;
        /// @brief action à réaliser lorsque le noeud est actif
        virtual void action() = 0;

        /**
         * @brief attache un enfant au noeud
         * @param child
         */
        constexpr void addChild(Node *child) {
            this->children.push_back(child);
            child->parent.push_back(this);
        }

        /**
         * @brief retourne la liste des enfants
         * @return la liste des enfants
         */
        [[nodiscard]] std::pmr::vector<Node*> getChildren() const { return children; }

        std::pmr::string name = "Node";
        /// true si le noeud est une transition, false sinon
        bool isTransition = false;
        /// true si le noeud est synchronisant
        bool synchronize = false;
        /// true si le noeud est actif
        bool active = false;
    protected:
        /// Liste des noeuds parents
        std::pmr::vector<Node*> parent = {};
        /// Liste des noeuds enfants
        std::pmr::vector<Node*> children = {};

        friend StateMachine;
    };
}
#endif //TEAM2026_NODE_H
