/* 
 * File:   AGE.h
 * Author: alumno
 *
 * Created on 3 de diciembre de 2014, 11:31
 */

#ifndef AGE_H
#define	AGE_H

#include <utility>
#include "AG.h"

using namespace std;

class AGE : public AG {
    protected:
        float pm;
        bool pmx;
    public:
        AGE(const string& rutaFichero, bool usarPmx = false, float _pm = 1, unsigned _tam_pob = 50);
        virtual ~AGE();
        virtual unsigned long ejecutar();
};

#endif	/* AGE_H */

