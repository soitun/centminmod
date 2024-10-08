#######################################################
zopfliinstall() {
  if [[ "$PHP_INSTALL" = [yY] ]]; then
    if [[ "$PHPZOPFLI" = [yY] ]]; then
      if [ ! -f /usr/bin/zopfli ]; then
        yum -y -q install zopfli
      fi
      PHPEXTDIRD=`cat /usr/local/bin/php-config | awk '/^extension_dir/ {extdir=$1} END {gsub(/\047|extension_dir|=|)/,"",extdir); print extdir}'`
      # set extra cflags fro devtoolset-7 and devtoolset-8 compatibility
      check_devtoolset_php
      enable_devtoolset
      echo "*************************************************"
      cecho "* Installing Zopfli PHP extension" $boldgreen
      echo "*************************************************"
      echo "Downloading Zopfli PHP extension..."
      cd "$DIR_TMP"
      rm -rf php-ext-zopfli
      git clone https://github.com/kjdev/php-ext-zopfli

      cecho "Compiling Zopfli PHP extension..." $boldgreen   
      pwd
      echo "cd $DIR_TMP"
      cd "$DIR_TMP"
      cd "${DIR_TMP}/php-ext-zopfli"
      git submodule update --init
      if [[ "$INITIALINSTALL" != [yY] ]]; then
          make clean
      fi
      /usr/local/bin/phpize
      CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config
      make${MAKETHREADS}
      make install
      
      #######################################################
      # check to see if zopfli.so already loaded in php.ini
      ZOPFLISOCHECK=`grep 'zopfli.so' /usr/local/lib/php.ini`
      ZOPFLISOCHECKB=$(grep 'zopfli.so' ${CONFIGSCANDIR}/zopfli.ini)
      PHPEXTDIRD=`cat /usr/local/bin/php-config | awk '/^extension_dir/ {extdir=$1} END {gsub(/\047|extension_dir|=|)/,"",extdir); print extdir}'`
      
      if [[ -z "$ZOPFLISOCHECK" || -z "$ZOPFLISOCHECKB" ]]; then
          #echo "" >> /usr/local/lib/php.ini
          echo "extension=zopfli.so" > "${CONFIGSCANDIR}/zopfli.ini"
      else
          echo ""
          echo "zopfli.so already loaded in ${CONFIGSCANDIR}/zopfli.ini"
          echo "$ZOPFLISOCHECK"
          echo ""
      fi # zopfli.so check
  fi # PHPZOPFLI=y
fi # PHP_INSTALL=y
}