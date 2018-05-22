/********************************************************************************** #
#                                                                                   #
#                                                      #   # #### #### ####         #
#     Created by : Fares BENLAKEHAL                    #   # #  # #    #            #
#      			                                       #   # #### ###  #            #
#                                                      #   # #    #    #            #
#                  2017                                 ###  #    #### ####         #
#                                           										#
#                                          										    #
#                                                                                   # 
#***********************************************************************************/


Jeu : Bomberman

Crée par : BENLAKEHAL Fares, SAADI Yani

Licence 2 informatique UPEC

Année Scolaire : 2017/2018

Bomberman est un jeu arcade 2D avec lequel on peut jouer à deux joueurs. Le but du jeu est de tuer son adversaire en posant des bombes.

Conception du jeu :

Transposition de notre carte dans un tableau double pointeur (matrice).
Création du joueur avec des caractéristiques précises (nombre de vies, nombre de bombes, vitesse relative du joueur, explosion associée à ses bombes).
Destruction possible de certains blocs par plusieurs explosion (1 à 9).
La vie diminue d’un joueur lorsqu’il est touché par une bombe.
Un timer est utilisé pour chaque intervalle de temps. 
Un gestion des fichiers est utilisé pour parcourir plusieurs modes de jeux.


Améliorations possibles :

Création d’une structure comportant toutes les informations du jeu placée dans chacune des cases mémoires de notre matrice.
Ajouter des vies.
Jouer jusqu’à 4 joueurs.
Possibilité de jouer en réseau local.
Optimisation du code.
