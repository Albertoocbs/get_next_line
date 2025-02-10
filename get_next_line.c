/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:42:46 by aoutumur          #+#    #+#             */
/*   Updated: 2025/01/16 10:36:06 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* 
Fonction qui va lire le fichier et ajouter le contenu a la stash
Va aussi concatener avec ft_strjoin les donnees du buffer dans la stash
Cherche en appelant ft_strchr si \n se trouve dans le buffer
	Bytes_read controle la boucle et se mets a jour a chaque appel de read
	Utilise variable temp pour stocker temporairement les donnes de stash
*/
static char	*readnfill_until_newline(int fd, char *stash, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!stash)
			stash = ft_strdup("");
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

/*
Cette fonction retourne une ligne complète et met à jour la stash
*/
static char	*extract_line(char *stash)
{
	/*
	La nouvelle fonction extract_line doit :

	1.Gérer les cas particuliers :

   		 Si la stash est vide (NULL) ou ne contient qu’une chaîne vide, retourner immédiatement NULL.
	2.Extraire une ligne complète :

   	 	Inclure le caractère \n si présent.
    	Retourner tout le contenu si aucun \n n’est trouvé.

	3.Mettre à jour la stash :

    	Retirer les données extraites de la ligne et conserver les données restantes.
    	Libérer la mémoire de la stash si elle est vide après extraction.

	4.Ne pas modifier directement les données sources :

    	Travailler uniquement sur des copies pour éviter des modifications non désirées.

	*/
}

/*
Fonction qui appel readnfill_until_newline pour lire et mettre a jour stash
Appele extract_line pour obtenir la ligne complete et retourner la ligne
		Utilise un buffer temp pour lire depuis le fd
		Utilise static char * stash pour stocker les donnees lu entre appels
		Utilise une variable line pour extraire et retourner la ligne complete
Alloue memoire dans le buffer avec taille BUFFER_SIZE + 1 necessaire pour 
stocker la chaine a cahque fois car BUFFER_SIZE n'est pas une valeur fixe
*/
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		free(stash);
		stash = NULL;
		line = NULL;
		return (NULL);
	}
	stash = read_until_newline(fd, stash, buffer);
	if (!stash)
	{
		free(buffer);
		return (NULL);
	}
	line = extract_line(&stash);
	free(buffer);
	return (line);
}
