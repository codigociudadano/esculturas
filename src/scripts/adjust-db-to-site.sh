#!/bin/sh

# This script is used to setup the settings of the site.

set -e 

SITE=$1
if [ -z $1 ]
then
    echo "Using the current directory as sitename"
    SITE=${PWD##*/}
else
    SITE=$1
fi

echo ""
echo "Configuring variables & settings for sitename: $SITE ..."
drush vset file_public_path "sites/$SITE/files"
drush vset file_private_path "sites/$SITE/private"
drush vset file_temporary_path "sites/$SITE/files"
drush vset preprocess_css 0
drush vset preprocres_js 0

echo ""
echo "Updating modules enabled ..."
drush cc all
drush dis `cat sites/default/modules_disabled.txt` -y
drush en `cat sites/default/modules_enabled.txt` -y

echo ""
echo "Applying database updates ..."
drush updb -y
drush fra -y
drush cc all
