REM keyword�����ꊇ�ݒ�
REM �{���Ȃ�Aadd import�̑O��
REM config�t�@�C����auto-props
REM ��keywords��ݒ肵�Ă���
REM �̂��؂��Ǝv���܂��B

for /R %%F IN (*.cpp *.h *.hpp *.bat *.txt *.ini *.php *.inc *.phtml *.html *.css *.tpl *.rb *.sql *.org *.py *.cs) DO (
	pushd %%~dpF
	svn propset svn:keywords "Id Date Author Revision HeadURL"  %%~nF%%~xF
	popd
)

svn commit -m "keywords �����ǉ�"

pause