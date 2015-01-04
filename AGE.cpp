
#include "AGE.h"

AGE::AGE(const string& rutaFichero, bool usarPmx, float _pm, unsigned _tam_pob ):
AG(rutaFichero, _tam_pob) 
{
    pmx = usarPmx;
    pm = _pm;
}

AGE::~AGE() {}

unsigned long AGE::ejecutar() {
    //Vector poblaciÃ³n
    vector<pair<unsigned*, unsigned long> > pob;
    
    //PoblaciÃ³n inicial
    iniciarPob(pob);
    
    unsigned ind_1, ind_2;
    unsigned* p1;
    unsigned* p2;
    
    pair<unsigned*, unsigned*> h;
    pair<unsigned long, unsigned long> coste_h;
    
    while(evaluaciones < max_eval) {
        //Seleccionamos dos padres       
        ind_1 = rand() % pob.size();
        
        do {
            ind_2 = rand() % pob.size();
        } while (ind_2 == ind_1);
        
        p1 = pob[ind_1].first;
        p2 = pob[ind_2].first;
        
        //Cruzamos        
        if(pmx) {
            h = cruce_pmx(p1, p2);
        } else {
            h.first = cruce_pos(p1, p2);
        }
        
        //Mutamos
        unsigned p = rand () % 100;
        unsigned g;
        if(p < pm) {
            g = rand () % tam;
            mutar(h.first, g);
        }
        
        //Calculamos coste hijos        
        coste_h.first = calculaCoste(h.first);
        evaluaciones++;
        
        if(pmx) {
            coste_h.second = calculaCoste(h.second);
            evaluaciones++;
        }
        
        if(evaluaciones == max_eval)
            break;
        
        //Reemplazo y actualizar mejor global
        unsigned long peorCoste = 0;
        unsigned peor;
        
        for(unsigned i = 0; i < tam_pob; i++) {
            if(pob[i].second > peorCoste) {
                peorCoste = pob[i].second;
                peor = i;
            }
        }
        
        delete [] pob[peor].first;
        pob[peor].first = h.first;
        pob[peor].second = coste_h.first;
        
        if(coste_h.first < mejorCoste) {
            mejorCoste = coste_h.first;
            solucion = h.first;
        }
        
        if(pmx) {
            peorCoste = 0;
            for(unsigned i = 0; i < tam_pob; i++) {
                if(pob[i].second > peorCoste) {
                    peorCoste = pob[i].second;
                    peor = i;
                }
            }
            
            delete [] pob[peor].first;
            pob[peor].first = h.second;
            pob[peor].second = coste_h.second;
            
            if(coste_h.second < mejorCoste) {
                mejorCoste = coste_h.second;
                solucion = h.second;
            }
        }
    }
    
    //Liberar memoria
    for(unsigned i = 0; i < pob.size(); i++) {
        delete [] pob[i].first;
    }
    
    //Devolver mejor coste
    return mejorCoste;
}