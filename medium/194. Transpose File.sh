# Read from the file file.txt and print its transposed content to stdout.
awk '
{
    for (i = 1; i <= NF; i++) {
        if (NR == 1) {
            row[i] = $i
        } else {
            row[i] = row[i] " " $i
        }
    }
}
END {
    for (i = 1; i <= NF; i++) {
        print row[i]
    }
}' file.txt
