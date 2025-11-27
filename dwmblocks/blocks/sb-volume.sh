# DWM enviou a variável $BUTTON pra gente?
 case $BUTTON in
	     1) pavucontrol ;; # Botão esquerdo
	         3) pamixer -t ;;  # Botão direito
	 esac

	 # Imprime o volume
	  echo "🔊 $(pamixer --get-volume)%"

