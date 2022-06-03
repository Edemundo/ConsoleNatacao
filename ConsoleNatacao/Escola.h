// Declarações do programa Escola de Natação
#include <iostream>
#include <windows.h>
using namespace std;
// Definições
#define PAUSA				system("pause")
#define LIMPAR_TELA			system("cls")
// Delimitação do programa
#define QTDE_PERIODOS		3			// quantidade de períodos (1 - manhã, 2 - tarde e 3 - noite)
#define QTDE_MINIMA_RAIAS_PISCINA	5	// quantidade minima de raias da piscina
#define QTDE_MAXIMA_RAIAS_PISCINA	10	// quantidade máxima de raias da piscina
#define PERIODO_MANHA		1			// período da manhã
#define PERIODO_TARDE		2			// período da tarde
#define PERIODO_NOITE		3			// período da noite
#define RAIA_LIVRE				false
#define RAIA_OCUPADA			true
// opções do menu
#define MATRICULAR_ALUNO		'M'			
#define CANCELAR_MATRICULA		'C'
#define EXIBIR_DADOS_ALUNO		'E'
#define LISTAR_PERIODO			'P'
#define SAIR_DO_PROGRAMA		'S'
// valores e descontos de mensalidade
#define VALOR_MENSALIDADE			157.50	// valor da mensalidade do primeiro da família
#define VALOR_DESCONTO_POR_PARENTE	10		// porcentagem de desconto para cada parente com o mesmo sobrenome
#define EXTENSAO_NOME			20			
#define EXTENSAO_SOBRENOME		20
// caminho dos arquivos do programa
#define CAMINHO_QUANTIDADE		"..\\QtdeRaias.arq"
#define CAMINHO_RAIA			"..\\Raia.arq"

// struct para quantidade de raias da piscina
typedef struct tagQTDE_RAIAS
{
	int nQtdeRaias;							// quantidade de raias da piscina
} QTDE_RAIAS;

// struct para cada aluno da escola
typedef struct tagRAIA
{
	int	nPeriodo,							// períodos da escola (1, 2 e 3 - manhã tarde e noite
		nRaia;								// raia de 1, 2, 3, .......quantidade de raias da piscina
	bool flgRaiaOcupada;					// true indica que raia ocupada e false raia livre
	char cNome[EXTENSAO_NOME + 1],			// nome do aluno
		cSobreNome[EXTENSAO_SOBRENOME + 1];	// sobrenome do aluno (para dar desconto de família)
	double dVlrMensalidade;					// valor da mensalidade
} RAIA;										// struct de cada raia da piscina nos três períodos

// protótipos das funções
bool PedirPeriodoRaia(int *ptrPeriodo, int *ptrRaia,
	int nQtdePeriodos, int nQtRaiasPiscina, char *ptrAcao);
int BuscarRaiaLivreNoPeriodo(int nPeriodo, int nQtRaiasPiscina, RAIA *ptrStRaia, FILE *fdRaia);
int PedirPeriodo(int nQtdePeriodos, char *ptrAcao);
int VerificaParentes(char *ptrSobrenome, FILE *fdRaia, int  QtdRaias);
bool GravaPosicional(int nPosicional, RAIA *ptrStRaia, FILE *fdRaia);
bool LerPosicional(int nPosicional, RAIA *ptrStRaia, FILE *fdRaia);
