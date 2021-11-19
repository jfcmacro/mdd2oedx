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
    virtual std::string getText() const = 0;
  };

  class Elems {
    std::vector<Elem*> elems;
  public:
    Elems();
    ~Elems();
    std::vector<Elem*>& getElems();
    void addElem(Elem* elem);
  };

  class Html : public Elem {
    std::string body;
  public:
    Html(std::string& body);
    ~Html();
    std::string getText() const;
    std::string getBody() const;
  };

  class SubChapter : public Named, public Elems {
    std::string title;
  public:
    SubChapter(std::string& title);
    std::string getTitle() const;
  };

  class Chapter : public Named, public Elems {
    std::string title;
    std::vector<SubChapter*> subChapters;
  public:
    Chapter(std::string& title);
    void addSubChapter(SubChapter* subChapter);
    std::string getTitle() const;
    std::vector<SubChapter*> getSubChapters() const;
    SubChapter* getLastSubChapter() const;
  };

  class Section : public Named, public Elems {
    std::string title;
    std::vector<Chapter*> chapters;
  public:
    Section(std::string& title);
    void addChapter(Chapter* chapter);
    std::string getTitle() const;
    std::vector<Chapter*> getChapters() const;
    Chapter* getLastChapter() const;
  };

  class Unit : public Named, public Elems {
    std::vector<Section*> sections;
    std::string title;
  public:
    Unit(std::string& title);
    void addSection(Section* section);
    std::string getTitle() const;
    std::vector<Section*> getSections() const;
    Section* getLastSection() const;
  };

  class Module : public Named, public Elems {
    std::vector<Unit*> units;
    std::string title;
  public:
    Module(std::string& title);
    void addUnit(Unit* unit);
    std::string getTitle() const;
    std::vector<Unit*> getUnits() const;
    Unit* getLastUnit() const;
  };

  class Course : public Named, public Elems {
    std::string name;
    std::string org;
    std::string language;
    std::vector<Module*> modules;
  public:
    Course(std::string& url_name, std::string& name, std::string& org);
    std::string getXMLLine() const;
    void addModule(Module* mod);
    std::vector<Module*> getModules();
    Module* getLastModule() const;
  };

}
