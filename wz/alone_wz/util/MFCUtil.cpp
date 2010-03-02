//---------------------------------------------------------------------------
// ファイル名	: MFCUtil.cpp
// $Revision:: 150             $
// $Author:: yukio             $
// $Date:: 2006-12-18 15:34:17#$

//---------------------------------------------------------------------------
//インクルードファイル
#include "stdafx.h"
#include "MFCUtil.hpp"

#include "util/types.hpp"
#include "util/StringUtil.hpp"

#pragma warning(push)
#pragma warning(disable : BOOST_WAR_BLOCK)
#include <boost/scoped_array.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#pragma warning(pop)

/// VerQueryValueなどのバージョン関数用
#pragma comment(lib, "Version")

using namespace boost;


//---------------------------------------------------------------------------
//プリプロセッサ
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/// ModulePath取得
TString MFCUtil::getModuleFileName(HMODULE hHandle)
{
	TCHAR fname[_MAX_PATH];
	const DWORD copyLen = ::GetModuleFileName(hHandle, &fname[0], _MAX_PATH);
	if(0 == copyLen)
	{
		return _T("");
	}

	return TString(&fname[0], static_cast<TString::size_type>(copyLen));
}

/// Moduleのあるディレクトリを取得
/*!
 * 末尾に「\」が付きます。
 */
TString MFCUtil::getModuleDir(HMODULE hHandle)
{
	const TString moduleFileName(getModuleFileName(hHandle));
	if(moduleFileName.empty())
	{
		return _T("");
	}

	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	
	if(0 != ::_tsplitpath_s(moduleFileName.c_str()
					, &drive[0], _MAX_DRIVE
					, &dir[0], _MAX_DIR
					, 0, 0
					, 0, 0))
	{
		return _T("");
	}

	TString moduleDir(&drive[0]);
	moduleDir += &dir[0];
	
	return moduleDir;
}

/// Moduleの名前取得
/*!
 * getModuleFileNameがc:\hoge\abc\123.exe
 * を返すとき
 * 123を返します。
 */
TString MFCUtil::getModuleName(HMODULE hHandle)
{
	const TString moduleFileName(getModuleFileName(hHandle));
	if(moduleFileName.empty())
	{
		return _T("");
	}

	TCHAR fname[_MAX_FNAME];

	if(0 != ::_tsplitpath_s(moduleFileName.c_str()
					, 0, 0
					, 0, 0
					, &fname[0], _MAX_FNAME
					, 0, 0))
	{
		return _T("");
	}

	TString moduleName(&fname[0]);
	return moduleName;
}

//---------------------------------------------------------------------------
/// モジュール情報を取得する。
MFCUtil::ModuleInfo MFCUtil::getModuleInfo(const TCHAR* const pModuleName)
{
	MFCUtil::ModuleInfo moduleInfo;

	HMODULE handle = ::GetModuleHandle(pModuleName);
	if(handle)
	{
		const TString filePath = MFCUtil::getModuleFileName(handle);
		if(!filePath.empty())
		{
			moduleInfo = getPathModuleInfo(filePath.c_str());
		}
	}

	return moduleInfo;
}

/// パスからモジュール情報を取得する
MFCUtil::ModuleInfo MFCUtil::getPathModuleInfo(const TCHAR* const pPath)
{
	MFCUtil::ModuleInfo moduleInfo;
	
	DWORD  dwReserved;
	DWORD dwSize = ::GetFileVersionInfoSize(const_cast<TCHAR*>(pPath), &dwReserved);
	
	LPVOID lpBuffer = ::HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSize);
	if(lpBuffer != NULL)
	{
		UINT dwLength;
		LPTSTR buf;

		if(GetFileVersionInfo(const_cast<TCHAR*>(pPath), 0, dwSize, lpBuffer))
		{
			// ロケールの取得
			if(VerQueryValue(lpBuffer, _T("\\VarFileInfo\\Translation"), (void**)&buf, &dwLength))
			{
				int locale;
				CopyMemory(&locale, buf, sizeof(int));

				// 情報取得に使う文字列
				const TCHAR* const fileInfoWords = _T("\\StringFileInfo\\%04X%04X\\%s");

				if(VerQueryValue(
							lpBuffer,
							const_cast<TCHAR*>(io::str(TFormat(fileInfoWords) % LOWORD(locale) 
									% HIWORD(locale) % _T("FileDescription")).c_str()),
							(void **) &buf,
							&dwLength))
				{
					moduleInfo.fileDescription = buf;
				}

				if(VerQueryValue(lpBuffer, 
					const_cast<TCHAR*>(io::str(TFormat(fileInfoWords) % LOWORD(locale) 
									% HIWORD(locale) % _T("ProductVersion")).c_str()),
					(void **)&buf, &dwLength))

				{
					moduleInfo.version = buf;
				}
				

				if(VerQueryValue(lpBuffer, 
					const_cast<TCHAR*>(io::str(TFormat(fileInfoWords) % LOWORD(locale)
									% HIWORD(locale) % _T("LegalCopyright")).c_str()),
					(void **)&buf, &dwLength))
				{
					moduleInfo.copyright = buf;
				}
			}
		}

		HeapFree(GetProcessHeap(), 0, lpBuffer);
	}

	return moduleInfo;
}

DWORD MFCUtil::getDlgCode(CWnd* pWnd, LPMSG lpMsg /* =NULL */)
{
	if (pWnd == NULL)
		return 0;

	WPARAM wParam = (lpMsg == NULL) ? 0 : lpMsg->wParam;

	return (DWORD)SendMessage(pWnd->m_hWnd, WM_GETDLGCODE,
		wParam, (LPARAM)(LPMSG)lpMsg);
}

/// フォーカス設定
/*!
 * フォーカスを取得するウインドウがEdit系の場合は、全選択も行う
 */
void MFCUtil::setFocus(CWnd* pWnd)
{
	ASSERT(pWnd);
	if(!pWnd)
	{
		return;
	}

	if(getDlgCode(pWnd) & DLGC_HASSETSEL)
		pWnd->SendMessage(EM_SETSEL, 0, -1);

	pWnd->SetFocus();
}

//---------------------------------------------------------------------------
/// 文字列からフォントを生成
bool MFCUtil::createLogFont(LOGFONT* logFont, const TString& value)
{
	memset(logFont, 0, sizeof(LOGFONT));
	logFont->lfOutPrecision = OUT_DEFAULT_PRECIS;
	logFont->lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logFont->lfQuality = DEFAULT_QUALITY;

	typedef tokenizer<char_separator<TCHAR>, 
					TString::const_iterator,
					TString> 
		Tokenizer;
	char_separator<TCHAR> number_separator(_T(","), _T(""), boost::keep_empty_tokens);

	Tokenizer toks(value, number_separator);
	Tokenizer::const_iterator itr = toks.begin();
	Tokenizer::const_iterator end = toks.end();

	bool isOK = false;
	try {
		if( itr == end ) return false;

		logFont->lfHeight = lexical_cast<int>(*itr);
		if( ++itr == end ) return false;

		logFont->lfWeight = lexical_cast<int>(*itr);
		if( ++itr == end ) return false;

		logFont->lfItalic = (BYTE)lexical_cast<int>(*itr);
		if( ++itr == end ) return false;

		logFont->lfCharSet = (BYTE)lexical_cast<int>(*itr);
		if( ++itr == end ) return false;

		logFont->lfPitchAndFamily = (BYTE)lexical_cast<int>(*itr);
		if( ++itr == end ) return false;

		const TString faceName = *itr;
		_tcscpy_s(logFont->lfFaceName, LF_FACESIZE, faceName.c_str());

		isOK = true;

	} catch(bad_lexical_cast&){
		isOK = false;
	}
	return isOK;
}

bool MFCUtil::createFont(CFont& font, const TString& value)
{
	LOGFONT logFont;
	if(!createLogFont(&logFont, value))
	{
		return false;
	}

	if(!font.CreatePointFontIndirect(&logFont))
	{
		return false;
	}

	return true;
}

/// 直接指定でフォントを生成
bool MFCUtil::createFontDirect(CFont& font, 
			const double scaling,
			const int point, LPCTSTR faceName, 
			const bool bold /* =false */, const bool italic /* =false */, 
			const BYTE charSet /* =DEFAULT_CHARSET */,
			const BYTE pitchAndFamily /* =FF_DONTCARE */)
{
	LOGFONT logFont;
	memset(&logFont, 0, sizeof(LOGFONT));
	logFont.lfHeight = (int)((((double)point) * scaling) + 0.5);
	logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logFont.lfQuality = DEFAULT_QUALITY;
	logFont.lfWeight = (bold)?FW_BOLD:FW_NORMAL;
	logFont.lfItalic = (italic)?TRUE:FALSE;
	logFont.lfCharSet = charSet;
	logFont.lfPitchAndFamily = pitchAndFamily;
	_tcscpy_s(logFont.lfFaceName, LF_FACESIZE, faceName);

	if( !font.CreatePointFontIndirect(&logFont) ) return false;
	return true;
}

/// フォントから文字列を生成
TString MFCUtil::fontToString(CFont& font)
{
	LOGFONT logfont;
	font.GetLogFont(&logfont);

	return io::str(TFormat(_T("%d,%d,%d,%d,%d,%s")) %
			logfont.lfHeight % logfont.lfWeight % 
			static_cast<unsigned int>(logfont.lfItalic) %
			static_cast<unsigned int>(logfont.lfCharSet) %
			static_cast<unsigned int>(logfont.lfPitchAndFamily) % logfont.lfFaceName);
}

/// フォントから文字列を生成
TString MFCUtil::fontToStringDirect(
			const int point, LPCTSTR faceName, 
			const bool bold /* =false */, const bool italic /* =false */, 
			const BYTE charSet /* =DEFAULT_CHARSET */,
			const BYTE pitchAndFamily /* =FF_DONTCARE */)
{
	return io::str(TFormat(_T("%d,%d,%d,%d,%d,%s")) %
			point % (bold?FW_BOLD:FW_NORMAL) % (italic?TRUE:FALSE) %
			static_cast<unsigned int>(charSet) %
			static_cast<unsigned int>(pitchAndFamily) % faceName);
}

/// ユーザロケールをstring型で取得
std::string MFCUtil::getUserLocale()
{
	const int LOC_SIZE = 256;
	TCHAR localeName[LOC_SIZE];
	if(0 == GetLocaleInfo(LOCALE_USER_DEFAULT, 
		// LOCALE_SENGCOUNTRY
		LOCALE_SENGLANGUAGE 
		, &localeName[0], LOC_SIZE))
	{
		return "";
	}

#ifdef _UNICODE
	char acciiSysLocale[LOC_SIZE];
	wcstombs_s(0, &acciiSysLocale[0], LOC_SIZE, &localeName[0], wcslen(&localeName[0]));
	return &acciiSysLocale[0];
#else
	return &localeName[0];
#endif
}

/// GetLastErrorの理由を文字列で取得
TString MFCUtil::getLastErrorMsg()
{
	LPVOID error_buf;
	TString msg;
	
	if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,NULL,GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &error_buf,0,NULL))
	{
		if(error_buf)
		{
			msg = static_cast<TCHAR*>(error_buf);
			::LocalFree(error_buf);
		}
	}

	return msg;
}

/// CException* クラスからエラーメッセージ取得
TString MFCUtil::getCause(CException* pEx)
{
	const size_t BUF_SIZE = 256;
	TCHAR buf[BUF_SIZE];
	pEx->GetErrorMessage(&buf[0], BUF_SIZE);

	return TString(&buf[0]);
}

/// アプリケーションを起動する
bool MFCUtil::execute(const TString& cmd, bool waitClose)
{
	bool isOK = false;

	STARTUPINFO infoStart;
	PROCESS_INFORMATION infoProcess;
	::memset(&infoStart, 0, sizeof(infoStart));
	::memset(&infoProcess, 0, sizeof(infoProcess));
	infoStart.cb = sizeof(STARTUPINFO);
	infoStart.wShowWindow = SW_SHOW;

	isOK = (0 != ::CreateProcess(0, const_cast<LPTSTR>(cmd.c_str()),
								0, 0, FALSE, NORMAL_PRIORITY_CLASS, 0, 0, &infoStart, 
								&infoProcess));

	if(isOK)
	{
		if(waitClose)
		{
			::WaitForSingleObject(infoProcess.hProcess, INFINITE);
		}
		
		::CloseHandle(infoProcess.hThread);
		::CloseHandle(infoProcess.hProcess);
	}

	return isOK;
}
