#! /bin/bash

#echo "ok"

MAX_PAGE="$1"
TEMPFILE="tempfile.txt"
#echo $(pdfinfo *.pdf | grep Pages | awk '{print $2}') > $TEMPFILE

for pdffile in $(find . -name '*.pdf')
do
	pages=$(pdfinfo "$pdffile" | grep Pages | awk '{print $2}') #> $TEMPFILE
	if [ "$pages" -ge "$MAX_PAGE" ]
	then 
		
	fi
		
done
