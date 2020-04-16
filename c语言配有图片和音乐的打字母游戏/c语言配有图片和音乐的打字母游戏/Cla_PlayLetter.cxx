/***********************************************
//�������ƣ�Cla_PlayLetter��
//����˵�����̳���Cla_LivingThings
//�������ߣ��ٶ�:haha1111111113
//�����汾��1.1.4
//���ʱ�䣺2013.4.25
//����޸�ʱ�䣺2013.5.19
//��Ȩ��GPL��׼
***********************************************/
#include "Cla_PlayLetter.h"

Cla_PlayLetter::Cla_PlayLetter()
{
	letter = 'A';
	LetterSize = 36;
}
Cla_PlayLetter::Cla_PlayLetter(Cla_PLGLSMC &GetMsg)
{
	letter = GetMsg.letter;
	LetterSize = GetMsg.LetterSize;
	ActionSpaceBegin_x_coo = GetMsg.ActionSpaceBegin_x_coo;
	ActionSpaceBegin_y_coo = GetMsg.ActionSpaceBegin_y_coo;
	ActionSpaceEnd_x_coo = GetMsg.ActionSpaceEnd_x_coo;
	ActionSpaceEnd_y_coo = GetMsg.ActionSpaceEnd_y_coo;
	now_x_coo = GetMsg.LivingThings_x_coo;
	now_y_coo = GetMsg.LivingThings_y_coo;
	x_coo_increment = GetMsg.LivingThings_x_coo_increment;
	y_coo_increment = GetMsg.LivingThings_y_coo_increment;
}

void Cla_PlayLetter::AgainGaveFeature(Cla_PLGLSMC &GetMsg)
{
	life = true;
	letter = GetMsg.letter;
	LetterSize = GetMsg.LetterSize;
	ActionSpaceBegin_x_coo = GetMsg.ActionSpaceBegin_x_coo;
	ActionSpaceBegin_y_coo = GetMsg.ActionSpaceBegin_y_coo;
	ActionSpaceEnd_x_coo = GetMsg.ActionSpaceEnd_x_coo;
	ActionSpaceEnd_y_coo = GetMsg.ActionSpaceEnd_y_coo;
	now_x_coo = GetMsg.LivingThings_x_coo;
	now_y_coo = GetMsg.LivingThings_y_coo;
	x_coo_increment = GetMsg.LivingThings_x_coo_increment;
	y_coo_increment = GetMsg.LivingThings_y_coo_increment;
	LivingThingsRecord(0,1,1);
}

Stru_PLSLF Cla_PlayLetter::SendLetterFeature()
{
	Stru_PLSLF STFeature;
	Stru_PLSLF &stf = STFeature;
	stf.letter = letter;
	stf.LetterSize = LetterSize;
	stf.now_x_coo = now_x_coo;
	stf.now_y_coo = now_y_coo;
	stf.last_x_coo = last_x_coo;
	stf.last_y_coo = last_y_coo;
	stf.life = life;
	stf.NaturalDeath = NaturalDeath;
	stf.UnnaturalDeath = UnnaturalDeath;
	stf.transmigrate = transmigrate;
	stf.CreateLifeTotalNumber = CreateLifeTotalNumber;
	return stf;
}
void Cla_PlayLetter::sqecial(int value)
{
	y_coo_increment += value;
}