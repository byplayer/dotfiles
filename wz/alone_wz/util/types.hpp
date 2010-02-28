//---------------------------------------------------------------------------
/*!
 * \file types.hpp
 * \brief �֗��f�[�^�^��`
 *
 * $Revision:: 150             $
 * $Author:: yukio             $
 * $Date:: 2006-12-18 15:34:17#$
 */


//---------------------------------------------------------------------------
//�v���v���Z�b�T
#ifndef INCLUDE_TYPES_HPP
#define INCLUDE_TYPES_HPP

//---------------------------------------------------------------------------
//���p����N���X


//---------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
#include "util/TAppDefine.hpp"
#include <vector>

#pragma warning(push)
#pragma warning(disable : BOOST_WAR_BLOCK)
#include <boost/format.hpp>
#pragma warning(pop)

//---------------------------------------------------------------------------
/// TCHAR�pformat
typedef boost::basic_format<TCHAR> TFormat;

#ifdef _UNICODE
#define TMemset wmemset
#define TIFstream wifstream
#else
#define TMemset memset
#define TIFstream ifstream
#endif

//---------------------------------------------------------------------------
/// �����񃊃X�g�^
typedef std::vector<TString> TStringList_type;
typedef std::vector<TStringList_type> TStringListList_type;

/// �g���C�풓�A�v���P�[�V�����̗�O�N���X
/**
 * what�֐��ŁATCHAR*��Ԃ��悤�ɂȂ��Ă��܂��B
 * std::exception����what��char*���Ԃ��Ă���̂�
 * UNICODE���C�u�������g������s�ւ��ȂƂ������ŁB
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
