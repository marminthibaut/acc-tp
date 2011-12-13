/*
 * nb_vertices.cpp
 *
 *  Created on: 13 déc. 2011
 *      Author: clement
 */

#include <stdio.h>

int
maino()
{
  int nbr_arcs;
  for (int nbr_vertices = 100; nbr_vertices <= 1000; nbr_vertices += 100)
    {
      printf("=================================\n");

      printf("nbr_vertices : %d \n", nbr_vertices);
      for (int percent = 10; percent <= 100; percent += 10)
        {
          nbr_arcs = ((nbr_vertices * (nbr_vertices - 1)) / 2
          ) * (float(percent)/100.);

          printf("%d : %d \n", percent, nbr_arcs);
        }
    }

  return 0;
}

