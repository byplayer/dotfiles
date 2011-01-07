# .zshrc

source $HOME/.zsh.d/init.sh

# プロンプトのカラー表示を有効
autoload -U colors
colors

eval `dircolors ~/.dir_colors -b`

# デフォルトの補完機能を有効
autoload -U compinit
compinit

zstyle ':completion:*' list-colors ${(s.:.)LS_COLORS}

# ベルを鳴らさない。
setopt no_beep

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
# alias emacs='XMODIERS="@im=none" LC_CTYPE="ja_JP.utf8" emacs 2>/dev/null'
alias emacs='XMODIERS="@im=none" emacs 2>/dev/null'
EDITOR=/usr/bin/emacsclient
export EDITOR

export ALTERNATE_EDITOR="emacs"

alias ec="emacsclient"
alias ecn='emacsclient -n'

# ruby environment
RUBY_HOME=/usr/local/ruby

export PATH=${RUBY_HOME}/bin:$PATH
export MANPATH=${RUBY_HOME}/share/man:`manpath -q`

# rails env
alias r="rails"

# freemind
export PATH=/usr/local/freemind:$PATH

# ctags 環境設定
export PATH=/usr/local/ctags/bin:$PATH
export MANPATH=/usr/local/ctags/share/man:`manpath -q`

# mysql
export PATH=/usr/local/mysql/bin:$PATH
export MANPATH=/usr/local/mysql/man:`manpath -q`
export LD_LIBRARY_PATH=/usr/local/mysql/lib/mysql:$LD_LIBRARY_PATH

# tmux
export PATH=/usr/local/tmux/bin:$PATH
export MANPATH=/usr/local/tmux/man:`manpath -q`

# less color option
export LESS='-R'

# alias 設定
alias ls="ls -CF --color"

# tmux
alias tmux="tmux -2"

# add path private scripts
export PATH=~/.bin:$PATH

# rvm
if [[ -s $HOME/.rvm/scripts/rvm ]] ;
then
  source $HOME/.rvm/scripts/rvm ;
fi

# ローカル用設定ファイルの読み込み
if [ -f ~/.zsh_local ]; then
  . ~/.zsh_local
fi

