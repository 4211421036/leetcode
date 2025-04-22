# Read from the file file.txt and output the tenth line to stdout.
str=""
count=0
while IFS= read -r file
do
    str=$file
    (( ( count+=1 ) == 10 )) && break
done < "file.txt"
[ $count -eq 10 ] && echo $str
