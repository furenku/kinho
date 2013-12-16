#include "storage.h"


//{ attribute

Attribute::Attribute(){
    init();
}

void Attribute::init(){

    boolValue=false;
    charValue=0;
    intValue=0;
    floatValue=0.0f;
    stringValue="";
//range&interpolation
    intRangeMin=intRangeMax=intInterpMin=intInterpMax = 0;
    floatRangeMin=floatInterpMin=0.0f;
    floatRangeMax=floatInterpMax=1.0f;

}

void Attribute::setValue(bool _bool){ boolValue=_bool; }
void Attribute::setValue(char _char){ charValue=_char; }
void Attribute::setValue(int _int) { intValue=_int; }
void Attribute::setValue(float _float) { floatValue = _float; }
void Attribute::setValue(string _string) { stringValue = _string; }
//range
void Attribute::setRange(int _min, int _max) {
    intRangeMin = _min;
    intRangeMax = _max;
}
void Attribute::setRange(float _min, float _max){
    floatRangeMin = _min;
    floatRangeMax = _max;
}
//interpolation
void Attribute::setInterpolation(int _min, int _max){
    intInterpMin = _min;
    intInterpMax = _max;
}
void Attribute::setInterpolation(float _min, float _max){
    floatInterpMin = _min;
    floatInterpMax = _max;
}

bool Attribute::getValue(bool _bool){ return boolValue; }
char Attribute::getValue(char _char){ return charValue;}
int Attribute::getValue(int _int){ return intValue; }
float Attribute::getValue(float _float){ return floatValue; }
string Attribute::getValue(string _string){ return stringValue;}
//range
int Attribute::getRange(int _int){
    int range = intRangeMax-intRangeMin;
    return range;
}
float Attribute::getRange(float _float){
    float range = floatRangeMax-floatRangeMin;
    return range;
}
//interpolation
int Attribute::getInterpolatedValue(int _int){
    //limit value to range
    int x = intValue;
    x = max(x,intRangeMin);
    x = min(x,intRangeMax);
    x/=getRange(0);
    x+=intInterpMin;
    x*=(intInterpMax-intInterpMin);


    return x;

}

float Attribute::getInterpolatedValue(float _float){
    float x = floatValue;
    x = max(x,floatRangeMin);
    x = min(x,floatRangeMax);
    x/=getRange(0);
    x+=floatInterpMin;
    x*=(floatInterpMax-floatInterpMin);
    return x;
}


//}


//{ attribute group

void AttributeGroup::addAttribute(shared_ptr<Attribute> _attr){
    attvec[_attr->getName()]=_attr;
}



void AttributeGroup::addAttribute( string _name, bool _val) {
    shared_ptr<Attribute> attr = make_shared<Attribute>( );
    attr->setInfo(_name, "bool",0);
    attr->setValue(_val);
    attvec[_name] = attr;
}
void AttributeGroup::addAttribute( string _name, char _val) {
    shared_ptr<Attribute> attr = make_shared<Attribute>( );
    attr->setInfo(_name, "char",0);
    attr->setValue(_val);
    attvec[_name] = attr;
}
void AttributeGroup::addAttribute( string _name, int _val) {
    shared_ptr<Attribute> attr = make_shared<Attribute>( );
    attr->setInfo(_name, "int",0);
    attr->setValue(_val);
    attvec[_name] = attr;
}

void AttributeGroup::addAttribute( string _name, float _val) {
    shared_ptr<Attribute> attr = make_shared<Attribute>( );
    attr->setInfo(_name, "float",0);
    attr->setValue(_val);
    attvec[_name] = attr;
}

void AttributeGroup::addAttribute( string _name, string _val) {
    shared_ptr<Attribute> attr = make_shared<Attribute>( );
    attr->setInfo(_name, "string",0);
    attr->setValue(_val);
    attvec[_name] = attr;
}




void AttributeGroup::eraseAttribute(string _name){
    attvec.erase(_name);
}


shared_ptr<Attribute> AttributeGroup::getAttribute(string _name){
    map<string, shared_ptr< Attribute > >::iterator iter;
    iter = attvec.find(_name);

    if(iter!=attvec.end()){
        return iter->second;
    }

}

vector<shared_ptr< Attribute > > AttributeGroup::getAttributesByType(string _type){

    map<string,shared_ptr< Attribute > > m;
    pair<string,shared_ptr< Attribute > > p; // what a map<int, int> is made of
    vector< shared_ptr< Attribute > > v;

    BOOST_FOREACH(p, m) {

      if(p.second->getType()==_type)
        v.push_back(p.second);

    }

    return v;

}


vector<shared_ptr< Attribute > > AttributeGroup::getAttributes() {

    map<string,shared_ptr< Attribute > > m;
    pair<string,shared_ptr< Attribute > > p; // what a map<int, int> is made of
    vector< shared_ptr< Attribute > > v;

    BOOST_FOREACH(p, m) {
        v.push_back(p.second);
    }

    return v;

}

vector<shared_ptr< string > > AttributeGroup::getAttributeTypes() {
    map<string,shared_ptr< Attribute > > m;
    pair<string,shared_ptr< Attribute > > p; // what a map<int, int> is made of
    vector<shared_ptr< string > > v;

    BOOST_FOREACH(p, m) {
        v.push_back( make_shared<string>( p.second->getType() ));
    }
}

vector< shared_ptr< string >  > AttributeGroup::getAttributeNames() {
    map<string,shared_ptr< Attribute > > m;
    pair<string,shared_ptr< Attribute > > p; // what a map<int, int> is made of
    vector<shared_ptr< string > > v;

    BOOST_FOREACH(p, m) {
        v.push_back( make_shared<string>( p.second->getName() ));
    }
}

//}


//{ store object


    AbstractStoreObject::AbstractStoreObject(){
        init();
    }
    AbstractStoreObject::~AbstractStoreObject(){}

    void AbstractStoreObject::init() {
        setInfo("","",0);
    }

    StoreObject::StoreObject(){
        attgrps.push_back(make_shared<AttributeGroup>());
    }

int StoreObject::getIndexByName(vector< shared_ptr<StoreObject> > _objs,string _name){
    int index=-1;
    for (int i=0; i<_objs.size(); i++)
    {
    	if( _objs[i]->getName() == _name) {
            index=i;
            break;
    	}
    }
    return index;
}


int StoreObject::getAttGrpIndexByName(string _name){
    int index=-1;
    for (int i=0; i<attgrps.size(); i++)
    {
    	if( attgrps[i]->getName() == _name) {
            index=i;
            break;
    	}
    }
    return index;
}


void StoreObject::addAttributeGroup(string _name,string _type){
    attgrps.push_back(make_shared<AttributeGroup>());
    attgrps.back()->setName(_name);
    attgrps.back()->setType(_type);

}

void StoreObject::removeAttributeGroup(string _name){
    int index = getAttGrpIndexByName(_name);
    if(index>=0)
        attgrps.erase(attgrps.begin()+index);
}

//addAttr

void StoreObject::addAttribute( string _name, bool _val) {
    getLastGroup()->addAttribute(_name, _val);
}
void StoreObject::addAttribute( string _name, char _val){
    getLastGroup()->addAttribute(_name, _val);
}
void StoreObject::addAttribute( string _name, int _val){
    getLastGroup()->addAttribute(_name, _val);
}
void StoreObject::addAttribute( string _name, float _val){
    getLastGroup()->addAttribute(_name, _val);
}
void StoreObject::addAttribute( string _name, string _val){
    getLastGroup()->addAttribute(_name, _val);
}

void StoreObject::addAttribute( string _grpname, string _name, bool _val){
    int index = getAttGrpIndexByName(_grpname);
    if(index>=0) {
        attgrps[index]->addAttribute(_name,_val);
    }
}
void StoreObject::addAttribute( string _grpname, string _name, char _val){
    int index = getAttGrpIndexByName(_grpname);
    if(index>=0) {
        attgrps[index]->addAttribute(_name,_val);
    }
}
void StoreObject::addAttribute( string _grpname, string _name, int _val){
    int index = getAttGrpIndexByName(_grpname);
    if(index>=0) {
        attgrps[index]->addAttribute(_name,_val);
    }
}
void StoreObject::addAttribute( string _grpname, string _name, float _val){
    int index = getAttGrpIndexByName(_grpname);
    if(index>=0) {
        attgrps[index]->addAttribute(_name,_val);
    }
}
void StoreObject::addAttribute( string _grpname, string _name, string _val){
    int index = getAttGrpIndexByName(_grpname);
    if(index>=0) {
        attgrps[index]->addAttribute(_name,_val);
    }
}
    //set
        //only name



//set
//lastcreated AttributeGroup
void StoreObject::setAttribute( string _name, bool _val){
    getLastGroup()->getAttribute(_name)->setValue(_val);
}
void StoreObject::setAttribute( string _name, char _val){
    getLastGroup()->getAttribute(_name)->setValue(_val);
}
void StoreObject::setAttribute( string _name, int _val){
    getLastGroup()->getAttribute(_name)->setValue(_val);
}
void StoreObject::setAttribute( string _name, float _val){
    getLastGroup()->getAttribute(_name)->setValue(_val);
}
void StoreObject::setAttribute( string _name, string _val){
    getLastGroup()->getAttribute(_name)->setValue(_val);
}
//group & name

void StoreObject::setAttribute( string _grpname, string _name, bool _val){
    int index = getAttGrpIndexByName(_grpname);
    if(index>=0) {
        attgrps[index]->getAttribute(_name)->setValue(_val);
    }
}

void StoreObject::setAttribute( string _grpname, string _name, char _val){
    int index = getAttGrpIndexByName(_grpname);
    if(index>=0) {
        attgrps[index]->getAttribute(_name)->setValue(_val);
    }
}
void StoreObject::setAttribute( string _grpname, string _name, int _val){
    int index = getAttGrpIndexByName(_grpname);
    if(index>=0) {
        attgrps[index]->getAttribute(_name)->setValue(_val);
    }
}
void StoreObject::setAttribute( string _grpname, string _name, float _val){
    int index = getAttGrpIndexByName(_grpname);
    if(index>=0) {
        attgrps[index]->getAttribute(_name)->setValue(_val);
    }
}
void StoreObject::setAttribute( string _grpname, string _name, string _val){
    int index = getAttGrpIndexByName(_grpname);
    if(index>=0) {
        attgrps[index]->getAttribute(_name)->setValue(_val);
    }
}
//get
shared_ptr<AttributeGroup> StoreObject::getAttributeGroup(string _name) {
    int index = getAttGrpIndexByName(_name);
    if(index>=0) {
        return attgrps[index];
    }
}

vector< shared_ptr<AttributeGroup> > StoreObject::getAttributeGroups() {
    return attgrps;
}
vector< shared_ptr<AttributeGroup> > StoreObject::getAttributeGroupsByType(string _type) {
    vector< shared_ptr<AttributeGroup> > v;
    int index=-1;
    for (int i=0; i<attgrps.size(); i++)
    {
    	if( attgrps[i]->getType() == _type) {
            v.push_back(attgrps[i]);
    	}
    }
    return v;

}
shared_ptr<Attribute> StoreObject::getAttribute(string _grpname, string _name){
    shared_ptr<Attribute> attr;
    attr = attgrps[getAttGrpIndexByName(_grpname)]->getAttribute(_name);
    return attr;

}

//behaviour:
shared_ptr<AttributeGroup> StoreObject::getLastGroup() {
    return attgrps.back();
}


//}


//{storage


//add

void Storage::addObject( shared_ptr<StoreObject> _strObj){
    string name = _strObj->getName();
    string type = _strObj->getType();

    map<string, vector< shared_ptr<StoreObject> >  >::iterator iter;
    iter = TypeMap.find( type );

    if(iter==TypeMap.end()){
        TypeMap[type]=vector < shared_ptr<StoreObject> >();
    }
    TypeMap[type].push_back(_strObj);

    NameMap[name]= _strObj;
    IDMap[nextID]= _strObj;
    _strObj->setID(nextID);
    nextID++;

    related[_strObj]=vector < shared_ptr<StoreObject> >();
    children[_strObj]=vector < shared_ptr<StoreObject> >();
    parents[_strObj]=vector < shared_ptr<StoreObject> >();
}

//remove

void Storage::removeObject( shared_ptr<StoreObject> _strObj){
    removeRelated( _strObj);
    removeHierarchy(_strObj);



    map<string, vector< shared_ptr<StoreObject> >  >::iterator iter;
    string type = _strObj->getType();
    iter = TypeMap.find( type );

    if(iter!=TypeMap.end()){
        vector < shared_ptr<StoreObject> > v = TypeMap[type];
        v.erase(remove(v.begin(), v.end(), _strObj), v.end());
    }

    NameMap.erase(  _strObj->getName() );
    IDMap.erase(    _strObj->getID() );
//    _strObj.reset();
}



vector< shared_ptr<int> > Storage::getIDs(){

    pair<int,shared_ptr< StoreObject > > p;
    vector< shared_ptr< int > > v;

    BOOST_FOREACH(p, IDMap) {
        int id = p.first;
        v.push_back( make_shared<int>(id) );
    }

    return v;

}



shared_ptr<StoreObject> Storage::getObject( string _name ){
    map<string, shared_ptr< StoreObject > >::iterator iter;
    iter = NameMap.find(_name);

    if(iter!=NameMap.end()){
        return iter->second;
    }
}
shared_ptr<StoreObject> Storage::getObject( int _id ){
    map<int, shared_ptr< StoreObject > >::iterator iter;
    iter = IDMap.find(_id);

    if(iter!=IDMap.end()){
        return iter->second;
    }


}

vector< shared_ptr<StoreObject> > Storage::getObjectsByType( string _type ){

    map<string, vector< shared_ptr<StoreObject> >  >::iterator iter;
    iter = TypeMap.find(_type);

    if(iter!=TypeMap.end()){
        return iter->second;
    }

}


vector< shared_ptr<StoreObject> > Storage::getObjects(){
    pair<int,shared_ptr< StoreObject > > p;
    vector< shared_ptr< StoreObject > > v;

    /*
    BOOST_FOREACH(p, IDMap) {
        v.push_back( p.second );
    }
    */
    for(map<int,shared_ptr< StoreObject > >::iterator it = IDMap.begin(); it != IDMap.end(); ++it) {
        v.push_back(it->second);
    }

    return v;
}




//}


//{ RELATIONSHIPS


    //set
        void Relationships::setRelated(shared_ptr<StoreObject> _obj1, shared_ptr<StoreObject> _obj2) {
            related[_obj1].push_back(_obj2);
            related[_obj2].push_back(_obj1);
        }

        void Relationships::removeRelated(shared_ptr<StoreObject> _obj1, shared_ptr<StoreObject> _obj2) {
            vector < shared_ptr<StoreObject> > & v1 = getRelated(_obj1);
            vector < shared_ptr<StoreObject> > & v2 = getRelated(_obj2);
            v1.erase(remove(v1.begin(), v1.end(), _obj2), v1.end());
            v2.erase(remove(v2.begin(), v2.end(), _obj1), v2.end());
        }

        void Relationships::setHierarchy(shared_ptr<StoreObject> _obj1, shared_ptr<StoreObject> _obj2){
            children[_obj1].push_back(_obj2);
            parents[_obj2].push_back(_obj1);
        }

        void Relationships::removeHierarchy(shared_ptr<StoreObject> _obj1, shared_ptr<StoreObject> _obj2){
            vector < shared_ptr<StoreObject> > & v1 = getChildren(_obj1);
            vector < shared_ptr<StoreObject> > & v2 = getParents(_obj2);
            v1.erase(remove(v1.begin(), v1.end(), _obj2), v1.end());
            v2.erase(remove(v2.begin(), v2.end(), _obj1), v2.end());

        }

        void Relationships::removeRelated(shared_ptr<StoreObject> _obj) {
            vector < shared_ptr<StoreObject> > vr = related[_obj];

            for (u_int i=0; i < vr.size(); i++) {
                vector < shared_ptr<StoreObject> > & vrr=getRelated(vr[i]);
                vrr.erase(remove(vrr.begin(), vrr.end(), _obj), vrr.end());
            }
            vr.clear();

            related.erase(_obj);
        }

        void Relationships::removeHierarchy(shared_ptr<StoreObject> _obj){
            vector < shared_ptr<StoreObject> > vc = children[_obj];
            vector < shared_ptr<StoreObject> > vp = parents[_obj];



            for (u_int i=0; i<vc.size(); i++) {
                vector < shared_ptr<StoreObject> > & vcp = getParents(vc[i]);
                vcp.erase(remove(vcp.begin(), vcp.end(), _obj), vcp.end());
            }
            for (u_int i=0; i<vp.size(); i++) {
                vector < shared_ptr<StoreObject> > & vpc = getChildren(vp[i]);
                vpc.erase(remove(vpc.begin(), vpc.end(), _obj), vpc.end());
            }
            vp.clear();
            vc.clear();
            children.erase(_obj);
            parents.erase(_obj);

        }


    //get
        vector< shared_ptr<StoreObject> > & Relationships::getParents( shared_ptr<StoreObject> _obj ) {
            return parents[_obj];
        }

        vector< shared_ptr<StoreObject> > & Relationships::getChildren( shared_ptr<StoreObject> _obj ){
            return children[_obj];
        }

        vector< shared_ptr<StoreObject> > & Relationships::getRelated( shared_ptr<StoreObject> _obj ){
            return related[_obj];
        }

        vector< shared_ptr<StoreObject> > Relationships::getDescendants( shared_ptr<StoreObject> _obj ) {
            descendants.clear();
            addAllChildren(_obj);
            return descendants;
        }

        vector< shared_ptr<StoreObject> > Relationships::getAncestors( shared_ptr<StoreObject> _obj ) {
            ancestors.clear();
            addAllAncestors(_obj);
            return ancestors;
        }

        vector< shared_ptr<StoreObject> > Relationships::getSiblings( shared_ptr<StoreObject> _obj ){
            vector< shared_ptr<StoreObject> > parentsVec = parents[_obj];
            for(u_int i = 0; i<parentsVec.size(); i++ ) {
                vector<shared_ptr<StoreObject> > childrenVec = getChildren(parentsVec[i]);
                for(u_int j = 0; j<childrenVec.size(); j++ ) {
                    siblings.push_back(childrenVec[j]);
                }
            }
            return siblings;
        }



        void Relationships::addAllChildren( shared_ptr<StoreObject> _obj )  {
            vector< shared_ptr<StoreObject> > & vc = getChildren( _obj );

            for(int i = 0 ; i < vc.size(); i++ ) {
                descendants.push_back( vc[i] );
                cout << "fkkkp"<<4 << endl;
            }
            for(int i = 0 ; i < vc.size(); i++ ) {
                cout << vc[i]->getName()<<5 << endl;
                addAllChildren( vc[i] );

            }

        }


        void Relationships::addAllAncestors( shared_ptr<StoreObject> _obj )  {

            vector< shared_ptr<StoreObject> > & vp = getParents( _obj );
            for(int i = 0 ; i < vp.size(); i++ )  {
                ancestors.push_back( vp[i] );
            }
            for(int i = 0 ; i < vp.size(); i++ )  {
                addAllAncestors( vp[i] );
            }


        }


//}


//{ xmlmanager

//void XMLManager::setRelated( shared_ptr<StoreObject>,shared_ptr<StoreObject>){}
//void XMLManager::setHierarchy( shared_ptr<StoreObject>,shared_ptr<StoreObject>){}
//void XMLManager::eraseRelationships(shared_ptr<StoreObject> _strobj){}
//void XMLManager::eraseRelationships(shared_ptr<StoreObject> _strobj1, shared_ptr<StoreObject> _strobj2){}
////xml
//void XMLManager::addAndPushTag(string _tag){}
//void XMLManager::popTag(){}
//void XMLManager::addToTag(shared_ptr<StoreObject> _strobj, string _tag){}
////read
//string XMLManager::readTag(string _tag1, string _tag2){}
//void XMLManager::writeObject(shared_ptr<StoreObject> _strobj) {
//}
//void XMLManager::deleteObject(shared_ptr<StoreObject> _strobj) {
//    eraseRelationships(_strobj);
//}
//vector< shared_ptr<StoreObject> > XMLManager::loadObjects(){
//    //navigate xml
//    //check type
//    //factory->make obj func
//}
//


//write
//object
//association
//void XMLManager::setRelated( shared_ptr<StoreObject>,shared_ptr<StoreObject>){}
//void XMLManager::setHierarchy( shared_ptr<StoreObject>,shared_ptr<StoreObject>){}
//void XMLManager::eraseRelationships(shared_ptr<StoreObject> _strobj){}
//void XMLManager::eraseRelationships(shared_ptr<StoreObject> _strobj1, shared_ptr<StoreObject> _strobj2){}
////xml
//void XMLManager::addAndPushTag(string _tag){}
//void XMLManager::popTag(){}
//void XMLManager::addToTag(shared_ptr<StoreObject> _strobj, string _tag){}
////read
//string XMLManager::readTag(string _tag1, string _tag2){}
//void XMLManager::writeObject(shared_ptr<StoreObject> _strobj) {
//}
//void XMLManager::deleteObject(shared_ptr<StoreObject> _strobj) {
//    eraseRelationships(_strobj);
//}
//vector< shared_ptr<StoreObject> > XMLManager::loadObjects(){
//    //navigate xml
//    //check type
//    //factory->make obj func
//}
//

//}

