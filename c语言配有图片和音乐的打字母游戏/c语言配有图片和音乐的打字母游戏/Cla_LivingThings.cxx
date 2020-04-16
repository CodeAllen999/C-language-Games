/***********************************************
//�������ƣ�Cla_LivingThings��
//����˵����Ϊ�����˶��ഴ���ĸ���
//�������ߣ��ٶ�:haha1111111113
//�����汾��1.1.4
//���ʱ�䣺2013.4.25
//����޸�ʱ�䣺2013.5.19
//��Ȩ��GPL��׼
***********************************************/

#include "Cla_LivingThings.h"

int Cla_LivingThings::CreateLifeTotalNumber = 0;
Cla_LivingThings::Cla_LivingThings()
{
	ActionSpaceBegin_x_coo = 0;
	ActionSpaceBegin_y_coo = 0;
	ActionSpaceEnd_x_coo = 0;
	ActionSpaceEnd_y_coo = 0;
	now_x_coo = 0;
	now_y_coo = 0;
	x_coo_increment = 0;
	y_coo_increment = 0;
	last_x_coo = 0;
	last_y_coo = 0;
	later_x_coo = now_x_coo + x_coo_increment;
	later_y_coo = now_y_coo + y_coo_increment;
	life = true;
	NaturalDeath = 0;
	UnnaturalDeath = 0;
	transmigrate = 0;
	++CreateLifeTotalNumber;
}
Cla_LivingThings::Cla_LivingThings(Cla_GLSMC &GLMsg)
{
	ActionSpaceBegin_x_coo = GLMsg.ActionSpaceBegin_x_coo;
	ActionSpaceBegin_y_coo = GLMsg.ActionSpaceBegin_y_coo;
	ActionSpaceEnd_x_coo = GLMsg.ActionSpaceEnd_x_coo;
	ActionSpaceEnd_y_coo = GLMsg.ActionSpaceEnd_y_coo;
	now_x_coo = GLMsg.LivingThings_x_coo;
	now_y_coo = GLMsg.LivingThings_y_coo;
	x_coo_increment = GLMsg.LivingThings_x_coo_increment;
	y_coo_increment = GLMsg.LivingThings_y_coo_increment;
	last_x_coo = 0;
	last_y_coo = 0;
	later_x_coo = now_x_coo + x_coo_increment;
	later_y_coo = now_y_coo + y_coo_increment;
	life = true;
	NaturalDeath = 0;
	UnnaturalDeath = 0;
	transmigrate = 0;
	++CreateLifeTotalNumber;
}
void Cla_LivingThings::LivingThingsAction()
{
	last_x_coo = now_x_coo;
	last_y_coo = now_y_coo;
	now_x_coo += x_coo_increment;
	now_y_coo += y_coo_increment;
	later_x_coo = now_x_coo + x_coo_increment;
	later_y_coo = now_y_coo + y_coo_increment;

	if(now_x_coo < ActionSpaceBegin_x_coo || 
	   now_x_coo > ActionSpaceEnd_x_coo ||
	   now_y_coo < ActionSpaceBegin_y_coo || 
	   now_y_coo > ActionSpaceEnd_y_coo )
	{
		life = false;
	}
}
void Cla_LivingThings::LivingThingsAccident()
{
	life = false;
	LivingThingsRecord(1,0,0);
}
void Cla_LivingThings::LivingThingsRecord(int UD,int TS,int CL)
{
	UnnaturalDeath += UD;
	transmigrate += TS;
	CreateLifeTotalNumber += CL;
	NaturalDeath = transmigrate - UnnaturalDeath;
}
Stru_LTSMC Cla_LivingThings::SendMessageCenter()
{
	Stru_LTSMC LivingThingsInformation;
	Stru_LTSMC &LTI = LivingThingsInformation;
	LTI.life = life;
	LTI.now_x_coo = now_x_coo;
	LTI.now_y_coo = now_y_coo;
	LTI.NaturalDeath = NaturalDeath;
	LTI.UnnaturalDeath = NaturalDeath;
	LTI.transmigrate = transmigrate;
	LTI.CreateLifeTotalNumber = CreateLifeTotalNumber;
	return LTI;
}
void Cla_LivingThings::GaveLife(Cla_GLSMC &GLMsg)
{
	life = true;
	ActionSpaceBegin_x_coo = GLMsg.ActionSpaceBegin_x_coo;
	ActionSpaceBegin_y_coo = GLMsg.ActionSpaceBegin_y_coo;
	ActionSpaceEnd_x_coo = GLMsg.ActionSpaceEnd_x_coo;
	ActionSpaceEnd_y_coo = GLMsg.ActionSpaceEnd_y_coo;
	now_x_coo = GLMsg.LivingThings_x_coo;
	now_y_coo = GLMsg.LivingThings_y_coo;
	x_coo_increment = GLMsg.LivingThings_x_coo_increment;
	y_coo_increment = GLMsg.LivingThings_y_coo_increment;
	LivingThingsRecord(0,1,1);
}
