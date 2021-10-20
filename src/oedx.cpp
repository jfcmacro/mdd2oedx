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

  Course::Course(std::string name,
		 std::string org) : Named(name),
				    name(name),
				    org(org) {
    std::transform(url_name.begin(),
		   url_name.end(),
		   url_name.begin(),
		   [](unsigned char c){ return std::tolower(c); });
  }

  std::string
  oedx::Course::getXMLLine() const {
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

  Module::Module() : Named() { }
}
