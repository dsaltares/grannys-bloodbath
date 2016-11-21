/*
    This file is part of Granny's Bloodbath.

    Granny's Bloodbath is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Granny's Bloodbath is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Granny's Bloodbath.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _PARSER_
#define _PARSER_

#include <vector>
#include <string>
#include "ticpp/ticpp.h"

//! Parsea ficheros XML

/**
	@author David Saltares Márquez
	@version 1.0
	
	Clase que sigue el patrón de diseño Singleton (una sóla instancia accesible desde todo el sistema).
	Se utiliza para parsear ficheros XML. Tratamos de que todos los datos del juego estén separados del código.
	De esta manera se consigue que los hipotéticos diseñadores puedan cambiar parámetros de la jugabilidad sin saber programar ni recompilar el código.
	
	Se utilizará generalmente para leer aunque también se puede escribir en ficheros XML con esta clase (ficheros de configuración, por ejemplo).
	
	Ejemplo de uso:
	
	Si tenemos un fichero xml con esta estructura:
	\code
		<personaje vx="5" vy="2" energia="4" ataque="2" imagen="personaje">
		<colisiones>
			<colision x="48" y="0" w="20" h="94" />
			<colision x="0" y="38" w="115" h="16" />
		</colisiones>
		<animaciones>
			<animacion nombre="normal" anim="0,1,2,3,4,5,6,7" retardo="1"/>
			<animacion nombre="saltar" anim="0,8,9,10,11,12,13,14,15,16" retardo="1"/>
			<animacion nombre="atacar" anim="0,17,18,19,20,21" retardo="1"/>
			<animacion nombre="morir" anim="0,22,23,24,25,26" retardo="1"/>
		</animaciones>
		</personaje>	
	\endcode
	
	Podemos parsearlo de la siguiente forma:
	\code
		...
		
		Parser parser("personaje.xml");
	
		ticpp::Element* element = parser.root();
	
		// Atributos
		string img;
		int vx, vy, energia, ataque;
		parser.get_attribute("energia", element, &energia);
		parser.get_attribute("vx", element, &vx);
		parser.get_attribute("vy", element, &vy);
		parser.get_attribute("ataque", element, &ataque);
		img = parser.get_attribute("imagen", element);
	
		// Cajas de colisión
		SDL_Rect collision_box;
		vector<ticpp::Element*> collisions;
	
		parser.find("colision", collisions, parser.find("colisiones"));
	
		for(vector<ticpp::Element*>::iterator i = collisions.begin(); i != collisions.end(); i++){
		
			parser.get_attribute("x", *i, &(collision_box.x));
			parser.get_attribute("y", *i, &(collision_box.y));
			parser.get_attribute("w", *i, &(collision_box.w));
			parser.get_attribute("h", *i, &(collision_box.h));
		}
	
		...
	\endcode
*/
class Parser{
	public:
		/**
			Constructor
			
			Carga el fichero xml indicado por la ruta
			
			@param path Ruta del fichero xml a cargar
		*/
		Parser(const std::string& path);
		
		/**
			@return Elemento raíz del fichero XML, a partir de él, cuelgan todos los demás.
		*/
		ticpp::Element* root();
		
		/**
			Consultor
			
			Accede al contenido de texto de un elemento del fichero xml
			
			@param element Elemento del que se quiere consultar su contenido
			@return Contenido del elemento
		*/
		std::string get_content(const ticpp::Element* element) const;
		
		/**
			Consultor
			
			Obtiene el atributo en forma de cadena del nombre indicado del elemento dado
			
			@param name Nombre del atributo cuyo valor se quiere consultar
			@param element Elemento del que se quiere saber su atributo
			@return Cadena con el valor del atributo
		*/
		std::string get_attribute(const std::string& name, const ticpp::Element* element) const;
		
		/**
			Consultor
			
			Obtiene el atributo en forma del tipo deseado del nombre indicado del elemento dado
			
			@param name Nombre del atributo cuyo valor se quiere consultar
			@param element Elemento del que se quiere consultar el atributo
			@param value Variable en la que se quiere guardar el valor del atributo
			@return true si la operación ha tenido éxito, false en caso contrario
		*/
		template <typename T>
		bool get_attribute(const std::string& name, const ticpp::Element *element, T* value) const{
			if(element){
				try{
					element->GetAttribute(name, value);
				}
				catch(ticpp::Exception& e){
					return false;
				}
				return true;
			}
			return false;
		}
		
		/**
			Busca y devuelve el primer elemento a partir de un padre con el nombre dado
			
			@param name Nombre del elemento a buscar
			@param element Elemento padre desde el que se realizará la búsqueda. Si se omite, se tomará la raíz, es decir, se buscará desde el principio del documento XML.
		*/
		ticpp::Element* find(const std::string& name, ticpp::Element* element = 0);
		
		/**
			Busca e inserta en el vector dado los elementos que coincidan con el nombre indicado
			
			@param name Nombre de los elementos a buscar
			@param v Vector de elementos donde se gardarán los resultados coincidentes
			@param element Elemento padre a partir del cual se realiza la búsqueda. Si se omite se tomará la raíz. es decir, se buscará desde el principio del documento XML.
			@return true si la operación tiene éxito, false, en caso contrario
		*/
		bool find(const std::string& name, std::vector<ticpp::Element*>& v, ticpp::Element* element = 0);
		
		/**
			Añade el elemento dado como hijo de otro también indicado.
			
			@param name Nombre del elemento a añadir
			@param father Padre del elemento a añadir. Si se omite se toma por defecto el elemennto raíz.
			@return true si la operación tiene éxito, false en caso contrario
		*/
		bool add_element(const std::string& name, ticpp::Element* father = 0);
		
		/**
			Establece un parámetro al elemento dado
			
			@param name Nombre del atributo a establecer
			@param value Valor del atributo
			@param element Elemento del que se quiere establecer el atributo
			@return true si la operación tiene éxito, false en caso contrario
		*/
		template<typename T>
		bool set_attribute(const std::string& name, const T& value, ticpp::Element* element){
			if(element){
				try{
					element->SetAttribute(name, value);
				}catch(ticpp::Exception& e){
					return false;
				}
				return true;
			}
			return false;
		}
		
		/**
			Establece el contenido del elemento dado
			
			@param value Valor del contenido a establecer
			@param element Elemento del que queremos establecer su valor
			@return true si la operación tiene éxito, false en caso contrario
		*/
		template<typename T>
		bool set_content(const T& value, ticpp::Element* element){
			if(element){
				try{
					element->SetText(value);
				}catch(ticpp::Exception& e){
					return false;
				}
				return true;
			}
			return false;
		}
		
		/**
			Guarda el documento con las modificaciones realizadas
			
			@param path ruta del fichero a guardar
			@return true si la operación tiene éxito, false en caso contrario
		*/
		bool save_document(const char* path);
		
	private:
		ticpp::Document document;
		void find_aux(const std::string& name, ticpp::Element* father, ticpp::Element*& element, bool& stop);
		void find_aux(const std::string& name, ticpp::Element* father, std::vector<ticpp::Element*>& v);
};

#endif
