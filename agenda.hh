/** @file agenda.hh
    @brief Especificacio de la classe Agenda
*/

#ifndef AGENDA_HH
#define AGENDA_HH

#include "activitat.hh"
#include "rellotge.hh"
#include <vector> //s'ha de treure per el doxygen

/** @class Agenda
    @brief Representa una agenda, que conté activitats associades a un moment en el temps i un rellotge intern.
    Sobre aquesta agenda es poden realitzar operacions d'inserció d'activitats, de consulta i modificacio
    d'activitats i del rellotge intern i d'esborrat d'activitats o etiquetes associades a aquestes.
 */

class Agenda {
  
private:
    /** @brief Rellotge intern de l'agenda. Es crea per defecte a les 00:00 del
    20.04.15, i nomes es pot modificar avançant-lo cap al futur, mai cap al passat. */
    Rellotge rellotge_intern;
    /** @brief L'agenda consta d'un map d'Activitats, ordenades creixentment per rellotges. 
    Inv: No hi ha dos rellotges iguals, per tant, les activitats no es poden superposar en el temps ni coincidir a la mateixa hora i data */
    map<Rellotge, Activitat> agenda;
    /** @brief Al menu hi ha els iteradors de les tasques del'ultima consulta. Si una tasca ha estat modificada o esborrada, o s'ha avançat el
    rellotge inern, les activitats que ja no existeixin o pertanyin al passat no seran accessibles des del menu, mes concretament, l'iterador 
    en uqestio passara a apuntar al final de l'agenda en comptes de al rellotge que apuntava abans de la modificacio */
    typedef vector<map<Rellotge, Activitat>::iterator> Menu;
    Menu menu;
    /** @brief Funcio per l'escriptura de tasques de l'agenda
    \pre  expressio pot ser un string buit o una expressio booleana d'etiquetes;
    agenda.begin() <= principi < final <= agenda.end();
    passat indica si s'esta fent una escriptura de activitats passades.
    \post Ha escrit, numerades, totes les activitats compreses entre 
    principi i final que compleixen l'expressio booleana;
    Si passat es fals, ha actualitzat el menu amb les activitats escrites, 
    si es cert, ha buidat el menu demanera que no es puguin fer mes modificacions.*/
    void escriu(string expressio, map<Rellotge,Activitat>::iterator& principi, map<Rellotge,Activitat>::iterator& final, bool passat);

  
public:
  
    // Constructora
    
    /** @brief Constructora per defecte. Crea una agenda buida.
    \pre Cert.
    \post S'ha creat una agenda amb el rellotge intern a les 00:00 del 20.04.15 i sense activitats*/
    Agenda();
    /** @brief Destructora per defecte. */
    ~Agenda();
    
    //Consultores:
    /** @brief Donat un enter i, verifica si aquest pertany a l'index d'alguna activitat del menu.
    \pre Cert.
    \post Retorna true si a l'ultima consulta existia una tasca i-essima*/
    bool i_valida(int i) const;

    /** @brief Actualitza rel amb el valor del rellotge intern.
    \pre Cert.
    \post rel te el valor del rellotge intern de l'agenda.
    */
    void consultar_rellotge_intern(Rellotge& rel) const;

    /** @brief Actualitza rel amb l'hora i data de la tasca iessima del menu.
    \pre La tasca iessima existeix i  pertany al menu del p.i.
    \post rel te la data i hora daquesta tasca.
    */
    void consultar_rellotge_iessim(Rellotge & rel, int i) const;

    /** @brief Actualitza act amb l'activitat iessima del manu.
    \pre La tasca iessima existeix i pertany al menu del p.i.
    \post act conte el titol i les etiquetes de la tasca iessima del menu del p.i.
    */
    void consultar_activitat_iessima(Activitat & act, int i) const;

    // Modificadores

    /** @brief Avança el rellotge intern fins a la data i hora especificades al parametre.
    \pre rel >= rellotge intern de l'agenda
    \post l'hora i data de l'agenda s'han avançat fins a la data i hora de rel*/
    void modifica_rellotge_intern(Rellotge& rel);

    /** @brief Si no hi ha una activitat a la data i hora especificades al rellotge i si no es 
    una data passada, insereix la nova activitat a l'agenda. En cas contrari no fa res.
    \pre act no es buida.
    \post Retorna true si sha pogut afegir l'activitat a l'agenda i false en cas contrari. */
    bool afegir_activitat(const Rellotge& rel,const Activitat& act);

    /** @brief Modifica una activitat del menu actual i l'actualitza a l'agenda.
    \pre i es refereix a una tasca del menu existent i modificable, act no es buida.
    \post La tasca iessima del manu del p.i. te els atributs de l'activitat act*/
    void modifica_activitat_iessima(Activitat& act, int i);

    /** @brief Esborra l'etiqueta especificada de l'activitat i-essima del menu del p.i.
    \pre i es refereix a una activitat del menu del p.i. existent i modificable.
    \post Retorna true si s'ha esborrat l'etiqueta de la tasca iessima del menu.
    S'ha actualitzat la tasca iessima a l'agenda.
    Si la tasca i-essima no tenia l'etiqueta especificada, no realitza cap canvi i retorna false.*/
    bool esborra_etiqueta(int i,string etiq);

    /** @brief Esborra totes les etiquetes de l'activitat i-essima del menu del parametre implicit.
    \pre i es refereix a una activitat del menu del p.i. existent i modificable.
    \post S'han esborrat les etiquetes de la tasca iessima del menu i sha actualitzat l'agenda. Si la tasca i-essima no tenia 
    cap etiqueta associada, no realitza cap canvi.*/
    void esborra_etiquetes(int i);

    /** @brief Esborra del P.I. l'activitat i-essima del menu.
    \pre i es refereix a una activitat del menu del p.i. existent i modificable.
    \post S'ha esborrat la tasca en el p.i. */
    bool esborra_activitat(int i);


    // Escriptura


    /** @brief Escriu l'hora i dia actual de l'agenda.
    \pre Cert.
    \post Ha escrit la data i hora "actuals" en format "hh:mm dd.mm.aa".  */
    void escriu_rellotge();

    /** @brief Escriu totes les activitats de l'agenda fins a l'hora del rellotge actual.
    \pre Cert.
    \post Ha escrit en ordre cronologic les activitats que ja han passat.*/
    void escriu_passat();

    /** @brief Escriu totes les activitats de l'agenda en l'interval temporal especificat. Si s no es buit, tambe ho escriu en funcio
     * de l'expressio booleana d'etiquetes determinada per aquest.
    \pre Si data es true, primera_data < segona_data, i les dues pertanyen a l'agenda. s es "" o una expressio booleana d'etiquetes
        correctament parentitazada. h es true quan la primera data es la mateixa que la data actual del p.i..
    \post Ha escrit en ordre cronolgic i numerades les activitats futures que compleixen les pre.*/
    void escriu_per_condicio(const bool& data, string primera_data, string segona_data, const string& s, bool h);

    /** @brief Escriu totes les activitats de l'agenda a partir de l'hora del rellotge actual
    \pre Cert.
    \post Ha escrit en ordre cronologic les activitats de l'agenda a partir de la data i hora actuals del p.i. */
    void escriu_futur();
  
};

#endif
