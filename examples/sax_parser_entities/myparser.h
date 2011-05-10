// -*- C++ -*-

/* myparser.h
 *
 * Copyright (C) 2002 The libxml++ development team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __LIBXMLPP_EXAMPLES_MYPARSER_H
#define __LIBXMLPP_EXAMPLES_MYPARSER_H

#include <libxml++/libxml++.h>

class MySaxParser : public xmlpp::SaxParser
{
public:
  MySaxParser();
  virtual ~MySaxParser();

protected:
  //overrides:
  virtual void on_start_document();
  virtual void on_end_document();
  virtual void on_start_element(const xmlpp::string& name,
                                const AttributeList& properties);
  virtual void on_end_element(const xmlpp::string& name);
  virtual void on_characters(const xmlpp::string& characters);
  virtual void on_comment(const xmlpp::string& text);
  virtual void on_warning(const xmlpp::string& text);
  virtual void on_error(const xmlpp::string& text);
  virtual void on_fatal_error(const xmlpp::string& text);

  virtual _xmlEntity* on_get_entity(const xmlpp::string& name);
  virtual void on_entity_declaration(const xmlpp::string& name, xmlpp::XmlEntityType type, const xmlpp::string& publicId, const xmlpp::string& systemId, const xmlpp::string& content);
};


#endif //__LIBXMLPP_EXAMPLES_MYPARSER_H
