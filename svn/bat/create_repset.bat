@echo off
REM �������ɓn���ꂽURL�̃��|�W�g�����쐬
REM ���̌�A����ȉ��� trunk tags branches�����܂�

if "" == "%1" (
	echo �쐬���郊�|�W�g�����w�肵�ĉ������B
	echo �� : create_repset.bat http://xxxx.xxx.xxx/svnroot/aaa
	GOTO END
)

SET __REP_ROOT=%1

echo �V�K���|�W�g���쐬
svn mkdir %__REP_ROOT% -m "�V�K���|�W�g���쐬"

echo trunk�t�H���_�쐬
svn mkdir %__REP_ROOT%/trunk -m "���|�W�g����trunk�t�H���_�쐬"

echo tags�t�H���_�쐬
svn mkdir %__REP_ROOT%/tags -m "���|�W�g����tags�t�H���_�쐬"

echo branches�t�H���_�쐬
svn mkdir %__REP_ROOT%/branches -m "���|�W�g����branches�t�H���_�쐬"

:END