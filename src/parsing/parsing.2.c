/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:34:21 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/03 11:53:29 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Retourne la priorité de chaque opérateur
int get_operator_priority(int operator_type)
{
    if (operator_type == PIPE)
        return 1;  // Priorité la plus basse pour |
    else if (operator_type == AND || operator_type == OR)
        return 2;  // Priorité plus haute pour && et ||
    return 0;  // Aucun opérateur
}

// Fonction pour analyser une commande (CMD)
void parse_cmd(t_node *cmd, t_token **cur)
{
    t_node *node;

    // Analyser les tokens jusqu'à ce qu'on rencontre un opérateur
    while (*cur && !ft_isoperator((*cur)->type))  // Tant qu'on ne rencontre pas un opérateur
    {
        if ((*cur)->type == WORD)  // Si c'est un mot (argument ou commande)
        {
            node = new_node(WORD, (*cur)->value);  // Créer un nœud pour ce mot
            *cur = (*cur)->next;  // Passer au token suivant
            lst_add_child(cmd, node);  // Ajouter le mot comme enfant de la commande
        }
        else if (ft_isredir((*cur)->value))  // Si c'est une redirection (>, >>, <)
        {
            node = new_node(RDR, (*cur)->value);  // Créer un nœud pour la redirection
            *cur = (*cur)->next;  // Passer au token suivant
            lst_add_child(cmd, node);  // Ajouter la redirection comme enfant de la commande
        }
        else
        {
            *cur = (*cur)->next;  // Passer au token suivant si ce n'est ni un mot ni une redirection
        }
    }
}

// Fonction pour analyser une commande sans opérateur
t_node *parse_left(t_token **cur)
{
    t_node *node;

    if (!cur || !*cur)
        return NULL;

    node = new_node(CMD, NULL);  // Créer un nœud de type "CMD" (commande)
    if (!node)
        return NULL;

    parse_cmd(node, cur);  // Appel à parse_cmd pour analyser la commande
    return node;
}

// Fonction pour analyser un opérateur et créer un nœud correspondant
static t_node *parse_operator(t_token **cur)
{
    t_node *node;

    if (*cur && ft_isoperator((*cur)->type))
    {
        node = new_node(OPE, (*cur)->value); // Créer un nœud pour l'opérateur
        *cur = (*cur)->next; // Passer au token suivant
        return node;
    }
    return NULL;
}

// Fonction pour analyser un pipeline avec gestion des priorités des opérateurs
t_node *parse_pipeline(t_token **cur, int min_priority)
{
    t_node *left;
    t_node *operator;
    t_node *right;

    // Analyse de la commande à gauche (première commande)
    left = parse_left(cur);
    if (!left)
        return NULL;

    // Analyse des opérateurs en tenant compte de leur priorité
    operator = parse_operator(cur);
    while (operator && get_operator_priority(operator->type) >= min_priority)
    {
        // Analyse de la commande à droite de l'opérateur
        right = parse_left(cur);
        if (!right)
            return NULL;

        // Créer une relation entre l'opérateur et les deux commandes
        lst_add_child(operator, left);  // Ajouter la commande gauche à l'opérateur
        lst_add_child(operator, right); // Ajouter la commande droite à l'opérateur

        // Mettre à jour left pour l'itération suivante
        left = operator;

        // Passer à l'opérateur suivant
        operator = parse_operator(cur);
    }

    return left;  // Retourner le nœud de gauche (qui devient un opérateur ou une commande)
}

// Fonction pour analyser toute l'expression avec gestion des priorités des opérateurs
t_node *parse(t_token *cur)
{
    t_node *pipeline;

    if (!cur)
        return NULL;

    // Analyser avec la priorité minimale (0 ici)
    pipeline = parse_pipeline(&cur, 0); 

    // Retourner l'AST généré
    return pipeline;
}
