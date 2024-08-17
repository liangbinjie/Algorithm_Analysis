int size = 16;

const char* tableHeader = 
    "\\begin{table}[ht]\n"
    "\\begin{tabularx}{\\columnwidth}{cXXXXXXXXXXXXXXXX}\n"
    "& \\B{-} & \\B{-} & \\B{-} & \\B{-} & \\B{-} & \\B{-} & \\B{-} & \\B{-} & \\B{-} & \\B{-} & \\B{1} & \\B{1} & \\B{1} & \\B{1} & \\B{1} & \\B{1}\\\\\n"
    "& \\B{0} & \\B{1} & \\B{2} & \\B{3} & \\B{4} & \\B{5} & \\B{6} & \\B{7} & \\B{8} & \\B{9} & \\B{0} & \\B{1} & \\B{2} & \\B{3} & \\B{4} & \\B{5}\\\\\n"
    "\\hline\n";

const char* latexContent = 
    "\\newcommand{\\C}[1]{\\texttt{#1}}\n"
    "\\newcommand{\\B}[1]{\\textbf{\\C{#1}}}\n"
    "\\newcommand{\\X}[1]{\\textbf{\\underline{\\C{#1}}}}\n"
    "\\documentclass[journal]{IEEEtran}\n"
    "\\usepackage{hyperref}\n"
    "\\usepackage{tabularx}\n"
    "\\title{Project 1: An Analysis of Different Sorting Algorithms}\n"
    "\\author{\n"
    "    \\IEEEauthorblockN{Binjie Liang,}\n"
    "    \\IEEEauthorblockA{\n"
    "        \\textit{2023064642}, bliang@estudiantec.cr\n"
    "    }\n"
    "    and\n"
    "    \\IEEEauthorblockN{Esteban Secaida,}\n"
    "    \\IEEEauthorblockA{\n"
    "        \\textit{2019042589}, esecaida@estudiantec.cr\n"
    "    }\n"
    "}\n"
    "% The paper headers\n"
    "\\markboth{IC-3002, Algorithm Analysis, Computer Science, Costa Rica Institute of Technology, Second Semester 2024}{}\n"
    "\\begin{document}\n"
    "\\maketitle\n"
    "\\begin{abstract}\n"
    "This program compares the efficiency of different sorting algorithms. It takes a string of 16 capital letters as input and generates a LaTeX PDF document with a detailed comparison of various sorting algorithms.\n"
    "\\end{abstract}\n";


// function to create the table, with its title and reference
void createTable(FILE *file, char sortName[], char textInput[]) {
    // create section title
    // create table structure
    fprintf(file, "\\section{%s}\n%s\n", sortName, tableHeader);

    // label the input
    for (int i = 0; i < size; i++) {
        fprintf(file, "& \\B{%c} ", textInput[i]);
    }
    fprintf(file, "\\\\\n\\hline\n");
}


// function to close the table
void closeTable(FILE *file, char sortName[]) {
    fprintf(file, "\\end{tabularx}\n\\caption{Execution Trace of \\textbf{%s}}\n\\label{T:%s}\\end{table}\n", sortName, sortName);
}