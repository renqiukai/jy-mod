#ifndef SaveGRPFile_h__
#define SaveGRPFile_h__

#pragma once

#pragma pack(push, 1)

struct Person
{
	unsigned short usNo;			//人物编号
	unsigned short usModel;			//模型编号
	char szRev4[2];					//未知数据0
	unsigned short usType;			//类型 0:普通 1:主角 80:程英
	char szName[10];               // 姓名
	char szNick[10];               // 江湖称号
	unsigned short usSex;			//性别 0:男 1:女 2:XX
	unsigned short usLevel;        // 等级
	unsigned short usExp;          // 经验
	unsigned short usLife;         // 生命值
	unsigned short usMaxLife;      // 生命最大值
	unsigned short usInjury;       // 受伤程度
	unsigned short usPoison;       // 中毒程度
	unsigned short usStamina;      // 体力
	char szRev1[2];				//未知数据1
	unsigned short usWeapon;       // 装备武器
	unsigned short usArmor;        // 装备防具
	char szRev2[30];			//未知数据2
	unsigned short usForceType;    // 内力属性 0:阴性;1:阳性;2:兼容
	unsigned short usForce;        // 内力值
	unsigned short usMaxForce;     // 内力最大值
	unsigned short usAttack;       // 攻击力
	unsigned short usLightness;    // 轻功
	unsigned short usDefense;      // 防御力
	unsigned short usMedicine;     // 医疗能力
	unsigned short usToxic;        // 用毒能力
	unsigned short usDetox;        // 解毒能力
	unsigned short usResistance;   // 抗毒能力
	unsigned short usFist;         // 拳掌功夫
	unsigned short usSword;        // 御剑能力
	unsigned short usBlade;        // 耍刀技巧
	unsigned short usExotic;       // 特殊兵器
	unsigned short usDagger;       // 暗器技巧
	unsigned short usKnowledge;    // 武学常识
	unsigned short usMorality;     // 道德值
	unsigned short usPoisonSkill;  // 武功带毒
	unsigned short usAmbidextrous; // 双手互搏
	unsigned short usReputation;   // 声望值
	unsigned short usTalent;       // 资质
	unsigned short usTrainItem;    // 修炼物品
	unsigned short usTrainExp;     // 修炼经验
	unsigned short usSkills[10];      // 武功一到十
	unsigned short usSkillExps[10];   // 武功一到十经验
	unsigned short usItem[4];        // 携带物品一到四
	unsigned short usItemCount[4];  // 携带物品一到四数量
};

#pragma pack(pop)

void ReadPersonFromSaveFile(const char * pszFileName);
void ExportToCSV(const char* filename);

#endif // SaveGRPFile_h__
