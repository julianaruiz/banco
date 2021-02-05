/*
 El usuario 1001015599 tiene de clave 9876 y saldo de 50.000.
 codificacion: 11001110110011011100110011001011110100101100101011001111110011111100111111001111
 El usuario 1001015552 tiene de clave 1234 y saldo de 1'000.000.
 codificacion:110011101100110111001100110010111101001011001110110011111100111111001111110011111100111111001111
*/

#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;
void escribirU(string nom_arch, string texto);
string leerU(string nom_arch);
string asciiU(string texto);
string binarioU(string texto);
string codi_o_decoU(string texto);
string consultar_saldo(string texto);
string retirar(string texto);

int Usuario(){ //menu usuario.
    int sel=0;
    string doc, clave_tex, texto, saldo, clave, bin;
    cout << "Binevenido al banco." << endl;
    cout << endl;
    cout << "Ingrese su documento:";
    cin >> doc;
    doc=doc+".txt";
    texto=leerU(doc);
    bin=codi_o_decoU(texto);
    texto=asciiU(bin);
    for(unsigned int i=0;i<texto.length();i++){
        if (texto[i]=='-'){
            sel++;
        }
    }
    if(sel==0){
        cout << "No es un usuario, por favor registrese como uno." << endl;
        exit(1);
    }
    cout << "Ingrese la clave:";
    cin >> clave;
    for(unsigned int i=0; i<4;i++)
            clave_tex+=texto[i];
    if (clave_tex!=clave){
        cout<< "Clave incorrecta.";
        exit(1);
    }
    cout << "Ingrese el número de la opción a elegir: " << endl;
    cout << "1.Consultar saldo." << endl;
    cout << "2.Retirar." << endl;
    cin >> sel;
    if(sel==1)
        saldo=consultar_saldo(texto);
    else if(sel==2)
        saldo=retirar(texto);
    else{
        while (sel!=1 || sel!=2){
            cout << "Opción incorrecta, por favor ingrese una de las opciones" << endl;
            cout << "1. Consultar saldo." << endl;
            cout << "2.Retirar." << endl;
            cin >> sel;
        }
    }
    texto=clave_tex+'-'+saldo;
    bin=binarioU(texto);
    texto=codi_o_decoU(bin);
    escribirU(doc,texto);

    return 0;
}

string leerU(string nom_arch){ //lee el archivo.
    ifstream archivo;
    string texto;

    archivo.open(nom_arch);
    if(!archivo.is_open()){
        cout << "No se encontro el documento, usted no esta registrado." << endl;
        exit(1);
    }
    while (!archivo.eof())
        getline(archivo,texto);

    archivo.close();
    return texto;
}

void escribirU(string nom_arch, string texto){ //modifica el archivo.
    ofstream archivo;

    archivo.open(nom_arch,ios::out);
    if(!archivo.is_open()){
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    archivo<<texto;
    archivo.close();
}

string codi_o_decoU(string bin){ //codifica o decodifica el texto binario.
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

string asciiU(string texto){ //transforma de binario a ascii y luego a caracter.
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

string consultar_saldo(string texto){ //menu para consultar saldo.
    string saldo;
    stringstream s;
    char res;
    int resta;
    for (unsigned int i=5; i<texto.length();i++)
        saldo+=texto[i];
    cout << "Esta transaccion tiene un costo de 1.000 COP, se le cobrara luego de ver el saldo." << endl;
    cout << "desea continuar?(s/n):";
    cin >> res;
    if (res=='n' or res=='N'){
        cout << "Cancelo la operacion, gracias por visitarnos." << endl;
        exit(0);
    }
    cout << "El saldo es: " << saldo << " COP" << endl;
    resta=atoi(saldo.c_str())-1000;
    s<<resta;
    return s.str();

}

string retirar(string texto){ //retira el valor ingresado.
    int ret, resta;
    string saldo="";
    stringstream s;
    char res;
    for (unsigned int i=5; i<texto.length();i++)
        saldo+=texto[i];
    cout << "cuanto desea retirar?, escriba un numero entero sin puntos ni comas:" << endl;
    cin >> ret;
    resta=atoi(saldo.c_str())-ret;
    while(resta<1000){
        cout << "Fondos insuficientes, debe dejar un saldo de minimo 1.000 COP" << endl;
        cout << "Ingrese un monto a retirar" << endl;
        cin >> ret;
        resta=atoi(saldo.c_str())-ret;
    }
    cout << "Esta transaccion tiene un costo de 1.000 COP, desea continuar?(s/n): ";
    cin >> res;
    if(res=='n' or res=='N'){
        cout << "Cancelo la operacion, gracias por visitarnos." << endl;
        exit(0);
    }
    resta=resta-1000;
    s<<resta;
    cout << "Quedo con un saldo de: " << resta << " COP" << endl;
    return s.str();

}

string binarioU(string texto){ //convierte caracter a ascii y luego a binario.
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
#endif // USUARIO_H
