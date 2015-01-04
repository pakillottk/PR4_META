
#include "AGG.h"

AGG::AGG(const string& rutaFichero, bool usarPmx, float _pc, float _pm, unsigned _tam_pob ):
AG(rutaFichero, _tam_pob)
{
    pmx = usarPmx;
    n_cruces = _pc * (tam_pob/2);
    n_mutac = tam * _pm;
}

AGG::~AGG(){}

vector<unsigned*> AGG::seleccion(vector<pair<unsigned*,unsigned long> >& pob) {
    vector<unsigned*> selec;
    
    unsigned p;
    unsigned m;
    
    for(unsigned i = 0; i < pob.size(); i++) {
        p = rand() % pob.size();
        do {
            m = rand() % pob.size();
        } while(p == m);
        
      
        
        if(pob[p].second < pob[m].second) {
            selec.push_back(pob[p].first);
        } else {
            selec.push_back(pob[m].first);
        }
    }
    
    return selec;
}

unsigned long AGG::ejecutar() {    
   //Vector población
    vector<pair<unsigned*, unsigned long> > pob;
    
    //Población inicial
    iniciarPob(pob);
    
    //Vector de padres
    vector<unsigned*> padres;
    //Vector de hijos
    vector<pair<unsigned*, unsigned long> > hijos;
    
    while(evaluaciones < max_eval) {
        //Generar padres
        padres = seleccion(pob);
        
        //Generar hijos        
        pair<unsigned*, unsigned*> h;       
        pair<unsigned*, unsigned long> insert;
        insert.second = 0;
        
        for(unsigned i = 0; i < n_cruces; i=i+2) {            
            if(pmx)
                h = cruce_pmx(padres[i], padres[i+1]);
            else
                h.first = cruce_pos(padres[i], padres[i+1]);           
          
            
            
            insert.first = h.first;
            hijos.push_back(insert);
            
            if(pmx) {
                 insert.first = h.second;   
                 hijos.push_back(insert);
            }
        }        
        
        //Mutar hijos
        unsigned j, gen;       
        for(unsigned i = 0; i < n_mutac; i++) {
            j = rand() % hijos.size();
            gen = rand() % tam;        
            
            mutar(hijos[j].first, gen);           
        }        
        
        //Evaluar hijos
        unsigned peorHijo;
        unsigned long peorCoste = 0;
        for(unsigned i = 0; i < hijos.size(); i++) {
            hijos[i].second = calculaCoste(hijos[i].first);
            
            if(hijos[i].second > peorCoste) {
                peorHijo = i;
                peorCoste = hijos[i].second;
            }

            evaluaciones++;
            if(evaluaciones == max_eval)
                break;
        }     
        
        //Comprobamos si hemos cumplido condicion de parada
        if(evaluaciones == max_eval)
                break;
        
        //Reemplazo
        unsigned* mejorHijo;
        unsigned  mejorCoste_h = 999999999;
        unsigned cur_p = 0;
        
        if(pmx) {
            delete [] hijos[peorHijo].first;
            hijos[peorHijo].first = 0;
        } else {
            for(unsigned i = 0; i < hijos.size(); i++) {
                if(!hijos[i].first)
                    continue;
                
                if(pob[cur_p].first == solucion) {
                    cur_p++;
                } 

                delete [] pob[cur_p].first;
                pob[cur_p].first = hijos[i].first;
                pob[cur_p].second = hijos[i].second; 
                cur_p++;
                
                if(hijos[i].second < mejorCoste_h) {
                    mejorHijo = hijos[i].first;
                    mejorCoste_h = hijos[i].second;
                }
            }
        }       
        
        //Actualizar mejor solución
        if(mejorCoste_h < mejorCoste) {
            solucion = mejorHijo;
            mejorCoste = mejorCoste_h;
        }       
        
        //Reiniciar vectores
        padres.clear();
        hijos.clear();        
    } 
    
    //Liberamos la memora
    for(unsigned i = 0; i < pob.size(); i++)
        delete [] pob[i].first;
    
    //Devolvemos mejor coste encontrado
    return mejorCoste;
}

