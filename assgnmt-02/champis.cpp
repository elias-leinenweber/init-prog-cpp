#include <iostream>
using namespace std;

int
main()
{
	int ans, champi;

	cout << "Pensez à un champignon : amanite tue-mouches, pied bleu, girolle," << endl
	     << "cèpe de Bordeaux, coprin chevelu ou agaric jaunissant." << endl << endl;

	cout << "Est-ce que votre champignon a un chapeau convexe (1 : oui, 0 : non) ? ";
	cin >> ans;
	if (ans) {
		cout << "Est-ce que votre champignon vit en forêt (1 : oui, 0 : non) ? ";
		cin >> ans;
		if (ans) {
			cout << "Est-ce que votre champignon a un anneau (1 : oui, 0 : non) ? ";
			cin >> ans;
			champi = ans ? 1 : 5;
		} else
			champi = 0;
	} else {
		cout << "Est-ce que votre champignon a un anneau (1 : oui, 0 : non) ? ";
		cin >> ans;
		if (ans)
			champi = 3;
		else {
			cout << "Est-ce que votre champignon a des lamelles (1 : oui, 0 : non) ? ";
			cin >> ans;
			champi = ans ? 4 : 2;
		}
	}

	cout << "==> Le champignon auquel vous pensez est ";
	switch (champi) {
	case 0:
		cout << "l'agaric jaunissant";
		break;
	case 1:
		cout << "l'amanite tue-mouches";
		break;
	case 2:
		cout << "le cèpe de Bordeaux";
		break;
	case 3:
		cout << "le coprin chevelu";
		break;
	case 4:
		cout << "la girolle";
		break;
	case 5:
		cout << "le pied bleu";
		break;
	}
	cout << "." << endl;
}
