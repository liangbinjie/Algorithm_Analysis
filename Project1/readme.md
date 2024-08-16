

> Ask for input: it only accepts 16 capital letters

> Que pasa si ingresa mas de 16 caracteres en mayuscula?


> Ejecutar los algoritmos y mostrar tabla de ejecucion

    > La tabla de ejecucion debe mostrar en negrita y subrayado las letras que cambiaron de posicion


Despues de corrido su programa,  ́ no se deben borrar ni el fuente
de LATEX ni el PDF generados.

Salida:
\newcommand{\C}[1]{\texttt{#1}}
\newcommand{\B}[1]{\textbf{\C{#1}}}
\newcommand{\X}[1]{\textbf{\underline{\C{#1}}}}
\begin{table}[]
\begin{tabularx}{\columnwidth}{cXXXXXXXXXXXXXXXX}
& \B{-} & \B{-} & \B{-} & \B{-} & \B{-} & \B{-} & \B{-} & \B{-} & \B{-} & \B{-} & \B{1} & \B{1} & \B{1} & \B{1} & \B{1} & \B{1}\\
& \B{0} & \B{1} & \B{2} & \B{3} & \B{4} & \B{5} & \B{6} & \B{7} & \B{8} & \B{9} & \B{0} & \B{1} & \B{2} & \B{3} & \B{4} & \B{5}\\
\hline
& \B{L} & \B{D} & \B{Q} & \B{F} & \B{D} & \B{R} & \B{N} & \B{Q} & \B{S} & \B{D} & \B{W} & \B{A} & \B{L} & \B{O} & \B{K} & \B{D}\\
\hline
{\bf 1}& \X{D} & \X{L} & \C{Q} & \C{F} & \C{D} & \C{R} & \C{N} & \C{Q} & \C{S} & \C{D} & \C{W} & \C{A} & \C{L} & \C{O} & \C{K} & \C{D}\\
{\bf 2}& \C{D} & \C{L} & \X{F} & \X{Q} & \C{D} & \C{R} & \C{N} & \C{Q} & \C{S} & \C{D} & \C{W} & \C{A} & \C{L} & \C{O} & \C{K} & \C{D}\\
{\bf 3}& \X{D} & \X{F} & \X{L} & \X{Q} & \C{D} & \C{R} & \C{N} & \C{Q} & \C{S} & \C{D} & \C{W} & \C{A} & \C{L} & \C{O} & \C{K} & \C{D}\\
{\bf 4}& \C{D} & \C{F} & \C{L} & \C{Q} & \X{D} & \X{R} & \C{N} & \C{Q} & \C{S} & \C{D} & \C{W} & \C{A} & \C{L} & \C{O} & \C{K} & \C{D}\\
{\bf 5}& \C{D} & \C{F} & \C{L} & \C{Q} & \C{D} & \C{R} & \X{N} & \X{Q} & \C{S} & \C{D} & \C{W} & \C{A} & \C{L} & \C{O} & \C{K} & \C{D}\\
{\bf 6}& \C{D} & \C{F} & \C{L} & \C{Q} & \X{D} & \X{N} & \X{Q} & \X{R} & \C{S} & \C{D} & \C{W} & \C{A} & \C{L} & \C{O} & \C{K} & \C{D}\\
{\bf 7}& \X{D} & \X{D} & \X{F} & \X{L} & \X{N} & \X{Q} & \X{Q} & \X{R} & \C{S} & \C{D} & \C{W} & \C{A} & \C{L} & \C{O} & \C{K} & \C{D}\\
{\bf 8}& \C{D} & \C{D} & \C{F} & \C{L} & \C{N} & \C{Q} & \C{Q} & \C{R} & \X{D} & \X{S} & \C{W} & \C{A} & \C{L} & \C{O} & \C{K} & \C{D}\\
{\bf 9}& \C{D} & \C{D} & \C{F} & \C{L} & \C{N} & \C{Q} & \C{Q} & \C{R} & \C{D} & \C{S} & \X{A} & \X{W} & \C{L} & \C{O} & \C{K} & \C{D}\\
{\bf 10}& \C{D} & \C{D} & \C{F} & \C{L} & \C{N} & \C{Q} & \C{Q} & \C{R} & \X{A} & \X{D} & \X{S} & \X{W} & \C{L} & \C{O} & \C{K} & \C{D}\\
{\bf 11}& \C{D} & \C{D} & \C{F} & \C{L} & \C{N} & \C{Q} & \C{Q} & \C{R} & \C{A} & \C{D} & \C{S} & \C{W} & \X{L} & \X{O} & \C{K} & \C{D}\\
{\bf 12}& \C{D} & \C{D} & \C{F} & \C{L} & \C{N} & \C{Q} & \C{Q} & \C{R} & \C{A} & \C{D} & \C{S} & \C{W} & \C{L} & \C{O} & \X{D} & \X{K}\\
{\bf 13}& \C{D} & \C{D} & \C{F} & \C{L} & \C{N} & \C{Q} & \C{Q} & \C{R} & \C{A} & \C{D} & \C{S} & \C{W} & \X{D} & \X{K} & \X{L} & \X{O}\\
{\bf 14}& \C{D} & \C{D} & \C{F} & \C{L} & \C{N} & \C{Q} & \C{Q} & \C{R} & \X{A} & \X{D} & \X{D} & \X{K} & \X{L} & \X{O} & \X{S} & \X{W}\\
{\bf 15}& \X{A} & \X{D} & \X{D} & \X{D} & \X{D} & \X{F} & \X{K} & \X{L} & \X{L} & \X{N} & \X{O} & \X{Q} & \X{Q} & \X{R} & \X{S} & \X{W}\\
\end{tabularx}
\caption{Traza de Ejecuci ́on de \textbf{Merge Sort}}
\label{T:merge}
\end{table}