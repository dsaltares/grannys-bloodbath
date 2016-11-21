#include <ctime>
#include <cstring>
#include "logger.h"

using namespace std;

Logger* Logger::_instance = 0;

Logger::Logger(){}

void Logger::open_file(const std::string& path)
{
	string final_path;
	
	/* Si no le pasamos un fichero creamos un fichero con la fecha del sistema */
	if(path == ""){
		/* Construimos la ruta de la forma "Grannys_dd-mm-aaaa_hh-mm-ss.log" */
		char date[30];
		final_path += "Grannys_";
		time_t rawtime;
		struct tm* timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		sprintf(date, "%d-%d-%d_%d-%d-%d", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
		final_path += date + string(".log");
	}
	else
		final_path = string(path);
	
	/* Si teníamos un fichero abierto lo cerramos */
	if(file.is_open())
		file.close();
		
	/* Abrimos el fichero y escribimos en él la cabecera inicial*/
	file.open(final_path.c_str(), ios_base::app);
	write_header();
}

void Logger::write_header()
{
	if(file.is_open()){
		time_t rawtime;
		struct tm* timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		file << endl << "GRANNY'S BLOODBATH Log for " << asctime(timeinfo) << endl;
	}	
}

void Logger::close_file()
{
	if(file.is_open())
		file.close();	
}

void Logger::message(const std::string& msg)
{
	if(file.is_open())
		file << "Message: " << msg << endl;
	else
		cout << "Message: " << msg << endl;
}

void Logger::error(const std::string& msg)
{
	if(file.is_open())
		file << "ERROR: " << msg << endl;
	else
		cerr << "ERROR: " << msg << endl;
}

void Logger::warning(const std::string& msg)
{
	if(file.is_open())
		file << "Warning: " << msg << endl;
	else
		cout << "Warning: " << msg << endl;
}
