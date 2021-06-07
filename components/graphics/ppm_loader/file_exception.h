


#pragma once
#ifndef FILE_EXCEPTION_H
#define FILE_EXCEPTION_H
#include <exception>
namespace exception {

	class file_error_exception : public  std::exception
	{
	public:
		const char* what() const throw () { // bad file
			return "file error";
		}



	};

	class bad_dimensions_exception : public  file_error_exception {
	public:
		const char* what() const throw () {
			return "invalid image dimensions";// bad ppm dimensions
		}
	};




	class invalid_path_exception : public  file_error_exception {
	public:
		const char* what() const throw () { //invalid path
			return "invalid image path";
		}
	};



	class invalid_file_format_exception : public  file_error_exception {
	public:
		const char* what() const throw () { // the file has bad format
			return "invalid file format";
		}
	};



	class invalid_character_exception : public  file_error_exception {
	public:
		const char* what() const throw () { // invalid character
			return "unexpected character occurred";
		}
	};

	class not_implemented_file_format_exception : public  file_error_exception {
	public:
		const char* what() const throw () {  // the file has bad format
			return "not implemented file format";
		}
	};


}
#endif // !FILE_EXCEPTION_H
