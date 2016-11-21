#ifndef _LOGGER_
#define _LOGGER_

#include <iostream>
#include <fstream>
#include <string>

//! Gestiona los logs de eventos, utilizado para depuración

/**
	@author David Saltares Márquez
	@version 1.0
	
	Clase que sigue el patrón de diseño Singleton (una sóla instancia accesible desde todo el sistema).
	Se utiliza para llevar un registro de lo que ocurre en el sistema. Si queremos escribir un mensaje (normal, de error o de aviso) lo utilizaremos.
	Podemos desviar la salida hacia un fichero en lugar de a la salida estándar.
	
	Ejemplo de uso
	
	\code
		// Comienzo del programa
		logger->open_file();
		
		...
		
		// Constructor de la clase Image
		Image::Image(const char* path, int rows, int cols)
		{
			logger->message("Entrando en Image::Image()"); // Equivalente a Logger::get_instance->message("Entrando en Image::Image()");
			
			...
			
			if(error){
				logger->error("No se pudo abrir la imagen");
				exit(1);
			}
			
			...
			
			logger->message("Saliendo de Image::Image()");
		}
		
	\endcode
*/
class Logger{
	public:
		/**
			@return Si es la primera vez que se usa Logger llama a su constructor, sino es así, devuelve la única instancia de Logger
		*/
		static Logger* get_instance(){
			if(_instance == 0)
				_instance = new Logger;
			return _instance;
		}
		
		/**
			Abre el fichero indicado (sino lo existe, lo crea) y comienza a escribir al final del fichero
			Si no se indica nombre de fichero toma por defecto: Grannys_dd-mm-aaaa_hh-mm-ss.log
			
			@param path Ruta del fichero
		*/
		void open_file(const std::string& path = "");
		
		/**
			Cierra el fichero del log, si estaba cerrado no hace nada.
			A partir de ahora los mensajes se mostrarán en la salida estándar o en la salida estándar de errores (si es de error).
		*/
		void close_file();
		
		/**
			Escribe un mensaje común en el fichero si está abierto, sino en la salida estándar
			
			@param msg Mensaje a escribir
		*/
		void message(const std::string& msg);
		
		/**
			Escribe un mensaje de error en el fichero si está abierto, sino en la salida estándar de errores
			
			@param msg Mensaje a escribir
		*/
		void error(const std::string& msg);
		
		/**
			Escribe un mensaje de aviso en el fichero si está abierto, sino en la salida estándar
			
			@param msg Mensaje a escribir
		*/
		void warning(const std::string& msg);
	protected:
		Logger();
		Logger(const Logger& logger);
		Logger& operator = (const Logger& logger);
		~Logger();
	private:
		void write_header();
		static Logger* _instance;
		std::ofstream file;
};

#define logger Logger::get_instance()

#endif
