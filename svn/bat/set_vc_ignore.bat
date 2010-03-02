REM needs-lock属性一括設定
REM 本来なら、add importの前に
REM configファイルのauto-props
REM に*=svn:needs-lockを設定しておく
REM のが筋かと思います。

SET IGNORE_FILE=C:\tools\bin\ig_prop.txt

svn propset svn:ignore -F %IGNORE_FILE% .\

svn commit -m " * 開発時に作成されるファイルをignore属性へ追加"

