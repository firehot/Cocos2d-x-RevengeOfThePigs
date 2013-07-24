//
//  GameElementStruct.h
//  RevengeOfThePigs
//
//  Created by terryliu on 12-6-18.
//  Copyright 2012年 Cloud Game. All rights reserved.
//

#ifndef _GAMEELEMENTSTRUCT_H_
#define _GAMEELEMENTSTRUCT_H_

class PropsInfo
{
public:
    PropsInfo()
    : m_image("")
    {}
    virtual ~PropsInfo(){}
    
	virtual void SetInfo(std::string image, float x, float y, int propsType=-1, float rot=0,int tag=0,int to=0,int to2=0,std::string state="")
	{
		m_image = image;
		m_x = x;
		m_y = y;
		m_rot = rot;
		m_propsType = propsType;
		m_tag = tag;
		m_to = to;
		m_to2 = to2;
		m_state = state;

	}
    virtual std::string GetImage(){return m_image;}
    virtual float GetX(){return m_x;}
    virtual float GetY(){return m_y;}
    virtual float GetRot(){return m_rot;}
    int GetPropsType(){return m_propsType;}
	int GetPropsTag(){return m_tag;}
	int GetPropsTo(){return m_to;}
	int GetPropsTo2(){return m_to2;}
	std::string GetState(){return m_state;}
	void AddPolygonPoint(float x, float y){m_vPolygonX.push_back(x);m_vPolygonY.push_back(y);}
	std::vector<float> GetPolygonPointX(){return m_vPolygonX;}
	std::vector<float> GetPolygonPointY(){return m_vPolygonY;}
    
protected:
    std::string m_image;
    float m_x;
    float m_y;
    float m_rot;
    int m_propsType;
	int m_tag;
	int m_to;
	int m_to2;
	std::string m_state;
	std::vector<float> m_vPolygonX;
	std::vector<float> m_vPolygonY;
};

class PigInfo : public PropsInfo
{
public:
    PigInfo(){}
    virtual ~PigInfo(){}
    
    virtual void SetInfo( int type, std::string image, float x, float y)
    {
        m_type = type;
        PropsInfo::SetInfo(image, x, y);
    }
    
    virtual int GetType(){return m_type;}
    
protected:
    int m_type;
};

class LevelInfo
{
public:
    LevelInfo()
    : m_slingShotL(NULL)
    , m_slingShotR(NULL)
    {}
    virtual ~LevelInfo(){}
    
    void SetSmallID(int id){m_smallid = id;}
    void SetBigId(int bigid){BigStageId=bigid;}
    int GetBigId(){return BigStageId;}
    void SetShotPos(float x, float y){m_shotPosX = x; m_shotPosY = y;}
    void SetRubberLeftPos(float x,float y){m_rubberLeftPosX=x;m_rubberLeftPosY=y;}
    void SetRubberRightPos(float x,float y){m_rubberRightX=x;m_rubberRightY=y;}
    void SetSlingShotL(PropsInfo* pInfo){m_slingShotL = pInfo;}
    void SetSlingShotR(PropsInfo* pInfo){m_slingShotR = pInfo;}
    void AddPig(PigInfo* pPig){m_vPigs.push_back(pPig);}
    void AddProps(PropsInfo* pProps){m_vProps.push_back(pProps);}
	PropsInfo* GetLatestProps(){return m_vProps.size()<=0?NULL:m_vProps[m_vProps.size()-1];}
	void SetHingestScore(int score1,int score2,int score3){OneStarScore = score1;TwoStarScore = score2;ThreeStarScore = score3;}//获取本关最多可达到的最高分;

    CC_SYNTHESIZE_READONLY(int, m_smallid, ID);
    //传递三个阶段分值;
	int GetOneStarScore(){return OneStarScore;}
	int GetTwoStarScore(){return TwoStarScore;}
	int GetThreeStarScore(){return ThreeStarScore;}
    float GetShotPosX(){return m_shotPosX;}
    float GetShotPosY(){return m_shotPosY;}

    float GetRubberLeftPosX(){return m_rubberLeftPosX;}
    float GetRubberLeftPosY(){return m_rubberLeftPosY;}
    float GetRubberRightPosX(){return m_rubberRightX;}
    float GetRubberRightPosY(){return m_rubberRightY;}

    PropsInfo* GetSlingShotL(){return m_slingShotL;}
    PropsInfo* GetSlingShotR(){return m_slingShotR;}
    std::vector<PigInfo*> GetPigs(){return m_vPigs;}
    std::vector<PropsInfo*> GetProps(){return m_vProps;}
    
private:
    float m_shotPosX;
    float m_shotPosY;
    float m_rubberLeftPosX;
    float m_rubberLeftPosY;
    float m_rubberRightX;
    float m_rubberRightY;
	int OneStarScore;
	int TwoStarScore;
	int ThreeStarScore;
    int BigStageId;
    PropsInfo* m_slingShotL;
    PropsInfo* m_slingShotR;
    std::vector<PigInfo*> m_vPigs;
    std::vector<PropsInfo*> m_vProps;
};

#endif
