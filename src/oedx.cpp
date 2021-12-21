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

  Elems::Elems() : elems() { }

  Elems::~Elems() { }

  std::vector<Elem*>& Elems::getElems() {
    return elems;
  }

  void Elems::addElem(Elem* elem) {
    this->elems.push_back(elem);
  }

  Html::Html(std::string& body) : Elem(),
				  body(body) { }

  Html::~Html() { }

  std::string Html::getBody() const {
    return body;
  }

  std::string Html::getText() const {
    return Html::getBody();
  }

  SubChapter::SubChapter(std::string& title)
    : Named(),
      Elems(),
      title(title) { }

  std::string
  SubChapter::getTitle() const {
    return title;
  }

  Chapter::Chapter(std::string& title)
    : Named(),
      Elems(),
      subChapters(),
      title(title) { }

  std::string
  Chapter::getTitle() const {
    return title;
  }

  void Chapter::addSubChapter(SubChapter* subChapter) {
    subChapters.push_back(subChapter);
  }

  std::vector<SubChapter*>
  Chapter::getSubChapters() const {
    return subChapters;
  }

  SubChapter* Chapter::getLastSubChapter() const {
    return subChapters.back();
  }

  Section::Section(std::string& title)
    : Named(),
      Elems(),
      chapters(),
      title(title) { }

  std::string
  Section::getTitle() const {
    return title;
  }

  void Section::addChapter(Chapter* section) {
    chapters.push_back(section);
  }

  std::vector<Chapter*>
  Section::getChapters() const {
    return chapters;
  }

  Chapter* Section::getLastChapter() const {
    return chapters.back();
  }


  Unit::Unit(std::string& title) : Named(),
				   Elems(),
				   title(title),
				   sections() { }

  void Unit::addSection(Section* section) {
    sections.push_back(section);
  }

  std::string
  Unit::getTitle() const {
    return title;
  }

  std::vector<Section*>
  Unit::getSections() const {
    return sections;
  }

  Section* Unit::getLastSection() const {
    return sections.back();
  }

  Module::Module(std::string& title) : Named(),
				       Elems(),
				       title(title),
				       units() { }

  void Module::addUnit(Unit* unit) {
    units.push_back(unit);
  }

  std::string
  Module::getTitle() const {
    return title;
  }

  std::vector<Unit*>
  Module::getUnits() const {
    return units;
  }

  Unit* Module::getLastUnit() const {
    return units.back();
  }


  Course::Course(std::string& url_name,
		 std::string& name,
		 std::string& org) : Named(url_name),
				     Elems(),
				     name(name),
				     org(org),
				     language("es"),
				     modules() {

    std::transform(url_name.begin(),
		   url_name.end(),
		   this->url_name.begin(),
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

  std::vector<Module*>
  Course::getModules() {
    return modules;
  }

  Module* Course::getLastModule() const {
    return modules.back();
  }

}
