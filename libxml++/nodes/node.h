/* node.h
 * libxml++ and this file are copyright (C) 2000 by Ari Johnson, and
 * are covered by the GNU Lesser General Public License, which should be
 * included with libxml++ as the file COPYING.
 */

#ifndef __LIBXMLPP_NODES_NODE_H
#define __LIBXMLPP_NODES_NODE_H

#include <libxml++/noncopyable.h>
#include <libxml++/exceptions/exception.h>
#include <libxml++/string.h>
#include <list>
#include <map>
#include <vector>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
extern "C" {
  struct _xmlNode;
}
#endif //DOXYGEN_SHOULD_SKIP_THIS

namespace xmlpp
{

class TextNode;
class Element;
class Attribute;

class Node;
typedef std::vector<Node*> NodeSet;

/** Represents XML Nodes.
 * You should never new or delete Nodes. The Parser will create and manage them for you.
 */
class Node : public NonCopyable
{
public:
  typedef std::list<Node*> NodeList;

  explicit Node(_xmlNode* node);
  virtual ~Node();

  /** Get the name of this node.
   * @returns The node's name.
   */
  xmlpp::string get_name() const;

  /** Set the name of this node.
   * @param name The new name for the node.
   */
  void set_name(const xmlpp::string& name);

  /** Set the namespace prefix used by the node.
   * If no such namespace prefix has been declared then this method will throw an exception.
   * @param ns_prefix The namespace prefix.
   */
  void set_namespace(const xmlpp::string& ns_prefix);

  xmlpp::string get_namespace_prefix() const;
  xmlpp::string get_namespace_uri() const;

  /** Discover at what line number this node occurs in the XML file.
   * @returns The line number.
   */
  int get_line() const;
  
  /** Get the parent element for this node.
   * @returns The parent node
   */
  const Element* get_parent() const;  

  /** Get the parent element for this node.
   * @returns The parent node
   */
  Element* get_parent();  

  /** Get the next sibling for this node.
   * @returns The next sibling
   */
  const Node* get_next_sibling() const;  

  /** Get the next sibling for this node.
   * @returns The next sibling
   */
  Node* get_next_sibling();  

  /** Get the previous sibling for this node .
   * @returns The previous sibling
   */
  const Node* get_previous_sibling() const;  

  /** Get the previous sibling for this node.
   * @returns The previous sibling
   */
  Node* get_previous_sibling();  

  /** Obtain the list of child nodes. You may optionally obtain a list of only the child nodes which have a certain name.
   * @param name The names of the child nodes to get. If you do not specigy a name, then the list will contain all nodes, regardless of their names.
   * @returns The list of child nodes.
   */
  NodeList get_children(const xmlpp::string& name = xmlpp::string());

  /** Obtain the list of child nodes. You may optionally obtain a list of only the child nodes which have a certain name.
   * @param name The names of the child nodes to get. If you do not specigy a name, then the list will contain all nodes, regardless of their names.
   * @returns The list of child nodes.
   */
  const NodeList get_children(const xmlpp::string& name = xmlpp::string()) const;

  /** Add a child element to this node.
   * @param name The new node name
   * @param ns_prefix The namespace prefix. If the prefix has not been declared then this method will throw an exception.
   * @returns The newly-created element
   */
  Element* add_child(const xmlpp::string& name,
                     const xmlpp::string& ns_prefix = xmlpp::string());

  /** Add a child element to this node after the specified existing child node.
   *
   * @newin{2,24}
   *
   * @param previous_sibling An existing child node.
   * @param name The new node name
   * @param ns_prefix The namespace prefix. If the prefix has not been declared then this method will throw an exception.
   * @returns The newly-created element
   */
  Element* add_child(xmlpp::Node* previous_sibling, const xmlpp::string& name,
                     const xmlpp::string& ns_prefix = xmlpp::string());

  /** Add a child element to this node before the specified existing child node.
   *
   * @newin{2,24}
   *
   * @param next_sibling An existing child node.
   * @param name The new node name
   * @param ns_prefix The namespace prefix. If the prefix has not been declared then this method will throw an exception.
   * @returns The newly-created element
   */
  Element* add_child_before(xmlpp::Node* next_sibling, const xmlpp::string& name,
                     const xmlpp::string& ns_prefix = xmlpp::string());

  /** Remove the child node.
   * @param node The child node to remove. This Node will be deleted and therefore unusable after calling this method.
   */
  void remove_child(Node* node);

  /** Import node(s) from another document under this node, without affecting the source node.
   * @param node The node to copy and insert under the current node.
   * @param recursive Whether to import the child nodes also. Defaults to true.
   * @returns The newly-created node.
   */
  Node* import_node(const Node* node, bool recursive = true);

  
  /** Return the XPath of this node.
   * @result The XPath of the node.
   */
  xmlpp::string get_path() const;

  /** Find nodes from a XPath expression.
   * @param xpath The XPath of the nodes.
   */
  NodeSet find(const xmlpp::string& xpath) const;

  /** A map of namespace prefixes to namespace URIs.
   */
  typedef std::map<xmlpp::string, xmlpp::string> PrefixNsMap;

  /** Find nodes from a XPath expression.
   * @param xpath The XPath of the nodes.
   * @param namespaces A map of namespace prefixes to namespace URIs to be used while finding.
   */
  NodeSet find(const xmlpp::string& xpath, const PrefixNsMap& namespaces) const;


  ///Access the underlying libxml implementation.
  _xmlNode* cobj();

  ///Access the underlying libxml implementation.
  const _xmlNode* cobj() const;

  /** Construct the correct C++ instance for a given libxml C struct instance.
   *
   * This is only for use by the libxml++ implementation.
   *
   * @para node A pointer to an xmlNode or a "derived" struct, such as xmlDoc, xmlAttr, etc.
   */
  static void create_wrapper(_xmlNode* node);
  
  /** Delete the C++ instance for a given libxml C struct instance, and also 
   * recursively destroy the C++ instances for any children.
   *
   * This is only for use by the libxml++ implementation.
   * @para node A pointer to an xmlNode or a "derived" struct, such as xmlDoc, xmlAttr, etc.
   */
  static void free_wrappers(_xmlNode* attr);
  
protected:

  ///Create the C instance ready to be added to the parent node.
  _xmlNode* create_new_child_node(const xmlpp::string& name, const xmlpp::string& ns_prefix);

private:
  _xmlNode* impl_;
};

} // namespace xmlpp

#endif //__LIBXMLPP_NODES_NODE_H
