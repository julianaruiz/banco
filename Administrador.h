/*
 El administrador 1001370876 tiene de clave abcd.
 codificación: 10011110100111011001110010011011
*/

#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
void escribir(string nom_arch, string texto);
string leer(string nom_arch);
string ascii(string texto);
string binario(string texto);
string codi_o_deco(string texto);
void IngresoUsuario();


int Administrador(){ //menu administrador.
    string doc, clave,texto,pass,bin;
    cout << "Bienvenido al menu Administrador" << endl;
    cout << "Ingrese su documento, sin espacios: ";
    cin >> doc;
    doc=doc+".txt";
    texto=leer(doc);
    cout << "Ingrese su clave: ";
    cin >> clave;
    bin=codi_o_deco(texto);
    pass=ascii(bin);
    for(unsigned int i=0;i<pass.length();i++){
        if (pass[i]=='-'){
            cout << "No esta registrado como administrador." << endl;
            exit(1);
        }
    }
    if (clave!=pass){
        cout << "Clave equivocada." << endl;
        exit(1);
    }
    bin=binario(pass);
    texto=codi_o_deco(bin);
    escribir(doc,texto);
    IngresoUsuario();


    return 0;
}

string leer(string nom_arch){ //lee el archivo.
    ifstream archivo;
    string texto;

    archivo.open(nom_arch);
    if(!archivo.is_open()){
        cout << "No se encontro el documento, no puede entrar como administrador" << endl;
        exit(1);
    }
    while (!archivo.eof())
        getline(archivo,texto);

    archivo.close();
    return texto;
}

void escribir(string nom_arch, string texto){ //sobreescribe el archivo.
    ofstream archivo;

    archivo.open(nom_arch,ios::out);
    if(!archivo.is_open()){
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    archivo<<texto;
    archivo.close();
}

string ascii(string texto){ //pasa de binario a ascii y luego a caracter.
    string as, numeros;
    for(unsigned int i=0;i<texto.length();i+=8){
        as="";
        char numero=0;
        int num=128;
        for (unsigned int j=0;j<8;j++)
            as+=texto[j+i];
        for (unsigned int j=0;j<8;j++){
            if ('1'==as[j])
                numero+=num;
            num/=2;
        }
        numeros+=numero;
    }
    return numeros;
}

string binario(string texto){ //pasa de caracter a ascii y luego a binario.
    string bin, texto_bin;
    int num;

    for(unsigned int i=0; i < texto.length();i++){
        num=texto[i];
        bin="";

        for(unsigned j=1; j<=8;j++){
            bin[8-j]=num%2+48;
            num/=2;
        }

        for(unsigned j=0;j<8;j++)
            texto_bin+=bin[j];
    }

    return texto_bin;
}

string codi_o_deco(string bin){ //codifica o decodifica los binarios.
    string grupo, codi="";
    for(unsigned int i=0;i<bin.length();i+=4){
        grupo="";
        for(unsigned int j=0;j<4;j++)
            grupo+=bin[j+i];
        for(unsigned int j=0;j<grupo.length();j++){

                if (grupo[j]=='1')
                    grupo[j]='0';
                else if(grupo[j]=='0')
                    grupo[j]='1';

        }
        codi+=grupo;
    }
    return codi;
}

void IngresoUsuario(){ //menú para agregar un usuario.
    bool ingreso=true;
    char sn;
    while (ingreso){
        string doc, clave, saldo, interior,bin;
        cout << endl;
        cout << "Registro de usuarios." << endl;
        cout << endl;
        cout << "Ingrese el documento: ";
        cin >> doc;
        cout << "Ingrese una clave de 4 digitos: ";
        cin >> clave;
        while(clave.length()!=4){
            cout << "Ingrese una clave de 4 digitos: ";
            cin >> clave;
        }
        cout << "Ingrese el saldo: ";
        cin >> saldo;
        doc=doc+".txt";
        interior=clave+'-'+saldo;
        bin=binario(interior);
        interior=codi_o_deco(bin);
        escribir(doc,interior);

        cout << "Ingresar otro usuario (s/n): " << endl;
        cin >> sn;
        if (sn==78 || sn==110)
            ingreso=false;

    }
}

#endif // ADMINISTRADOR_H
