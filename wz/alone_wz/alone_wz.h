// alone_wz.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��


// Alone_wzApp:
// ���̃N���X�̎����ɂ��ẮAalone_wz.cpp ���Q�Ƃ��Ă��������B
//

class Alone_wzApp : public CWinApp
{
public:
	Alone_wzApp();

// �I�[�o�[���C�h
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern Alone_wzApp theApp;