import csv

# Função para gerar o código LaTeX para a tabela
def generate_latex_table(data):
    latex_code = (
        "% Please add the following required packages to your document preamble:\n"
        "% \\usepackage{graphicx}\n"
        "\\begin{table}[ht]\n"
        "\\centering\n"
        "\\resizebox{0.75\\textwidth}{!}{%\n"  # Reduzindo a largura para 75% do texto
        "\\begin{tabular}{|cc|c|c|c|c|c|c|}\n"
        "\\hline\n"
        "vertices & edges & Exact & Moreno Et Al & R-BEP (randon) & R-BEP (100) & PG1 (100) & PG1 (100)\\\\ \\hline\n"
    )

    for row in data:
        col3 = float(row[3])
        col4 = float(row[4])
        col5 = float(row[5])
        col6 = float(row[6])
        col7 = float(row[7])


        # Determine the smallest value among columns 3, 4, 5, and 6
        min_value = min(col3, col4, col5, col6, col7)

        # Prepare the output for columns 4, 5, and 6
        formatted_col4 = f"\\textcolor{{blue}}{{{row[4]}}}" if col4 < col3 else row[4]
        formatted_col5 = f"\\textcolor{{blue}}{{{row[5]}}}" if col5 < col3 else row[5]
        formatted_col6 = f"\\textcolor{{blue}}{{{row[6]}}}" if col6 < col3 else row[6]
        formatted_col7 = f"\\textcolor{{blue}}{{{row[7]}}}" if col7 < col3 else row[7]

        # Format the smallest value in bold
        if col4 == min_value:
            formatted_col4 = f"\\textbf{{{formatted_col4}}}"
        if col5 == min_value:
            formatted_col5 = f"\\textbf{{{formatted_col5}}}"
        if col6 == min_value:
            formatted_col6 = f"\\textbf{{{formatted_col6}}}"
        if col7 == min_value:
            formatted_col7 = f"\\textbf{{{formatted_col7}}}"
        if col3 == min_value:
            row3_formatted = f"\\textbf{{{row[3]}}}"
        else:
            row3_formatted = row[3]

        latex_code += f"{row[0]} & {row[1]} & {row[2]} & {row3_formatted} & {formatted_col4} & {formatted_col5} & {formatted_col6} & {formatted_col7}\\\\\n"

    # Finalize the LaTeX table
    latex_code += "\\hline\n\\end{tabular}%\n}\n"
    latex_code += "\\caption{Analise sobre os resultados minimos nas variações do algoritmo R-BEP com a seed fixada.}\n"
    latex_code += "\\label{tab:large_min_seed_100}\n\\end{table}"

    return latex_code

# Função para ler os dados do arquivo CSV
def read_csv_file(filename):
    data = []

    with open(filename, newline='') as csvfile:
        csv_reader = csv.reader(csvfile, delimiter=';')
        next(csv_reader)  # Ignora a primeira linha, que contém os cabeçalhos

        for row in csv_reader:
            data.append(row)

    return data

# Nome do arquivo CSV
filename = 'result-large-seed-100.csv'

# Ler os dados do arquivo CSV
data = read_csv_file(filename)

# Gerar o código LaTeX para a tabela
latex_table = generate_latex_table(data)

# Imprimir o código LaTeX
print(latex_table)