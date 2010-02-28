// alone_wz.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// Alone_wzApp:
// このクラスの実装については、alone_wz.cpp を参照してください。
//

class Alone_wzApp : public CWinApp
{
public:
	Alone_wzApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern Alone_wzApp theApp;