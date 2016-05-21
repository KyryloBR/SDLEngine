#ifndef XMLDOCUMENT_H_
#define XMLDOCUMENT_H_

#include <RapidXML\rapidxml.hpp>

class XMLDocument
{
public:
	static XMLDocument * Instance()
	{
		if (!s_pInstance)
		{
			s_pInstance = new XMLDocument();
		}
		return s_pInstance;
	}

	rapidxml::xml_document<> * getDoc() { return m_pDocument; }
private:
	rapidxml::xml_document<> * m_pDocument;

	static XMLDocument * s_pInstance;
	XMLDocument() { m_pDocument = new rapidxml::xml_document<>(); }
	~XMLDocument() { delete m_pDocument; }
};

XMLDocument * XMLDocument::s_pInstance = nullptr;

#endif // XMLDOCUMENT_H_