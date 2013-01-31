/*

class Clip: public Observable{
    public:
        Clip(){
            name = "default";
            description = "a default clip";
            filename = "movies/blood01.mov";
            tags.push_back("tag1");
            tags.push_back("tag2");
            aspectRatio = 1.33f;
            createEvents();
        }

        void createEvents(){
            saveEvent("addRange");
        }


        void addRange( shared_ptr<Range> _range ) {
            ranges.push_back(_range);
            notify("addRange");
        }

        void setName(string _name ){
            name = _name;
        }

        string name;
        string description;
        vector<string> tags;
        string filename;
        float aspectRatio;

        vector< shared_ptr<Clip> > parents;
        vector<shared_ptr<Clip> > silblings;
        vector<shared_ptr<Clip> > children;

        vector < shared_ptr<Range> > ranges;

};

*/
