#!/bin/bash
export PATH="/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin:/root/bin"
#################################################################
# add sudo user script as discussed at
# http://stackoverflow.com/questions/8784761/adding-users-to-sudoers-through-shell-script?lq=1
# http://www.liquidweb.com/kb/how-to-add-a-user-and-grant-root-privileges-on-centos-7/
# http://www.liquidweb.com/kb/how-to-add-a-user-and-grant-root-privileges-on-centos-6-5/
#################################################################
# usage:
# 
# ./addsudousers.sh username
# 
#################################################################
DT=$(date +"%d%m%y-%H%M%S")
SCRIPTDIR="$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd)"
BASEDIR=$(dirname $SCRIPTDIR)

# set locale temporarily to english
# due to some non-english locale issues
export LC_ALL=en_US.UTF-8
export LANG=en_US.UTF-8
export LANGUAGE=en_US.UTF-8
export LC_CTYPE=en_US.UTF-8
# disable systemd pager so it doesn't pipe systemctl output to less
export SYSTEMD_PAGER=''
ARCH_CHECK="$(uname -m)"

shopt -s expand_aliases
for g in "" e f; do
    alias ${g}grep="LC_ALL=C ${g}grep"  # speed-up grep, egrep, fgrep
done

if [ -d /etc/sudoers.d ]; then
  while [[ -n $1 ]]; do
  echo
  echo "Creating a sudo user & setting password for $1"
  echo
  # read -ep "Enter the username for sudo user you want to create: " sudo_username
  sudo_username=$1
  useradd "$sudo_username"
  usermod -aG wheel "$sudo_username"
  # read -ep "Enter the password for $sudo_username: " sudo_userpass
  passwd "$sudo_username"

  # https://community.centminmod.com/posts/39469/
  echo "alias cmdir='pushd /usr/local/src/centminmod'" >> "/home/${sudo_username}/.bash_profile"
  echo "alias centmin='sudo centmin'" >> "/home/${sudo_username}/.bashrc"
  echo "alias cminfo='sudo cminfo'" >> "/home/${sudo_username}/.bashrc"
  echo "alias cmupdate='sudo cmupdate'" >> "/home/${sudo_username}/.bashrc"
  echo "alias pwdh='echo -n \"\$HOSTNAME\"; echo \" \$PWD\"'" >> "/home/${sudo_username}/.bashrc"
  echo "alias postfixlog='sudo pflogsumm -d today --verbose_msg_detail /var/log/maillog'" >> "/home/${sudo_username}/.bashrc"

  echo
  # echo "${sudo_username}:${sudo_userpass}" | chpasswd
  echo "$sudo_username with password: $sudo_userpass created"
  echo "sudo setup for $sudo_username"
  echo "${sudo_username}    ALL=(ALL:ALL) ALL" > "/etc/sudoers.d/${sudo_username}"
  # echo "${sudo_username}    ALL=(ALL:ALL) ALL: /usr/bin/centmin, /usr/bin/cminfo" > "/etc/sudoers.d/${sudo_username}"
  chmod 0440 "/etc/sudoers.d/${sudo_username}"
  visudo -c -q -f "/etc/sudoers.d/${sudo_username}"
  shift # shift all parameters;
  echo
  echo "${sudo_username} sudo user setup at /etc/sudoers.d/${sudo_username}"
  done
fi

exit