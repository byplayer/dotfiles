import os
import sys
from clnch import *


# 設定処理
def configure(window):

    # --------------------------------------------------------------------
    # F1 キーでヘルプファイルを起動する
    def command_Help():
        print u"Helpを起動 :"
        help_path = os.path.join( os.path.split(sys.argv[0])[0], 'doc\\index.html' )
        shellExecute( None, None, help_path, u"", u"" )
        print u"Done.\n"

    window.cmd_keymap[ VK_F1 ] = command_Help

    # --------------------------------------------------------------------
    # Ctrl-E で、入力中のファイルパスを編集する
    window.cmd_keymap[ KeyEvent( VK_E, MODKEY_CTRL ) ] = window.command_Edit

    # --------------------------------------------------------------------
    # テキストエディタを設定する
    window.editor = u"WZEDITOR.exe"

    # --------------------------------------------------------------------
    # ファイルタイプごとの動作設定
    window.association_list += [
        ( "*.mpg *.mpeg *.avi *.wmv", window.command_ShellExecute( None, u"wmplayer.exe", "/prefetch:7 /Play %param%", u"" ) ),
    ]

    # --------------------------------------------------------------------
    # 非アクティブ時の時計の形式
    if 1:
        # 年と秒を省略した短い形式
        window.clock_format = u"%m/%d(%a) %H:%M"
    else:
        # 年月日(曜日) 時分秒 の全てを表示する
        window.clock_format = u"%Y/%m/%d(%a) %H:%M:%S"

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

    window.launcher.command_list += [ ( u"", command_QuickActivate ) ]

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
                    print u"%s に %sドライブを割り当てました。" % ( path, drive_letter )
            else:
                if window.subProcessCall( [ "net", "use", drive_letter+":", "/D" ], cwd=None, env=None, enable_cancel=False )==0:
                    print u"%sドライブの割り当てを解除しました。" % ( drive_letter )
        else:
            print u"ドライブの割り当て : NetDrive;<ドライブ名>;<パス>"
            print u"ドライブの解除     : NetDrive;<ドライブ名>"

    # --------------------------------------------------------------------
    # コマンドを登録する
    window.launcher.command_list += [
        ( u"alc",       window.command_ShellExecute( None, u"C:/Users/yukio.goto/AppData/Local/Google/Chrome/Application/chrome.exe", u"http://eow.alc.co.jp/%param%/UTF-8/", u"C:/Users/yukio.goto/AppData/Local/Google/Chrome/Application/" ) ),
        ( u"Becky",     window.command_ShellExecute( None, u"C:/Program Files (x86)/OnlineServiceGate/OnlineServiceGate.Client.MailerStarterForBecky.exe", u"", u"C:/Program Files (x86)/OnlineServiceGate/" ) ),
        ( u"chrome",    window.command_ShellExecute( None, u"C:/Users/yukio.goto/AppData/Local/Google/Chrome/Application/chrome.exe", u"", u"C:/Users/yukio.goto/AppData/Local/Google/Chrome/Application/" ) ),
        ( u"ie32",        window.command_ShellExecute( None, u"C:/Program Files (x86)/Internet Explorer/iexplore.exe", u"", u"C:/Program Files (x86)/Internet Explorer/" ) ),
        ( u"ie64",        window.command_ShellExecute( None, u"C:/Program Files/Internet Explorer/iexplore.exe", u"", u"C:/Program Files/Internet Explorer/" ) ),
        ( u"df",        window.command_ShellExecute( None, u"C:/goto/tools/DF/DF.exe", u"", u"C:/goto/tools/DF" ) ),
        ( u"eyes",      window.command_ShellExecute( None, u"C:/Program Files (x86)/MA-EYES/MA-EYES.exe", u"", u"C:/Program Files (x86)/MA-EYES" ) ),
        ( u"vbox",      window.command_ShellExecute( None, u"C:/goto/tools/Oracle/VirtualBox/VirtualBox.exe", u"", u"C:/goto/tools/Oracle/VirtualBox" ) ),
        ( u"Poderosa",  window.command_ShellExecute( None, u"C:/goto/tools/Poderosa/Poderosa.exe", u"", u"C:/goto/tools/Poderosa" ) ),
        ( u"GanttProject",  window.command_ShellExecute( None, u"C:/goto/tools/GanttProject/ganttproject.exe", u"", u"C:/goto/tools/GanttProject" ) ),
        ( u"wz",        window.command_ShellExecute( None, u"C:/goto/tools/WZ Editor/WZEDITOR.EXE", u"", u"C:/goto/tools/WZ Editor" ) ),
        ( u"kf",        window.command_ShellExecute( None, u"C:/goto/tools/KF/KF.EXE", u"", u"C:/goto/tools/KF" ) ),
        ( u"WinDirStat",window.command_ShellExecute( None, u"C:/goto/tools/WinDirStat/windirstat.exe", u"", u"C:/goto/tools/WinDirStat" ) ),
        ( u"projects",  window.command_ShellExecute( None, u"s:/projects", u"", u"" ) ),
        ( u"ProcMon",window.command_ShellExecute( None, u"C:/goto/tools/Sysinternals/Procmon.exe", u"", u"C:/goto/tools/Sysinternals" ) ),
        ( u"ProcExp",window.command_ShellExecute( None, u"C:/goto/tools/Sysinternals/Procexp.exe", u"", u"C:/goto/tools/Sysinternals" ) ),
        ( u"proxy",window.command_ShellExecute( None, u"C:/squid/bin/squid_env.bat", u"%param%", u"C:/squid/bin/" ) ),
        ( u"Meadow",window.command_ShellExecute( None, u"C:/goto/tools/meadow/bin/RunMW32.exe", u"", u"C:/Goto/tools/meadow/bin" ) ),
    ]


# リストウインドウの設定処理
def configure_ListWindow(window):

    # --------------------------------------------------------------------
    # F1 キーでヘルプファイルを表示する

    def command_Help():
        print u"Helpを起動 :"
        help_path = os.path.join( os.path.split(sys.argv[0])[0], 'doc\\index.html' )
        shellExecute( None, None, help_path, u"", u"" )
        print u"Done.\n"

    window.keymap[ VK_F1 ] = command_Help

