#ifndef MINI_XML_HEADER
#define MINI_XML_HEADER


#define  BUFFLENGTH  256
class miniXmlNode
{
	miniXmlNode * parent;	/// the father of this node
	miniXmlNode * child;   /// the child of this node
	miniXmlNode * next;    /// the next node , child of this father
	char *name;     /// the node name
	char *value;    /// value of this node
	
public:
	/// defautl ctor
	miniXmlNode(const char *_name, char *_value, miniXmlNode *_parent = nullptr, miniXmlNode *_child = nullptr, miniXmlNode *_next = nullptr);
	/// default destructor
	~miniXmlNode();
	/// add a child node a this node. _name as
	/// xPath for crossing from iinternal child nodes
	/// path separator is assumend the point '.'
	miniXmlNode * add(const char *name, char *value);
	/// this function link at this node a child xmlNode
	miniXmlNode * link(char *name, miniXmlNode  *_child);
	/// this function add a value at already existent value
	miniXmlNode * cat(char * addValue);
	/// inbox for value, return the current value
	const char * getValue(void);
	/// walking from child , return the child with has next field set a  nullptr pointer
	miniXmlNode * lastchild(void);
	/// this function return a node with name as requested
	miniXmlNode * findNextChild(const char *_name);
	/// this function return a next node 
	miniXmlNode * findNext(const char *_name);
	/// this function return a specified node 
	miniXmlNode * find(const char *_name);
	/// generate a XML file
	void print(FILE *out);
	/// assign a requested name
	void setName(const char *_name);
	/// assigne a requested value
	void setValue(char *_value);
	/// in line return parent
	inline miniXmlNode * getParent(void) { return parent; }
	inline miniXmlNode * getChild(void) { return child; }
	inline miniXmlNode * getNext(void) { return next; }

};

#endif