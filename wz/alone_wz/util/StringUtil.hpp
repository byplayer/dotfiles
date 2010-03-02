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
//�v���v���Z�b�T
#ifndef INCLUDE_STRINGUTIL_H
#define INCLUDE_STRINGUTIL_H

//---------------------------------------------------------------------------
//���p����N���X


//---------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
#include <string>

/// 
namespace StringUtil
{
	/// �������u������
	/*!
	 * \pram target
	 *    �u���Ώۂ̕�����
	 *
	 * \param oldStr
	 *    �u������O�̕�����
	 *
	 * \param newStr
	 *    �u����̕�����
	 *
	 * \return
	 *    �u��������
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

	/// �������u������
	/*!
	 * \pram target
	 *    �u���Ώۂ̕�����
	 *
	 * \param oldStr
	 *    �u������O�̕�����
	 *
	 * \param newStr
	 *    �u����̕�����
	 *
	 * \return
	 *    �u��������
	 */
	template<class Ch, class Tr, class Alloc>
	int replace(std::basic_string<Ch, Tr, Alloc>& target, 
			const char* pOldStr, 
			const char* pNewStr)
	{
		return replace(target, string(pOldStr), string(pNewStr));
	}

	/// �������u������
	/*!
	 * \pram target
	 *    �u���Ώۂ̕�����
	 *
	 * \param oldStr
	 *    �u������O�̕�����
	 *
	 * \param newStr
	 *    �u����̕�����
	 *
	 * \return
	 *    �u��������
	 */
	template<class Ch, class Tr, class Alloc>
	int replace(std::basic_string<Ch, Tr, Alloc>& target, 
			const wchar_t* pOldStr, 
			const wchar_t* pNewStr)
	{
		return replace(target, wstring(pOldStr), wstring(pNewStr));
	}

	/// ������̌���
	/*!
	 * \param target
	 *    �����Ώۂ̕�����
	 *
	 * \param searchWord
	 *    �������镶����
	 *
	 * \param pos
	 *    �������J�n����ʒu�Bnpos�̎��A�擪���猟��
	 *
	 *
	 * \return
	 *    ���������������0����n�܂�C���f�b�N�X��Ԃ��B
	 *    �����񂪌�����Ȃ������ꍇ�́Anpos��Ԃ��B
	 */
	std::string::size_type find(const std::string& target
						, const std::string& searchWord
						, std::string::size_type pos = std::string::npos);

	/// ������̌���
	/*!
	 * \param target
	 *    �����Ώۂ̕�����
	 *
	 * \param searchWord
	 *    �������镶����
	 *
	 * \param pos
	 *    �������J�n����ʒu�Bnpos�̎��A�擪���猟��
	 *
	 *
	 * \return
	 *    ���������������0����n�܂�C���f�b�N�X��Ԃ��B
	 *    �����񂪌�����Ȃ������ꍇ�́Anpos��Ԃ��B
	 */
	std::wstring::size_type find(const std::wstring& target
						, const std::wstring& searchWord
						, std::wstring::size_type pos = std::wstring::npos);

	/// ������𖖔����猟�����A�Ō�ɕ����񂪌����ʒu��Ԃ�
	/*!
	 * \param target
	 *    �����Ώۂ̕�����
	 *
	 * \param searchWord
	 *    �������镶����
	 *
	 * \return
	 *    ���������������0����n�܂�C���f�b�N�X(�擪��0)��Ԃ��B
	 *    �����񂪌�����Ȃ������ꍇ�́Anpos��Ԃ��B
	 */
	std::string::size_type rfind(const std::string& target
							, const std::string& searchWord);


	/// ������𖖔����猟�����A�Ō�ɕ����񂪌����ʒu��Ԃ�
	/*!
	 * \param target
	 *    �����Ώۂ̕�����
	 *
	 * \param searchWord
	 *    �������镶����
	 *
	 * \return
	 *    ���������������0����n�܂�C���f�b�N�X(�擪��0)��Ԃ��B
	 *    �����񂪌�����Ȃ������ꍇ�́Anpos��Ԃ��B
	 */
	std::wstring::size_type rfind(const std::wstring& target
							, const std::wstring& searchWord);

	/// ������̑O��ɂ���X�y�[�X���폜
	void trim(std::string& target);

	/// ������̑O��ɂ���X�y�[�X���폜
	void trim(std::wstring& target);

	/// ������̑O��ɂ���X�y�[�X���폜
	std::wstring trimRet(std::wstring target);

} // StringUtil

//---------------------------------------------------------------------------
//�C�����C�����\�b�h


#endif // INCLUDE_STRINGUTIL_H
