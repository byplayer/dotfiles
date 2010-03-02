// alone_wz.cpp : �A�v���P�[�V�����̃N���X������`���܂��B
//

#include "stdafx.h"
#include "alone_wz.h"
#include "alone_wzDlg.h"
#include "util/MFCUtil.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Alone_wzApp

BEGIN_MESSAGE_MAP(Alone_wzApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Alone_wzApp �R���X�g���N�V����

Alone_wzApp::Alone_wzApp()
{
}


// �B��� Alone_wzApp �I�u�W�F�N�g�ł��B

Alone_wzApp theApp;


// Alone_wzApp ������

BOOL Alone_wzApp::InitInstance()
{
	// �A�v���P�[�V���� �}�j�t�F�X�g�� visual �X�^�C����L���ɂ��邽�߂ɁA
	// ComCtl32.dll Version 6 �ȍ~�̎g�p���w�肷��ꍇ�́A
	// Windows XP �� InitCommonControlsEx() ���K�v�ł��B�����Ȃ���΁A�E�B���h�E�쐬�͂��ׂĎ��s���܂��B
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �A�v���P�[�V�����Ŏg�p���邷�ׂẴR���� �R���g���[�� �N���X���܂߂�ɂ́A
	// �����ݒ肵�܂��B
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// �W��������
	// �����̋@�\���g�킸�ɍŏI�I�Ȏ��s�\�t�@�C����
	// �T�C�Y���k���������ꍇ�́A�ȉ�����s�v�ȏ�����
	// ���[�`�����폜���Ă��������B
	// �ݒ肪�i�[����Ă��郌�W�X�g�� �L�[��ύX���܂��B
	// ��Ж��܂��͑g�D���Ȃǂ̓K�؂ȕ������
	// ���̕������ύX���Ă��������B
	// SetRegistryKey(_T("�A�v���P�[�V���� �E�B�U�[�h�Ő������ꂽ���[�J�� �A�v���P�[�V����"));

	TString cmd(_T("\""));
	cmd += MFCUtil::getModuleDir(0);
	cmd += _T("wz_main.exe\"");

	for(int i=1; i<__argc; ++i)
	{
		cmd += _T(" \"");
		cmd += __targv[i];
		cmd += _T("\"");
	}

	cmd += _T(" /i");

	TRACE(_T("cmd[%s]\n"), cmd.c_str());

	MFCUtil::execute(cmd, true);

#if 0
	Alone_wzDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
#endif

	// �_�C�A���O�͕����܂����B�A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n���Ȃ���
	//  �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return FALSE;
}
