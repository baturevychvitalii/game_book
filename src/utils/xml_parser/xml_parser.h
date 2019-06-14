#ifndef __XML_PARSER__
#define __XML_PARSER__

#include "document.h"

namespace xml
{
	/**
	initializes parser, and cleans up mess after libxml2 is no longer needed
	*/
	struct Parser final
	{
		Parser();
		~Parser();

		/**
		Reads xml document from a file
		*/
		static Document GetDoc(const std::string & name);

		/**
		creates xml document
		@param name name of a document
		@param root name of a root element of a document
		*/
		static Document NewDoc(const std::string & name, const std::string & root);

		/**
		creates xml document
		@param name name of a document
		@param root root tag of a document
		*/
		static Document NewDoc(const std::string & name, Tag & root);
	};
}

#endif
