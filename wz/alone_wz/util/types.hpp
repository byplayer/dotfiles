//---------------------------------------------------------------------------
/*!
 * \file types.hpp
 * \brief 便利データ型定義
 *
 * $Revision:: 150             $
 * $Author:: yukio             $
 * $Date:: 2006-12-18 15:34:17#$
 */


//---------------------------------------------------------------------------
//プリプロセッサ
#ifndef INCLUDE_TYPES_HPP
#define INCLUDE_TYPES_HPP

//---------------------------------------------------------------------------
//利用するクラス


//---------------------------------------------------------------------------
//インクルードファイル
#include "util/TAppDefine.hpp"
#include <vector>

#pragma warning(push)
#pragma warning(disable : BOOST_WAR_BLOCK)
#include <boost/format.hpp>
#pragma warning(pop)

//---------------------------------------------------------------------------
/// TCHAR用format
typedef boost::basic_format<TCHAR> TFormat;

#ifdef _UNICODE
#define TMemset wmemset
#define TIFstream wifstream
#else
#define TMemset memset
#define TIFstream ifstream
#endif

//---------------------------------------------------------------------------
/// 文字列リスト型
typedef std::vector<TString> TStringList_type;
typedef std::vector<TStringList_type> TStringListList_type;

/// トレイ常駐アプリケーションの例外クラス
/**
 * what関数で、TCHAR*を返すようになっています。
 * std::exceptionだとwhatでchar*が返ってくるので
 * UNICODEライブラリを使ったら不便かなという事で。
 */
class TAppException
{
public:
	TAppException(const TString& msg)
		 : m_msg(msg)
	{
	}

	virtual const TCHAR* what() const
	{
		return m_msg.c_str();
	}

private:
	TString m_msg;
};


#endif // INCLUDE_TYPES_HPP
