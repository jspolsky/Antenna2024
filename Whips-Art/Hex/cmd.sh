for f in raw/*[0-9].gif raw/*[0-9].webp ; do 
    echo $f
    basename="${f%.*}"
    # 24 pixels wide
    narrow="${basename}a.${f##*.}"
    echo $narrow
    [ ! -f $narrow ] && magick $f -coalesce -resize 24x110! $narrow
    # 1268 pixels wide
    wide="${basename}b.${f##*.}"
    echo $wide
    [ ! -f $wide ] && magick $f -coalesce -resize 1268x110! $wide
    # stretch the narrow one
    stretch="${basename}c.${f##*.}"
    echo $stretch
    [ ! -f $stretch ] && magick $f -coalesce -resize 24x110! -scale 1268x110! \
        -fill black \
        -draw "
            rectangle 1,0 53,109
            rectangle 56,0 108,109
            rectangle 111,0 163,109
            rectangle 166,0 218,109
            rectangle 221,0 273,109
            rectangle 276,0 328,109
            rectangle 331,0 383,109
            rectangle 386,0 438,109
            rectangle 441,0 493,109
            rectangle 496,0 548,109
            rectangle 551,0 603,109
            rectangle 606,0 658,109
            rectangle 661,0 713,109
            rectangle 716,0 768,109
            rectangle 771,0 823,109
            rectangle 826,0 878,109
            rectangle 881,0 933,109
            rectangle 936,0 988,109
            rectangle 991,0 1043,109
            rectangle 1046,0 1098,109
            rectangle 1101,0 1153,109
            rectangle 1156,0 1208,109
            rectangle 1211,0 1263,109
        " $stretch
    # shutter the wide one
    shutter="${basename}d.${f##*.}"
    echo $shutter
    [ ! -f $shutter ] && magick $f -coalesce -resize 1268x110! \
        -fill black \
        -draw "
            rectangle 1,0 53,109
            rectangle 56,0 108,109
            rectangle 111,0 163,109
            rectangle 166,0 218,109
            rectangle 221,0 273,109
            rectangle 276,0 328,109
            rectangle 331,0 383,109
            rectangle 386,0 438,109
            rectangle 441,0 493,109
            rectangle 496,0 548,109
            rectangle 551,0 603,109
            rectangle 606,0 658,109
            rectangle 661,0 713,109
            rectangle 716,0 768,109
            rectangle 771,0 823,109
            rectangle 826,0 878,109
            rectangle 881,0 933,109
            rectangle 936,0 988,109
            rectangle 991,0 1043,109
            rectangle 1046,0 1098,109
            rectangle 1101,0 1153,109
            rectangle 1156,0 1208,109
            rectangle 1211,0 1263,109
        " $shutter
    # alternate version of stretch that is not as wide
    stretch2="${basename}e.${f##*.}"
    echo $stretch2
    [ ! -f $stretch2 ] && magick $f -coalesce -resize 24x110! -scale 116x110! \
        -fill black \
        -draw "
            rectangle 1,0 4,109
            rectangle 6,0 9,109
            rectangle 11,0 14,109
            rectangle 16,0 19,109
            rectangle 21,0 24,109
            rectangle 26,0 29,109
            rectangle 31,0 34,109
            rectangle 36,0 39,109
            rectangle 41,0 44,109
            rectangle 46,0 49,109
            rectangle 51,0 54,109
            rectangle 56,0 59,109
            rectangle 61,0 64,109
            rectangle 66,0 69,109
            rectangle 71,0 74,109
            rectangle 76,0 79,109
            rectangle 81,0 84,109
            rectangle 86,0 89,109
            rectangle 91,0 94,109
            rectangle 96,0 99,109
            rectangle 101,0 104,109
            rectangle 106,0 109,109
            rectangle 111,0 114,109
        " $stretch2
    # alternate version of shutter that is not as wide
    shutter2="${basename}f.${f##*.}"
    echo $shutter2
    [ ! -f $shutter2 ] && magick $f -coalesce -resize 116x110! \
        -fill black \
        -draw "
            rectangle 1,0 4,109
            rectangle 6,0 9,109
            rectangle 11,0 14,109
            rectangle 16,0 19,109
            rectangle 21,0 24,109
            rectangle 26,0 29,109
            rectangle 31,0 34,109
            rectangle 36,0 39,109
            rectangle 41,0 44,109
            rectangle 46,0 49,109
            rectangle 51,0 54,109
            rectangle 56,0 59,109
            rectangle 61,0 64,109
            rectangle 66,0 69,109
            rectangle 71,0 74,109
            rectangle 76,0 79,109
            rectangle 81,0 84,109
            rectangle 86,0 89,109
            rectangle 91,0 94,109
            rectangle 96,0 99,109
            rectangle 101,0 104,109
            rectangle 106,0 109,109
            rectangle 111,0 114,109
        " $shutter2
done


# pixel height: 110 pixels = 6 feet = 72"  ... 1.53 pixels per inch
# width = 3 feet * 23 + 1 inch = 829" = 1268 pixels
# 55 pixels per whip


# run time on Nov 2023 M3 Max - 2015.13s user 258.09s system 143% cpu 26:21.30 total
# run time on     2020 M1     - 2699.13s user 196.42s system 143% cpu 33:42.11 total
#
# user 34% faster
# total 28% faster

