#ifndef ERROR_MANAGEMENT
#define ERROR_MANAGEMENT

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <ctime>
#include <Windows.h>

#define ERROR_PATH 		".\\err\\errors.txt"
#define ERROR_PATH_WIDE L".\\err\\errors.txt"
#ifndef FAILURE
#define FAILURE		1
#endif
#define PASSWORD_ERROR	0x6

class ErrorManagement
{
private:
    std::ofstream errors;

    void PrintError(const char*, const char *fileName, unsigned int line);
    int CreateErrorPath(const wchar_t *errorPath);

public:
	ErrorManagement(void);
	~ErrorManagement(void);
    void BailOut(const char* errorString, const char *fileName, unsigned int line, int errorCode);
};

#endif
