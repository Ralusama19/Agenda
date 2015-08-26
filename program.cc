/** @mainpage
    El programa principal program.cc posa en practica les operacions demanades a l'enunciat
    de la practica de PRO2. 

    En aquesta practica s'ha hagut de crear un gestor de tasques que ens permeti afegir, modificar,
    i esborrar tasques mitjançant unes comandes especifiques.
    El gestor tambe ens permet accedir a un rellotge intern modificable que ens marca el moment del temps
    que considerem com a "present". 
    Un cop executat el gestor, aquest no conte cap activitat, i la seva data per defecte es troba a les 00:00 del 20.04.15.
    Un cop iniciat es poden dur a terme totes les operacions que especifica l'enunciat.

    Per implementar el gestor de tasques hem fet us, per una banda, de la classe Comanda que ens han proporcionat
    els professors de PRO2 i que ens permeten llegir i interpretar les comandes que utilitza el gestor.
    Per altra banda hem utilitzat classes implementades per nosaltres: Agenda, Activitat i Rellotge.
*/

/** @file program.cc
    @brief Programa principaldel gestor de tasques 
*/
#include "agenda.hh"
#include "comanda.hh"

 /** @brief Indicia si la data i hora especificades a la comanda son valides, es a dir, son iguals o posteriors a les de rintern.
      \pre rmodificat = rintern, la comanda no te errors sintactics.
      \post retorna true i rmodificat conte la data i hora de la comanda. Si la comanda nomes conte hora, la data no es modifica, i a l'inreves;
      retorna false quan la comanda no conte ni data ni hora o quan aquests son anteriors a rintern.
  */
bool es_rellotge(Rellotge & rmodificat, Rellotge rintern, Comanda & comanda) {
    string hora, data;
    int dates = comanda.nombre_dates();
    if (comanda.te_hora() and dates == 1) {
        hora = comanda.hora();
        data = comanda.data(1);
    }
    else if (comanda.te_hora()) {
        hora = comanda.hora();
        data = rmodificat.consultar_data();

    }
    else if (dates == 1) {
        hora = rmodificat.consultar_horaminut();
        data = comanda.data(1);
    }
    else return false;
    Rellotge aux(hora, data);
    bool error = (aux < rintern);
    if (not error) rmodificat = aux;
    return (error == false);
}

 /** @brief Actualitza amodificada amb el titol i etiquetes de la comanda.
      \pre amodificada = aoriginal; la comanda no te errors sintactics
      \post Si la comanda contenia un titol, el titol de amodifcada ha estat modificat amb aquest.
      Si la comanda contenia etiquetes, aquestes han estat afegides a amodificada.
  */
void actualitza_activitat(Activitat& amodificada, Activitat& aoriginal,Comanda& comanda) {
    string titol;
    amodificada = aoriginal;
    if (comanda.te_titol()){
        titol = comanda.titol();
        amodificada.modificar_titol(titol);
    }
    if (comanda.nombre_etiquetes() != 0){
        for(int i = 1; i <= comanda.nombre_etiquetes(); ++i){
            string etiq = comanda.etiqueta(i);
            amodificada.afegir_etiqueta(etiq);
        }
    }
}

int main(){
    Agenda agenda;
    Comanda comanda;
    bool be;
    while (comanda.llegir(be)){
        if (be){
            //AFEGIR
            if (comanda.es_insercio()){
                Rellotge rmodificat;
                Rellotge rintern;
                agenda.consultar_rellotge_intern(rintern);
                rmodificat = rintern;
                bool rellotge_correcta = es_rellotge(rmodificat, rintern, comanda);
                Activitat amodificada;
                bool ins_correcta = false;
                actualitza_activitat(amodificada, amodificada, comanda);
                if (rellotge_correcta) {
                    ins_correcta = agenda.afegir_activitat(rmodificat, amodificada);
                }
                if (not ins_correcta)  cout << "No s'ha realitzat" << endl;
            }
            //ESCRIPTURA
                //ESCRIU T.PASSAT
            else if (comanda.es_consulta()){
                if (comanda.es_passat()){
                    agenda.escriu_passat();
                }
                //ESCRIU T.PRESENT
                else if (comanda.es_rellotge()){
                    agenda.escriu_rellotge();
                    cout << endl;
                }
                else if (comanda.nombre_dates() == 0 and comanda.nombre_etiquetes() == 0 and not comanda.te_expressio()){
                    agenda.escriu_futur();
                }
                //ESCRIU T.EXPRESIO QUE HAGI INDICAT AMB ETIQUETES I/o DATES
                else{
                    string s;
                    if (comanda.te_expressio()){
                         s = comanda.expressio();
                    }
                    else if (comanda.nombre_etiquetes() == 0){
                         s = "";
                    }
                    else{
                        s = comanda.etiqueta(1);
                    }
                    bool hi_ha_data = (comanda.nombre_dates() > 0);
                    if (hi_ha_data){
                        Rellotge rintern, r1;
                        agenda.consultar_rellotge_intern(rintern);
                        string dataintern = rintern.consultar_data(), data1 = comanda.data(1);
                        r1.modificar("23:59", data1);
                        bool h = false;
                        if (data1 == dataintern){
                            h = true;
                        }
                        if (comanda.nombre_dates() == 1){
                            if (not (r1 < rintern)){
                                agenda.escriu_per_condicio(hi_ha_data, data1, data1,s, h);
                            }
                        }
                        else if(comanda.nombre_dates() == 2){
                            string data2 = comanda.data(2);
                            Rellotge r2("23:59", data2);
                            if (not (r2 < r1) and not (r2 < rintern)){
                                if (r1 < rintern){
                                    h = true;
                                    agenda.escriu_per_condicio(hi_ha_data, dataintern, data2,s,h);
                                }
                                else agenda.escriu_per_condicio(hi_ha_data, data1, data2,s,h);
                            }
                        }
                    }
                    else agenda.escriu_per_condicio(hi_ha_data, "", "",s, false);
                }
            }
            //MODIFCAR RELLOTGE
            else if (comanda.es_rellotge()){

                Rellotge rmodificat, rintern;
                agenda.consultar_rellotge_intern(rintern);
		        rmodificat = rintern;
                if (es_rellotge(rmodificat, rintern, comanda)) {
                    agenda.modifica_rellotge_intern(rmodificat);
                }
                else cout << "No s'ha realitzat" << endl;
            }
            //MODIFICAR ACTIVITAT
            else if (comanda.es_modificacio()){
                int i = comanda.tasca();
                --i;
                bool correcte = agenda.i_valida(i);
                if(correcte){
                    Rellotge rmodificada, rintern;
                    agenda.consultar_rellotge_iessim(rmodificada, i);
                    Activitat amodificada, aoriginal;
                    agenda.consultar_activitat_iessima(aoriginal, i);
                    agenda.consultar_rellotge_intern(rintern);
                    bool r = es_rellotge(rmodificada, rintern, comanda);
                    actualitza_activitat(amodificada, aoriginal, comanda);
                    if (not r){
                        if (comanda.te_hora() or comanda.nombre_dates() != 0) correcte = false;
                            agenda.modifica_activitat_iessima(amodificada, i);
                    }
                    else{
                        correcte = agenda.afegir_activitat(rmodificada, amodificada);
                        if (correcte){
                            agenda.esborra_activitat(i);
                        }
                    }
                }
                if (not correcte) cout << "No s'ha realitzat" << endl;
            }
            //ESBORRAR
            else if (comanda.es_esborrat()){
		int i = comanda.tasca()-1;
		bool correcte = agenda.i_valida(i);
		if (correcte){
		    if (comanda.tipus_esborrat() == "etiqueta"){
			//ESBORRA UNA ETIQUETA D'UNA TASCA
			if (not agenda.esborra_etiqueta(i, comanda.etiqueta(1)))
			    correcte = false;
		    }

		    else if (comanda.tipus_esborrat() == "etiquetes"){
			//ESBORRA TOTES LES ETIQUETES D'UNA TASCA
			agenda.esborra_etiquetes(i);
		    }

		    else if (comanda.tipus_esborrat() == "tasca"){
			//ESBORRA UNA ACTIVITAT - TASCA
			if (not agenda.esborra_activitat(i))
			    correcte = false;
		    }
		}
		if (not correcte) cout << "No s'ha realitzat" << endl;
            }
        }
    }
}
