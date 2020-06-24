#include <iostream>
using namespace std;

int separer_chiffre_gauche(int& nombre)
{
  int dix(1);
  int temp(nombre);
  while (temp >= 10) {
    dix  *= 10;
    temp /= 10;
  }
  nombre %= dix;
  return temp;
}

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/

void ajouter_chiffre_droit(int& nombre, int chiffre)
{
  nombre = 10 * nombre + chiffre;
}

void dire_chiffre(int& nombre, int repetitions_chiffre, int chiffre)
{
  ajouter_chiffre_droit(nombre, repetitions_chiffre);
  ajouter_chiffre_droit(nombre, chiffre);
}

int lire_et_dire(int nombre)
{
  int chiffre_gauche, chiffre_prec = 0, nb_rep = 0, res = 0;

  do {
    chiffre_gauche = separer_chiffre_gauche(nombre);
    if (chiffre_prec == 0 || chiffre_gauche == chiffre_prec)
      ++nb_rep;
    else {
      dire_chiffre(res, nb_rep, chiffre_prec);
      nb_rep = 1;
    }
    chiffre_prec = chiffre_gauche;
  } while (nombre > 0);
  dire_chiffre(res, nb_rep, chiffre_prec);
  return res;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void repeter_lire_et_dire(int& nombre, int fois)
{
  while (fois-- > 0) {
    nombre = lire_et_dire(nombre);
  }
}

int main()
{
  int nombre(1);
  int fois(1);
  cin >> nombre >> fois;
  repeter_lire_et_dire(nombre, fois);
  cout << nombre << endl;
  return 0;
}
