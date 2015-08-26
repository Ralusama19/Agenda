/** @file rellotge.cc
    @brief Codi de la classe Rellotge.
*/

#include "rellotge.hh"

//Constructora

Rellotge::Rellotge() {
	//Inicialitza un rellotge el 20.04.15 a les 00:00
	hora = "00";
	minut = "00";
	dia = "20";
	mes = "04";
	any = "15";
}


Rellotge::Rellotge(const string& horaminut, const string& data) {
	//Agafem els substrings corresponents dels strings d'entrada
	hora = horaminut.substr(0,2);
	minut = horaminut.substr(3,2);
	dia = data.substr(0,2);
	mes = data.substr(3,2);
	any = data.substr(6,2);
}


Rellotge::~Rellotge() {}

//Modificadores
//*
void Rellotge::modificar(const string& horaminut, const string& data){ 
	//modifica el p.i. amb els substrings corresponents dels strings d'entrada
	hora = horaminut.substr(0,2);
	minut = horaminut.substr(3,2);
	dia = data.substr(0,2);
	mes = data.substr(3,2);
	any = data.substr(6,2);
}

// Consultora

bool Rellotge::operator<(const Rellotge& r) const{
    if (any != r.any) return any < r.any;
    if (mes != r.mes) return mes < r.mes;
    if (dia != r.dia) return dia < r.dia;
    if (hora != r.hora) return hora < r.hora;
    return minut < r.minut;
}

bool Rellotge::operator==(const Rellotge& r) const{
	return (any == r.any and mes == r.mes and dia == r.dia and hora == r.hora and minut == r.minut);
}

string Rellotge::consultar_data() const{
  string data = dia + "." + mes + "." + any;
  return data;
}


string Rellotge::consultar_horaminut() const {
	string horaminut = hora + ":" + minut;
	return horaminut;
}

//Escriptura
void Rellotge::escriu_rellotge() {
	//Escriu el rellotge en el format adient
	cout << consultar_data() << " " << consultar_horaminut();
}
