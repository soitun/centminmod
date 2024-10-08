function funct_nginxmodules_openresty {

    # nginx Modules
    cd ${DIR_TMP}

    if [ -s ngx-fancyindex-0.3.1.tar.gz ]; then
        cecho "ngx-fancyindex 0.3.1 Archive found, skipping download..." $boldgreen
    else
        wget --progress=bar http://gitorious.org/ngx-fancyindex/ngx-fancyindex/archive-tarball/v0.3.1 -O ngx-fancyindex-0.3.1.tar.gz --tries=3
    fi

    tar zvxf ngx-fancyindex-0.3.1.tar.gz

if [ ! -d ${DIR_TMP}/ngx-fancyindex-ngx-fancyindex ]; then
rm -rf ngx-fancyindex-0.3.1.tar.gz

    if [ -s ngx-fancyindex-0.3.1.tar.gz ]; then
        cecho "ngx-fancyindex 0.3.1 Archive found, skipping download..." $boldgreen
    else
        wget --progress=bar http://gitorious.org/ngx-fancyindex/ngx-fancyindex/archive-tarball/v0.3.1 -O ngx-fancyindex-0.3.1.tar.gz --tries=3
    fi

    tar zvxf ngx-fancyindex-0.3.1.tar.gz

fi

    if [ -s "$NGX_CACHEPURGEFILE" ]; then
        cecho "ngx_cache_purge ${NGINX_CACHEPURGEVER} Archive found, skipping download..." $boldgreen
    else
        download_cmd "$NGX_CACHEPURGE" $WGETRETRY
    fi

    tar zvxf "$NGX_CACHEPURGEFILE"

    if [ -s Nginx-accesskey-2.0.5.tar.gz ]; then
        cecho "Nginx-accesskey 2.0.3 Archive found, skipping download..." $boldgreen
    else
        download_cmd "$NGX_ACCESSKEYLINK" $WGETRETRY
    fi

    tar zvxf "$NGX_ACCESSKEYLINKFILE"

if [ -s memc-nginx-module_v0.13rc3.tar.gz ]; then
  cecho "memc-nginx-module_v0.13rc3.tar.gz Archive found, skipping download..." $boldgreen
  else
  cecho "Error: memc-nginx-module_v0.13rc3.tar.gz not found!!! Downloading now......"
        wget --progress=bar --no-check-certificate https://github.com/agentzh/memc-nginx-module/tarball/v0.13rc3 -O memc-nginx-module_v0.13rc3.tar.gz --tries=3
fi

    tar xvzf memc-nginx-module_v0.13rc3.tar.gz

if [ -s srcache-nginx-module_v0.13rc6.tar.gz ]; then
  cecho "srcache-nginx-module_v0.13rc6.tar.gz Archive found, skipping download..." $boldgreen
  else
  cecho "Error: srcache-nginx-module_v0.13rc6.tar.gz not found!!! Downloading now......"
        wget --progress=bar --no-check-certificate https://github.com/agentzh/srcache-nginx-module/tarball/v0.13rc6 -O srcache-nginx-module_v0.13rc6.tar.gz --tries=3
fi

    tar xvzf srcache-nginx-module_v0.13rc6.tar.gz

# if [ -s ngx_auto_lib.tar.gz ]; then
#   cecho "ngx_auto_lib.tar.gz Archive found, skipping download..." $boldgreen
#   else
#   cecho "Error: ngx_auto_lib.tar.gz not found!!! Downloading now......"
#         wget --progress=bar --no-check-certificate https://github.com/simpl/ngx_auto_lib/tarball/master -O ngx_auto_lib.tar.gz --tries=3
# fi

#     tar xvzf ngx_auto_lib.tar.gz

}