checkphpextmailparse() {
    if [[ "$INITIALINSTALL" != [yY] ]]; then
        php-config --version | cut -d . -f1,2 | egrep -w '7.0|7.1|7.2|7.3|7.4|8.0|8.1|8.2|8.3|8.4'
    else
        echo $PHP_VERSION | cut -d . -f1,2 | egrep -w '7.0|7.1|7.2|7.3|7.4|8.0|8.1|8.2|8.3|8.4'
    fi
    PHPSEVEN_CHECKVER=$?
    echo "checkphpextmailparse $PHPSEVEN_CHECKVER"

    # mailparse 3.0.0 only works with PHP 7.0 branch
    # so use 2.1.6 if not PHP 7.0 branch
    if [[ "$PHPSEVEN_CHECKVER" = '0' ]]; then
        if [[ "$PHPMVER" = '8.4' || "$PHPMVER" = '8.3' || "$PHPMVER" = '8.2' || "$PHPMVER" = '8.1' || "$PHPMVER" = '8.0' || "$REDIS_PHPCURRENTVER" = '8.4' || "$PHPMUVER" = '8.4' || "$REDIS_PHPCURRENTVER" = '8.3' || "$PHPMUVER" = '8.3' || "$REDIS_PHPCURRENTVER" = '8.2' || "$PHPMUVER" = '8.2' || "$REDIS_PHPCURRENTVER" = '8.1' || "$PHPMUVER" = '8.1' || "$REDIS_PHPCURRENTVER" = '8.0' || "$PHPMUVER" = '8.0' ]] || [[ "$PHPMVER" = '7.4' || "$REDIS_PHPCURRENTVER" = '7.4' || "$PHPMUVER" = '7.4' ]]; then
            MAILPARSEPHP_VER="$MAILPARSEPHPSEVENFOUR_COMPATVER"
        else
            MAILPARSEPHP_VER="$MAILPARSEPHP_COMPATVER"
        fi
        PHPEXT_MAILPARSELINKFILE="mailparse-${MAILPARSEPHP_VER}.tgz"
        PHPEXT_MAILPARSELINK="https://pecl.php.net/get/${PHPEXT_MAILPARSELINKFILE}"
        PHPEXT_MAILPARSELINKLOCAL="${LOCALCENTMINMOD_MIRROR}/centminmodparts/mailparse/${PHPEXT_MAILPARSELINKFILE}"
    fi

    cecho "Check for php extensions" $boldyellow
    if [[ ! -f "${DIR_TMP}/mailparse-${MAILPARSEPHP_VER}.tgz" ]]; then
        echo "Downloading mailparse extension"
        echo "MAILPARSEPHP_VER=$MAILPARSEPHP_VER"
        mailparsephpexttarball
    fi
    echo
}

mailparseinstall() {
    if [[ "$PHP_INSTALL" = [yY] ]]; then
        if [[ "$PHPMAILPARSE" = [yY] ]]; then

            checkphpextmailparse
            # set extra cflags fro devtoolset-7 and devtoolset-8 compatibility
            check_devtoolset_php
            enable_devtoolset

            if [[ "$INITIALINSTALL" != [yY] ]]; then
                php-config --version | cut -d . -f1,2 | egrep -w '7.0|7.1|7.2|7.3|7.4|8.0|8.1|8.2|8.3|8.4'
            else
                echo $PHP_VERSION | cut -d . -f1,2 | egrep -w '7.0|7.1|7.2|7.3|7.4|8.0|8.1|8.2|8.3|8.4'
            fi
            PHPSEVEN_CHECKVER=$?
            echo "mailparseinstall $PHPSEVEN_CHECKVER"

            # mailparse 3.0.0 only works with PHP 7.0 branch
            # so use 2.1.6 if not PHP 7.0 branch
            if [[ "$PHPSEVEN_CHECKVER" = '0' ]]; then
                if [[ "$PHPMVER" = '8.4' || "$PHPMVER" = '8.3' || "$PHPMVER" = '8.2' || "$PHPMVER" = '8.1' || "$PHPMVER" = '8.0' || "$REDIS_PHPCURRENTVER" = '8.4' || "$PHPMUVER" = '8.4' || "$REDIS_PHPCURRENTVER" = '8.3' || "$PHPMUVER" = '8.3' || "$REDIS_PHPCURRENTVER" = '8.2' || "$PHPMUVER" = '8.2' || "$REDIS_PHPCURRENTVER" = '8.1' || "$PHPMUVER" = '8.1' || "$REDIS_PHPCURRENTVER" = '8.0' || "$PHPMUVER" = '8.0' ]] || [[ "$PHPMVER" = '7.4' || "$REDIS_PHPCURRENTVER" = '7.4' || "$PHPMUVER" = '7.4' ]]; then
                    MAILPARSEPHP_VER="$MAILPARSEPHPSEVENFOUR_COMPATVER"
                else
                    MAILPARSEPHP_VER="$MAILPARSEPHP_COMPATVER"
                fi
                PHPEXT_MAILPARSELINKFILE="mailparse-${MAILPARSEPHP_VER}.tgz"
                PHPEXT_MAILPARSELINK="https://pecl.php.net/get/${PHPEXT_MAILPARSELINKFILE}"
                PHPEXT_MAILPARSELINKLOCAL="${LOCALCENTMINMOD_MIRROR}/centminmodparts/mailparse/${PHPEXT_MAILPARSELINKFILE}"
            fi
            echo "*************************************************"
            cecho "* Installing mailparse $MAILPARSEPHP_VER PHP Extension" $boldgreen
            echo "*************************************************"
            echo
            echo "mailparseinstall MAILPARSEPHP_VER=$MAILPARSEPHP_VER"

            pwd
            echo "cd $DIR_TMP"
            cd $DIR_TMP
            if [[ "$PHPSEVENTHREE_MAILPARSE" != [yY] ]]; then
                if [ ! -d "$DIR_TMP/mailparse-${MAILPARSEPHP_VER}" ]; then
                    tar xzf ${PHPEXT_MAILPARSELINKFILE}
                fi
                cd mailparse-${MAILPARSEPHP_VER}
                if [[ "$INITIALINSTALL" != [yY] ]]; then
                    make clean
                fi
            else
                cd mailparse-git
            fi
            /usr/local/bin/phpize
            CFLAGS="-fPIC -O2 -fstack-protector-strong -D_FORTIFY_SOURCE=2" CPPFLAGS="-D_FORTIFY_SOURCE=2" CXXFLAGS="-fPIC -O2" LDFLAGS="-Wl,-z,relro,-z,now -pie" ./configure --with-php-config=/usr/local/bin/php-config
            make${MAKETHREADS}
            make install

            #######################################################
            # check if mailparse.so exists in php.ini

            MAILPARSESOCHECK=$(grep 'extension=mailparse.so' /usr/local/lib/php.ini >/dev/null 2>&1; echo $?)
            MAILPARSESOCHECKB=$(grep 'extension=mailparse.so' "${CONFIGSCANDIR}/mailparse.ini" >/dev/null 2>&1; echo $?)

            if [[ "$MAILPARSESOCHECK" = '1' || "$MAILPARSESOCHECKB" = '1' ]]; then
                echo -e "\nCopying mailparse.ini > ${CONFIGSCANDIR}/mailparse.ini\n"
                echo "extension=mailparse.so" > ${CONFIGSCANDIR}/mailparse.ini
            fi #check if mailparse.so exists in php.ini

            # cmservice php-fpm restart
            echo "*************************************************"
            cecho "* mailparse PHP installed" $boldgreen
            echo "*************************************************"

        fi
    fi # PHP_INSTALL=y
}