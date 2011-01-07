# .zshrc

source $HOME/.zsh.d/init.sh

# ローカル用設定ファイルの読み込み
if [ -f ~/.zsh_local ]; then
  . ~/.zsh_local
fi

