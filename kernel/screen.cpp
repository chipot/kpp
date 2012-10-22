#include "Screen.h"

screen::tty tty;

namespace screen {

/* 
 * 'scrollup' scrolle l'ecran (la console mappee en ram) vers le haut
 * de n lignes (de 0 a 25).
 */
void tty::scrollup(unsigned int n)
{
	unsigned char *video, *tmp;

	for (video = (unsigned char *) RAMSCREEN;
	     video < (unsigned char *) SCREENLIM; video += 2) {
		tmp = (unsigned char *) (video + n * 160);

		if (tmp < (unsigned char *) SCREENLIM) {
			*video = *tmp;
			*(video + 1) = *(tmp + 1);
		} else {
			*video = 0;
			*(video + 1) = 0x07;
		}
	}

	this->y -= n;
	if (this->y < 0)
		this->y = 0;
}

void tty::putcar(uchar c)
{
	unsigned char *video;
	int i;

	if (c == 10) {		/* CR-NL */
		this->x = 0;
		this->y++;
	} else if (c == 9) {	/* TAB */
		this->x = this->x + 8 - (this->x % 8);
	} else if (c == 13) {	/* CR */
		this->x = 0;
	} else {		/* autres caracteres */
		video = (unsigned char *) (RAMSCREEN + 2 * this->x + 160 * this->y);
		*video = c;
		*(video + 1) = this->_attr;

		this->x++;
		if (this->x > 79) {
			this->x = 0;
			this->y++;
		}
	}

	if (this->y > 24)
		scrollup(this->y - 24);
}

/*
 * 'print' affiche a l'ecran, a la position courante du curseur, une chaine
 * de caracteres terminee par \0.
 */

void tty::puts(char const *string)
{
	while (*string != 0) /* tant que le caractere est different de 0x0 */
    {
		putcar(*string);
		string++;
	}
}

}
