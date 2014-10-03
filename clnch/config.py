import os
import sys
from clnch import *


# 設定処理
def configure(window):

    # --------------------------------------------------------------------
    # F1 キーでヘルプファイルを起動する
    def command_Help():
        print("Helpを起動 :")
        help_path = os.path.join( os.path.split(sys.argv[0])[0], 'doc\\index.html' )
        shellExecute( None, None, help_path, "", "" )
        print("Done.\n")

    window.cmd_keymap[ "F1" ] = command_Help

    # --------------------------------------------------------------------
    # Ctrl-E で、入力中のファイルパスを編集する
    window.cmd_keymap[ "C-E" ] = window.command.Edit

    # --------------------------------------------------------------------
    # テキストエディタを設定する
    window.editor = "C:/goto/tools/SublimeText2/sublime_text.exe"

    # --------------------------------------------------------------------
    # ファイルタイプごとの動作設定
    window.association_list += [
        ( "*.mpg *.mpeg *.avi *.wmv", window.ShellExecuteCommand( None, "wmplayer.exe", "/prefetch:7 /Play %param%", "" ) ),
    ]

    # --------------------------------------------------------------------
    # 非アクティブ時の時計の形式
    if 1:
        # 年と秒を省略した短い形式
        window.clock_format = "%m/%d(%a) %H:%M"
    else:
        # 年月日(曜日) 時分秒 の全てを表示する
        window.clock_format = "%Y/%m/%d(%a) %H:%M:%S"

    # --------------------------------------------------------------------
    # 空欄コマンド
    #   コマンド名なしでEnterを押したときに実行されるコマンドです。
    #   この例では、ほかのアプリケーションをフォアグラウンド化するために使います。
    def command_QuickActivate( args, mod ):

        def callback( wnd, arg ):
            process_name, class_name = arg[0], arg[1]
            if (process_name==None or wnd.getProcessName()==process_name) and (class_name==None or wnd.getClassName()==class_name):
                wnd = wnd.getLastActivePopup()
                wnd.setForeground(True)
                return False
            return True

        if mod==MODKEY_SHIFT:
            pyauto.Window.enum( callback, ["cfiler.exe",None] )
        elif mod==MODKEY_CTRL:
            pyauto.Window.enum( callback, ["notepad.exe","Notepad"] )
        elif mod==MODKEY_SHIFT|MODKEY_CTRL:
            pyauto.Window.enum( callback, ["mintty.exe","MinTTY"] )

    window.launcher.command_list += [ ( "", command_QuickActivate ) ]

    # --------------------------------------------------------------------
    # "NetDrive" コマンド
    #   ネットワークドライブを割り当てるか解除を行います。
    #    NetDrive;L;\\server\share : \\machine\public を Lドライブに割り当てます
    #    NetDrive;L                : Lドライブの割り当てを解除します
    def command_NetDrive(args):
        
        if len(args)>=1:
            drive_letter = args[0]
            if len(args)>=2:
                path = args[1]
                checkNetConnection(path)
                if window.subProcessCall( [ "net", "use", drive_letter+":", os.path.normpath(path), "/yes" ], cwd=None, env=None, enable_cancel=False )==0:
                    print("%s に %sドライブを割り当てました。" % ( path, drive_letter ))
            else:
                if window.subProcessCall( [ "net", "use", drive_letter+":", "/D" ], cwd=None, env=None, enable_cancel=False )==0:
                    print("%sドライブの割り当てを解除しました。" % ( drive_letter ))
        else:
            print("ドライブの割り当て : NetDrive;<ドライブ名>;<パス>")
            print("ドライブの解除     : NetDrive;<ドライブ名>")

    # --------------------------------------------------------------------
    # コマンドを登録する
    window.launcher.command_list += [
        ( "alc",       window.ShellExecuteCommand( None, "C:/Users/yukio.goto/AppData/Local/Google/Chrome/Application/chrome.exe", "http://eow.alc.co.jp/%param%/UTF-8/", "C:/Users/yukio.goto/AppData/Local/Google/Chrome/Application/" ) ),
        ( "Becky",     window.ShellExecuteCommand( None, "C:/Program Files (x86)/OnlineServiceGate/OnlineServiceGate.Client.MailerStarterForBecky.exe", "", "C:/Program Files (x86)/OnlineServiceGate/" ) ),
        ( "chrome",    window.ShellExecuteCommand( None, "C:/Users/yukio.goto/AppData/Local/Google/Chrome/Application/chrome.exe", "", "C:/Users/yukio.goto/AppData/Local/Google/Chrome/Application/" ) ),
        ( "ie32",        window.ShellExecuteCommand( None, "C:/Program Files (x86)/Internet Explorer/iexplore.exe", "", "C:/Program Files (x86)/Internet Explorer/" ) ),
        ( "ie64",        window.ShellExecuteCommand( None, "C:/Program Files/Internet Explorer/iexplore.exe", "", "C:/Program Files/Internet Explorer/" ) ),
        ( "df",        window.ShellExecuteCommand( None, "C:/goto/tools/DF/DF.exe", "", "C:/goto/tools/DF" ) ),
        ( "eyes",      window.ShellExecuteCommand( None, "C:/Program Files (x86)/MA-EYES/MA-EYES.exe", "", "C:/Program Files (x86)/MA-EYES" ) ),
        ( "vbox",      window.ShellExecuteCommand( None, "C:/goto/tools/Oracle/VirtualBox/VirtualBox.exe", "", "C:/goto/tools/Oracle/VirtualBox" ) ),
        ( "Poderosa",  window.ShellExecuteCommand( None, "C:/goto/tools/Poderosa/Poderosa.exe", "", "C:/goto/tools/Poderosa" ) ),
        ( "GanttProject",  window.ShellExecuteCommand( None, "C:/goto/tools/GanttProject/ganttproject.exe", "", "C:/goto/tools/GanttProject" ) ),
        ( "wz",        window.ShellExecuteCommand( None, "C:/goto/tools/WZ Editor/WZEDITOR.EXE", "", "C:/goto/tools/WZ Editor" ) ),
        ( "kf",        window.ShellExecuteCommand( None, "C:/goto/tools/KF/KF.EXE", "", "C:/goto/tools/KF" ) ),
        ( "WinDirStat",window.ShellExecuteCommand( None, "C:/goto/tools/WinDirStat/windirstat.exe", "", "C:/goto/tools/WinDirStat" ) ),
        ( "projects",  window.ShellExecuteCommand( None, "s:/projects", "", "" ) ),
        ( "ProcMon",window.ShellExecuteCommand( None, "C:/goto/tools/Sysinternals/Procmon.exe", "", "C:/goto/tools/Sysinternals" ) ),
        ( "ProcExp",window.ShellExecuteCommand( None, "C:/goto/tools/Sysinternals/Procexp.exe", "", "C:/goto/tools/Sysinternals" ) ),
        ( "proxy",window.ShellExecuteCommand( None, "C:/squid/bin/squid_env.bat", "%param%", "C:/squid/bin/" ) ),
        ( "Meadow",window.ShellExecuteCommand( None, "C:/goto/tools/meadow/bin/RunMW32.exe", "", "C:/Goto/tools/meadow/bin" ) ),
        ( "tail",window.ShellExecuteCommand( None, "C:/Goto/tools/tail/tail.exe", "%param%", "C:/Goto/tools/tail/" ) ),
        ( "eclipse",window.ShellExecuteCommand( None, "C:/goto/tools/eclipse/eclipse.exe", "", "C:/goto/tools/eclipse/" ) ),
        ( "SublimeText",window.ShellExecuteCommand( None, "C:/goto/tools/SublimeText2/sublime_text.exe", "", "C:/goto/tools/SublimeText2/" ) ),
        ( "ADT",window.ShellExecuteCommand( None, "C:/goto/tools/adt-bundle-windows-x86_64/eclipse/eclipse.exe", "", "C:/goto/tools/adt-bundle-windows-x86_64/eclipse" ) ),
        ( "vagrant up",window.ShellExecuteCommand( None, "vagrant", "up", "C:/Goto/vagrant-devenv" ) ),
    ]

# リストウインドウの設定処理
def configure_ListWindow(window):

    # --------------------------------------------------------------------
    # F1 キーでヘルプファイルを表示する

    def command_Help(info):
        print( "Helpを起動 :" )
        help_path = os.path.join( getAppExePath(), 'doc\\index.html' )
        shellExecute( None, help_path, "", "" )
        print( "Done.\n" )

    window.keymap[ "F1" ] = command_Help
