#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ls='ls --color=auto'
alias grep='grep --color=auto'
alias cdwm='vim ~/dwm-btw/config.h'
alias cstwm='vim ~/slstatus/config.h'

alias mdwm='cd ~/dwm-btw; sudo make clean install; cd -'
alias mstwm='cd ~/slstatus; sudo make clean install; cd -'

alias catdwm='cat ~/dwm-btw/config.h'

PS1='[\u@\h \W]\$ '

export PATH=$PATH:/home/guisandroni/.local/bin

#eval "$(oh-my-posh init bash --config ~/.poshthemes/catppucin_mocha.omp.json)"

#eval "$(starship init bash)"

#THIS MUST BE AT THE END OF THE FILE FOR SDKMAN TO WORK!!!
export SDKMAN_DIR="$HOME/.sdkman"
[[ -s "$HOME/.sdkman/bin/sdkman-init.sh" ]] && source "$HOME/.sdkman/bin/sdkman-init.sh"


(cat ~/.cache/wal/sequences &)
