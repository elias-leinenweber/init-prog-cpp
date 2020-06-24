#include <iostream>

int	demander_annee(void);
void	affiche_date(int, int);
int	date_Paques(int);

int
main()
{
	int annee;

	annee = demander_annee();
	affiche_date(annee, date_Paques(annee));
	return 0;
}

int
demander_annee(void)
{
	int annee = 0;

	do {
		std::cout << "Entrez une annee (1583-4000) : ";
		std::cin >> annee;
	} while (!(annee >= 1583 && annee <= 4000));
	return annee;
}

void
affiche_date(int annee, int nb_jours)
{
	std::cout << "Date de Paques en " << annee << " : ";
	if (nb_jours <= 31)
		std::cout << nb_jours << " mars";
	else
		std::cout << nb_jours - 31 << " avril";
	std::cout << std::endl;
}

int
date_Paques(int annee)
{
	int siecle, p, q, M, N, d, e, jour;

	siecle = annee / 100;
	p = (13 + 8 * siecle) / 25;
	q = siecle / 4;
	M = (15 - p + siecle - q) % 30;
	N = (4 + siecle - q) % 7;
	d = (M + 19 * (annee % 19)) % 30;
	e = (2 * (annee % 4) + 4 * (annee % 7) + 6 * d + N) % 7;
	jour = e + d + 22;
	if (e == 6 && (d == 29 || (d == 28 && (11 * (M + 1)) % 30 < 19)))
		jour -= 7;
	return jour;
}
