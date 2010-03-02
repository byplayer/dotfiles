//---------------------------------------------------------------------------
/*!
 * \file MFCUtil.hpp
 * \brief MFC�Awindows API�Ɉˑ����郆�[�e�B���e�B���`
 *
 * $Revision:: 150             $
 * $Author:: yukio             $
 * $Date:: 2006-12-18 15:34:17#$
 */


//---------------------------------------------------------------------------
//�v���v���Z�b�T
#ifndef INCLUDE_MFCUTIL_HPP
#define INCLUDE_MFCUTIL_HPP

//---------------------------------------------------------------------------
//���p����N���X


//---------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
#include <util/TAppDefine.hpp>
#include <string>

#pragma warning(push)
#pragma warning(disable : BOOST_WAR_BLOCK)
#include <boost/format.hpp>
#pragma warning(pop)

//---------------------------------------------------------------------------
/// MFC�Awindows API�Ɉˑ����郆�[�e�B���e�B���`
namespace MFCUtil
{
	/// ModulePath�擾
	TString getModuleFileName(HMODULE hHandle);

	/// Module�̂���f�B���N�g�����擾
	/*!
	 * �����Ɂu\�v���t���܂��B
	 */
	TString getModuleDir(HMODULE hHandle);

	/// Module�̖��O�擾
	/*!
	 * getModuleFileName��c:\hoge\abc\123.exe
	 * ��Ԃ��Ƃ�
	 * 123��Ԃ��܂��B
	 */
	TString getModuleName(HMODULE hHandle);

	/// ���W���[�����擾�p
	struct ModuleInfo {
		/// �t�@�C�����
		TString fileDescription;
		/// �o�[�W����
		TString version;
		/// ���쌠
		TString copyright;
	};

	/// ���W���[�������擾����B
	ModuleInfo getModuleInfo(const TCHAR* const pModuleName);
	/// �p�X���烂�W���[�������擾����
	ModuleInfo getPathModuleInfo(const TCHAR* const pPath);

	DWORD getDlgCode(CWnd* pWnd, LPMSG lpMsg=NULL);

	/// �t�H�[�J�X�ݒ�
	/*!
	 * �t�H�[�J�X���擾����E�C���h�E��Edit�n�̏ꍇ�́A�S�I�����s��
	 */
	void setFocus(CWnd* pWnd);

	/// �����񂩂�t�H���g�𐶐�
	bool createLogFont(LOGFONT* logFont, const TString& value);
	bool createFont(CFont& font, const TString& value);

	/// ���ڎw��Ńt�H���g�𐶐�
	bool createFontDirect(CFont& font, 
		const double scaling,
		const int point, LPCTSTR faceName, 
		const bool bold=false, const bool italic=false, 
		const BYTE charSet=DEFAULT_CHARSET,
		const BYTE pitchAndFamily=FF_DONTCARE);

	/// �t�H���g���當����𐶐�
	TString fontToString(CFont& font);
	/// �t�H���g���當����𐶐�
	TString fontToStringDirect(
		const int point, LPCTSTR faceName, 
		const bool bold=false, const bool italic=false, 
		const BYTE charSet=DEFAULT_CHARSET,
		const BYTE pitchAndFamily=FF_DONTCARE);

	/// ���[�U���P�[����string�^�Ŏ擾
	std::string getUserLocale();

	/// GetLastError�̗��R�𕶎���Ŏ擾
	TString getLastErrorMsg();

	/// CHttpConnection, CHttpFile�pauto_ptr�݂����Ȃ�
	/*!
	 * Close���Ă���f�X�g���N�^���Ă΂Ȃ��Ƃ����������[�j���O
	 * ���\������邩��B�f�X�g���N�^�ŃN���[�Y����Ȃ�A����
	 * �����悤�Ȏ��ł͂Ȃ��Ǝv���̂����E�E�E�B
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
		/// �R�s�[�R���X�g���N�^�֎~
		ClosePtr(const ClosePtr& other);
		/// ������Z�q�֎~
		ClosePtr& operator=(const ClosePtr& rhs);

	private:
		T* m_pT;
	};

	/// CException* �N���X����G���[���b�Z�[�W�擾
	TString getCause(CException* pEx);

	/// �A�v���P�[�V�������N������
	bool execute(const TString& cmd, bool waitClose);
}

#endif // INCLUDE_MFCUTIL_HPP
