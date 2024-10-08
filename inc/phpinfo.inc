phpiadmin() {
    if [ -f /usr/local/nginx/html/phpi.php ]; then
        # Randomize phpi.php filename
        echo "run phpiadmin"
        NPHP=$(od -vAn -N4 -tx < /dev/urandom)
        NPHP=$(echo ${NPHP} | sed -e 's/\s//')
        PHPISALT=$(/usr/bin/openssl rand -base64 14 | tr -dc 'a-zA-Z0-9')
        PHPIUSER=$(echo "phpiadmin${PHPISALT}")
        PHPIPASS=$(/usr/bin/openssl rand -base64 21 | tr -dc 'a-zA-Z0-9')
        echo ""
        mv /usr/local/nginx/html/phpi.php "/usr/local/nginx/html/${NPHP}_phpi.php"
        # cecho "Insert Username/Password into /usr/local/nginx/html/${NPHP}_phpi.php file itself" $boldyellow
        sed -i "s|PHPUSERNAME|$PHPIUSER|" "/usr/local/nginx/html/${NPHP}_phpi.php"
        sed -i "s|PHPPASSWORD|$PHPIPASS|" "/usr/local/nginx/html/${NPHP}_phpi.php"
        chown nginx:nginx "/usr/local/nginx/html/${NPHP}_phpi.php"
        echo "*************************************************"
        cecho "PHP Info Login File: /usr/local/nginx/html/${NPHP}_phpi.php" $boldgreen
        cecho "PHP Info Login: ${hname}/${NPHP}_phpi.php" $boldgreen
        cecho "PHP Info Login username: ${PHPIUSER}" $boldgreen
        cecho "PHP Info Login password: ${PHPIPASS}" $boldgreen
        echo "*************************************************"
        echo
    fi
}