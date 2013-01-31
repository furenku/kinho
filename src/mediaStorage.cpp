#include "mediaStorage.h"


//{

//}
//{ clip


void MediaHolder::setAuthor(string _str){
    author=_str;
}
void MediaHolder::setDescription(string _str){
    description=_str;
}
void MediaHolder::setDate(string _str){
    date=_str;
}
void MediaHolder::setAudioTrack(int _track){
    audioTrack=_track;
}
void MediaHolder::setMarker( shared_ptr<Marker> _marker, float _min, float _len ){
    _marker->setPosition(_min);
    _marker->setLength(_len);
}
void MediaHolder::setParam( shared_ptr<Param> _param, float _val ){
//    _param->setValue(_val);
}

string MediaHolder::getAuthor(){ return author; }

string MediaHolder::getDescription(){ return description; }

string MediaHolder::getDate(){ return date; }

int MediaHolder::getAudioTrack(){ return audioTrack; }

shared_ptr<Marker> MediaHolder::getMarker(string _name){
    vector< shared_ptr<StoreObject> > v;
    for (int i=0; i<markers.size(); i++)
    	v.push_back(markers[i]);

    int index =getIndexByName(v,_name);
    return markers[index];
}

//shared_ptr<Marker> MediaHolder::getParam( string _name ){
//
//}





void MediaHolder::addMarker( string _name, float _pos, float _len, string _desc ) {
    shared_ptr<Marker>  mrkr = make_shared<Marker>();
    mrkr->setName(_name);
    mrkr->setPosition(_pos);
    mrkr->setLength(_len);
    mrkr->setDescription(_desc);
    markers.push_back(mrkr);
}

void MediaHolder::addMarker( shared_ptr<Marker> _marker ) {
    markers.push_back( _marker );
}
void MediaHolder::removeMarker( shared_ptr<Marker> _marker ) {
    markers.erase(remove(markers.begin(),markers.end(),_marker), markers.end());
}
//void MediaHolder::removeMarker( string _name) {
//    int index = getIndexByName(markers,_name);
//    markers.erase(markers.begin()+index);
//}

void MediaHolder::addMarkerAttributes(){
    for (int i=0; i<markers.size(); i++)
    {
        addAttribute("marker_"+ofToString(i)+"_name",markers[i]->getName());
        addAttribute("marker_"+ofToString(i)+"_description",markers[i]->getDescription());
        addAttribute("marker_"+ofToString(i)+"_pos",markers[i]->getPosition());
        addAttribute("marker_"+ofToString(i)+"_length",markers[i]->getLength());
//            	addAttribute("marker_"+ofToString(i)+"r",markers[i]->getLength());
//            	addAttribute("marker_"+ofToString(i)+"g",markers[i]->getLength());
//            	addAttribute("marker_"+ofToString(i)+"b",markers[i]->getLength());
    }
}
void MediaHolder::addParamAttributes(){
    for (int i=0; i<markers.size(); i++)
    {
        addAttribute("param_"+ofToString(i)+"_name",params[i]->getName());
        addAttribute("param_"+ofToString(i)+"_pos",params[i]->getValue());
    }
}

vector < shared_ptr<Marker> > & MediaHolder::getMarkers(){
    return markers;
}

//}


