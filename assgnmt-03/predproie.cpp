#include <iostream>
#include <iomanip> // pour setprecision()
using namespace std;

int main()
{
  // Réduire le format d'affichage
  cout << setprecision(4);

  // Paramètres
  double taux_croissance_lapins(0.3);
  double taux_attaque(0.01);
  double taux_croissance_renards(0.008);
  double taux_mortalite(0.1);
  int duree(50);

  double renards_i(0.0);
  double lapins_i(0.0);

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/

  // ===== PARTIE 1 =====
  // Saisie des populations initiales
  do {
    cout << "Combien de renards au départ (>= 2) ? ";
    cin >> renards_i;
  } while (renards_i < 2);

  do {
    cout << "Combien de lapins au départ  (>= 5) ? ";
    cin >> lapins_i;
  } while (lapins_i < 5);

  // ===== PARTIE 2 =====
  // Première simulation
  cout <<  endl << "***** Le taux d'attaque vaut "<< taux_attaque * 100 << "%" <<  endl;
  double nb_lapins = lapins_i, nb_renards = renards_i, tmp;
  int mois = 0;
  while (mois++ < duree) {
    tmp = nb_lapins;
    nb_lapins *= 1.0 + taux_croissance_lapins - taux_attaque * nb_renards;
    nb_renards *= 1.0 + taux_attaque * tmp * taux_croissance_renards - taux_mortalite;
    if (nb_lapins < 0)
      nb_lapins = 0;
    if (nb_renards < 0)
      nb_renards = 0;
    cout << "Après " << mois << " mois, il y a " << nb_lapins << " lapins et " << nb_renards << " renards" << endl;
  }

  // ===== PARTIE 3 =====
  // Variation du taux d'attaque
  cout << endl;

  double ta_deb_in = 0, ta_fin_in = 0;
  double ta_deb, ta_fin;
  do {
    cout << "taux d'attaque au départ en % (entre 0.5 et 6) ? ";
    cin >> ta_deb_in;
  } while (!(ta_deb_in >= 0.5 && ta_deb_in <= 6));
  ta_deb = (double)ta_deb_in / 100;
  do {
    cout << "taux d'attaque à la fin  en % (entre " << ta_deb_in << " et 6) ? ";
    cin >> ta_fin_in;
  } while (!(ta_fin_in >= ta_deb_in && ta_fin_in <= 6));
  ta_fin = (double)ta_fin_in / 100;

  bool voieExtinction[2], popRemontee[2], disparu[2];
  for (taux_attaque = ta_deb; taux_attaque <= ta_fin; taux_attaque += 0.01) {
    voieExtinction[0] = voieExtinction[1] = popRemontee[0] = popRemontee[1] = disparu[0] = disparu[1] = false;
    cout <<  endl << "***** Le taux d'attaque vaut "<< taux_attaque * 100 << "%" <<  endl;
    nb_lapins = lapins_i, nb_renards = renards_i;
    mois = 0;
    while (mois++ < duree && (nb_lapins > 0 || nb_renards > 0)) {
      tmp = nb_lapins;
      nb_lapins *= 1.0 + taux_croissance_lapins - taux_attaque * nb_renards;
      nb_renards *= 1.0 + taux_attaque * tmp * taux_croissance_renards - taux_mortalite;
      if (nb_lapins < 5)
        voieExtinction[0] = true;
      if (nb_renards < 5)
        voieExtinction[1] = true;
      if (voieExtinction[0] && nb_lapins >= 5)
        popRemontee[0] = true;
      if (voieExtinction[1] && nb_renards >= 5)
        popRemontee[1] = true;
      if (nb_lapins < 2) {
        nb_lapins = 0;
        disparu[0] = true;
      }
      if (nb_renards < 2) {
        nb_renards = 0;
        disparu[1] = true;
      }
    }
    cout << "Après " << --mois << " mois, il y a " << max(nb_lapins, 0.) << " lapins et " << max(nb_renards, 0.) << " renards" << endl;
    if (voieExtinction[1]) {
      cout << "Les renards ont été en voie d'extinction" << endl;
      if (disparu[1])
        cout << "et les renards ont disparu :-(" << endl;
      else if (popRemontee[1])
        cout << "mais la population est remontée ! Ouf !" << endl;
    }
    if (voieExtinction[0]) {
      cout << "Les lapins ont été en voie d'extinction" << endl;
      if (disparu[0])
        cout << "et les lapins ont disparu :-(" << endl;
      else if (popRemontee[0])
        cout << "mais la population est remontée ! Ouf !" << endl;
    }
    if (!(voieExtinction[0] || voieExtinction[1]))
      cout << "Les lapins et les renards ont des populations stables." << endl;
  }
  /*******************************************
   * Ne rien modifier après cette ligne.
   *******************************************/

  return 0;
}
