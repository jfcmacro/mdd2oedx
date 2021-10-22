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
    std::vector<Section> sections;
  public:
    Unit();
    void addSection(Section& section);
  };

  class Module : public Named {
    std::vector<Unit> units;
  public:
    Module();
    void addUnit(Unit& unit);
  };

  class Course : public Named {
    std::string name;
    std::string org;
    std::vector<Module> modules;
  public:
    Course(std::string name, std::string org);
    std::string getXMLLine() const;
    void addModule(Module& mod); 
  };

}
