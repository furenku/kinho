#pragma once

#include "storage.h"

#include "general.h"
#include "videoStorage.h"

//

class Ontology: public StoreObject {
    public:
        Ontology(){
            setType("ontology");
            addAttribute("value","...");
        }
};


class Tag: public Ontology {
    public:
        Tag(){ setType("tag"); }
};

class Category: public Ontology {
    public:
        Category(){ setType("category"); }
};

    //children allowed only one parent
class OntologyObject: public Ontology {
    public:
        OntologyObject(){ setType("ontologyObject"); }
};

class Place: public Ontology {
    public:
        Place(){ setType("place"); setCoordinates(0,0); }
        void setCoordinates(float _x, float _y) { coordX = _x; coordY = _y; }

        float coordX;
        float coordY;

};

class Action: public Ontology {
    public:
        Action(){ setType("action"); setLengthM(0); setLengthS(0); }
        void setLengthS(float _s) { lengthS = _s; }
        void setLengthM(float _min) { lengthMin = _min; }
        float lengthS;
        float lengthMin;
};

class Web: public Ontology {
    public:
        Web(){ setType("web"); }
};


