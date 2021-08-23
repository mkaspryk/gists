#include "gists.h"

Gists::Gists(){

    this->downloader = new HTTPDownloader();
    this->input = new InputHelper();
    this->jsonHelper = new JsonHelper();
}

Gists::~Gists(){

    delete this->downloader;
    delete this->input;
    delete this->jsonHelper;
}

void Gists::gistsApp(){

    if(!gistsServiceGet(false)){

        return;
    }

    char key;
    bool update = false;

    //! application loop
    while(true){

        std::cout<<"Options\n";
        std::cout<<"__________________________________________________________________________\n";
        std::cout<<"'p' key to print the list\n";
        std::cout<<"'a' key to add a new record\n";
        std::cout<<"'d' key to delete a record\n";
        std::cout<<"'q' key to quit the application\n";
        std::cout<<"Press key: ";
        while ((key=input->getch()) == '\n');
        std::cout<<std::endl;
        switch(key){
        case 'p':
            if(update){
                gistsServiceGet(true);
                update=false;
            }
            this->gistsPrint();
            break;
        case 'a':
            this->gistsServiceAdd();
            update = true;
            break;
        case 'd':
            this->gistsServiceDelete();
            update = true;
            break;
        case 'q':
            return;
            break;
        default:
            break;
        }
    }
}

bool Gists::gistsServiceGet(bool passCorrect){

    this->gistObjects.clear();

    std::string output;

    delete this->downloader;
    this->downloader = new HTTPDownloader();

    if(!passCorrect){

        std::cout<<"Enter host name for user: ";
        std::cin>>this->name;
        while(input->getch() == '\n'){
            break;
        }
        this->api_key = input->getpass("Enter host password for user '" + name + "':", false);
        this->url="https://api.github.com/users/" + this->name + "/gists";
    }

    while(!downloader->get(this->name, this->api_key, this->url, output)){

        this->api_key = input->getpass("Wrong password, re-type host password for user '" + name + "':", false);
    }

    std::string json_content;
    if (!jsonHelper->getJsonContent(output, json_content)){

        std::cout<<"No json content !\n";
        return false;
    }

    json j = json::parse(json_content);
    this->gistsReadJsonParameters(j);
    return true;
}

void Gists::gistsPrint(){

    unsigned int i;
    for(i=0;i<this->gistObjects.size();++i){

        std::cout<<"Record: "<<i<<std::endl;
        std::cout<<"__________________________________________________________________________\n";
        std::cout<<"Name: "<<this->gistObjects[i].file<<std::endl;
        std::cout<<"Description: "<<this->gistObjects[i].description<<std::endl;
        std::cout<<"Content: "<<this->gistObjects[i].content<<std::endl;
        std::cout<<"Created at: "<<this->gistObjects[i].created_at<<std::endl;
        std::cout<<"Updated at: "<<this->gistObjects[i].updated_at<<std::endl<<std::endl;
    }
}

void Gists::gistsServiceAdd(){

    std::string name, description, content;

    std::cout<<"Enter the name: ";
    std::getline (std::cin, name);
    std::cout<<"Enter the description: ";
    std::getline (std::cin, description);
    std::cout<<"Enter the content: ";
    std::getline (std::cin, content);

    json j;
    j["description"] = description;
    j["public"] = false;
    j["files"][name]["content"] = content;

    if(!downloader->addGist(this->name, this->api_key, this->url_gists, j.dump())){

        std::cout<<"Error at adding\n";
    }

    std::cout<<"Added successfully\n";
}

void Gists::gistsServiceDelete(){

    std::cout<<"Which record do you want to delete ?\n";
    unsigned int i=0;
    for(GistObject &f : this->gistObjects){

        std::cout<<"Record " << i << " : " << f.file << " - '" << i <<"'\n";
        ++i;
    }
    try {

        std::cout<<"Enter the record number: ";
        std::string record;
        std::cin>>record;

        if(!downloader->deleteGist(this->name, this->api_key, gistObjects[std::stoi(record)].url)){

            std::cout<<"Error at deleting \n";
        }
    }  catch (std::exception const &e) {

        std::cout<<e.what()<<std::endl;
        return;
    }

    std::cout<<"Deleted successfully\n";
}

void Gists::gistsReadJsonParameters(json &j){

    for (json &el : j){

        GistObject g;
        g.url = el["url"];
        std::string content = el["url"];
        std::string out;
        this->getContent(content, out);
        g.content = out;
        for (json &el2 : el["files"]){

            g.file = el2["filename"];
        }        
        g.created_at = el["created_at"];
        g.updated_at = el["updated_at"];
        g.description = el["description"];
        this->gistObjects.push_back(g);
    }
}

bool Gists::getContent(std::string &url, std::string &out){

    std::string output;
    while(!downloader->get(this->name, this->api_key, url, output)){

        this->api_key = input->getpass("Wrong password, re-type host password for user '" + name + "':", false);
    }

    std::string json_content;
    if (!jsonHelper->getJsonContentOneElement(output, json_content)){

        std::cout<<"No json content !\n";
        return false;
    }

    json j = json::parse(json_content);
    for (json &el : j["files"]){

        out=el["content"];
    }

    return true;
}
