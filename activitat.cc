/** @file activitat.cc
    @brief Codi de la classe Activitat
*/

#include "activitat.hh"


void Activitat::solve(const string & all, int & i, bool & correcta, bool eval){
    // CAS BASE
    if (all[i] == '#') {
        int j = 0;
        while((all[i + j] != '.' and all[i + j] != ','
            and all[i + j] != ')' and i+j != all.size())) ++j;
        if (eval) correcta = te_etiqueta(all.substr(i, j));
        i += j;
    }
    //CAS RECURSIU
    else {
        ++i;
        solve (all, i, correcta, eval);
        //H.I. correcta conte el resultat del primer element de l'expressio
        bool correcta1 = correcta;
        char operador;
        operador = all[i];
        ++i;
        bool eval1;
        if((correcta and operador == '.') or (not correcta and operador == ',')) eval1 = true;
        else eval1 = false;
        solve (all, i, correcta, eval1);
        //H.I. correcta conte el resultat d'avaluar el segon element de l'expressio
        if(operador == '.') correcta = correcta1 and correcta;
        else if(operador == ',') correcta = correcta1 or correcta;
        ++i;
     }
}

bool Activitat::te_etiqueta(const string& etiqueta) const {
  //Si l'etiqueta existeix retorna true, en cas contrari retorna false;
    return etiquetes.find(etiqueta) != etiquetes.end();
}

int Activitat::num_etiquetes() const{
    return etiquetes.size();
}

//Creadora

Activitat::Activitat() {}

Activitat::~Activitat(){}

//Consultores

Activitat& Activitat::operator=(const Activitat& original){
  //Assignem els parametres de l'original sobre el p.i.
  descripcio = original.descripcio;
  etiquetes = original.etiquetes;
  return *this;
}

bool Activitat::compleix_expressio(const string& formula){
  bool correcta;
  int i = 0;
  //Per la primera crida recursiva hem d'inicialitzar la i a la posicio 0
  //per tal d'evaluar l'string amb l'expressio des del principi;
  //eval = true perque sabem que segur que s'ha d'evaluar el primer parentesi.
  solve(formula, i, correcta, true);
  return correcta;
}

string Activitat::consultar_titol() const {
  return descripcio;
}

//Modificadores 

void Activitat::modificar_titol(const string& titol) {
  descripcio = titol;
}

bool Activitat::afegir_etiqueta(const string& etiq) {
  //Ens assegurem que l'etiqueta no estigui en el p.i.
  //i si no hi es l'afegim
  pair<map<string,bool>::const_iterator,bool> correcte;
  correcte = etiquetes.insert(make_pair(etiq,true));
  return (correcte.second);
}

bool Activitat::esborrar_etiqueta(const string& etiq) {
  //Verifiquem que l'etiqueta estigui en el p.i. abans d'esborrarla
  int num_borrats = etiquetes.erase(etiq);
  //Per inv. del map d'etiquetes, 0 <= num_borrats <= 1;
  return (num_borrats > 0);
}

void Activitat::esborrar_totes_etiquetes() {
   etiquetes.clear();
}

//Escriptura

void Activitat::escriu_titol(){
  cout << descripcio;
}

void Activitat::escriu_etiquetes(){
  //Recorrem el map amb iteradors i n'escrivim les claus (etiquetes).
  //Per inv. del map d'etiquetes, les escrivim per ordre alfabetic
  for(map<string,bool>::const_iterator it = etiquetes.begin(); it != etiquetes.end(); ++it){
    cout << " " << it->first;
  }
}
