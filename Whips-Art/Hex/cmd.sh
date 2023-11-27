# There are two options for resizing, using -resize or -sample.
# -resize does smoothing, preserving more of the effect but looking blurrier.
# -sample samples individual pixels, preserving sharp colors but looking very jittery by comparison.
# we may need to play it by ear in terms of which one looks better.

parallel -j 8 'if [ ! -f {.}-resize.gif ]; then convert {} -coalesce -resize 24x110! -rotate 90 {.}-resize.gif; fi' ::: raw/[hp]*[0-9].*
parallel -j 8 'if [ ! -f {.}-sample.gif ]; then convert {} -coalesce -sample 24x110! -rotate 90 {.}-sample.gif; fi' ::: raw/[hp]*[0-9].*

# generate two previews of each of these, one at 116x110 and one at 1268x110, so we can see what they look like

parallel -j 8 'if [ ! -f {.}-resize-pn.gif ]; then convert {} -coalesce -resize 24x110! -scale 116x110!  -fill black -draw "
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
         " {.}-resize-pn.gif; fi' ::: raw/[hp]*[0-9].*
parallel -j 8 'if [ ! -f {.}-resize-pw.gif ]; then convert {} -coalesce -resize 24x110! -scale 1268x110! -fill black -draw "
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
         " {.}-resize-pw.gif; fi' ::: raw/[hp]*[0-9].*
parallel -j 8 'if [ ! -f {.}-sample-pn.gif ]; then convert {} -coalesce -sample 24x110! -scale 116x110!  -fill black -draw "
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
         " {.}-sample-pn.gif; fi' ::: raw/[hp]*[0-9].*
parallel -j 8 'if [ ! -f {.}-sample-pw.gif ]; then convert {} -coalesce -sample 24x110! -scale 1268x110! -fill black -draw "
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
         " {.}-sample-pw.gif; fi' ::: raw/[hp]*[0-9].*







# pixel height: 110 pixels = 6 feet = 72"  ... 1.53 pixels per inch
# width = 3 feet * 23 + 1 inch = 829" = 1268 pixels

