/** @file activitat.hh
    @brief Especificacio de la classe Activitat
 */

#ifndef ACTIVITAT_HH
#define ACTIVITAT_HH

#include "utils.PRO2"//
#include <string>//
#include <map>//


/** @class Activitat
    @brief Una activitat consta d'un text descriptiu. Pot tenir un conjunt d'etiquetes associat que permet classicar-la.
    Les etiquetes s'escriuen en el format de #etiqueta, on "etiqueta" pot ser qualsevol paraula.
 */
class Activitat{

private:
    /** @brief Titol de l'activitat */
    string descripcio;
    /** @brief Conjunt d'etiquetes. Inv: No hi ha dues etiquetes repetides i estan ordenades per ordre alfabetic.*/
    map<string, bool> etiquetes;
      
    /** @brief Evalua una expressio booleana d'etiquetes, indicant si el p.i. compleix la condicio o no.
    \pre all es una expressio booleana d'etiquetes;
         all.begin()<= i < all.end();
         i = I;
    \post i ha avançat fins a l'operador de l'expressio binària o el final d'aquesta;
         el boolea correcta indica si el P.I. compleix la condicio expressada entre all[I]..all[i-1]; */
    void solve(const string& all, int& i, bool& correcta, bool eval);

    /** @brief Busca si hi ha una determinada etiqueta en una activitat.
    \pre Cert.
    \post Retorna true o false en funció de si l'etiqueta buscada està a la activitat o no.*/
    bool te_etiqueta(const string& etiqueta) const;

    /** @brief Retorna el número d'etiquetes del p.i.
    \pre Cert.
    \post Ha retornat el número d'etiquetes del p.i.*/
    int num_etiquetes() const;

public:
    // Creadores

    /** @brief Creadora per defecte, crea una activitat buida.
    \pre Cert.
    \post S'ha creat una activitat sense descripcio ni etiquetes.*/
    Activitat();

    /** @brief Destructora per defecte. */
    ~Activitat();

    /** @brief Operador d'assignació.
    \pre Cert.
    \post Assigna el valor de 'original' a l'activitat sobre la ques'utilitzi l'operador '='*/
    Activitat& operator=(const Activitat& original);

    /** @brief Indica si el P.I. compleix l'expressio booleana d'etiquetes.
    \pre Cert.
    \post Retorna true si el P.I. compleix l'expressio i false en cas contrari.*/
    bool compleix_expressio(const string& formula);

    /** @brief Retorna la descripció de l'activitat.
    \pre: Cert.
    \post: S'ha retornat la descripció del parametre implicit.*/
    string consultar_titol() const;

   // Modificadores

    /** @brief Actualitza la descripció de l'activitat amb la que s'ha enviat com a parametre.
    \pre Cert.
    \post S'ha modificat la descripcio del parametre implicit.*/
    void modificar_titol(const string& titol);

    /** @brief Afegeix una etiqueta a l'activitat.
    \pre Cert.
    \post S'ha afegit l'etiqueta desitjada al parametre implicit, si ja hi era retorna false.*/
    bool afegir_etiqueta(const string& etiq);

    /** @brief Esborra una etiqueta de l'activitat.
    \pre Cert.
    \post Si l'etiqueta pertanyia al parametre implicit, s'ha esborrat i retorna true.
    Si no, retorna false.*/
    bool esborrar_etiqueta(const string& etiq);

    /** @brief Esborra totes les etiquetes d'una activitat.
    \pre Cert.
    \post Si el parametre implicit tenia conjunt d'etiquetes, s'han esborrat i la funció retorna true. En cas contrari, retorna false.*/
    void esborrar_totes_etiquetes();

    //Escriptura
    /** @brief Escriu la descripció de l'activitat pel canal estandard de sortida.
    \pre Cert.
    \post S'ha escrit la descripcio del parametre implicit.*/
    void escriu_titol();

    /** @brief Escriu les etiquetes de l'activitat pel canal estandard de sortida.
    \pre Cert.
    \post S'han escrit les etiquetes del parametre implicit per ordre alfabetic.*/
    void escriu_etiquetes();
};
#endif
