REM needs-lock�����ꊇ�ݒ�
REM �{���Ȃ�Aadd import�̑O��
REM config�t�@�C����auto-props
REM ��*=svn:needs-lock��ݒ肵�Ă���
REM �̂��؂��Ǝv���܂��B

SET IGNORE_FILE=C:\tools\bin\ig_prop.txt

svn propset svn:ignore -F %IGNORE_FILE% .\

svn commit -m " * �J�����ɍ쐬�����t�@�C����ignore�����֒ǉ�"

