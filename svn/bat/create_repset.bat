@echo off
REM 第一引数に渡されたURLのリポジトリを作成
REM その後、それ以下に trunk tags branchesを作ります

if "" == "%1" (
	echo 作成するリポジトリを指定して下さい。
	echo 例 : create_repset.bat http://xxxx.xxx.xxx/svnroot/aaa
	GOTO END
)

SET __REP_ROOT=%1

echo 新規リポジトリ作成
svn mkdir %__REP_ROOT% -m "新規リポジトリ作成"

echo trunkフォルダ作成
svn mkdir %__REP_ROOT%/trunk -m "リポジトリにtrunkフォルダ作成"

echo tagsフォルダ作成
svn mkdir %__REP_ROOT%/tags -m "リポジトリにtagsフォルダ作成"

echo branchesフォルダ作成
svn mkdir %__REP_ROOT%/branches -m "リポジトリにbranchesフォルダ作成"

:END