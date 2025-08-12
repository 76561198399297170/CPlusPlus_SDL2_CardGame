#ifndef _CARDTYPE_H_
#define _CARDTYPE_H_

//卡牌类型
enum class CardType
{
	None,		//无
	SEED,		//种子
	MATERIAL,	//材料
	ENEMY,		//敌人
	BLUEPRINT,	//蓝图
	ACTION,		//行动
	CURSE,		//诅咒
	UNKNOW		//未知
};

//卡牌标签
enum class CardTag
{
	CONSUME,    // 消耗：使用后进入除外堆
	USE,        // 使用：场景退出后入弃牌堆
	ANNIHILATE, // 湮灭：未使用直接入除外堆
	FIXED,      // 固定：未使用保留在手牌
	DISABLED,   // 禁用：不允许打出
	RETURN,     // 回归：使用后入抽牌堆
	FORCE       // 强置：回合结束强制打出
};

//作物标签
enum class PlantType
{
	VEGETABLE,  // 蔬菜
	FRUIT,      // 水果
	FLOWER,     // 花卉
	MEDICINAL   // 药用
};

#endif