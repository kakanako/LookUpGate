#include "ev3api.h"
#include "app.h"
#include "lookup.h"


Motor* m_tail;//������
GyroSensor* m_gyro;//���Ⴂ��

/*
 * ���b�N�A�b�v�Q�[�g�p�֐�
 * �Ԃ�l�Ftrue�����Cfalse���s
 */

bool lookup(GyroSensor* gyro, ColorSensor* color, Motor* leftmotor,Motor* rightmotor,Motor* tail){


	//�K�v�ȃC���X�^���X��app����Ⴄ(�c�O�Ȃ������)
	//gyro,color,leftmotor,rightmotor,tail
	m_tail = tail;
	m_gyro = gyro;
	
	//�����ۂ�������i���Ă�Ƃ��܂Łj
	//bool result = standuptail();
	//if(result == false){
	//	return false;
	//}
	bool ret = false;
	while(1){
		if(!ret){
			ret = tail_ctr(TAIL_ANGLE_STAND_UP, eSlow);
		}
		else{
			//�����ۂ���������I���
			ret = false;
			break;
		}
	}
	//�|�����sOFF
	m_gyro->reset();
	balance_init();

	//�����ۂ��������悤�ɂ�����肳����
	while(1){
		if(!ret){
			ret = tail_ctr(TAIL_ANGLE_LOOKUPGATE, eSlow);
		}
		else{
			//�����ۂ���������I���
			ret = false;
			break;
		}
	}	

	//���C���ɂ����ăQ�[�g��������
	

	//�����ۂ�������i���Ă�Ƃ��܂Łj
	while(1){
		if(!ret){
			ret = tail_ctr(TAIL_ANGLE_STAND_UP, eSlow);
		}
		else{
			//�����ۂ���������I���
			ret = false;
			break;
		}
	}

	//�|�����sOFF�C���x0�ő���

	//�����ۂ��グ�Ȃ��烉�C���g���[�X���J�n

	return true;//����

}

bool standuptail(){

	//�����ۂŌ��Ă�Ƃ���܂ł����ۂ�������
	return true;
}

bool tail_ctr(int32_t angle, tailSpeed sp){
	
	float pwm_max;
	float pwm = (float)(angle - m_tail->getCount()) * P_GAIN;

	if(pwm<0.1 && pwm >-0.1){
		m_tail->setBrake(true);
		m_tail->setPWM(0);
		return true;
	}
	else{
		m_tail->setBrake(false);
		if (sp == eFast){
			pwm_max = PWM_ABS_MAX_FAST;
		}else if (sp == eSlow){
			pwm_max = PWM_ABS_MAX_SLOW;
		}else{
			pwm_max = 45;
		}
		
		// PWM�o�͖O�a����
		if (pwm > pwm_max)
		{
			pwm = pwm_max;
		}
		else if (pwm < -pwm_max)
		{
			pwm = -pwm_max;
		}
		m_tail->setPWM(pwm);
		return false;
	
	}
}



