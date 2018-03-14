# export GIT_PAGER="nkf -sW | less"
PS1='[\w\[\033[033;040m\]$(__git_ps1 ":%s")\[\033[037;040m\]]% '
[[ -s ~/.git-extensions/scripts/init ]] && source ~/.git-extensions/scripts/init

alias g="git"

export PATH=/c/goto/tools/bin:$PATH