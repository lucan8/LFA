#pragma once
#include <exception>
#include <fstream>

class FileOpenException : public std :: exception{
private:
    std :: string file_name; 
public:
    FileOpenException(const std :: string& file_name) : file_name(file_name){}
    const char* what() const  noexcept{return (std :: string("Could not open ") + file_name).c_str();}
};

class DirectoryNotFound : public std :: exception{
private:
    std :: string directory; 
public:
    DirectoryNotFound(const std :: string& directory) : directory(directory){}
    const char* what() const  noexcept{return (std :: string("Directory not found: ") + directory).c_str();}
};