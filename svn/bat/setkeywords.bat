REM keyword属性一括設定
REM 本来なら、add importの前に
REM configファイルのauto-props
REM にkeywordsを設定しておく
REM のが筋かと思います。

for /R %%F IN (*.cpp *.h *.hpp *.bat *.txt *.ini *.php *.inc *.phtml *.html *.css *.tpl *.rb *.sql *.org *.py *.cs) DO (
	pushd %%~dpF
	svn propset svn:keywords "Id Date Author Revision HeadURL"  %%~nF%%~xF
	popd
)

svn commit -m "keywords 属性追加"

pause