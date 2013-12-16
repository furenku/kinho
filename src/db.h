/*//#ifndef DB_H
//#define DB_H

//#include "testApp.h"

//ALMACENAMIENTO
class AbstractStoreObject {
    public:
    AbstractStoreObject();

    virtual ~AbstractStoreObject();

    virtual void init();

//funcs
    //set
        void setName(string _name);
        void setType(string _type );
        void setID(int _id;
        void setInfo(string _name, string _type, int _id);

    //get
        string getName();
        string getType();
        int getID();

    protected:
        //atts
        string name;
        string type;
        int id;
};



class Attribute: public AbstractStoreObject {

    public:

    Attribute();

    void init();

    //value
    //value
    //funcs
    //set
        //value
            void setValue(bool _bool);
            void setValue(char _char);
            void setValue(int _int);
            void setValue(float _float);
            void setValue(string _string);
        //range
            void setRange(char _min, char _max);
            void setRange(int _min, int _max);
            void setRange(float _min, float _max);
        //interpolation
            void setInterpolation(int _min, int _max);
            void setInterpolation(float _min, float _max);
    //get
        //value
            bool getValue(bool _bool);
            char getValue(char _char);
            int getValue(int _int);
            float getValue(float _float);
            string getValue(string _string);
        //range
            int getRange(int _int);
            float getRange(float _float);
        //interpolation
            int getInterpolatedValue(int _int);
            float getInterpolatedValue(float _float);


        protected:
            bool boolValue;
            char charValue;
            int intValue;
            float floatValue;
            string stringValue;
        //range&interpolation
            int intRangeMin, intRangeMax, intInterpMin, intInterpMax;
            float floatRangeMin, floatRangeMax, floatInterpMin, floatInterpMax;

};


class AttributeGroup: public Attribute {
    public:
        AttributeGroup(){}
    //funcs

        void addAttribute(shared_ptr<Attribute> _attr);

        void addAttribute( string _name, bool _val);
        void addAttribute( string _name, char _val);
        void addAttribute( string _name, int _val);
        void addAttribute( string _name, float _val);
        void addAttribute( string _name, string _val);

        void eraseAttribute(string _name);

        shared_ptr<Attribute> getAttribute(string _name);

        vector<shared_ptr< Attribute > >    getAttributesByType(string _type);
        vector<shared_ptr< Attribute > >    getAttributes();
        vector<shared_ptr< string > >       getAttributeTypes();
        vector<shared_ptr< string > >       getAttributeNames();


    protected://atts
        map<string, shared_ptr< Attribute > > attvec;

};

class StoreObject: virtual public AttributeGroup{
    public:
        StoreObject();


    //funcs
    //f
    //store

        void addAttributeGroup(string _name,string _type);
        void removeAttributeGroup(string _name);
    //addAttr

        void addAttribute( string _name, bool _val);
        void addAttribute( string _name, char _val);
        void addAttribute( string _name, int _val);
        void addAttribute( string _name, float _val);
        void addAttribute( string _name, string _val);
        void addAttribute( string _grpname, string _name, bool _val);
        void addAttribute( string _grpname, string _name, char _val);
        void addAttribute( string _grpname, string _name, int _val);
        void addAttribute( string _grpname, string _name, float _val);
        void addAttribute( string _grpname, string _name, string _val);
    //set
        //only name

// works on last
//created AttributeGroup

        void setAttribute( string _name, bool _val);
        void setAttribute( string _name, char _val);
        void setAttribute( string _name, int _val);
        void setAttribute( string _name, float _val);
        void setAttribute( string _name, string _val);
    //group & name
        void setAttribute( string _grpname, string _name, bool _val);
        void setAttribute( string _grpname, string _name, char _val);
        void setAttribute( string _grpname, string _name, int _val);
        void setAttribute( string _grpname, string _name, float _val);
        void setAttribute( string _grpname, string _name, string _val);
    //get
        int                                     getAttGrpIndexByName(string _name);
        shared_ptr<AttributeGroup>              getAttributeGroup(string _name);
        vector< shared_ptr<AttributeGroup> >    getAttributeGroups();
        vector< shared_ptr<AttributeGroup> >    getAttributeGroupsByType(string _type);
        shared_ptr<Attribute>                   getAttribute(string _grpname, string _name);
    //behaviour:
        shared_ptr<AttributeGroup> getLastGroup();


    protected:
    //atts
        vector<shared_ptr<AttributeGroup> > attgrps;



};

class XMLManager: public ofxXmlSettings {
    public:
        XMLManager(){}

        //funciones
            //file
                void openFile(string _filename);
                void createFile(string _filename);
            //write
            //object
                void writeObject(shared_ptr<StoreObject> _strobj);
                void deleteObject(shared_ptr<StoreObject> _strobj);
            //association
                void setRelated( shared_ptr<StoreObject>,shared_ptr<StoreObject>);
                void setHierarchy( shared_ptr<StoreObject>,shared_ptr<StoreObject>);
                void eraseRelationships(shared_ptr<StoreObject> _strobj);
                void eraseRelationships(shared_ptr<StoreObject> _strobj1, shared_ptr<StoreObject> _strobj2);
            //xml
                void addAndPushTag(string _tag);
                void popTag();
                void addToTag(shared_ptr<StoreObject> _strobj, string _tag);
            //read
                string readTag(string _tag1, string _tag2);
                vector< shared_ptr<StoreObject> > loadObjects();
                    //navigate xml
                    //check type
                    //factory->make obj func
            //navigate
        protected:
            string filename;


};













class Relationships: public StoreObject{
    public:
    Relationships(){}

        //funcs

    //set
        void setRelated(shared_ptr<StoreObject> _obj1, shared_ptr<StoreObject> _obj2) {
            related[_obj1].push_back(_obj2);
            related[_obj2].push_back(_obj1);
        }
        void removeRelated(shared_ptr<StoreObject> _obj1, shared_ptr<StoreObject> _obj2) {
            related[_obj1].push_back(_obj2);
            related[_obj2].push_back(_obj1);
        }
        void setHierarchy(shared_ptr<StoreObject> _obj1, shared_ptr<StoreObject> _obj2){
            children[_obj1].push_back(_obj2);
            parents[_obj2].push_back(_obj1);
        }
        void removeHierarchy(shared_ptr<StoreObject> _obj1, shared_ptr<StoreObject> _obj2){
            children[_obj1].push_back(_obj2);
            parents[_obj2].push_back(_obj1);
        }
    //get
        vector< shared_ptr<StoreObject> > getParents( shared_ptr<StoreObject> _obj ) {
            return parents[_obj];
        }
        vector< shared_ptr<StoreObject> > getChildren( shared_ptr<StoreObject> _obj ){
            return children[_obj];
        }


        vector< shared_ptr<StoreObject> > getSiblings( shared_ptr<StoreObject> _obj ){
            vector< shared_ptr<StoreObject> > parentsVec = parents[_obj];
            for(int i = 0; i<parentsVec.size(); i++ ) {
                vector<shared_ptr<StoreObject> > childrenVec = getChildren(parentsVec[i]);
                for(int j = 0; j<childrenVec.size(); j++ ) {
                    siblings.push_back(childrenVec[j]);
                }
            }
            return siblings;
        }


    protected:
        map < shared_ptr<StoreObject>, vector< shared_ptr<StoreObject> > > parents;
        map < shared_ptr<StoreObject>, vector< shared_ptr<StoreObject> > > children;
        map < shared_ptr<StoreObject>, vector< shared_ptr<StoreObject> > > related;
        vector<shared_ptr<StoreObject> > siblings;

};



class Storage: public StoreObject, virtual public Relationships {
    public:
        Storage(){ init(); }

        void init() {}
        //Funcs
        //get
        vector< shared_ptr<int> > getIDs();
        shared_ptr<StoreObject> getObject( string _name );
        shared_ptr<StoreObject> getObject( int _id );
        vector< shared_ptr<StoreObject> > getObjectsByType( string _type );
        vector< shared_ptr<StoreObject> > getObjects();
        //add
        void addObject( shared_ptr<StoreObject> _strObj);

    protected:
        map < int, shared_ptr<StoreObject> > IdMap;
        map < string, vector< shared_ptr<StoreObject> > > TypeMap;
        map < string, shared_ptr<StoreObject> > NameMap;
        map < string, vector< shared_ptr<StoreObject> > >::iterator typeIter;

};




class DBManager: public Storage {
    public:
        DBManager(){}
    //f
        //write
        void writeObject(shared_ptr<StoreObject> _obj) {
            xml->writeObject(_obj);
        }
        void deleteObject(shared_ptr<StoreObject> _obj) {
            xml->writeObject(_obj);
        }
        void createTag(string _name) {
            xml->addAndPushTag(_name);
        }
        void closeTag() {
            xml->popTag();
        }
    protected:
        //atts
        shared_ptr<XMLManager> xml;

};


















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
