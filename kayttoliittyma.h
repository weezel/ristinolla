#ifndef __KAYTTOLIITTYMA_H_
#define __KAYTTOLIITTYMA_H_

#define	IKK_LEVEYS	60
#define	IKK_KORKEUS	30
#define TYHJA_MERKKI	32 /* Space */

struct point {
	int	x;
	int	y;
};

void	alusta_varit(void);
int	laillinen_siirto(const int, const int);
void	piirra_kentta(void);

#endif
