#include <vector>
#include <string>

using namespace std;

#ifdef OS_LINUX
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#else
#include <io.h>
#endif


void get_dirs(const std::string& dir, std::vector<std::string>& dirs)  
{
#ifdef OS_LINUX
	DIR *dp;
	struct dirent *dirp;
    if ((dp = opendir(dir.c_str())) == NULL) {
        perror("opendir error");
       return;
    }
    while ((dirp = readdir(dp)) != NULL) {
        if ((strcmp(dirp->d_name, ".") == 0) || (strcmp(dirp->d_name, "..") == 0))
            continue;
        if (DT_DIR == dirp->d_type)
        	dirs.push_back(dirp->d_name);
    }
#else
	_finddata_t file;
	long longf;
	std::string s = dir + "*.*";
	if((longf = _findfirst(s.c_str(), &file))==-1l) {
		printf("opendir error!\n");
	}
	else {
		std::string tempName;
		while( _findnext( longf, &file ) == 0 ) {
			tempName = "";
			tempName = file.name;
			if (tempName == "..") {
				continue;
			} 
			if(file.attrib == _A_SUBDIR) {
				dirs.push_back(file.name);
			}
		}
	}
	_findclose(longf);
#endif // OS_LINUX
}


void get_files(const std::string& dir, std::vector<std::string>& files)  
{
#ifdef OS_LINUX
	DIR *dp;
	struct dirent *dirp;
    if ((dp = opendir(dir.c_str())) == NULL) {
        perror("opendir error!\n");
        return;
    }
    while ((dirp = readdir(dp)) != NULL) {
        if ((strcmp(dirp->d_name, ".") == 0) || (strcmp(dirp->d_name, "..") == 0))
            continue;
        if (DT_DIR != dirp->d_type)
        	files.push_back(dirp->d_name);
    }
#else
	_finddata_t file;
	long longf;
	std::string s = dir + "*.*";
	if((longf = _findfirst(s.c_str(), &file))==-1l) {
		printf("opendir error!\n");
	}
	else {
		std::string tempName;
		while( _findnext( longf, &file ) == 0 ) {
			tempName = "";
			tempName = file.name;
			if (tempName == "..") {
				continue;
			}
			if(_A_SUBDIR != file.attrib) {
				files.push_back(file.name);
			}
		}
	}
	_findclose(longf);
#endif // OS_LINUX
}
