#include <iostream>
#include <ctime>

// pour les nombres aléatoires
#include <random>
#include <cstring> // strlen

using namespace std;

// ======================================================================
// Couleur au hasard
std::uniform_int_distribution<int> distribution;
std::default_random_engine generateur(time(NULL)); /* NOT using std::random_device since not
                                                    * all compilers seems to support it :-( */

char tirer_couleur()
{
  static const char* const couleurs = ".RGBCYM";
  static const int nb = strlen(couleurs) - 1;

  return couleurs[distribution(generateur,
                               std::uniform_int_distribution<int>::param_type {0, nb})];
}

// ======================================================================
char poser_question()
{
  char lu(' ');
  cout << "Entrez une couleur : ";
  cin >> lu;
  return lu;
}

// ---- prototype -------------------------------------------------------
bool couleur_valide(char c);

// ======================================================================
char lire_couleur()
{
  char lu(poser_question());
  while (not couleur_valide(lu)) {
    cout << "'" << lu << "' n'est pas une couleur valide." << endl;
    cout << "Les couleurs possibles sont : ., R, G, B, C, Y ou M." << endl;
    lu = poser_question();
  }
  return lu;
}

// ======================================================================
void afficher_couleurs(char c1, char c2, char c3, char c4)
{
  cout << ' ' << c1 << ' ' << c2 << ' ' << c3 << ' ' << c4;
}

// ======================================================================
void afficher(int nb, char c)
{
  while (nb-- > 0) {
    cout << c;
  }
}

// ---- prototype -------------------------------------------------------
void afficher_reponses(char c1, char c2, char c3, char c4,
                       char r1, char r2, char r3, char r4);

// ======================================================================
void afficher_coup(char c1, char c2, char c3, char c4,
                   char r1, char r2, char r3, char r4)
{
  afficher_couleurs(c1, c2, c3, c4);
  cout << " : ";
  afficher_reponses(c1, c2, c3, c4,
                    r1, r2, r3, r4);
  cout << endl;
}

// ======================================================================
void message_gagne(int nb_coups)
{
  cout << "Bravo ! Vous avez trouvé en " << nb_coups << " coups." << endl;
}

// ======================================================================
void message_perdu(char c1, char c2, char c3, char c4)
{
  cout << "Perdu :-(" << endl;
  cout << "La bonne combinaison était : ";
  afficher_couleurs(c1, c2, c3, c4);
  cout << endl;
}

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/

// ======================================================================
bool couleur_valide(char c)
{
  return c == '.' || c == 'R' || c == 'G' || c == 'B' || c == 'C' || c == 'Y' || c == 'M';
}

// ======================================================================
bool verifier(char c1, char &c2, int &score)
{
  bool res = c1 == c2;

  if (res) {
    ++score;
    c2 = 'x';
  }
  return res;
}

// ======================================================================
void apparier(char c1, char &r2, char &r3, char &r4, int &score)
{
  verifier(c1, r2, score) || verifier(c1, r3, score) || verifier(c1, r4, score);
}

// ======================================================================
void afficher_reponses(char c1, char c2, char c3, char c4,
                       char r1, char r2, char r3, char r4)
{
  bool a_apparier[4];
  int correct = 0, mal_place = 0;

  a_apparier[0] = !verifier(c1, r1, correct);
  a_apparier[1] = !verifier(c2, r2, correct);
  a_apparier[2] = !verifier(c3, r3, correct);
  a_apparier[3] = !verifier(c4, r4, correct);
  if (a_apparier[0]) apparier(c1, r2, r3, r4, mal_place);
  if (a_apparier[1]) apparier(c2, r1, r3, r4, mal_place);
  if (a_apparier[2]) apparier(c3, r1, r2, r4, mal_place);
  if (a_apparier[3]) apparier(c4, r1, r2, r3, mal_place);
  afficher(correct, '#');
  afficher(mal_place, '+');
  afficher(4 - correct - mal_place, '-');
}

// ======================================================================
bool gagne(char c1, char c2, char c3, char c4,
           char r1, char r2, char r3, char r4)
{
  return c1 == r1 && c2 == r2 && c3 == r3 && c4 == r4;
}

// ======================================================================
void jouer(int max_coups = 8)
{
  int r1, r2, r3, r4;
  int nb_coups = 0;
  bool a_gagne = false;

  r1 = tirer_couleur();
  r2 = tirer_couleur();
  r3 = tirer_couleur();
  r4 = tirer_couleur();
  do {
    int c1, c2, c3, c4;
    c1 = lire_couleur();
    c2 = lire_couleur();
    c3 = lire_couleur();
    c4 = lire_couleur();
    afficher_coup(c1, c2, c3, c4, r1, r2, r3, r4);
    ++nb_coups;
    a_gagne = gagne(c1, c2, c3, c4, r1, r2, r3, r4);
  } while (!a_gagne && nb_coups < max_coups);
  if (a_gagne)
    message_gagne(nb_coups);
  else
    message_perdu(r1, r2, r3, r4);
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  jouer();
  return 0;
}
