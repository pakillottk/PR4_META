/*
 * File:   Utils.h
 * Author: Fasgort
 *
 * Created on 15 de octubre de 2014, 10:35
 */

#ifndef LIMITES_H
#define	LIMITES_H

#include <iostream>
using namespace std;

/**@brief Permite restringir el valor que se le pasa dentro de un rango de valores
 * @param limi L�mite inferior
 * @param limis L�mite superior
 * @param valor El valor al que se le aplica la restricci�n
 * @pre 'limi' debe ser menor que 'limis', para que la funci�n tenga sentido
 * @return Devuelve el mismo valor si ya est� dentro del rango, u otro valor que se pide si el que se le pasa no est� dentro del rango
 */
int LimiteEntero(int limi, int limis, int valor);

/**@brief Permite restringir la longitud de la cadena que se le pasa dentro de un rango de valores
 * @param limi Longitud m�nima
 * @param limis Longitud m�xima
 * @param valor La cadena a la que se le aplica la restricci�n
 * @pre 'limi' debe ser menor que 'limis', para que la funci�n tenga sentido
 * @return Devuelve la misma cadena si su longitud ya est� dentro del rango, u otra cadena que se pide si la longitud de la cadena no est� dentro del rango
 */
string LimiteCadena(unsigned int limi, unsigned int limis, string valor);

/**@brief Pide un dato por teclado, y comprueba que est� dentro de un rango, si no lo est� devuelve un mensaje y vuelve a pedir que se introduzca otro, y si est� en el rango, lo devuelve tal cual
 * @param limi L�mite inferior del rango
 * @param limis L�mite superior del rango
 * @param mensaje Mensaje que se devuelve si el valor introducido no est� en el rango
 * @return Devuelve un valor introducido que est� en el rango
 */
int Limites(int limi, int limis, string mensaje);

/**@brief Funci�n auxiliar que limpia std::stdin, que a veces queda '\n' y da fallos al utilizar 'getline' despues de 'cin'
 * @param stream Variable que almacena '\n', simplemente para eliminarlo de std::stdin
 */
void skipline(std::istream &stream);

#endif	/* LIMITES_H */

