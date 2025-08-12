#ifndef _CARDTYPE_H_
#define _CARDTYPE_H_

//��������
enum class CardType
{
	None,		//��
	SEED,		//����
	MATERIAL,	//����
	ENEMY,		//����
	BLUEPRINT,	//��ͼ
	ACTION,		//�ж�
	CURSE,		//����
	UNKNOW		//δ֪
};

//���Ʊ�ǩ
enum class CardTag
{
	CONSUME,    // ���ģ�ʹ�ú��������
	USE,        // ʹ�ã������˳��������ƶ�
	ANNIHILATE, // ����δʹ��ֱ��������
	FIXED,      // �̶���δʹ�ñ���������
	DISABLED,   // ���ã���������
	RETURN,     // �ع飺ʹ�ú�����ƶ�
	FORCE       // ǿ�ã��غϽ���ǿ�ƴ��
};

//�����ǩ
enum class PlantType
{
	VEGETABLE,  // �߲�
	FRUIT,      // ˮ��
	FLOWER,     // ����
	MEDICINAL   // ҩ��
};

#endif