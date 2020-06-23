#include <iostream>
using namespace std;

int main()
{
  cout << "Donnez l'heure de début de la location (un entier) : ";
  int debut;
  cin >> debut;

  cout << "Donnez l'heure de fin de la location (un entier) : ";
  int fin;
  cin >> fin;

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
  if (!(debut >= 0 && debut <= 24 && fin >= 0 && fin <= 24))
    cout << "Les heures doivent être comprises entre 0 et 24 !" << endl;
  else if (debut == fin)
    cout << "Bizarre, vous n'avez pas loué votre vélo bien longtemps !" << endl;
  else if (debut > fin)
    cout << "Bizarre, le début de la location est après la fin ..." << endl;
  else {
    cout << "Vous avez loué votre vélo pendant" << endl;

    int heures1 = 0, heures2 = 0;
    while (debut < fin) {
      if (debut < 7 || debut >= 17)
        ++heures1;
      else
        ++heures2;
      ++debut;
    }

    if (heures1 > 0)
      cout << heures1 << " heure(s) au tarif horaire de " << 1 << " franc(s)" << endl;
    if (heures2 > 0)
      cout << heures2 << " heure(s) au tarif horaire de " << 2 << " franc(s)" << endl;

    cout << "Le montant total à payer est de " << heures1 + 2 * heures2 << " franc(s)." << endl;
  }
  /*******************************************
   * Ne rien modifier après cette ligne.
   *******************************************/

  return 0;
}
