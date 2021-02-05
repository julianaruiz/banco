/*
 BANCO.
 menú administrador-usuario.
 administrador:
    acceder con cédula y clave(encriptada). Podrá realizar registro de usuarios
    (cédula,clave,saldo), los dos últimos encriptados.
 Usuario:
    accede con cédula y clave(encpritada). Podrá consultar saldo y retirar, en cada
    una se hace un retiro de 1.000 al saldo, el saldo a retirar no debe ser mayor que
    el saldo de su cuenta + 1.000. si esto pasa se le pedirá otro valor.
*/

#include <iostream>
#include "Administrador.h"
#include "Usuario.h"

using namespace std;

int main()
{
    int num;
    cout << "Bienvenido al banco" << endl;
    cout << "Seleccione una opcion para empezar: " << endl;
    cout << "1.Administrador" << endl;
    cout << "2.Usuario" << endl;
    cin >> num;

    if (num==1)
        Administrador();
    else if (num==2)
        Usuario();
    else
        cout << "Opcion invalida." << endl;
    return 0;
}
