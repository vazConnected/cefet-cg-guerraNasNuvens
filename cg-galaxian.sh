function excluirArquivosDesnecessarios {
    echo -e "\nExcluindo arquivos desnecessarios..."

    # rm -f $(pwd)/src/bibliotecas/jogador.o

    echo -e "Feito!"
}

clear
echo -e "\nCaro, $(whoami)O processo de compilacao foi inciado.\n"

echo -e "Compilando src/main.c"
gcc -c -o src/cg-galaxian.o src/main.c
if [ $? -ne 0 ]; then
    excluirArquivosDesnecessarios
    exit 1
fi

echo -e "\nCompilacao Finalizada!"
excluirArquivosDesnecessarios

echo -e "\nIniciando jogo...\n"
./src/cg-galaxian.o

echo -e "\nProcesso finalizado!\n"

exit 0