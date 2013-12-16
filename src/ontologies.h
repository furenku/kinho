#ifndef ONTOLOGIES_H
#define ONTOLOGIES_H

#include "storage.h"

#include "general.h"
#include "mediaStorage.h"



class Ontology: public StoreObject {
    public:
        Ontology();
};


class Tag: public Ontology {
    public:
        Tag();
};

class Category: public Ontology {
    public:
        Category();
};

    //children allowed only one parent
class OntologyObject: public Ontology {
    public:
        OntologyObject();
};

class Place: public Ontology {
    public:
        Place();
        void setCoordinates(float _x, float _y);

        float coordX;
        float coordY;

};

class Action: public Ontology {
    public:
        Action();
        void setLengthS(float _s);
        void setLengthM(float _min);
        float lengthS;
        float lengthMin;
};

class Web: public Ontology {
    public:
        Web();
};



#endif
