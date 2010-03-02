// alone_wz.cpp : アプリケーションのクラス動作を定義します。
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


// Alone_wzApp コンストラクション

Alone_wzApp::Alone_wzApp()
{
}


// 唯一の Alone_wzApp オブジェクトです。

Alone_wzApp theApp;


// Alone_wzApp 初期化

BOOL Alone_wzApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	// SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));

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

	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	//  アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}
