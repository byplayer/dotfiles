# .zshrc

# プロンプトのカラー表示を有効
autoload -U colors
colors

# プロンプトはバージョン関連情報を出す準備
autoload -Uz vcs_info
zstyle ':vcs_info:*' formats ':%b'
zstyle ':vcs_info:*' actionformats ':%b|%a'
vcs_console () {
  psvar=()
  LANG=en_US.UTF-8 vcs_info
  [[ -n "$vcs_info_msg_0_" ]] && psvar[1]="$vcs_info_msg_0_"
}

precmd () {
  vcs_console;
}

# prompt
PROMPT_FG_COLOR=white
RPROMPT_FG_COLOR=white
VC_FG_COLOR=blue

case ${UID} in
0)
  PROMPT_FG_COLOR=red
  ;;
*)
  PROMPT_FG_COLOR=white
  ;;
esac

PROMPT_CL_PREFIX="%F{${PROMPT_FG_COLOR}}"
PROMPT_PREFIX="${PROMPT_CL_PREFIX}"

PROMPT_CL_SUFIX="%f"
RPROMPT_CL_SUFIX="%f"

[ -n "${REMOTEHOST}${SSH_CONNECTION}" ] &&
    PROMPT_PREFIX="${PROMPT_PREFIX}%n@%m"

PROMPT="${PROMPT_PREFIX}%#${PROMPT_CL_SUFIX} "
PROMPT2="${PROMPT_CL_PREFIX}%_\$${PROMPT_CL_SUFIX} "
SPROMPT="${PROMPT_CL_PREFIX}%r is correct? [n,y,a,e]:${PROMPT_CL_SUFIX} "


RPROMPT="%F{${RPROMPT_FG_COLOR}}[%(4~,%-1~/.../%2~,%~)%f%1(v|%F{${VC_FG_COLOR}}%1v%f|)%F{${RPROMPT_FG_COLOR}}]%f"

# ヒストリ設定
HISTFILE=~/.zsh_history
HISTSIZE=10000000
SAVEHIST=10000000

# 全履歴の一覧を出力する
function history-all { history -E 1 }


# デフォルトの補完機能を有効
autoload -U compinit
compinit

# ベルを鳴らさない。
setopt no_beep

# 補完時にヒストリを自動的に展開する。
setopt hist_expand

# バックグラウンドジョブが終了したらすぐに知らせる。
setopt no_tify

# 履歴ファイルに時刻を記録
setopt extended_history

# 履歴をインクリメンタルに追加
setopt inc_append_history

# 履歴の共有
setopt share_history

# ヒストリに追加されるコマンド行が古いものと同じなら古いものを削除
setopt hist_ignore_all_dups

# 直前と同じコマンドラインはヒストリに追加しない
setopt hist_ignore_dups

# ヒストリを呼び出してから実行する間に一旦編集可能
setopt hist_verify

# 補完時にヒストリを自動的に展開する。
setopt hist_expand


# cdでpushdする。
setopt auto_pushd

# ディレクトリ名でcd
setopt auto_cd

# 間違えたら訂正を出す
setopt correct

# キーをemacs風に
bindkey -e

# emacs config
EDITOR=/usr/bin/emacsclient
export EDITOR

export ALTERNATE_EDITOR="emacs"

alias ec="emacsclient"
alias ecn='emacsclient -n'

# ruby environment
RUBY_HOME=/usr/local/ruby

export PATH=${RUBY_HOME}/bin:$PATH
export MANPATH=${RUBY_HOME}/share/man:`manpath -q`

# git env
export PATH=/usr/local/git/bin:$PATH
export MANPATH=/usr/local/git/share/man:`manpath -q`
alias g="git"

# freemind
export PATH=/usr/local/freemind:$PATH

# ctags 環境設定
export PATH=/usr/local/ctags/bin:$PATH
export MANPATH=/usr/local/ctags/share/man:`manpath -q`

# mysql
export PATH=/usr/local/mysql/bin:$PATH
export MANPATH=/usr/local/mysql/man:`manpath -q`

# alias 設定
alias ls="ls -CF --color=auto"

# add path private scripts
export PATH=~/.bin:$PATH

# ローカル用設定ファイルの読み込み
if [ -f ~/.zsh_local ]; then
  . ~/.zsh_local
fi

