REM needs-lock�����ꊇ�ݒ�
REM �{���Ȃ�Aadd import�̑O��
REM config�t�@�C����auto-props
REM ��*=svn:needs-lock��ݒ肵�Ă���
REM �̂��؂��Ǝv���܂��B

for /R %%F IN (*) DO (
	pushd %%~dpF
	svn propset svn:needs-lock ON %%~nF%%~xF
	popd
)

svn commit -m "needs-lock�����ǉ�"

pause