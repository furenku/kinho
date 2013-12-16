
#include "db.h"
/*
    AbstractStoreObject::AbstractStoreObject(){
        init();
    }
    virtual AbstractStoreObject::~AbstractStoreObject(){}

    virtual void AbstractStoreObject::init() {
        setInfo("","",0);
    }

//funcs
    //set
        void AbstractStoreObject::setName(string _name) { name = _name; }
        void AbstractStoreObject::setType(string _type ) { type = _type; }
        void AbstractStoreObject::setID(int _id) { id = _id; }
        void AbstractStoreObject::setInfo(string _name, string _type, int _id) {
            setName(_name); setType(_type); setID(_id);
        }
    //get
        string AbstractStoreObject::getName() { return name; }
        string AbstractStoreObject::getType() { return type; }
        int AbstractStoreObject::getID() { return id; }




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

    //value
    //value
    //funcs
    //set
        //value
            void Attribute::setValue(bool _bool);
            void Attribute::setValue(char _char);
            void Attribute::setValue(int _int);
            void Attribute::setValue(float _float);
            void Attribute::setValue(string _string);
        //range
            void Attribute::setRange(char _min, char _max);
            void Attribute::setRange(int _min, int _max);
            void Attribute::setRange(float _min, float _max);
        //interpolation
            void Attribute::setInterpolation(int _min, int _max);
            void Attribute::setInterpolation(float _min, float _max);
    //get
        //value
            bool Attribute::getValue(bool _bool);
            char Attribute::getValue(char _char);
            int Attribute::getValue(int _int);
            float Attribute::getValue(float _float);
            string Attribute::getValue(string _string);
        //range
            int Attribute::getRange(int _int);
            float Attribute::getRange(float _float);
        //interpolation
            int Attribute::getInterpolatedValue(int _int);
            float Attribute::getInterpolatedValue(float _float);





        AttributeGroup::AttributeGroup(){}
    //funcs

        void AttributeGroup::addAttribute(shared_ptr<Attribute> _attr);

        void AttributeGroup::addAttribute( string _name, bool _val);
        void AttributeGroup::addAttribute( string _name, char _val);
        void AttributeGroup::addAttribute( string _name, int _val);
        void AttributeGroup::addAttribute( string _name, float _val);
        void AttributeGroup::addAttribute( string _name, string _val);

        void AttributeGroup::eraseAttribute(string _name);

        shared_ptr<Attribute> getAttribute(string _name);

        vector<shared_ptr< Attribute > >    AttributeGroup::getAttributesByType(string _type);
        vector<shared_ptr< Attribute > >    AttributeGroup::getAttributes();
        vector<shared_ptr< string > >       AttributeGroup::getAttributeTypes();
        vector<shared_ptr< string > >       AttributeGroup::getAttributeNames();




        StoreObject::StoreObject(){
            attgrps.push_back(make_shared<AttributeGroup>());
        }


    //funcs
    //f
    //store

        void StoreObject::addAttributeGroup(string _name,string _type);
        void StoreObject::removeAttributeGroup(string _name);
    //addAttr

        void StoreObject::addAttribute( string _name, bool _val);
        void StoreObject::addAttribute( string _name, char _val);
        void StoreObject::addAttribute( string _name, int _val);
        void StoreObject::addAttribute( string _name, float _val);
        void StoreObject::addAttribute( string _name, string _val);
        void StoreObject::addAttribute( string _grpname, string _name, bool _val);
        void StoreObject::addAttribute( string _grpname, string _name, char _val);
        void StoreObject::addAttribute( string _grpname, string _name, int _val);
        void StoreObject::addAttribute( string _grpname, string _name, float _val);
        void StoreObject::addAttribute( string _grpname, string _name, string _val);
    //set
        //only name

// works on last
//created AttributeGroup

        void StoreObject::setAttribute( string _name, bool _val);
        void StoreObject::setAttribute( string _name, char _val);
        void StoreObject::setAttribute( string _name, int _val);
        void StoreObject::setAttribute( string _name, float _val);
        void StoreObject::setAttribute( string _name, string _val);
    //group & name
        void StoreObject::setAttribute( string _grpname, string _name, bool _val);
        void StoreObject::setAttribute( string _grpname, string _name, char _val);
        void StoreObject::setAttribute( string _grpname, string _name, int _val);
        void StoreObject::setAttribute( string _grpname, string _name, float _val);
        void StoreObject::setAttribute( string _grpname, string _name, string _val);
    //get
        int                                     StoreObject::getAttGrpIndexByName(string _name);
        shared_ptr<AttributeGroup>              StoreObject::getAttributeGroup(string _name);
        vector< shared_ptr<AttributeGroup> >    StoreObject::getAttributeGroups();
        vector< shared_ptr<AttributeGroup> >    getAttributeGroupsByType(string _type);
        shared_ptr<Attribute>                   getAttributeStoreObject::(string _grpname, string _name);
    //behaviour:
        shared_ptr<AttributeGroup> StoreObject::getLastGroup();






        XMLManager::XMLManager(){}

        //funciones
            //file
                void XMLManager::openFile(string _filename);
                void XMLManager::createFile(string _filename);
            //write
            //object
                void XMLManager::writeObject(shared_ptr<StoreObject> _strobj);
                void XMLManager::deleteObject(shared_ptr<StoreObject> _strobj);
            //association
                void XMLManager::setRelated( shared_ptr<StoreObject>,shared_ptr<StoreObject>);
                void XMLManager::setHierarchy( shared_ptr<StoreObject>,shared_ptr<StoreObject>);
                void XMLManager::eraseRelationships(shared_ptr<StoreObject> _strobj);
                void XMLManager::eraseRelationships(shared_ptr<StoreObject> _strobj1, shared_ptr<StoreObject> _strobj2);
            //xml
                void XMLManager::addAndPushTag(string _tag);
                void XMLManager::popTag();
                void XMLManager::addToTag(shared_ptr<StoreObject> _strobj, string _tag);
            //read
                string XMLManager::readTag(string _tag1, string _tag2);
                vector< shared_ptr<StoreObject> > XMLManager::loadObjects();
                    //navigate xml
                    //check type
                    //factory->make obj func
            //navigate




    Relationships::Relationships(){}

        //funcs

    //set
        void Relationships::setRelated(shared_ptr<StoreObject> _obj1, shared_ptr<StoreObject> _obj2) {
            related[_obj1].push_back(_obj2);
            related[_obj2].push_back(_obj1);
        }
        void Relationships::removeRelated(shared_ptr<StoreObject> _obj1, shared_ptr<StoreObject> _obj2) {
            related[_obj1].push_back(_obj2);
            related[_obj2].push_back(_obj1);
        }
        void Relationships::setHierarchy(shared_ptr<StoreObject> _obj1, shared_ptr<StoreObject> _obj2){
            children[_obj1].push_back(_obj2);
            parents[_obj2].push_back(_obj1);
        }
        void Relationships::removeHierarchy(shared_ptr<StoreObject> _obj1, shared_ptr<StoreObject> _obj2){
            children[_obj1].push_back(_obj2);
            parents[_obj2].push_back(_obj1);
        }
    //get
        vector< shared_ptr<StoreObject> > Relationships::getParents( shared_ptr<StoreObject> _obj ) {
            return parents[_obj];
        }
        vector< shared_ptr<StoreObject> > Relationships::getChildren( shared_ptr<StoreObject> _obj ){
            return children[_obj];
        }


        vector< shared_ptr<StoreObject> > Relationships::getSiblings( shared_ptr<StoreObject> _obj ){
            vector< shared_ptr<StoreObject> > parentsVec = parents[_obj];
            for(int i = 0; i<parentsVec.size(); i++ ) {
                vector<shared_ptr<StoreObject> > childrenVec = getChildren(parentsVec[i]);
                for(int j = 0; j<childrenVec.size(); j++ ) {
                    siblings.push_back(childrenVec[j]);
                }
            }
            return siblings;
        }







        Storage::Storage(){ init(); }

        void Storage::init() {}
        //Funcs
        //get
        vector< shared_ptr<int> > Storage::getIDs();
        shared_ptr<StoreObject> Storage::getObject( string _name );
        shared_ptr<StoreObject> Storage::getObject( int _id );
        vector< shared_ptr<StoreObject> > Storage::getObjectsByType( string _type );
        vector< shared_ptr<StoreObject> > Storage::getObjects();
        //add
        void Storage::addObject( shared_ptr<StoreObject> _strObj);






        DBManager::DBManager(){}
    //f
        //write
        void DBManager::writeObject(shared_ptr<StoreObject> _obj) {
            xml->writeObject(_obj);
        }
        void DBManager::deleteObject(shared_ptr<StoreObject> _obj) {
            xml->writeObject(_obj);
        }
        void DBManager::createTag(string _name) {
            xml->addAndPushTag(_name);
        }
        void DBManager::closeTag() {
            xml->popTag();
        }









*/




/*

class TestObj1: public StoreObject{
    public:
        TestObj1(){
            init();
        }

        void init(){
//            addAttributeGroup("testatts1","float");
//            addAttribute("testval1",0.25f);
//            addAttribute("testval2",0.35f);
//            addAttributeGroup("testatts2","string");
//            addAttribute("testval3","haha");
//            addAttribute("testval4","tutu");
        }

};

class TestObj2: public StoreObject{
 public:
        TestObj2(){
            init();
        }

        void init(){
            addAttributeGroup("testatts1","bool");
            addAttribute("testval1",false);
            addAttribute("testval2",false);
            addAttributeGroup("testatts2","int");
            addAttribute("testval3",132);
            addAttribute("testval4",12);
        }

};


class TestDB: public DBManager {
    public:
        TestDB(){}

    //protected:

};





*/


/*

        Hierarchy
        Clip
        DBManager
            SessionManager
                string
                    XMLpath
                    libraryFile
                    kinhoFile
                        scenes
                        outputs
                    archivoFile
                ()
                    type="sessionManager"
            LibraryManager
                protected:
                    //atts
                        Bimap?
                        vector< shared_ptr< Clip > >
                        vector< shared_ptr< Relationship > >
                        vector< shared_ptr< Ontologies > >
                    //funcs
                        //API
                            add
                                clip
                                    addClip(shared_ptr<Clip>)
                                    removeClip(shared_ptr<Clip>
                                ont
                                    addOntology(shared_ptr<Ontology>)
                                    removeOntology(shared_ptr<Ontology>)
                                        actualizar relaciones!!
                                        o ya se hace automaticamente con los metodos detach?
                            relate
                                relateClipOntology(shared_ptr<Clip>,shared_ptr<Ontology>)
                            get
                                shared_ptr<Clip>
                                    getClip()
                                vector< shared_ptr<Cllip> >
                                    getClips(shared_ptr<Ontology>)
                                shared_ptr<Ontology>
                                    getOntology( shared_ptr<Clip> )
                                    getOntology(string name)
                                    getOntology(int id)
                                vector< shared_ptr<Ontology> >
                                    getOntologies(shared_ptr<Clip>)
                                    getOntologies(string name)
                                    getOntologies(int id)
                ()
            SessionManager
            KinhoManager
            ArchivoManager
            InputManager
        Attribute
    Factory
        //atts
        //funcs
*/


