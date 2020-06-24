#include <iostream>
#include <vector>

int				somme_consecutifs_max(std::vector<int>);
std::vector<std::size_t>	lignes_max(std::vector< std::vector<int> >);
std::vector< std::vector<int> >	tranches_max(std::vector< std::vector<int> >);

int
main()
{
	std::vector< std::vector <int> > tab = {
		{ 2, 1, 0, 2, 0, 3, 2 },
		{ 0, 1, 0, 7, 0 },
		{ 1, 0, 1, 3, 2, 0, 3, 0, 4 },
		{ 5, 0, 5 },
		{ 1, 1, 1, 1, 1, 1, 1 }
	};
	
	tab = tranches_max(tab);
	for (std::vector<int> ligne : tab) {
		for (int n : ligne)
			std::cout << n << " ";
		std::cout << std::endl;
	}
	return 0;
}

int
somme_consecutifs_max(std::vector<int> tab)
{
	int max = 0, somme = 0;

	for (int n : tab)
		if (n != 0)
			somme += n;
		else {
			if (somme > max)
				max = somme;
			somme = 0;
		}
	return std::max(max, somme);
}

std::vector<std::size_t>
lignes_max(std::vector< std::vector<int> > tab)
{
	std::vector<std::size_t> lignes;
	std::size_t i;
	int max = 0, somme;

	for (i = 0; i < tab.size(); ++i) {
		somme = somme_consecutifs_max(tab[i]);
		if (somme >= max) {
			if (somme > max) {
				max = somme;
				lignes.clear();
			}
			lignes.push_back(i);
		}
	}
	return lignes;
}

std::vector< std::vector<int> >
tranches_max(std::vector< std::vector<int> > tab)
{
	std::vector< std::vector<int> > tranches;
	std::vector<std::size_t> lignes;

	lignes = lignes_max(tab);
	for (std::size_t ligne : lignes)
		tranches.push_back(tab[ligne]);	
	return tranches;
}
