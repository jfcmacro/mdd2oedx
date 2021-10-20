#pragma once
#include <string>

namespace oedx {
  class Named {
  protected:
    std::string url_name;
  public:
    Named();
    Named(std::string url_name);
    virtual std::string getUrlName() const;
  };

  class Course : public Named {
    std::string name;
    std::string org;
  public:
    Course(std::string name, std::string org);
    std::string getXMLLine() const;
  };

  class Module : public Named {
  public:
    Module();
  };
}
