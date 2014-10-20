/*
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "shared/Utils.h"
#include "server/PathFinding.h"

#define MAX_STEPS 10000

l_node openList;
l_node closedList;
std::list<sf::Vector2i> path;
node start;
sf::Vector2i end;

float (*PathFinding::m_level)[NB_TILES_WIDTH][NB_TILES_HEIGHT];

void PathFinding::initialize(float (*level)[NB_TILES_WIDTH][NB_TILES_HEIGHT]) {
    m_level = level;
}

sf::Vector2i PathFinding::choosePoint(area a) {

    sf::Vector2i min;
    sf::Vector2i max;
    sf::Vector2i choosenPoint;

    switch (a) {
        case area_center:
        {
            min.x = NB_TILES_WIDTH / 2 - NB_TILES_WIDTH / 4;
            min.y = NB_TILES_HEIGHT / 2 - NB_TILES_HEIGHT / 4;
            max.x = NB_TILES_WIDTH / 2 + NB_TILES_WIDTH / 4;
            max.y = NB_TILES_HEIGHT / 2 + NB_TILES_HEIGHT / 4;
        }
            break;

        case area_north_west:
        {
            min.x = 0;
            max.x = NB_TILES_WIDTH / 2;
            min.y = 0;
            max.y = NB_TILES_HEIGHT / 2;
        }
            break;

        case area_north_east:
        {
            min.x = NB_TILES_WIDTH / 2;
            max.x = NB_TILES_WIDTH - 1;
            min.y = 0;
            max.y = NB_TILES_HEIGHT / 2;
        }
            break;

        case area_south_west:
        {
            min.x = 0;
            max.x = NB_TILES_WIDTH / 2;
            min.y = NB_TILES_HEIGHT / 2;
            max.y = NB_TILES_HEIGHT - 1;
        }
            break;

        case area_south_east:
        {
            min.x = NB_TILES_WIDTH / 2;
            max.x = NB_TILES_WIDTH - 1;
            min.y = NB_TILES_HEIGHT / 2;
            max.y = NB_TILES_HEIGHT - 1;
        }
            break;

        default:
        {

        }
            break;

    }


    for (int i = 0; i < 100; ++i) {
        choosenPoint.x = rand() % (max.x - min.x) + min.x;
        choosenPoint.y = rand() % (max.y - min.y) + min.y;

        if (isWatterAround(choosenPoint.x, choosenPoint.y, 2)) {
            break;
        }
    }

    return choosenPoint;
}

int PathFinding::find(sf::Vector2i s, sf::Vector2i e, std::list<sf::Vector2i> &ch) {
    path.clear();
    openList.clear();
    closedList.clear();

    int nbSteps = 0;

    end.x = e.x;
    end.y = e.y;

    start.parent.first = s.x;
    start.parent.second = s.y;

    std::pair <int, int> current;

    /* déroulement de l'algo A* */

    current.first = s.x;
    current.second = s.y;
    // ajout de courant dans la liste ouverte

    openList[current] = start;
    addToClosedList(current);
    add_neightbours(current);


    while (!((current.first == end.x) && (current.second == end.y))
            &&
            (!openList.empty())
            &&
            (nbSteps < MAX_STEPS)
            ) {

        // on cherche le meilleur noeud de la liste ouverte, on sait qu'elle n'est pas vide donc il existe
        current = best_node(openList);

        // on le passe dans la liste fermee, il ne peut pas déjà y être
        addToClosedList(current);

        add_neightbours(current);
        nbSteps++;
    }

    if ((current.first == end.x) && (current.second == end.y)) {
        retrieve_path();
        ch = path;
    } else {
        return -1;
    }

    return 0;
}

float PathFinding::distance(int x1, int y1, int x2, int y2) {
    return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}

bool PathFinding::isWatterAround(int x, int y, int radius) {

    for (int i = x - radius; i <= x + radius; i++) {
        if ((i < 0) || (i >= NB_TILES_WIDTH))
            continue;

        for (int j = y - radius; j <= y + radius; j++) {
            if ((j < 0) || (j >= NB_TILES_HEIGHT))
                continue;

            if (!WATER((*m_level)[i][j])) {
                return false;
            }
        }
    }

    return true;
}

/*
ajoute toutes les cases adjacentes à n dans la liste ouverte
 */
void PathFinding::add_neightbours(std::pair <int, int>& n) {
    node tmp;

    // on met tous les noeud adjacents dans la liste ouverte (+vérif)
    for (int i = n.first - 1; i <= n.first + 1; i++) {
        if ((i < 0) || (i >= NB_TILES_WIDTH))
            continue;
        for (int j = n.second - 1; j <= n.second + 1; j++) {
            if ((j < 0) || (j >= NB_TILES_HEIGHT))
                continue;
            if ((i == n.first) && (j == n.second)) // case actuelle n
                continue;

            if (!isWatterAround(i, j, 2))
                // obstace, terrain non franchissable
                continue;

            std::pair<int, int> it(i, j);

            if (!isAlreadyIn(it, closedList)) {
                /* le noeud n'est pas déjà présent dans la liste fermée */

                tmp.g_cost = closedList[n].g_cost + distance(i, j, n.first, n.second);
                tmp.h_cost = distance(i, j, end.x, end.y);
                tmp.f_cost = tmp.g_cost + tmp.h_cost;
                tmp.parent = n;

                if (isAlreadyIn(it, openList)) {
                    /* le noeud est déjà présent dans la liste ouverte, il faut comparer les couts */
                    if (tmp.f_cost < openList[it].f_cost) {
                        /* si le nouveau chemin est meilleur, on update */
                        openList[it] = tmp;
                    }

                    /* le noeud courant a un moins bon chemin, on ne change rien */


                } else {
                    /* le noeud n'est pas présent dans la liste ouverte, on l'ajoute */
                    openList[std::pair<int, int>(i, j)] = tmp;
                }
            }
        }
    }
}

bool PathFinding::isAlreadyIn(std::pair<int, int> n, l_node& l) {
    l_node::iterator i = l.find(n);
    if (i == l.end())
        return false;
    else
        return true;
}

/*
    fonction qui renvoie la clé du meilleur noeud de la liste
 */
std::pair<int, int> PathFinding::best_node(l_node& l) {
    float m_coutf = l.begin()->second.f_cost;
    std::pair<int, int> m_noeud = l.begin()->first;

    for (l_node::iterator i = l.begin(); i != l.end(); i++)
        if (i->second.f_cost < m_coutf) {
            m_coutf = i->second.f_cost;
            m_noeud = i->first;
        }

    return m_noeud;
}

/*
    fonction qui passe l'élément p de la liste ouverte dans la fermée
 */
void PathFinding::addToClosedList(std::pair<int, int>& p) {
    node& n = openList[p];
    closedList[p] = n;

    // il faut le supprimer de la liste ouverte, ce n'est plus une solution explorable
    if (openList.erase(p) == 0)
        printf("n'apparait pas dans la liste ouverte, impossible à supprimer");
}

void PathFinding::retrieve_path() {
    // l'arrivée est le dernier élément de la liste fermée.
    node& tmp = closedList[std::pair<int, int>(end.x, end.y)];
    sf::Vector2i n;
    std::pair<int, int> prec;
    n.x = end.x;
    n.y = end.y;
    prec.first = tmp.parent.first;
    prec.second = tmp.parent.second;
    path.push_front(n);

    while (prec != std::pair<int, int>(start.parent.first, start.parent.second)) {
        n.x = prec.first;
        n.y = prec.second;
        path.push_front(n);
        tmp = closedList[tmp.parent];
        prec.first = tmp.parent.first;
        prec.second = tmp.parent.second;
    }
}

