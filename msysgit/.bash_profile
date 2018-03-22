# export GIT_PAGER="nkf -sW | less"
PS1='[\w\[\033[033;040m\]$(__git_ps1 ":%s")\[\033[037;040m\]]% '
[[ -s ~/.git-extensions/scripts/init ]] && source ~/.git-extensions/scripts/init

alias g="git"

export PATH=/c/goto/tools/bin:$PATH

alias d="docker"
alias dc="docker-compose"

docker() {
  case $1 in
    i.l.a)
      shift
      command docker image ls --all "$@"
      ;;
    i.l)
      shift
      command docker image ls "$@"
      ;;
    i.p)
      shift
      command docker image prune "$@"
      ;;
    i.r)
      shift
      command docker image rm "$@"
      ;;
    i)
      shift
      command docker image "$@"
      ;;
    c.l.a)
      shift
      command docker container ls --all "$@"
      ;;
    c.l)
      shift
      command docker container ls "$@"
      ;;
    c.p)
      shift
      command docker container prune "$@"
      ;;
    c.r)
      shift
      command docker container rm "$@"
      ;;
    c)
      shift
      command docker container "$@"
      ;;
    *)
      command docker "$@";;
  esac
}