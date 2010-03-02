//---------------------------------------------------------------------------
// �t�@�C����	: StringUtil.cpp
// $Revision:: 150             $
// $Author:: yukio             $
// $Date:: 2006-12-18 15:34:17#$

//---------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
#include "stdafx.h"
#include "StringUtil.hpp"

using namespace std;

//---------------------------------------------------------------------------
//�v���v���Z�b�T
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
namespace
{
	// �����񌟍�
	string::size_type findChar(const std::string& str, const std::string& findStr,
						std::string::size_type searchPos = std::string::npos)
	{
		// findStr���󕶎��Ȃ�A������Ȃ���Ԃ�
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

		// findStri[0]���}���`�o�C�g�̂P�o�C�g�ڂ̎��́A
		// �n��unsigned int �ɂQ�o�C�g���f�[�^���l�ߍ���
		// �K�v������
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

			// ���������ʒu����Astr�̖����܂ł̒�����
			// findStr���Z����Έ�v�͂Ȃ�
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

	/// char* ����int�̒l�擾
	/*!
	 * (*pC) ���V���O���o�C�g�̏ꍇ�́A���̒l�B
	 *
	 * (*pC) ���}���`�o�C�g�̏ꍇ�́A((*pC) << 8) | (*(++pC))
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

	/// �z���C�g�X�y�[�X��
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
			(L'�@' == c))
		{
			return true;
		}

		return false;
	}
}

//---------------------------------------------------------------------------
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
std::string::size_type StringUtil::find(const std::string& target
					, const std::string& searchWord
					, std::string::size_type pos /* = std::string::npos */)
{
	return findChar(target, searchWord, pos);
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
std::string::size_type StringUtil::rfind(const std::string& target
								, const std::string& searchWord)
{
	if(target.empty() || searchWord.empty())
	{
		return string::npos;
	}

	// �P���������Ɏg���l������Ă���
	// findStri[0]���}���`�o�C�g�̂P�o�C�g�ڂ̎��́A
	// �n��unsigned int �ɂQ�o�C�g���f�[�^���l�ߍ���
	// �K�v������
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
			// ������Ȃ�����
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
std::wstring::size_type StringUtil::rfind(const std::wstring& target
						, const std::wstring& searchWord)
{
	return target.rfind(searchWord);
}

/// ������̑O��ɂ���A�w��̕������폜
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

/// ������̑O��ɂ���X�y�[�X���폜
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


/// ������̑O��ɂ���X�y�[�X���폜
std::wstring StringUtil::trimRet(std::wstring target)
{
	trim(target);
	return target;
}
