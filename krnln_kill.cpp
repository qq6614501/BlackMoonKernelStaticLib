#include "stdafx.h"

//���̲��� - ɾ���ļ�
/*
    ���ø�ʽ�� ���߼��͡� ɾ���ļ� ���ı��� ��ɾ�����ļ����� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�kill
    �ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
    ����<1>������Ϊ����ɾ�����ļ�����������Ϊ���ı��ͣ�text������
*/
LIBAPI(BOOL, krnln_kill)
{
	return DeleteFile(ArgInf.m_pText);
}