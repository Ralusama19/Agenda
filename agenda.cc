/** @file agenda.cc
    @brief Codi de la classe Agenda
*/

#include "agenda.hh"

void Agenda::escriu(string expressio, map<Rellotge,Activitat>::iterator& principi, 
    map<Rellotge,Activitat>::iterator& final, bool passat){
    //Buidem el menu abans de cada consulta
    menu.clear();
    int i = 1;
    for(map<Rellotge,Activitat>::iterator it = principi; it != final; ++it){
        if((expressio == "") or (it->second.compleix_expressio(expressio))){
            //Si no es una consulta sobre el passat, actualitzem el menu amb els iteradors de les activitats escrites
            if (not passat) menu.push_back(it);
            cout << i << " " ;
            it->second.escriu_titol();
            cout << " " << it->first.consultar_data() << " " << it->first.consultar_horaminut();
            it->second.escriu_etiquetes();
            cout << endl;
            ++i;
        }
    }
}

// Constructora
Agenda::Agenda(){}

//Destructora 
Agenda::~Agenda(){}

// Consultores
bool Agenda::i_valida(int i) const{
    //Ens assegurem que la i es refereixi a una posicio del menu i que la tasca a la que es refereix existeixi
    return (0 <= i  and i < menu.size() and menu[i] != agenda.end());
}

void Agenda::consultar_rellotge_intern(Rellotge& rel) const{
  rel = rellotge_intern;
}

void Agenda::consultar_rellotge_iessim(Rellotge & rel, int i) const{
    rel = menu[i]->first;
}

void Agenda::consultar_activitat_iessima(Activitat & act, int i) const{
    act = menu[i]->second;
}

//Modificadores

void Agenda::modifica_rellotge_intern(Rellotge& rel) {
    //assignem rel al rellotge intern
    rellotge_intern = rel;
    int i = 0;
    //actualitzem el menu perque no es puguin modificar tasques que formen part del passat
    while (i < menu.size() and menu[i] != agenda.end() 
        and menu[i]->first < rellotge_intern){
        menu[i] = agenda.end();
        ++i;
    }
}

void Agenda::modifica_activitat_iessima(Activitat& act, int i) {
    menu[i]->second = act;
}

bool Agenda::afegir_activitat(const Rellotge& rel,const Activitat& act){
    pair<map<Rellotge, Activitat>::iterator, bool> result;
    //ens assegurem de no crear una tasca ala mateixa data i hora que unaltre 
    result = agenda.insert(make_pair(rel, act));
    return result.second;
}

bool Agenda::esborra_etiqueta(int i,string etiq){
   return menu[i]->second.esborrar_etiqueta(etiq);
}

void Agenda::esborra_etiquetes(int i){
   menu[i]->second.esborrar_totes_etiquetes();
}

bool Agenda::esborra_activitat(int i){
    int num_borrats = agenda.erase(menu[i]->first); 
    if (num_borrats > 0) menu[i] = agenda.end();
    return (num_borrats > 0);
}



// Escriptura

void Agenda::escriu_rellotge(){
    rellotge_intern.escriu_rellotge();
}

void Agenda::escriu_passat(){
    menu.clear();
    map<Rellotge,Activitat>::iterator principi = agenda.begin();
    map<Rellotge,Activitat>::iterator final = agenda.lower_bound(rellotge_intern);
    escriu("", principi, final, true);
}

void Agenda::escriu_per_condicio(const bool& data, string primera_data, string segona_data,
 const string& s, bool h){

    map<Rellotge,Activitat>::iterator principi, final;
    if(data){
        Rellotge rel1("00:00", primera_data), rel2("23:59", segona_data);
        if (h){
        	rel1 = rellotge_intern;
        }
        principi = agenda.lower_bound(rel1);
        final = agenda.upper_bound(rel2);
    }

    else {
        principi = agenda.lower_bound(rellotge_intern);
        final = agenda.end();
    }
    escriu(s,principi,final, false);
}

void Agenda::escriu_futur(){
    map<Rellotge,Activitat>::iterator principi = agenda.lower_bound(rellotge_intern);
    map<Rellotge,Activitat>::iterator final = agenda.end();
    escriu("", principi, final, false);
}


