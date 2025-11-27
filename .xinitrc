# Auto start config
#
#
#
#
#

 if [ -z "$DBUS_SESSION_BUS_ADDRESS" ]; then
     eval "$(dbus-launch --sh-syntax --exit-with-session)"
 fi

 
 eval $(/usr/bin/gnome-keyring-daemon --start --components=pkcs11,secrets,ssh)
 export SSH_AUTH_SOCK



xinput set-prop 11 'libinput Accel Speed' -0.7 &

feh --bg-scale ./Pictures/grass.jpg &

flatpak run io.github.libvibrant.vibrantLinux &

xrandr --output DVI-D-0 --left-of HDMI-A-0 --auto &
slstatus &


/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &


exec dwm
