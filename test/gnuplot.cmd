set xrange [0:200]
set yrange [0:200]
unset mouse
set title 'The set of raw points in the set' font 'Arial,12'
set style line 1 pointtype 7 linecolor rgb 'red'
set style line 2 pointtype 7 linecolor rgb 'green'
set style line 3 pointtype 7 linecolor rgb 'black'
plot '-' ls 1 with points notitle
165 36
69 174
177 156
131 198
157 153
90 129
111 52
103 84
99 148
100 140
148 199
187 9
87 166
189 6
167 124
43 81
110 63
4 86
169 85
33 125
e
pause -1 'Hit OK to move to the next state!'
set title 'The points partitioned into an upper and lower hull' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 2 with points notitle, '-' ls 3 with linespoints notitle
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
4 86
189 6
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
33 125
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
43 81
33 125
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
69 174
43 81
33 125
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
69 174
33 125
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
87 166
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
90 129
87 166
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
99 148
90 129
87 166
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
99 148
87 166
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
100 140
99 148
87 166
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
103 84
100 140
99 148
87 166
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
110 63
103 84
100 140
99 148
87 166
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
110 63
100 140
99 148
87 166
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
110 63
99 148
87 166
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
111 52
110 63
99 148
87 166
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
131 198
111 52
110 63
99 148
87 166
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
131 198
110 63
99 148
87 166
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
131 198
99 148
87 166
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
131 198
87 166
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
131 198
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
148 199
131 198
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
157 153
148 199
131 198
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
165 36
157 153
148 199
131 198
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
167 124
165 36
157 153
148 199
131 198
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
167 124
157 153
148 199
131 198
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
167 124
148 199
131 198
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
169 85
167 124
148 199
131 198
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
177 156
169 85
167 124
148 199
131 198
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
177 156
167 124
148 199
131 198
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
177 156
148 199
131 198
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
187 9
177 156
148 199
131 198
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
189 6
187 9
177 156
148 199
131 198
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
189 6
177 156
148 199
131 198
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Complete' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
189 6
e
4 86
189 6
e
189 6
177 156
148 199
131 198
69 174
4 86
e
33 125
43 81
69 174
87 166
90 129
99 148
100 140
103 84
110 63
111 52
131 198
148 199
157 153
165 36
167 124
169 85
177 156
187 9
e
pause -1 'Hit OK to move to the next state!'
