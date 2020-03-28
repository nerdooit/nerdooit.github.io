#!/bin/zsh

echo "Hello~ $1"

POST="post"
DATE=$(date +%Y)-$(date +%m)-$(date +%d)
NAME=$DATE-$1.md
AUTHOR="nerdooit"
BRACKET='"[]"'
IMAGE="'img/etc/'"

touch $NAME

echo "---" >> $NAME
echo "layout : $POST" >> $NAME
echo "title : $BRACKET" >> $NAME
echo 'subtitle : ""' >> $NAME
echo "date : $DATE" >> $NAME
echo "author : $AUTHOR" >> $NAME
echo "cover : $IMAGE" >> $NAME
echo "tags : " >> $NAME
echo "comments: true" >> $NAME
echo "---" >> $NAME

chmod 755 $NAME

#Open file
vi $NAME
