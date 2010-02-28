REM needs-lock属性一括設定
REM 本来なら、add importの前に
REM configファイルのauto-props
REM に*=svn:needs-lockを設定しておく
REM のが筋かと思います。

for /R %%F IN (*) DO (
	pushd %%~dpF
	svn propset svn:needs-lock ON %%~nF%%~xF
	popd
)

svn commit -m "needs-lock属性追加"

pause