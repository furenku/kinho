#pragma once

#ifndef storage_h
#define storage_h

//{ clases


#include <map>
#include <tr1/memory>
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>


using boost::shared_ptr;
using boost::enable_shared_from_this;
using boost::dynamic_pointer_cast;
using boost::make_shared;



#include "ofMain.h"
#include "ofxXmlSettings.h"

//ALMACENAMIENTO
class AbstractStoreObject {
    public:
    AbstractStoreObject(){
        init();
    }
    virtual ~AbstractStoreObject(){}

    virtual void init() {
        setInfo("","",0);
    }

//funcs
    //set
        void setName(string _name) { name = _name; }
        void setType(string _type ) { type = _type; }
        void setID(int _id) { id = _id; }
        void setInfo(string _name, string _type, int _id) {
            setName(_name); setType(_type); setID(_id);
        }
    //get
        string getName() { return name; }
        string getType() { return type; }
        int getID() { return id; }

    protected:
        //atts
        string name;
        string type;
        int id;
};



class Attribute: public AbstractStoreObject {

    public:

    Attribute(){
        init();
    }

    void init(){

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
        StoreObject(){
            attgrps.push_back(make_shared<AttributeGroup>());
        }


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
        int                                     getIndexByName(vector< shared_ptr<StoreObject> > _objs,string _name);
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
            vector < shared_ptr<StoreObject> > & v1 = getRelated(_obj1);
            vector < shared_ptr<StoreObject> > & v2 = getRelated(_obj2);
            v1.erase(remove(v1.begin(), v1.end(), _obj2), v1.end());
            v2.erase(remove(v2.begin(), v2.end(), _obj1), v2.end());
        }

        void setHierarchy(shared_ptr<StoreObject> _obj1, shared_ptr<StoreObject> _obj2){
            children[_obj1].push_back(_obj2);
            parents[_obj2].push_back(_obj1);
        }

        void removeHierarchy(shared_ptr<StoreObject> _obj1, shared_ptr<StoreObject> _obj2){
            vector < shared_ptr<StoreObject> > & v1 = getChildren(_obj1);
            vector < shared_ptr<StoreObject> > & v2 = getParents(_obj2);
            v1.erase(remove(v1.begin(), v1.end(), _obj2), v1.end());
            v2.erase(remove(v2.begin(), v2.end(), _obj1), v2.end());

        }

        void removeRelated(shared_ptr<StoreObject> _obj) {
            vector < shared_ptr<StoreObject> > vr = related[_obj];

            for (u_int i=0; i < vr.size(); i++) {
                vector < shared_ptr<StoreObject> > & vrr=getRelated(vr[i]);
                vrr.erase(remove(vrr.begin(), vrr.end(), _obj), vrr.end());
            }
            vr.clear();

            related.erase(_obj);
        }

        void removeHierarchy(shared_ptr<StoreObject> _obj){
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
        vector< shared_ptr<StoreObject> > & getParents( shared_ptr<StoreObject> _obj ) {
            return parents[_obj];
        }

        vector< shared_ptr<StoreObject> > & getChildren( shared_ptr<StoreObject> _obj ){
            return children[_obj];
        }

        vector< shared_ptr<StoreObject> > & getRelated( shared_ptr<StoreObject> _obj ){
            return related[_obj];
        }

        vector< shared_ptr<StoreObject> > getDescendants( shared_ptr<StoreObject> _obj ) {
            descendants.clear();
            addAllChildren(_obj);
            return descendants;
        }

        vector< shared_ptr<StoreObject> > getAncestors( shared_ptr<StoreObject> _obj ) {
            ancestors.clear();
            addAllAncestors(_obj);
            return ancestors;
        }

        vector< shared_ptr<StoreObject> > getSiblings( shared_ptr<StoreObject> _obj ){
            vector< shared_ptr<StoreObject> > parentsVec = parents[_obj];
            for(u_int i = 0; i<parentsVec.size(); i++ ) {
                vector<shared_ptr<StoreObject> > childrenVec = getChildren(parentsVec[i]);
                for(u_int j = 0; j<childrenVec.size(); j++ ) {
                    siblings.push_back(childrenVec[j]);
                }
            }
            return siblings;
        }



        void addAllChildren( shared_ptr<StoreObject> _obj )  {
            cout << "fkkkp"<<1 << endl;
            vector< shared_ptr<StoreObject> > & vc = getChildren( _obj );

            cout << "fkkkp"<<3 << endl;
            for(int i = 0 ; i < vc.size(); i++ ) {
                descendants.push_back( vc[i] );
                cout << "fkkkp"<<4 << endl;
            }
            for(int i = 0 ; i < vc.size(); i++ ) {
                cout << vc[i]->getName()<<5 << endl;
                addAllChildren( vc[i] );

            }

        }


        void addAllAncestors( shared_ptr<StoreObject> _obj )  {

            vector< shared_ptr<StoreObject> > & vp = getParents( _obj );

            for(int i = 0 ; i < vp.size(); i++ )  {
                ancestors.push_back( vp[i] );
            }
            for(int i = 0 ; i < vp.size(); i++ )  {
                addAllAncestors( vp[i] );
            }


        }



    protected:
        map < shared_ptr<StoreObject>, vector< shared_ptr<StoreObject> > > parents;
        map < shared_ptr<StoreObject>, vector< shared_ptr<StoreObject> > > children;
        map < shared_ptr<StoreObject>, vector< shared_ptr<StoreObject> > > related;

        vector< shared_ptr<StoreObject> > descendants, ancestors, siblings;

};



class Storage:  public Relationships {
    public:
        Storage(){ init(); }

        void init() { nextID=0; }
        //Funcs
        //get
        vector< shared_ptr<int> > getIDs();
        shared_ptr<StoreObject> getObject( string _name );
        shared_ptr<StoreObject> getObject( int _id );
        vector< shared_ptr<StoreObject> > getObjectsByType( string _type );
        vector< shared_ptr<StoreObject> > getObjects();
        //add:
        void addObject( shared_ptr<StoreObject> _strObj);
        void removeObject( shared_ptr<StoreObject> _strObj);

    protected:
        map < int, shared_ptr<StoreObject> > IDMap;
        map < string, vector< shared_ptr<StoreObject> > > TypeMap;
        map < string, shared_ptr<StoreObject> > NameMap;
        map < string, vector< shared_ptr<StoreObject> > >::iterator typeIter;

        int nextID;

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

        void loadObjects(){}

    protected:
        //atts
        shared_ptr<XMLManager> xml;
        string xmlFile;

};

















/*

        Hierarchy
        Clip
        DBManager

            SessionManager
            KinhoManager
            ArchivoManager
            InputManager
        Attribute
    Factory
        //atts
        //funcs
*/






class TestObj1: public StoreObject{
    public:
        TestObj1(){
            init();
        }

        void init(){
            addAttributeGroup("testatts1","float");
            addAttribute("testval1",0.25f);
            addAttribute("testval2",0.35f);
            addAttributeGroup("testatts2","string");
            addAttribute("testval3","haha");
            addAttribute("testval4","tutu");
        }

};

class TestObj2: public StoreObject{
 public:
        TestObj2(){
            init();
        }

        void init(){
            addAttributeGroup("testatts1","bool");
            addAttribute("testval1",true);
            addAttribute("testval2",false);
            addAttributeGroup("testatts2","int");
            addAttribute("testval3",132);
            addAttribute("testval4",12);
        }

};


class TestDB: public DBManager {
    public:
        TestDB(){}
    void addObj1(string _name, float _x, float _y){
        shared_ptr<StoreObject>  obj = make_shared<TestObj1>();
        obj->setInfo(_name,"testobj1",0);
        obj->addAttributeGroup("xy","float");
        obj->addAttribute("x",_x);
        obj->addAttribute("y",_y);
        addObject(obj);

    }
    void addObj2(string _name, float _x, float _y){
        shared_ptr<StoreObject>  obj = make_shared<TestObj2>();
        obj->setInfo(_name,"testobj2",0);
        obj->addAttributeGroup("xy","float");
        obj->addAttribute("x",_x);
        obj->addAttribute("y",_y);
        addObject(obj);

    }

    //protected:

};
















//}






#endif
