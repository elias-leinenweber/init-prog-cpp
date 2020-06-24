#include <iostream>
#include <vector>
using namespace std;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/
typedef vector<vector<int>> Carte;

struct Position {
  size_t i;
  size_t j;
};

bool    binaire(Carte const&);
void    affiche(Carte const&);
bool    verifie_et_modifie(Carte&);
double  longueur_cloture(Carte const&, double);
void    ajoute_unique(vector<int>&, int);
bool    convexite_lignes(Carte&, vector<int> const&);
bool    convexite_lignes(Carte&);
void    marque_composantes(Carte&);

bool
binaire(Carte const& carte)
{
  for (vector<int> ligne : carte)
    for (int n : ligne)
      if (n != 0 && n != 1)
        return false;
  return true;
}

void
affiche(Carte const& carte)
{
  for (vector<int> ligne : carte) {
    for (int n : ligne)
      cout << n;
    cout << endl;
  }
  cout << "----" << endl;
}

bool
verifie_et_modifie(Carte& carte)
{
  bool res = false;

  if (!binaire(carte))
    cout << "Votre carte du terrain ne contient pas que des 0 et des 1." << endl;
  else if (convexite_lignes(carte)) {
    for (vector<int>& ligne : carte) {
      int debut, i, fin;
      for (i = 0; i < ligne.size(); ++i)
        if (ligne[i] == 1)
          break;
      debut = i;
      for (i = ligne.size() - 1; i >= 0; --i)
        if (ligne[i] == 1)
          break;
      fin = i;
      for (i = debut; i < fin; ++i)
        ligne[i] = 1;
    }
    res = true;
  }
  return res;
}

double
longueur_cloture(Carte const& carte, double echelle = 2.5)
{
  size_t i, j;
  double longueur = 0;

  for (i = 0; i < carte.size(); ++i)
    for (j = 0; j < carte[i].size(); ++j) {
      if (carte[i][j] == 1) {
        if (i == 0 || carte[i - 1][j] != 1)
          longueur += echelle;
        if (i == carte.size() - 1 || carte[i + 1][j] != 1)
          longueur += echelle;
        if (j == carte[i].size() - 1 || carte[i][j + 1] != 1)
          longueur += echelle;
        if (j == 0 || carte[i][j - 1] != 1)
          longueur += echelle;
      }
    }
  return longueur;
}

void
ajoute_unique(vector<int>& ensemble, int valeur)
{
  for (int elem : ensemble)
    if (elem == valeur)
      return;
  ensemble.push_back(valeur);
}

bool
convexite_lignes(Carte& carte, vector<int> const& labels_bords)
{
  int i, j;

  for (i = 0; i < carte.size(); ++i) {
    int debut, fin;
    for (j = 0; j < carte[i].size(); ++j)
      if (carte[i][j] == 1)
        break;
    debut = j;
    for (j = carte[i].size() - 1; j >= 0; --j)
      if (carte[i][j] == 1)
        break;
    fin = j;
    for (j = debut; j < fin; ++j)
      for (int label : labels_bords)
        if (carte[i][j] == label) {
          cout << "Votre carte du terrain n'est pas convexe par lignes :" << endl;
          cout << "bord extérieur entrant trouvé en position [" << i << "][" << j << "]" << endl;
          return false;
        }
  }
  return true;
}

bool
convexite_lignes(Carte& carte)
{
  vector<int> labels_bords;
  size_t i, j;

  marque_composantes(carte);
  for (i = 0, j = 0; j < carte[i].size() - 1; ++j)
    if (carte[i][j] != 1)
      ajoute_unique(labels_bords, carte[i][j]);
  for (i = 0, j = carte[i].size() - 1; i < carte.size(); ++i)
    if (carte[i][j] != 1)
      ajoute_unique(labels_bords, carte[i][j]);
  for (i = carte.size() - 1, j = 0; j < carte[i].size(); ++j)
    if (carte[i][j] != 1)
      ajoute_unique(labels_bords, carte[i][j]);
  for (i = 0, j = 0; i < carte.size(); ++i)
    if (carte[i][j] != 1)
      ajoute_unique(labels_bords, carte[i][j]);
  return convexite_lignes(carte, labels_bords);
}

void
marque_composantes(Carte& carte)
{
  vector<Position> points;
  Position pos;
  int composante = 1, i, j;

  for (i = 0; i < carte.size(); ++i)
    for (j = 0; j < carte[i].size(); ++j) {
      if (carte[i][j] == 0) {
        ++composante;
        pos.i = i;
        pos.j = j;
        points.push_back(pos);
        while(!points.empty()) {
          pos = points.back();
          points.pop_back();
          if (carte[pos.i][pos.j] == 0) {
            carte[pos.i][pos.j] = composante;
            if (pos.i > 0 && carte[pos.i - 1][pos.j] == 0)
              points.push_back({ pos.i - 1, pos.j });
            if (pos.i < carte.size() - 1 && carte[pos.i + 1][pos.j] == 0)
              points.push_back({ pos.i + 1, pos.j });
            if (pos.j < carte[pos.i].size() - 1 && carte[pos.i][pos.j + 1] == 0)
              points.push_back({ pos.i, pos.j + 1 });
            if (pos.j > 0 && carte[pos.i][pos.j - 1] == 0)
              points.push_back({ pos.i, pos.j - 1 });
          }
        }
      }
    }
}
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Carte carte = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };

  cout << "Carte au départ :" << endl;
  affiche(carte);
  if (verifie_et_modifie(carte)) {
    cout << "Carte après modification :" << endl;
    affiche(carte);
    cout << "Il vous faut " << longueur_cloture(carte)
         << " mètres de clôture pour votre terrain."
         << endl;
  }

  return 0;
}
