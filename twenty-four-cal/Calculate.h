/*
	ͨ��������Ӧ�ļ�����ʽ�����ؼ�����
	�����������򷵻ش������
*/
#ifndef CALCULATE_H
#define CALCULATE_H
#include <windows.h>

//����������
#define	ERROR_CODE_NOZERO	1	//��������Ϊ0
#define	ERROR_CODE_WORRYNUM	2	//���������
#define	ERROR_CODE_WORRYEXP	3	//����ı��ʽ

BOOL EvaluateExpression(const TCHAR * Expression, double &result, int &error_code);
#endif
