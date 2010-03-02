//---------------------------------------------------------------------------
/*!
 * \file MFCUtil.hpp
 * \brief MFC、windows APIに依存するユーティリティを定義
 *
 * $Revision:: 150             $
 * $Author:: yukio             $
 * $Date:: 2006-12-18 15:34:17#$
 */


//---------------------------------------------------------------------------
//プリプロセッサ
#ifndef INCLUDE_MFCUTIL_HPP
#define INCLUDE_MFCUTIL_HPP

//---------------------------------------------------------------------------
//利用するクラス


//---------------------------------------------------------------------------
//インクルードファイル
#include <util/TAppDefine.hpp>
#include <string>

#pragma warning(push)
#pragma warning(disable : BOOST_WAR_BLOCK)
#include <boost/format.hpp>
#pragma warning(pop)

//---------------------------------------------------------------------------
/// MFC、windows APIに依存するユーティリティを定義
namespace MFCUtil
{
	/// ModulePath取得
	TString getModuleFileName(HMODULE hHandle);

	/// Moduleのあるディレクトリを取得
	/*!
	 * 末尾に「\」が付きます。
	 */
	TString getModuleDir(HMODULE hHandle);

	/// Moduleの名前取得
	/*!
	 * getModuleFileNameがc:\hoge\abc\123.exe
	 * を返すとき
	 * 123を返します。
	 */
	TString getModuleName(HMODULE hHandle);

	/// モジュール情報取得用
	struct ModuleInfo {
		/// ファイル情報
		TString fileDescription;
		/// バージョン
		TString version;
		/// 著作権
		TString copyright;
	};

	/// モジュール情報を取得する。
	ModuleInfo getModuleInfo(const TCHAR* const pModuleName);
	/// パスからモジュール情報を取得する
	ModuleInfo getPathModuleInfo(const TCHAR* const pPath);

	DWORD getDlgCode(CWnd* pWnd, LPMSG lpMsg=NULL);

	/// フォーカス設定
	/*!
	 * フォーカスを取得するウインドウがEdit系の場合は、全選択も行う
	 */
	void setFocus(CWnd* pWnd);

	/// 文字列からフォントを生成
	bool createLogFont(LOGFONT* logFont, const TString& value);
	bool createFont(CFont& font, const TString& value);

	/// 直接指定でフォントを生成
	bool createFontDirect(CFont& font, 
		const double scaling,
		const int point, LPCTSTR faceName, 
		const bool bold=false, const bool italic=false, 
		const BYTE charSet=DEFAULT_CHARSET,
		const BYTE pitchAndFamily=FF_DONTCARE);

	/// フォントから文字列を生成
	TString fontToString(CFont& font);
	/// フォントから文字列を生成
	TString fontToStringDirect(
		const int point, LPCTSTR faceName, 
		const bool bold=false, const bool italic=false, 
		const BYTE charSet=DEFAULT_CHARSET,
		const BYTE pitchAndFamily=FF_DONTCARE);

	/// ユーザロケールをstring型で取得
	std::string getUserLocale();

	/// GetLastErrorの理由を文字列で取得
	TString getLastErrorMsg();

	/// CHttpConnection, CHttpFile用auto_ptrみたいなの
	/*!
	 * Closeしてからデストラクタを呼ばないといちいちワーニング
	 * が表示されるから。デストラクタでクローズするなら、文句
	 * 言うような事ではないと思うのだが・・・。
	 */
	template<typename T>
	class ClosePtr
	{
	public:
		ClosePtr(T* pT)
			 : m_pT(pT)
		{
		}

		~ClosePtr()
		{
			m_pT->Close();
			delete m_pT;
			m_pT = 0;
		}

		T* operator->()
		{
			return m_pT;
		}

		T* get()
		{
			return m_pT;
		}

		T* release()
		{
			T* pTmp = m_pT;
			m_pT = 0;
			return m_pTmp;
		}
		
	private:
		/// コピーコンストラクタ禁止
		ClosePtr(const ClosePtr& other);
		/// 代入演算子禁止
		ClosePtr& operator=(const ClosePtr& rhs);

	private:
		T* m_pT;
	};

	/// CException* クラスからエラーメッセージ取得
	TString getCause(CException* pEx);

	/// アプリケーションを起動する
	bool execute(const TString& cmd, bool waitClose);
}

#endif // INCLUDE_MFCUTIL_HPP
