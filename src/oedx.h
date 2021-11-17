#pragma once
#include <string>
#include <vector>

namespace oedx {
  class Named {
  protected:
    std::string url_name;
  public:
    Named();
    Named(std::string url_name);
    virtual std::string getUrlName() const;
  };

  class Elem : public Named {
  public:
    Elem();
    virtual ~Elem() = 0;
  };

  class Html : public Elem {
    std::string body;
  public:
    Html(std::string& body);
    std::string getBody() const;
  };

  class Section : public Named {
    std::vector<Elem*> elems;
  public:
    Section();
    void addElem(Elem* elem);
  };

  class Unit : public Named {
    std::vector<Section*> sections;
    std::string title;
  public:
    Unit(std::string title);
    void addSection(Section* section);
    std::string getTitle();
    Section* getLastSection() const;
  };

  class Module : public Named {
    std::vector<Unit*> units;
    std::string title;
  public:
    Module(std::string& title);
    void addUnit(Unit* unit);
    std::string getTitle();
    Unit* getLastUnit() const;
  };

  class Course : public Named {
    std::string name;
    std::string org;
    std::string language;
    std::vector<Module*> modules;
  public:
    Course(std::string& url_name, std::string& name, std::string& org);
    std::string getXMLLine() const;
    void addModule(Module* mod);
    Module* getLastModule() const
  };

}
