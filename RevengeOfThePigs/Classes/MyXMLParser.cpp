//
//  MyXMLParser.cpp
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-17.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#include "MyXMLParser.h"
#include "CCSAXParser.h"
#include "SceneManager.h"

MyXMLParser::MyXMLParser()
: m_pCurLevelInfo(NULL)
, m_isNewLevel(false)
{
    
}

MyXMLParser::~MyXMLParser()
{
    m_pCurLevelInfo = NULL;
}

static const char* valueForKey(const char *key, std::map<std::string, std::string>* dict)
{
    if ( dict != NULL )
    {
        std::map<std::string, std::string>::iterator it = dict->find(key);
        return it!=dict->end() ? it->second.c_str() : "";
    }
    return "";
}

MyXMLParser* MyXMLParser::ParserWithFile(const char *file, EXMLConfigType type)
{
    MyXMLParser *pRet = new MyXMLParser();
	pRet->curConfigTye = type;
    if(pRet->InitXmlParse(file))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool MyXMLParser::InitXmlParse(const char* xmlName)
{
    CCSAXParser _par;  
    if (false == _par.init("UTF-8") )
    {
        return false;
    }
    
    _par.setDelegator(this);
    const char* _path = CCFileUtils::fullPathFromRelativePath(xmlName);
    return _par.parse(_path);
    
}

void MyXMLParser::startElement(void *ctx, const char *name, const char **atts)
{
    CC_UNUSED_PARAM(ctx);
    
    startXmlElement = (char*)name;
    
    std::map<std::string, std::string> *attributeDict = new std::map<std::string, std::string>();
    if(atts && atts[0])
    {
        for(int i = 0; atts[i]; i += 2) 
        {
            std::string key = (char*)atts[i];
            std::string value = (char*)atts[i+1];
            attributeDict->insert(pair<std::string, std::string>(key, value));
        }
    }
    
    if ( curConfigTye == EXMLConfigType_Levels )
		DoStartElementLevels(startXmlElement, attributeDict);
	//else if ( curConfigTye == EXMLConfigType_Version)
	//	DoStartElementVersion(startXmlElement, attributeDict);
	else if ( curConfigTye == EXMLConfigType_ModeControl )
		DoStartElementModeControl(startXmlElement, attributeDict);
    
    if (attributeDict)
    {
        attributeDict->clear();
        delete attributeDict;
    }
}

void MyXMLParser::endElement(void *ctx, const char *name)
{
    CC_UNUSED_PARAM(ctx);
    
    endXmlElement = (char*)name;
    if ( endXmlElement == m_rootName )
    {
        if ( curConfigTye == EXMLConfigType_Levels )
			DoEndElementLevels();
		//else if ( curConfigTye == EXMLConfigType_Version )
		//	DoEndElementVersion();
    }
}

void MyXMLParser::textHandler(void *ctx, const char *ch, int len)
{
    CC_UNUSED_PARAM(ctx);
    currString=string((char*)ch,0,len);
}

void MyXMLParser::DoStartElementLevels(std::string startXmlElement, std::map<std::string, std::string> *attributeDict)
{
	if ( startXmlElement == "Levels" )
		return;

	if(!m_isNewLevel)
	{
		m_isNewLevel = true;
		m_rootName = startXmlElement;
		m_pCurLevelInfo = new LevelInfo();
		int s_id = atoi(valueForKey("SmallId", attributeDict));
		int b_id = atoi(valueForKey("BigId", attributeDict));
		m_pCurLevelInfo->SetSmallID(s_id);
		m_pCurLevelInfo->SetBigId(b_id);
		return;
	}

	if ( m_pCurLevelInfo == NULL )
		return;

	if ( startXmlElement == "ShotPosition" )
	{
		float x = (float)atof(valueForKey("x", attributeDict));
		float y = (float)atof(valueForKey("y", attributeDict));
		m_pCurLevelInfo->SetShotPos(x, y);
	}else if(startXmlElement == "RubberLeftPosition")
	{
		float x = (float)atof(valueForKey("x", attributeDict));
		float y = (float)atof(valueForKey("y", attributeDict));
		m_pCurLevelInfo->SetRubberLeftPos(x,y);
	}else if(startXmlElement == "RubberRightPosition")
	{
		float x = (float)atof(valueForKey("x", attributeDict));
		float y = (float)atof(valueForKey("y", attributeDict));
		m_pCurLevelInfo->SetRubberRightPos(x,y);
	}
	else if ( startXmlElement == "SlingShotL" )
	{
		PropsInfo* pInfo = new PropsInfo();
		std::string image = valueForKey("image", attributeDict);
		float x = (float)atof(valueForKey("x", attributeDict));
		float y = (float)atof(valueForKey("y", attributeDict));
		pInfo->SetInfo(image, x, y);
		m_pCurLevelInfo->SetSlingShotL(pInfo);
	}
	else if ( startXmlElement == "SlingShotR" )
	{
		PropsInfo* pInfo = new PropsInfo();
		std::string image = valueForKey("image", attributeDict);
		float x = (float)atof(valueForKey("x", attributeDict));
		float y = (float)atof(valueForKey("y", attributeDict));
		pInfo->SetInfo(image, x, y);
		m_pCurLevelInfo->SetSlingShotR(pInfo);
	}
	else if ( startXmlElement == "Pig" )
	{
		PigInfo* pPig = new PigInfo();
		int type = atoi(valueForKey("type", attributeDict));
		std::string image = valueForKey("image", attributeDict);
		float x = (float)atof(valueForKey("x", attributeDict));
		float y = (float)atof(valueForKey("y", attributeDict));
		pPig->SetInfo(type, image, x, y);
		m_pCurLevelInfo->AddPig(pPig);
	}
	else if ( startXmlElement == "Props" )
	{
		PropsInfo* pInfo = new PropsInfo();
		std::string image = valueForKey("image", attributeDict);
		float x = (float)atof(valueForKey("x", attributeDict));
		float y = (float)atof(valueForKey("y", attributeDict));
		float rot = (float)atof(valueForKey("rot", attributeDict));
		int propsType = (float)atof(valueForKey("type", attributeDict));
		int tag = (float)atof(valueForKey("tag", attributeDict));
		int to = (float)atof(valueForKey("to", attributeDict));
		int to2 = (float)atof(valueForKey("to2", attributeDict));
		std::string state =  valueForKey("state", attributeDict);
		pInfo->SetInfo(image, x, y, propsType, rot,tag,to,to2,state);
		m_pCurLevelInfo->AddProps(pInfo);
	}
	else if( startXmlElement == "LockPig")
	{
		PropsInfo* pInfo = new PropsInfo();
		std::string image = valueForKey("image", attributeDict);
		float x = (float)atof(valueForKey("x", attributeDict));
		float y = (float)atof(valueForKey("y", attributeDict));
		float rot = (float)atof(valueForKey("rot", attributeDict));
		int propsType = (float)atof(valueForKey("type", attributeDict));
		int to = (float)atof(valueForKey("to", attributeDict));
		pInfo->SetInfo(image, x, y, propsType, rot,NULL,to);
		m_pCurLevelInfo->AddProps(pInfo);
	}
	//增加获取本关三个阶段分值;
	else if(startXmlElement == "Score")
	{
		int OneStarScore = (int)atoi(valueForKey("score1",attributeDict));
		int TwoStarScore = (int)atoi(valueForKey("score2",attributeDict));
		int ThreeStarScore = (int)atoi(valueForKey("score3",attributeDict));
		m_pCurLevelInfo->SetHingestScore(OneStarScore,TwoStarScore,ThreeStarScore);
	}
	else if ( startXmlElement == "Polygon" )
	{
		if ( m_pCurLevelInfo != NULL )
		{
			PropsInfo* pInfo = m_pCurLevelInfo->GetLatestProps();
			if ( pInfo != NULL )
			{
				int pointsNum = (int)atoi(valueForKey("number",attributeDict));
				if ( pointsNum > 0 )
				{
					for ( int i = 1; i <= pointsNum; ++i )
					{
						char x[50] = {0};
						sprintf(x, "x%d", i);
						char y[50] = {0};
						sprintf(y, "y%d", i);
						float fx = (float)atof(valueForKey(x, attributeDict));
						float fy = (float)atof(valueForKey(y, attributeDict));
						pInfo->AddPolygonPoint( fx, fy );
					}
				}
			}
		}
	}
}

void MyXMLParser::DoEndElementLevels()
{
	SceneManager::SharedSceneManager()->AddNewLevelConfig(m_pCurLevelInfo);
	m_pCurLevelInfo = NULL;
	m_isNewLevel = false;
	m_rootName="";
}

//void MyXMLParser::DoStartElementVersion(std::string startXmlElement, std::map<std::string, std::string> *attributeDict)
//{
//	if ( startXmlElement == "Version" )
//	{
//		int version = (int)atoi(valueForKey("id", attributeDict));
//		SceneManager::SharedSceneManager()->SetGameVersion((EGameVersion)version);
//	}
//}

//void MyXMLParser::DoEndElementVersion()
//{
//
//}

void MyXMLParser::DoStartElementModeControl(std::string startXmlElement, std::map<std::string, std::string> *attributeDict)
{
	if ( startXmlElement == "Mode" )
	{
		int mode = (int)atoi(valueForKey("id", attributeDict));
		SceneManager::SharedSceneManager()->SetIsTestGameMode(mode==1?true:false);
	}
}

void MyXMLParser::DoEndElementModeControl()
{

}
