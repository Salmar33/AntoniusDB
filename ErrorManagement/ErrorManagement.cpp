#include "ErrorManagement.h"

ErrorManagement::ErrorManagement()
{
    //attempt to open the error path
    errors.open(ERROR_PATH, std::ofstream::app);
    //if it does not exist, then attempt to create the error path
    if((errors.rdstate() & std::ofstream::failbit) != 0)
	{
        if(CreateErrorPath(ERROR_PATH_WIDE) == 0)
		{
			fprintf(stdout, "Error with CreateErrorPath()!\nUnable to create path: \n%s", ERROR_PATH);
			system("PAUSE");
			exit(EXIT_FAILURE);
		}
		else
		{
            errors.open(ERROR_PATH, std::ofstream::app);
            //if the error path still cannot be opened although the path should have been successfully created
            if((errors.rdstate() & std::ofstream::app) != 0)
            {
				fprintf(stdout, "Error with fopen(), although the error path has been successfully created\n%s", ERROR_PATH);
				system("PAUSE");
				exit(EXIT_FAILURE);
			}
		}
	}
}

ErrorManagement::~ErrorManagement()
{
    errors.close();
}

/**
 * @brief Creates a full path
 * @param errorPath A null terminated string of the path that should be created
 * @return 0 in case of an error or a value disparate from 0 otherwise
 */
int ErrorManagement::CreateErrorPath(const wchar_t* errorPath)
{
    const wchar_t *h = NULL;
    const wchar_t *dirName;
    wchar_t dir[MAX_PATH];
	unsigned int dirNameLength;		//length of dirName in bytes


	dirName = errorPath;
	//4 is a rather arbitrary bound to make sure that at least the operations below can be successfully conducted
    if(wcslen(errorPath) < 4)
	{
		return 0;
	}

    if((h = wcsstr(errorPath, L"\\")) == NULL)
	{
		return 0;
	}
	while(1)
	{
		h++;
        if((h = wcsstr(h, L"\\")) == NULL)
		{
			break;
		}
		dirNameLength = (h - dirName);
        wcsncpy(dir, dirName, dirNameLength);
        dir[dirNameLength] = L'\0';

        if(CreateDirectory(dir, NULL) == 0)
		{
			if(GetLastError() != ERROR_ALREADY_EXISTS)
			{
                fwprintf(stdout, L"Error with CreateDirectory()!\nUnable to create:\n%s", dir);
				return 0;
			}
		}

	}

	return 1;
}

void ErrorManagement::PrintError(const char *err_string, const char *fileName, unsigned int line)     //As 2. parameter provide __FILE__ and as 3.parameter __LINE__
{
	time_t start;
	struct tm *zeit;
	
	time(&start);
	zeit = localtime(&start);
    errors << "__________________________________________________";
    errors << "\nFilename: " << fileName << "\nLine: " << line << "\n" << err_string << "\nErrorcode (GetLastError()):" << GetLastError() << "\n" << zeit->tm_year+1900 << "." << zeit->tm_mon+1 << "." << zeit->tm_mday << " " << zeit->tm_hour << ":" << zeit->tm_min << ":" << zeit->tm_sec << "\n";
    errors.flush();
	return;
}


void ErrorManagement::BailOut(const char *errorString, const char *fileName, unsigned int line, int exitCode)
{
    PrintError(errorString, fileName, line);
	exit(exitCode);
}
