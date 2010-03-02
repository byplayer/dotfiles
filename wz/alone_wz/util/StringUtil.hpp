//---------------------------------------------------------------------------
/*!
 * \file StringUtil.h
 * \brief 
 *
 * $Revision:: 150             $
 * $Author:: yukio             $
 * $Date:: 2006-12-18 15:34:17#$
 */


//---------------------------------------------------------------------------
//プリプロセッサ
#ifndef INCLUDE_STRINGUTIL_H
#define INCLUDE_STRINGUTIL_H

//---------------------------------------------------------------------------
//利用するクラス


//---------------------------------------------------------------------------
//インクルードファイル
#include <string>

/// 
namespace StringUtil
{
	/// 文字列を置換する
	/*!
	 * \pram target
	 *    置換対象の文字列
	 *
	 * \param oldStr
	 *    置換する前の文字列
	 *
	 * \param newStr
	 *    置換後の文字列
	 *
	 * \return
	 *    置換した数
	 */
	template<class Ch, class Tr, class Alloc>
	int replace(std::basic_string<Ch, Tr, Alloc>& target, 
			const std::basic_string<Ch, Tr, Alloc>& oldStr, 
			const std::basic_string<Ch, Tr, Alloc>& newStr)
	{
		int replaceCount = 0;

		typedef std::basic_string<Ch, Tr, Alloc> str_type;

		str_type::size_type searchPos = 0;
		str_type::size_type findPos = 0;

		str_type result;

		for(;;)
		{
			findPos = StringUtil::find(target, oldStr, searchPos);
			if(str_type::npos == findPos)
			{
				break;
			}

			result += target.substr(searchPos, (findPos - searchPos));
			result += newStr;
			searchPos = findPos + oldStr.length();
			++replaceCount;
		}

		if(searchPos < target.length())
		{
			result += target.substr(searchPos);
		}

		target = result;

		return replaceCount;
	}

	/// 文字列を置換する
	/*!
	 * \pram target
	 *    置換対象の文字列
	 *
	 * \param oldStr
	 *    置換する前の文字列
	 *
	 * \param newStr
	 *    置換後の文字列
	 *
	 * \return
	 *    置換した数
	 */
	template<class Ch, class Tr, class Alloc>
	int replace(std::basic_string<Ch, Tr, Alloc>& target, 
			const char* pOldStr, 
			const char* pNewStr)
	{
		return replace(target, string(pOldStr), string(pNewStr));
	}

	/// 文字列を置換する
	/*!
	 * \pram target
	 *    置換対象の文字列
	 *
	 * \param oldStr
	 *    置換する前の文字列
	 *
	 * \param newStr
	 *    置換後の文字列
	 *
	 * \return
	 *    置換した数
	 */
	template<class Ch, class Tr, class Alloc>
	int replace(std::basic_string<Ch, Tr, Alloc>& target, 
			const wchar_t* pOldStr, 
			const wchar_t* pNewStr)
	{
		return replace(target, wstring(pOldStr), wstring(pNewStr));
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
	std::string::size_type find(const std::string& target
						, const std::string& searchWord
						, std::string::size_type pos = std::string::npos);

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
	std::wstring::size_type find(const std::wstring& target
						, const std::wstring& searchWord
						, std::wstring::size_type pos = std::wstring::npos);

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
	std::string::size_type rfind(const std::string& target
							, const std::string& searchWord);


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
	std::wstring::size_type rfind(const std::wstring& target
							, const std::wstring& searchWord);

	/// 文字列の前後にあるスペースを削除
	void trim(std::string& target);

	/// 文字列の前後にあるスペースを削除
	void trim(std::wstring& target);

	/// 文字列の前後にあるスペースを削除
	std::wstring trimRet(std::wstring target);

} // StringUtil

//---------------------------------------------------------------------------
//インラインメソッド


#endif // INCLUDE_STRINGUTIL_H
