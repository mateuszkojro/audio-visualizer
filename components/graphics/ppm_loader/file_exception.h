


#pragma once
#ifndef EQUALIZER_COMPONENTS_GRAPHICS_PPM_LOADER_FILE_EXCEPTION_H_
#define EQUALIZER_COMPONENTS_GRAPHICS_PPM_LOADER_FILE_EXCEPTION_H_
#include <exception>
namespace exception {

	class FileErrorException : public  std::exception
	{
	public:
		const char* what() const throw () { // bad file
			return "file error";
		}



	};

	class BadDimensionsException : public FileErrorException {
	public:
		const char* what() const throw () {
			return "invalid image dimensions";// bad ppm dimensions
		}
	};




	class InvalidPathException : public FileErrorException {
	public:
		const char* what() const throw () { //invalid path
			return "invalid image path";
		}
	};



	class InvalidFileFormatException : public FileErrorException {
	public:
		const char* what() const throw () { // the file has bad format
			return "invalid file format";
		}
	};



	class InvalidCharacterException : public FileErrorException {
	public:
		const char* what() const noexcept { // invalid character
			return "unexpected character occurred";
		}
	};

	class NotImplementedFileFormatException : public FileErrorException {
	public:
		const char* what() const throw () override {  // the file has bad format
			return "not implemented file format";
		}
	};


}
#endif // !EQUALIZER_COMPONENTS_GRAPHICS_PPM_LOADER_FILE_EXCEPTION_H_
