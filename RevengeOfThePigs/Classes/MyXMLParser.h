//
//  MyXMLParser.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-17.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _MYXMLPARSE_H_
#define _MYXMLPARSE_H_

#include "cocos2d.h"
#include "CCSAXParser.h"
#include "CCObject.h"
#include "CCMutableDictionary.h"
#include "SceneManager.h"

using namespace cocos2d;

typedef enum
{
	EXMLConfigType_Levels = 1,
	EXMLConfigType_Version = 2,
	EXMLConfigType_ModeControl = 3,
} EXMLConfigType;

class MyXMLParser :public CCObject, public CCSAXDelegator
{
public:
    MyXMLParser();
    virtual ~MyXMLParser();
    
    static MyXMLParser * ParserWithFile(const char *tmxFile, EXMLConfigType type);
    bool InitXmlParse(const char* xmlName);
    
    void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);
    
	EXMLConfigType curConfigTye;

private:
	void DoStartElementLevels(std::string startXmlElement, std::map<std::string, std::string> *attributeDict);
	void DoEndElementLevels();
	//void DoStartElementVersion(std::string startXmlElement, std::map<std::string, std::string> *attributeDict);
	//void DoEndElementVersion();
	void DoStartElementModeControl(std::string startXmlElement, std::map<std::string, std::string> *attributeDict);
	void DoEndElementModeControl();
private:
    std::string m_rootName;
    bool m_isNewLevel;
    LevelInfo* m_pCurLevelInfo;  //保存从XML文件中读出的当前关卡的信息;
    
    std::string startXmlElement;//用来记录每个key前字段;
    std::string endXmlElement;//用来记录每个key后字段;
    std::string currString;//记录每个value的值;
};

#endif

