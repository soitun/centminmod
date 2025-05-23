mimefix() {
  if [ -f /usr/local/nginx/conf/mime.types ]; then
    silence=$1
    \cp -af /usr/local/nginx/conf/mime.types /usr/local/nginx/conf/mime.types.bak-$DT
    
    if [ -z "$silence" ]; then
      # Current Nginx mime types for eot, ttf, otf, woff
      egrep '(eot|ttf|otf|woff|woff2)' /usr/local/nginx/conf/mime.types
    fi
    
    EOTCHECK=$(grep eot /usr/local/nginx/conf/mime.types)
    TTFCHECK=$(grep ttf /usr/local/nginx/conf/mime.types)
    OTTCHECK=$(grep otf /usr/local/nginx/conf/mime.types)
    WOFFCHECK=$(grep woff /usr/local/nginx/conf/mime.types)
    WOFFTWOCHECK=$(grep woff2 /usr/local/nginx/conf/mime.types)
    AVIFCHECK=$(grep avif /usr/local/nginx/conf/mime.types)
    XMLCHECK=$(grep 'application/xml' /usr/local/nginx/conf/mime.types)
    
    if [ -z "$silence" ]; then
      echo $EOTCHECK
      echo $TTFCHECK
      echo $OTTCHECK
      echo $WOFFCHECK
      echo $WOFFTWOCHECK
      echo $AVIFCHECK
      echo $XMLCHECK
    fi

    # remove duplicate xml mime type warning on nginx -t runs
    if [ "$(grep 'text\/xml' /usr/local/nginx/conf/mime.types)" ]; then
      sed -i '/text\/xml/d' /usr/local/nginx/conf/mime.types
    fi
    
    if [ -z "$XMLCHECK" ]; then
      sed -i 's/}//' /usr/local/nginx/conf/mime.types
      cat >> "/usr/local/nginx/conf/mime.types" <<EOF
    application/xml                                  xml;
}
EOF
    fi
    
    if [ -z "$TTFCHECK" ]; then
      sed -i 's/}//' /usr/local/nginx/conf/mime.types
      cat >> "/usr/local/nginx/conf/mime.types" <<EOF
    application/x-font-ttf                  ttf;
}
EOF
    fi
    
    if [ -z "$OTTCHECK" ]; then
      sed -i 's/}//' /usr/local/nginx/conf/mime.types
      cat >> "/usr/local/nginx/conf/mime.types" <<EFF
    font/opentype                           otf;
}
EFF
    fi
    
    if [ -z "$WOFFTWOCHECK" ]; then
      sed -i 's/}//' /usr/local/nginx/conf/mime.types
      cat >> "/usr/local/nginx/conf/mime.types" <<EAF
    font/woff2                   woff2;
    text/cache.manifest       manifest;
    text/cache.manifest       appcache;
}
EAF
    fi
    
    if [ -z "$AVIFCHECK" ]; then
      sed -i 's/}//' /usr/local/nginx/conf/mime.types
      cat >> "/usr/local/nginx/conf/mime.types" <<EAF
    image/avif                                       avif;
    image/avif-sequence                              avifs;
}
EAF
    fi
  fi
}