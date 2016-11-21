#include <iostream>
#include "parser.h"
#include "logger.h"

using namespace std;

Parser::Parser(const string& path): document(path.c_str())
{
	try{
		document.LoadFile();
	}
	catch(ticpp::Exception& e){
		logger->error(string("Parser::Parser(): ") + e.what());
		exit(1);
	}
}

ticpp::Element* Parser::root()
{
	return document.FirstChildElement();
}

std::string Parser::get_content(const ticpp::Element* element) const
{
	try{
		return element->GetText();
	}
	catch(ticpp::Exception& e){
	}
	return string();
}

std::string Parser::get_attribute(const std::string& name, const ticpp::Element* element) const
{
	try{
		return element->GetAttribute(name);
	}
	catch(ticpp::Exception& e){
	}
	return string();
}

void Parser::find_aux(const std::string& name, ticpp::Element* father, ticpp::Element*& element, bool& stop)
{
	if(father && !stop){
		ticpp::Iterator<ticpp::Element> son;
		for (son = son.begin(father); son != son.end() && !stop; ++son){
			if(son->Value() == name){
				element = son.Get();
				stop = true;
			}
			else
				find_aux(name, son.Get(), element, stop);
		}
	}
}

ticpp::Element* Parser::find(const std::string& name, ticpp::Element* element)
{
	ticpp::Element* father = element;
	if(!father)
		father = document.FirstChildElement(false);
	
	bool stop = false;
	ticpp::Element* e = 0;
	
	if(father){
		if(father->Value() == name)
			return father;
		else
			find_aux(name, father, e, stop);
	}
	
	return e;
}

void Parser::find_aux(const std::string& name, ticpp::Element* father, std::vector<ticpp::Element*>& v)
{
	if(father){
		ticpp::Iterator<ticpp::Element> son;
		for (son = son.begin(father); son != son.end(); ++son){
			if(son->Value() == name)
				v.push_back(son.Get());
			find_aux(name, son.Get(), v);
		}
	}
}

bool Parser::find(const std::string& name, std::vector<ticpp::Element*>& v, ticpp::Element* element)
{
	ticpp::Element* father = element;
	if(!father)
		father = document.FirstChildElement(false);
	
	size_t size = v.size();
	
	if(father){
		if(father->Value() == name)
			v.push_back(father);
		find_aux(name, father, v);
	}
	
	return size < v.size();
}

bool Parser::add_element(const std::string& name, ticpp::Element* father)
{
	ticpp::Element* root = father ? father : document.FirstChildElement(false);

	if(root){
		ticpp::Node* node = root->LinkEndChild(new ticpp::Element(name));
	if(node)
		return node->ToElement();
	}

	return 0;
}

bool Parser::save_document(const char* path)
{
	try{
		document.SaveFile(path);
	}
	catch(ticpp::Exception& e){
		return false;
	}
	return true;	
}

