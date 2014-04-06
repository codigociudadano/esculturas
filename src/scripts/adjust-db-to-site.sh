#!/bin/sh

set -e 

SITE=$1
if [ -z $1 ]
then
    echo "Using the current directory as sitename"
    SITE=${PWD##*/}
else
    SITE=$1
fi
echo "Configuring the database for sitename: $SITE"
drush vset file_public_path "sites/$SITE/files"
drush vset file_private_path "sites/$SITE/private"
drush vset file_temporary_path "sites/$SITE/files"
drush cc all
drush dis `cat modules_disabled.txt` -y
drush en `cat modules_enabled.txt` -y
drush updb -y
drush fra -y
drush vset preprocess_css 0
drush vset preprocres_js 0
