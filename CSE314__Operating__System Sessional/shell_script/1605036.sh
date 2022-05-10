#!/usr/bin/bash

DUMMY="0"
#/media/saif/New Volume/BUET/OS Lab/1605036

##################################################################################################
#task 1,2,3
#checking directory and input file


INPUT_FILE="abc"
DIRECTORY="0"
if [ -d "$1" ]
then
    DIRECTORY="$1"
    INPUT_FILE="$2"
else
    INPUT_FILE="$1"
fi

#checking input file

if [ -f "$INPUT_FILE" ]
then 
    DUMMY="0"
else 
    echo "Please provide input file name with proper extension."
    while read INPUT_FILE
    do
        if [ -f "$INPUT_FILE" ]
        then
            break
        else
            echo "Please provide input file name with proper extension."
        fi
    done
fi


##################################################################################################
#task 4
#reading input
READ_MODE=$(sed "1q;d" "$INPUT_FILE")
LINES_TO_READ=$(sed "2q;d" "$INPUT_FILE")
STRING_TO_SEARCH=$(sed "3q;d" "$INPUT_FILE")
        
# echo "$READ_MODE"
# echo "$LINES_TO_READ"
# echo "$STRING_TO_SEARCH"


##################################################################################################
#task 5
#finding the readable text according to the criteria

if [ -d "$DIRECTORY" ]
then
    cd "$DIRECTORY"
fi

TEMPFILE="../tempfile.txt"
if [ "$READ_MODE" = "begin" ]
then
    grep -rin "$STRING_TO_SEARCH" . > $TEMPFILE
elif [ "$READ_MODE" = "end" ]
then
    grep -rin "$STRING_TO_SEARCH" . | tac > $TEMPFILE
fi


##################################################################################################
#task 6,7
#creating the files and putting them in output directory


PREV_FILE="123456789.txt"
while read CURRENT_LINE
    do
        CURRENT_FILE=$(echo "$CURRENT_LINE" | cut -d':' -f 1)
        LINE_NUMBER=$(echo "$CURRENT_LINE" | cut -d':' -f 2)
        TOTAL_LINES=$(wc -l "$CURRENT_FILE")
        TOTAL_LINES=$(echo "$TOTAL_LINES" | cut -d' ' -f 1)

        if [ "$PREV_FILE" = "$CURRENT_FILE" ]
        then
            continue
        fi

        if [ "$READ_MODE" = "begin" -a "$LINE_NUMBER" -le "$LINES_TO_READ" ]
        then
            NEW_FILE=${CURRENT_FILE:2}
            NEW_FILE=$(tr '/' '.' <<<"$NEW_FILE")
            EXTENSION=${NEW_FILE##*.} 
            NEW_FILE=${NEW_FILE%.*} 

            if [ "$DIRECTORY" = "0" ]
            then
                NEW_FILE="$NEW_FILE$LINE_NUMBER.$EXTENSION"
            else
                NEW_FILE="$DIRECTORY.$NEW_FILE$LINE_NUMBER.$EXTENSION"
            fi

            mkdir -p "../output_dir"
            cp "$CURRENT_FILE" "../output_dir/$NEW_FILE"
        elif [ "$READ_MODE" = "end" -a $LINE_NUMBER -gt `expr $TOTAL_LINES - $LINES_TO_READ` ]
        then
            NEW_FILE=${CURRENT_FILE:2}
            NEW_FILE=$(tr '/' '.' <<<"$NEW_FILE")
            EXTENSION=${NEW_FILE##*.} 
            NEW_FILE=${NEW_FILE%.*} 

            if [ "$DIRECTORY" = "0" ]
            then
                NEW_FILE="$NEW_FILE$LINE_NUMBER.$EXTENSION"
            else
                NEW_FILE="$DIRECTORY.$NEW_FILE$LINE_NUMBER.$EXTENSION"
            fi

            mkdir -p "../output_dir"
            cp "$CURRENT_FILE" "../output_dir/$NEW_FILE"
        fi

done < "$TEMPFILE"


##################################################################################################
#task 8 and 9
#creating the csv file and reporting the number of files


PREV_FILE="123456789.txt"
CSV_FILE="../output.csv"
OUTPUT_FILE="0"
OUTPUT_LINE=0
OUTPUT_TEXT="0"
ANSWER=0
echo "File Path,Line Number,Line Containing Searched String" > $CSV_FILE
while read CURRENT_LINE
    do
        CURRENT_FILE=$(echo "$CURRENT_LINE" | cut -d':' -f 1)
        LINE_NUMBER=$(echo "$CURRENT_LINE" | cut -d':' -f 2)
        TEXT_LINE=$(echo "$CURRENT_LINE" | cut -d':' -f 3)
        TOTAL_LINES=$(wc -l "$CURRENT_FILE")
        TOTAL_LINES=$(echo "$TOTAL_LINES" | cut -d' ' -f 1)


        if [ "$READ_MODE" = "begin" -a "$LINE_NUMBER" -le "$LINES_TO_READ" ]
        then
            if [ "$PREV_FILE" = "$CURRENT_FILE" ]
            then
                OUTPUT_TEXT="$OUTPUT_TEXT$TEXT_LINE"
                continue
            else
                if [ "$OUTPUT_FILE" != "0" ]
                then
                    if [ "$DIRECTORY" = "0" ] 
                    then
                        echo "$OUTPUT_FILE,$OUTPUT_LINE,$OUTPUT_TEXT" >> $CSV_FILE
                    else
                        echo "$DIRECTORY/$OUTPUT_FILE,$OUTPUT_LINE,$OUTPUT_TEXT" >> $CSV_FILE
                    fi
                fi
                OUTPUT_FILE=${CURRENT_FILE:2}
                OUTPUT_LINE=$LINE_NUMBER
                OUTPUT_TEXT="$TEXT_LINE"
                PREV_FILE="$CURRENT_FILE"
                ((ANSWER++))
            fi
        elif [ "$READ_MODE" = "end" -a $LINE_NUMBER -gt `expr $TOTAL_LINES - $LINES_TO_READ` ]
        then
            if [ "$PREV_FILE" = "$CURRENT_FILE" ]
            then
                OUTPUT_TEXT="$OUTPUT_TEXT$TEXT_LINE"
                continue
            else
                if [ "$OUTPUT_FILE" != "0" ]
                then
                    if [ "$DIRECTORY" = "0" ] 
                    then
                        echo "$OUTPUT_FILE,$OUTPUT_LINE,$OUTPUT_TEXT" >> $CSV_FILE
                    else
                        echo "$DIRECTORY/$OUTPUT_FILE,$OUTPUT_LINE,$OUTPUT_TEXT" >> $CSV_FILE
                    fi
                fi
                OUTPUT_FILE=${CURRENT_FILE:2}
                OUTPUT_LINE=$LINE_NUMBER
                OUTPUT_TEXT="$TEXT_LINE"
                PREV_FILE="$CURRENT_FILE"
            fi
        fi

done < "$TEMPFILE"

if [ "$OUTPUT_FILE" != "0" ]
then
    if [ "$DIRECTORY" = "0" ]
    then
        echo "$OUTPUT_FILE,$OUTPUT_LINE,$OUTPUT_TEXT" >> $CSV_FILE
    else
        echo "$DIRECTORY/$OUTPUT_FILE,$OUTPUT_LINE,$OUTPUT_TEXT" >> $CSV_FILE
    fi
    ((ANSWER++))
fi

echo "Number of files found is $ANSWER"

#rm "$TEMPFILE"


