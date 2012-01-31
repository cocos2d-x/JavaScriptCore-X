#include "utils.h"

#include <string>
using namespace std;

// record the resource path
static string s_strResourcePath = "";

void setResourcePath(const char* pszResourcePath)
{
    CCAssert(pszResourcePath != NULL, "[FileUtils setRelativePath] -- wrong relative path");

    string tmp(pszResourcePath);

    if ((! pszResourcePath) || tmp.find(".apk") == string::npos)
    {
        return;
    }

    s_strResourcePath = pszResourcePath;
}

unsigned char* getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName, unsigned long * pSize)
{
    unsigned char * pBuffer = NULL;
    unzFile pFile = NULL;
    *pSize = 0;
LOGD("getFileDataFromZip line=%d", __LINE__);
    do 
    {
        CC_BREAK_IF(!pszZipFilePath || !pszFileName);
        CC_BREAK_IF(strlen(pszZipFilePath) == 0);
LOGD("getFileDataFromZip line=%d", __LINE__);
        pFile = unzOpen(pszZipFilePath);
        CC_BREAK_IF(!pFile);
LOGD("getFileDataFromZip line=%d", __LINE__);
        int nRet = unzLocateFile(pFile, pszFileName, 1);
        CC_BREAK_IF(UNZ_OK != nRet);
LOGD("getFileDataFromZip line=%d", __LINE__);
        char szFilePathA[260];
        unz_file_info FileInfo;
        nRet = unzGetCurrentFileInfo(pFile, &FileInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0);
        CC_BREAK_IF(UNZ_OK != nRet);
LOGD("getFileDataFromZip line=%d", __LINE__);
        nRet = unzOpenCurrentFile(pFile);
        CC_BREAK_IF(UNZ_OK != nRet);
LOGD("getFileDataFromZip line=%d", __LINE__);
        pBuffer = new unsigned char[FileInfo.uncompressed_size+1];
        memset(pBuffer, 0, FileInfo.uncompressed_size+1);
        int nSize = 0;
        nSize = unzReadCurrentFile(pFile, pBuffer, FileInfo.uncompressed_size);
        CCAssert(nSize == 0 || nSize == (int)FileInfo.uncompressed_size, "the file size is wrong");
LOGD("getFileDataFromZip line=%d", __LINE__);
        *pSize = FileInfo.uncompressed_size;
        unzCloseCurrentFile(pFile);
    } while (0);
LOGD("getFileDataFromZip line=%d", __LINE__);
    if (pFile)
    {LOGD("getFileDataFromZip line=%d", __LINE__);
        unzClose(pFile);
    }LOGD("getFileDataFromZip line=%d", __LINE__);

    return pBuffer;
}

unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{	
    unsigned char * pData = 0;
    string fullPath(pszFileName);

    if ((! pszFileName) || (! pszMode))
    {
        return 0;
    }

    if (pszFileName[0] != '/')
    {
        // read from apk
        fullPath.insert(0, "assets/");
        LOGD("s_strResourcePath=%s, fullPath=%s", s_strResourcePath.c_str(), fullPath.c_str());
        pData =  getFileDataFromZip(s_strResourcePath.c_str(), fullPath.c_str(), pSize);
    }
    else
    {
        do 
        {
            // read rrom other path than user set it
            FILE *fp = fopen(pszFileName, pszMode);
            CC_BREAK_IF(!fp);

            unsigned long size;
            fseek(fp,0,SEEK_END);
            size = ftell(fp);
            fseek(fp,0,SEEK_SET);
            pData = new unsigned char[size];
            size = fread(pData,sizeof(unsigned char), size,fp);
            fclose(fp);

            if (pSize)
            {
                *pSize = size;
            }			
        } while (0);		
    }

    return pData;
}