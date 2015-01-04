/* 
 * File:   AGG_POS.h
 * Author: alumno
 *
 * Created on 3 de diciembre de 2014, 11:30
 */

#ifndef AGG_POS_H
#define	AGG_POS_H

#include <utility>
#include "AG.h"
#include "BL.h"
using namespace std;

class AGG : public AG {
    protected:
        unsigned n_cruces;
        unsigned n_mutac;
        bool pmx;
        
        BL* bl;
        unsigned pOpt;
        bool mejor;
        
        vector<unsigned*> seleccion(vector<pair<unsigned*, unsigned long> >& pob);
        //Proceso de selección
    public:
        AGG(const string& rutaFichero, float _pOpt, bool _mejor = false, bool usarPmx = false, float _pc = 0.7, float _pm = 0.01, unsigned _tam_pob = 50);
        virtual ~AGG();
        virtual unsigned long ejecutar();
};

#endif	/* AGG_POS_H */

