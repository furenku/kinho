#include "ontologies.h"

Ontology::Ontology(){
    setType("ontology");
    addAttribute("value","...");
}

Tag::Tag(){ setType("tag"); }

Category::Category(){ setType("category"); }

//OntologyObject::OntologyObject(){ setType("ontologyObject"); }

Place::Place(){ setType("place"); setCoordinates(0,0); }
void Place::setCoordinates(float _x, float _y) { coordX = _x; coordY = _y; }

Action::Action(){ setType("action"); setLengthM(0); setLengthS(0); }
void Action::setLengthS(float _s) { lengthS = _s; }
void Action::setLengthM(float _min) { lengthMin = _min; }

Web::Web(){ setType("web"); }
