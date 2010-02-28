//---------------------------------------------------------------------------
// ファイル名	: StringUtil.cpp
// $Revision:: 150             $
// $Author:: yukio             $
// $Date:: 2006-12-18 15:34:17#$

//---------------------------------------------------------------------------
//インクルードファイル
#include "stdafx.h"
#include "StringUtil.hpp"

using namespace std;

//---------------------------------------------------------------------------
//プリプロセッサ
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
namespace
{
	// 文字列検索
	string::size_type findChar(const std::string& str, const std::string& findStr,
						std::string::size_type searchPos = std::string::npos)
	{
		// findStrが空文字なら、見つからないを返す
		if(findStr.empty())
		{
			return string::npos;
		}

		if(searchPos == string::npos)
		{
			searchPos = 0;
		}

		if(str.length() <= searchPos)
		{
			return string::npos;
		}

		// findStri[0]がマルチバイトの１バイト目の時は、
		// 渡すunsigned int に２バイト分データを詰め込む
		// 必要がある
		unsigned int searchInt = static_cast<unsigned int>(findStr[0] & 0xFF);
		if(_ismbblead(searchInt))
		{
			if(findStr.length() >= 2)
			{
				searchInt = (((searchInt << 8)) | static_cast<unsigned int>(findStr[1] & 0xFF));
			}
			else
			{
				return string::npos;
			}
		}
		
		for(;;)
		{
			unsigned char* searchPtr = (unsigned char *)&str[searchPos];

			const unsigned char* findChar = _mbschr(searchPtr, searchInt);
			if(0 == findChar)
			{
				return string::npos;
			}

			string::size_type findPos = (findChar - (const unsigned char *)&str[0]);

			// 見つかった位置から、strの末尾までの長さが
			// findStrより短ければ一致はなし
			if((str.length() - findPos) < findStr.length())
			{
				return string::npos;
			}

			const string work = str.substr(findPos, findStr.length());

			if(0 == ::_mbscmp((const unsigned char *)(work.c_str()), (const unsigned char *)findStr.c_str()))
			{
				return findPos;
			}
			else
			{
				searchPos = findPos + 1;
			}
		}

//		return string::npos;
	}

	/// char* からintの値取得
	/*!
	 * (*pC) がシングルバイトの場合は、その値。
	 *
	 * (*pC) がマルチバイトの場合は、((*pC) << 8) | (*(++pC))
	 */
	unsigned int getIntVal(const unsigned char* pC)
	{
		unsigned int intVal = static_cast<unsigned int>((*pC) & 0xFF);
		if(_ismbblead(intVal))
		{
			++pC;
			intVal = (((intVal << 8)) | static_cast<unsigned int>((*pC) & 0xFF));
		}

		return intVal;
	}

	/// ホワイトスペースか
	bool isSpace(unsigned int c)
	{
		if((0x20 == c) ||
			((0x09 <= c) && (c <= 0x0D)) ||
			(0x8140 == c))
		{
			return true;
		}

		return false;
	}

	bool isSpace(wchar_t c)
	{
		if((0x20 == c) ||
			((0x09 <= c) && (c <= 0x0D)) ||
			(L'　' == c))
		{
			return true;
		}

		return false;
	}
}

//---------------------------------------------------------------------------
/// 文字列の検索
/*!
 * \param target
 *    検索対象の文字列
 *
 * \param searchWord
 *    検索する文字列
 *
 * \param pos
 *    検索を開始する位置。nposの時、先頭から検索
 *
 *
 * \return
 *    見つかった文字列の0から始まるインデックスを返す。
 *    文字列が見つからなかった場合は、nposを返す。
 */
std::string::size_type StringUtil::find(const std::string& target
					, const std::string& searchWord
					, std::string::size_type pos /* = std::string::npos */)
{
	return findChar(target, searchWord, pos);
}

/// 文字列の検索
/*!
 * \param target
 *    検索対象の文字列
 *
 * \param searchWord
 *    検索する文字列
 *
 * \param pos
 *    検索を開始する位置。nposの時、先頭から検索
 *
 *
 * \return
 *    見つかった文字列の0から始まるインデックスを返す。
 *    文字列が見つからなかった場合は、nposを返す。
 */
std::wstring::size_type StringUtil::find(const std::wstring& target
					, const std::wstring& searchWord
					, std::wstring::size_type pos /* = std::wstring::npos */)
{
	if(pos == wstring::npos)
	{
		pos = 0;
	}
	return target.find(searchWord, pos);
}

/// 文字列を末尾から検索し、最後に文字列が現れる位置を返す
/*!
 * \param target
 *    検索対象の文字列
 *
 * \param searchWord
 *    検索する文字列
 *
 * \return
 *    見つかった文字列の0から始まるインデックス(先頭が0)を返す。
 *    文字列が見つからなかった場合は、nposを返す。
 */
std::string::size_type StringUtil::rfind(const std::string& target
								, const std::string& searchWord)
{
	if(target.empty() || searchWord.empty())
	{
		return string::npos;
	}

	// １文字検索に使う値を作っておく
	// findStri[0]がマルチバイトの１バイト目の時は、
	// 渡すunsigned int に２バイト分データを詰め込む
	// 必要がある
	unsigned int searchInt = static_cast<unsigned int>(searchWord[0] & 0xFF);
	if(_ismbblead(searchInt))
	{
		if(searchWord.length() >= 2)
		{
			searchInt = (((searchInt << 8)) | static_cast<unsigned int>(searchWord[1] & 0xFF));
		}
		else
		{
			return string::npos;
		}
	}

	string::size_type endPos = string::npos;
	string workTarget;

	for(;;)
	{
		workTarget = target.substr(0, endPos);
		unsigned char* searchPtr = (unsigned char *)&workTarget[0];

		const unsigned char* pFindPos = _mbsrchr(searchPtr, searchInt);
		if(!pFindPos)
		{
			// 見つからなかった
			return string::npos;
		}

		string::size_type findPos = (pFindPos - searchPtr);
		if(searchWord.length() <= (target.length() - findPos))
		{
			const string work = target.substr(findPos, searchWord.length());
			if(0 == ::_mbscmp((const unsigned char *)(work.c_str()), (const unsigned char *)searchWord.c_str()))
			{
				return findPos;
			}
			else
			{
				endPos = findPos;
			}
		}
		else
		{
			endPos = findPos;
		}
	}

//	return string::npos;
}

/// 文字列を末尾から検索し、最後に文字列が現れる位置を返す
/*!
 * \param target
 *    検索対象の文字列
 *
 * \param searchWord
 *    検索する文字列
 *
 * \return
 *    見つかった文字列の0から始まるインデックス(先頭が0)を返す。
 *    文字列が見つからなかった場合は、nposを返す。
 */
std::wstring::size_type StringUtil::rfind(const std::wstring& target
						, const std::wstring& searchWord)
{
	return target.rfind(searchWord);
}

/// 文字列の前後にある、指定の文字を削除
void StringUtil::trim(std::string& target)
{
	if(target.empty())
	{
		return;
	}
	
	const unsigned char* pStr = (const unsigned char*)target.c_str();
	const unsigned char* pOldPos = 0;
	string::size_type startPos = 0;

	while(startPos != target.length() && isSpace(getIntVal(pStr)))
	{
		pOldPos = pStr;
		pStr = _mbsinc((const unsigned char*)(pStr));
		startPos += (pStr - pOldPos);
	}

	if(0 != startPos)
	{
		if(startPos == target.length())
		{
			target.clear();
		}
		else
		{
			target = target.substr(startPos);
		}
	}

	if(target.empty())
	{
		return;
	}

	string::size_type lastPos = target.length()-1;
	pStr = (const unsigned char*)&target[lastPos];
	const unsigned char* pStart = (const unsigned char*)&target[0];
	if(2 <= target.length())
	{
		if(_ismbblead(target[target.length()-2]))
		{
			lastPos = target.length()-2;
			pStr = (const unsigned char*)&target[lastPos];
		}
	}

	while(isSpace(getIntVal(pStr)))
	{
		if(pStart == pStr)
		{
			break;
		}

		pOldPos = pStr;
		pStr = _mbsdec(pStart, pStr);
		lastPos -= (pOldPos - pStr);
	}

	target = target.substr(0, (lastPos + 1));
}

/// 文字列の前後にあるスペースを削除
void StringUtil::trim(std::wstring& target)
{
	if(target.empty())
	{
		return;
	}
	
	wstring::size_type startPos = 0;

	while(startPos != target.length() && isSpace(target[startPos]))
	{
		++startPos;
	}

	if(0 != startPos)
	{
		if(startPos == target.length())
		{
			target.clear();
		}
		else
		{
			target = target.substr(startPos);
		}
	}

	if(target.empty())
	{
		return;
	}

	wstring::size_type lastPos = target.length()-1;

	while(isSpace(target[lastPos]))
	{
		if(0 == lastPos)
		{
			break;
		}

		--lastPos;
	}

	target = target.substr(0, (lastPos + 1));
}


/// 文字列の前後にあるスペースを削除
std::wstring StringUtil::trimRet(std::wstring target)
{
	trim(target);
	return target;
}
