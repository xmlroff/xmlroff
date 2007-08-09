for FILE in *.pdf *.png ; do
 echo $FILE
 cp $FILE ref
 chmod 666 ref/$FILE
 rm -f diff/$FILE diff/$FILE.bak
 touch diff/$FILE
 touch diff/$FILE.bak
 chmod 666 diff/$FILE diff/$FILE.bak
 rm -f stereo/$FILE
done
