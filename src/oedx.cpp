#include "oedx.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <uuid++.hh>

namespace oedx {

  Named::Named() {
    uuid id;

    id.make(UUID_MAKE_V1);
    url_name = id.string();
  }

  Named::Named(std::string url_name) :
    url_name(url_name) { }

  std::string
  Named::getUrlName() const {
    return url_name;
  }

  Elem::Elem() : Named() { }

  Elem::~Elem() { }

  Html::Html(std::string& body) : Elem(),
				  body(body) { }

  std::string Html::getBody() const {
    return body;
  }

  Section::Section() : Named(),
		       elems() { }

  void Section::addElem(Elem* elem) {
    elems.push_back(elem);
  }

  Unit::Unit(std::string title) : Named(),
				  title(title),
				  sections() { }

  void Unit::addSection(Section* section) {
    sections.push_back(section);
  }

  Module::Module(std::string title) : Named(),
				      title(title),
				      units() { }

  void Module::addUnit(Unit* unit) {
    units.push_back(unit);
  }


  Course::Course(std::string& url_name,
		 std::string& name,
		 std::string& org) : Named(url_name),
				     name(name),
				     org(org),
				     language("es"),
				     modules() {
    std::transform(url_name.begin(),
		   url_name.end(),
		   url_name.begin(),
		   [](unsigned char c){ return std::tolower(c); });
  }

  std::string
  Course::getXMLLine() const {
    std::ostringstream sout;

    sout << "<course url_name=" << '"'
	 << url_name << '"'
	 << " org=" << '"'
	 << org << '"'
	 << " course=" << '"'
	 << name << '"'
	 << "/>";;

    return sout.str();
  }

  void Course::addModule(Module* mod) {
    modules.push_back(mod);
  }
}
