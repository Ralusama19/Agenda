/** @file rellotge.hh
    @brief Especificacio de la classe Rellotge
 */

#ifndef RELLOTGE_HH
#define RELLOTGE_HH

#include "utils.PRO2"
#include <string>

/** @class Rellotge
    @brief Representa un rellotge amb una data i una hora. 

    Les dates tenen el format **.**.** (dia, mes i any) i les hores, **:** (hora, minuts), on * representa un digit.
    Tant dates com hores respecten les restriccions habituals (nombre de mesos per any, dies per mes, 
    d'hores per dia i de minuts per hora).
 */

class Rellotge {
    
private:
    /** @brief Hora del rellotge */
    string hora;
    /** @brief Minuts del rellotge */
    string minut;
    /** @brief Dia del rellotge */
    string dia;
    /** @brief Mes del rellotge */
    string mes;
    /** @brief Any del rellotge */
    string any;

public:

// Constructores

    /** @brief Creadora per defecte. Crea un Rellotge nou amb la data i hora per defecte.
    \pre Cert.
    \post S'ha creat un rellotge per defecte amb hora 00:00 i data 20/04/15.*/
    Rellotge();

    /** @brief Crea un rellotge amb la data i hora dels strings d'entrada.
    \pre: Cert.
    \post S'ha creat un rellotge amb data i hora especificades */
    Rellotge(const string& horaminut, const string& data);

    /** @brief Destructora per defecte.*/
    ~Rellotge();

    // Modificadores
    
    /** @brief Modifica el P.I. amb la data i hora dels strings d'entrada.
    \pre: Cert.
    \post El P.I. te la data i hora especificades */
    void modificar(const string& horaminut, const string& data);

    // Consultores


    /** @brief Compara el parametre implicit amb r.
    \pre Cert
    \post Retorna true si el P.I. es mes petit que r. */
    bool operator<(const Rellotge& r) const;

    /** @brief Compara el parametre implicit amb r.
    \pre Cert
    \post Retorna true si el P.I. es igual r. */
    bool operator==(const Rellotge& r) const;
    
    /** @brief Retorna un string amb la data del parametre implicit.
    \pre Cert.
    \post S'ha retornat un string amb la data del P.I. en el format especificat */
    string consultar_data() const;

    /** @brief Retorna un string amb la hora i minuts del parametre implicit.
    \pre Cert.
    \post S'ha retornat un string amb la hora i minuts del P.I. en el format especificat */
    string consultar_horaminut() const;

    /** @brief Retorna un string amb la data i hora del parametre implicit.
    \pre Cert.
    \post S'ha retornat un string amb la hora i minuts del P.I. en el format especificat */
    //string consultar_rellotge() const;

    // Escritura

    /** @brief Escriu el dia i hora del parametre implicit en format "hh:mm dd.mm.aa"
    \pre Cert.
    \post S'ha escrit el parametre implicit pel canal de sortida en el format indicat.*/
    void escriu_rellotge();
};
#endif
