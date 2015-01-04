
#include "AG.h"

//CONSTRUCTORES Y DESTRUCTORES
//===========================
AG::AG(const string& rutaFichero, unsigned _tam_pob): Metaheuristica(rutaFichero) {
    tam_pob = _tam_pob;      
    evaluaciones = 0;
    mejorCoste = 999999999;
    t_subcadena = tam/2;   
    max_eval = 20000;
}

AG::~AG() { solucion = 0; }

//MÉTODOS PROTECTED
//=================
void AG::iniciarPob(vector<pair<unsigned*, unsigned long> >& pob) {
    unsigned* p;
    unsigned long coste;
    pair<unsigned*, unsigned long> insert;
    
    for(unsigned i = 0; i < tam_pob; i++) {
        p = new unsigned[tam];
        generarSolucion(p);
        
        coste = calculaCoste(p);
        evaluaciones++;
        
        insert.first = p;
        insert.second = coste;
        
        if(coste < mejorCoste) {
            solucion = p;
            mejorCoste = coste;
        }
        
        pob.push_back(insert);
    }
}

unsigned* AG::cruce_pos(unsigned* p, unsigned* m) {
    unsigned* h = new unsigned[tam];    
    char* libres = new char[tam];
    char* asignados = new char[tam];   
    
    for(unsigned i = 0; i < tam; i++) {
        libres[i] = 1;
        asignados[i] = 0;
    }
    
    for(unsigned i = 0; i < tam; i++) {       
        if(p[i] == m[i]) {           
            h[i] = p[i];
            libres[i] = 0;
            asignados[h[i]] = 1;
        }
    }   
    
    
    for(unsigned i = 0; i < tam; i++) {        
        if(libres[i]) {            
            do {
                h[i] = rand() % tam;                
            } while(asignados[h[i]]);        
           
            asignados[h[i]] = 1;
        }
    }    
    
    delete [] libres;
    delete [] asignados;
    
    return h;
}

pair<unsigned*, unsigned*> AG::cruce_pmx(unsigned* p, unsigned* m) {
    unsigned* h1 = new unsigned[tam]; //HIJO 1
    unsigned* h2 = new unsigned[tam]; //HIJO 2
    
    char* asignados_h1 = new char[tam];
    unsigned* precedente_h1 = new unsigned[tam];
    
    char* asignados_h2 = new char[tam];
    unsigned* precedente_h2 = new unsigned[tam];
    
    for(unsigned i = 0; i < tam; i++) {
        asignados_h1[i] = asignados_h2[i] = 0;
    }
    
    /*
        Subcadena central de m a h1 y de p a h2
     */
    for(unsigned i = t_subcadena-1; i < (2*t_subcadena) - 1; i++) {               
        h1[i] = m[i];
        
        asignados_h1[h1[i]] = 1;
        precedente_h1[h1[i]] = p[i];      
        
        h2[i] = p[i];    
        asignados_h2[h2[i]] = 1;
        precedente_h2[h2[i]] = m[i];
    }
    
    unsigned v;
    
    for(unsigned i = 0; i < t_subcadena-1; i++) {
        if(asignados_h1[p[i]]) {
            v = precedente_h1[p[i]];
        } else {
            v = p[i];
        }
        
        h1[i] = v;
        
        if(asignados_h2[m[i]]) {
            v = precedente_h2[m[i]];
        } else {
            v = m[i];
        }
        
        h2[i] = v;
    }
    
    for(unsigned i = (2*t_subcadena) - 1; i < tam; i++) {
        if(asignados_h1[p[i]]) {
            v = precedente_h1[p[i]];
        } else {
            v = p[i];
        }
        
        h1[i] = v;
        
        if(asignados_h2[m[i]]) {
            v = precedente_h2[m[i]];
        } else {
            v = m[i];
        }
        
        h2[i] = v;
    }
    
    delete [] asignados_h1;
    delete [] asignados_h2;
    delete [] precedente_h1;
    delete [] precedente_h2;
    
    return pair<unsigned*, unsigned*>(h1, h2);
}

void AG::mutar(unsigned* p, unsigned i) {
    unsigned j;
    
    do {
        j = rand() % tam;
    } while(i == j);
    
    intercambiar(p, i ,j);
}