// Programa Escola de Natação - Prova N2 - 07/12/2016 - Turma da Noite
// FATEC-MC - Linguagem de Programação - Prof. José Carlos Bortot
//
#include "Escola.h"
//	Entry point do programa
//
void main(void)
{
	int nPeriodo,								// periodo da aula de natação
		nRaia,									// raia da piscina
		nPosicionalRaia,						// posicional da raia dentro do arquivo de raias
		nQtdeParentes,							// quantidade de parentes para desconto
		nQtdeTotalDeRaias,						// qtde total de raias nos três períodos
		i, j, k;								// índices genéricos
	FILE *fdQuantidade,							// file descriptor para o arquivo de quantidade de raias da piscina
		*fdRaia;								// file descriptor da raia da piscina
	RAIA stRaia;								// struct para conter os dados de uma raia
	QTDE_RAIAS stQtRaias;						// struct para conter os dados da qtde raias da piscina
	double dValorMensalidade;					// para calcular a mensalidade
	char cOpcao,								// opcao do operador
		cNomeAluno[] = "Victor de Souza Gomes Martins", // para conter o nome do aluno que está fazendo a prova
		cWork[200];								// para sprintf_s
	SYSTEMTIME stTime;							// para data e hora do sistema
	char vetNomesPeriodos[QTDE_PERIODOS][7] =
	{ "Manhã", "Tarde", "Noite" };
	// para duas casas decimais nos valores
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	setlocale(LC_ALL, "portuguese_brazil");		// para acentuação brasileira
	// <<<1>>> - Digitar o seu nome na variável cNomeAluno.


	// <<<2>>> - Tratamento inicial dos arquivos de quantidade e raias.
	// <<<<<<< este tópico foi inteiramente codificado abaixo >>>>>>>>>

	//	2.1 - Abrir o arquivo de quantidades em modo r+b e testar se ele existe.
	//	2.2 - Se ele não existir o arquivo de quantidades:
	//		2.2.1 - Abrir o arquivo de quantidades em modo w+b e testar se foi aberto com sucesso.
	//		2.2.2 - Se o arquivo não foi aberto com sucesso:
	//			2.2.2.1 - Avisar o operador e abortar o programa.
	//		2.2.3 - Se o arquivo foi aberto com sucesso
	//			2.2.3.1 - Fazer um loop para obter uma quantidade de raias da piscina válida
	//						porque tem um mínimo e máximo no .h. Essa quantidade tem que ser
	//						armazenada na stQtRaias
	//			2.2.3.2 - Gravar stQtRaias no arquivo de quantidades e fechar o arquivo.
	//		2.2.4 - Abrir o arquivo de raias em modo w+b e testar se foi aberto com sucesso
	//			2.2.4.1 - Se houve erro de abertura avisar o operador e abortar o programa
	//			2.2.4.2 - Se o arquivo foi aberto com sucesso fazer um loop para gravar o
	//					  registro de cada raia (stRaia) indicando o período e a raia 
	//						1 e 1 - Manhã raia 1
	//						1 e 2 - Manhã raia 2 .....
	//						1 e qtde raias da piscina - Manhã e raia stQtRaias.nQtdeRaias
	//						2 e 1 - Tarde raia 1
	//						2 e 2 - Tarde raia 2
	//						2 e qtde raias da piscina - Tarde e raia stQtRaias.nQtdeRaias
	//						Idem para o período da noite....
	//					  Para cada raia a ser gravada indicar que a raia não está ocupada.
	//			2.2.4.3 - Se houver erro de gravação fechar o arquivo de raias, avisar o
	//					  operador e abortar a execução do programa
	//	
	//	2.3 - Se o arquivo de quantidades existir:
	//		2.3.1 - Ler a quantidade para stQtRaias e fechar o arquivo.
	//		2.3.2 - Abrir o arquivo de raias em modo r+b e testar se foi aberto com sucesso
	//			2.3.2.1 - Se houve erro de abertura avisar ao operador e abortar a execução do programa
	//			2.3.2.2 - Se o arquivo foi aberto com sucesso ir para o menu do operador
	//
	if (fopen_s(&fdQuantidade, CAMINHO_QUANTIDADE, "r+b") != 0)	// erro de abertura?
	{	// erro de abertura porque é a primeira vez da execução do programa
		if (fopen_s(&fdQuantidade, CAMINHO_QUANTIDADE, "w+b") != 0) // erro irrecuperável?
		{	// erro irrecuperável de abertura
			cout << "Erro irrecuperável do arquivo: " << CAMINHO_QUANTIDADE << endl;
			PAUSA;
			return;													// retorna ao sistema operacional
		}
		// loop para pedir a quantidade de raias da piscina
		cout << "\n\t\tConfiguração da Escola de Natação" << endl;
		do
		{
			cout << "\tQuantidade de raias da piscina entre " << QTDE_MINIMA_RAIAS_PISCINA << " e "
				<< QTDE_MAXIMA_RAIAS_PISCINA << ": ";
			cin >> stQtRaias.nQtdeRaias;							// recebe a quantidade de raias
		} while (stQtRaias.nQtdeRaias < QTDE_MINIMA_RAIAS_PISCINA ||
			stQtRaias.nQtdeRaias > QTDE_MAXIMA_RAIAS_PISCINA);
		// temos uma quantidade válida de raias
		if (fwrite(&stQtRaias, sizeof(QTDE_RAIAS), 1, fdQuantidade) == 0) // erro de gravação?
		{	// erro irrecuperável de gravação
			fclose(fdQuantidade);								// fechar o arquivo
			cout << "Erro irrecuperável gravação arquivo: " << CAMINHO_QUANTIDADE << endl;
			PAUSA;
			return;												// volta ao sistema operacional
		}
		fclose(fdQuantidade);									// fechar arquivo
		nQtdeTotalDeRaias = stQtRaias.nQtdeRaias * QTDE_PERIODOS; // qtde total de raias
		// vai inicializar o arquivo de raias da piscina
		if (fopen_s(&fdRaia, CAMINHO_RAIA, "w+b") != 0)			// erro irrecuperável de abertura?
		{	// erro irrecuperável de abertura
			cout << "Erro irrecuperável de abertura do arquivo: " << CAMINHO_RAIA << endl;
			PAUSA;
			return;												// volta ao sistema operacional
		}

		// loop de gravação de todas as raias nos periodos manhã, tarde e noite.
		for (i = 0; i < nQtdeTotalDeRaias;)						  // loop de todas as raias
		{
			for (j = 1; j <= PERIODO_NOITE;)					  // loop por período
			{
				for (k = 1; k <= stQtRaias.nQtdeRaias; k++, i++)	  // loop de gravação de cada raia em cada periodo
				{
					stRaia.nPeriodo = j;						  // periodo
					stRaia.nRaia = k;							  // raia
					stRaia.flgRaiaOcupada = RAIA_LIVRE;			  // indica que a raia está livre
					stRaia.cNome[0] = NULL;
					stRaia.cSobreNome[0] = NULL;
					stRaia.dVlrMensalidade = 0.0;
					if (fwrite(&stRaia, sizeof(RAIA), 1, fdRaia) == 0) // erro de gravação?
					{	// erro irrecuperável de gravação
						fclose(fdRaia);							 // fechar o arquivo
						cout << "Erro de gravação do arquivo: " << CAMINHO_RAIA << endl;
						PAUSA;
						return;									 // volta ao Sistema Operacional
					}
				} // for k - loop dentro do período
				j++;											  // próximo periodo
			} // for j - loop por período
		} // for i - todas raias
		// para garantir que o arquivo de raias seja gravado
		fclose(fdRaia);						// fechar o arquivo 
		// vai reabrir agora com todas as rais inicializadas.
		if (fopen_s(&fdRaia, CAMINHO_RAIA, "r+b") != 0)			 // erro de abertura?
		{	// erro irrecuperável de abertura do arquivo de raias
			cout << "O arquivo de raias não existe!" << endl;
			PAUSA;
			return;												 // volta ao Sistema Operacional
		}
		LIMPAR_TELA;
		cout << "\n\tA escola de natação foi configurada com:" << endl
			<< "\n\t\tQuantidade de raias da piscina: " << stQtRaias.nQtdeRaias << endl
			<< "\n\t\tForam gravados " << nQtdeTotalDeRaias << " para os três períodos" << endl
			<< endl << "\t\t";
		PAUSA;
	}	// primeira vez
	else
	{	// não é a primeira vez da execução do programa
		if (fread_s(&stQtRaias, sizeof(QTDE_RAIAS), sizeof(QTDE_RAIAS), 1, fdQuantidade) == 0) // erro leitura?
		{	// erro de leitura
			fclose(fdQuantidade);								// fechar arquivo
			cout << "Erro de leitura do arquivo: " << CAMINHO_QUANTIDADE << endl;
			PAUSA;
			return;												// volta ao sistema operacional
		}
		fclose(fdQuantidade);									// fechar o arquivo
		nQtdeTotalDeRaias = stQtRaias.nQtdeRaias * QTDE_PERIODOS; // quantidade total de raias nos periodos
		// vai abrir o arquivo de raias em modo leitura e gravação
		if (fopen_s(&fdRaia, CAMINHO_RAIA, "r+b") != 0)			 // erro de abertura?
		{	// erro irrecuperável de abertura do arquivo de raias
			cout << "O arquivo de raias não existe!" << endl;
			PAUSA;
			return;												 // volta ao Sistema Operacional
		}
	}
	//	Loop Infinito
	while (true)
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);						// data e hora do sistema
		sprintf_s(cWork, sizeof(cWork),
			"\n\tFATEC-MC - Escola de Natação %02d/%02d/%04d às %02d:%02d:%02d\n\tOperador: %s",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno);
		cout << cWork << endl;
		// exibir o menu
		cout << MATRICULAR_ALUNO << " - Matricular aluno em um período desejado" << endl
			<< CANCELAR_MATRICULA << " - Cancelar a matrícula de um aluno" << endl
			<< EXIBIR_DADOS_ALUNO << " - Exibir os dados de um aluno" << endl
			<< LISTAR_PERIODO << " - Listar os alunos de um dado período" << endl
			<< SAIR_DO_PROGRAMA << " - Sair do programa" << endl
			<< "\tSelecione: ";
		cin >> cOpcao;
		cOpcao = toupper(cOpcao);					// converte para maiúscula
		switch (cOpcao)								// avalia a opção escolhida
		{
		case MATRICULAR_ALUNO:
			// grande parte já codificado 

			nPeriodo = PedirPeriodo(QTDE_PERIODOS, "Matricular Aluno");
			if (nPeriodo == 0)					// cancelou a ação?
				break;							// cai fora do switch
			// chamar a função que vê se tem raia livre neste periodo
			nRaia = BuscarRaiaLivreNoPeriodo(nPeriodo, stQtRaias.nQtdeRaias, &stRaia, fdRaia);
			stRaia.nRaia = nRaia;

			// verificar se não tem raia livre neste periodo
			if (nRaia == 0)						// não tem raia livre?
			{	// não tem raia livre neste período
				cout << "Não tem vaga no periodo da " << vetNomesPeriodos[nPeriodo - 1] << endl;
				PAUSA;
				break;
			}
			//
			// pedir o nome e sobrenome com cin.getline e armazenar em
			//	stRaia.cNome e stRaia.cSobreNome com extensões: EXTENSAO_NOME e
			//		EXTENSAO_SOBRENOME
			//
			cin.ignore(1, EOF);									// ignorar a tecla ENTER
			//
			cout << "Informe o nome do aluno: ";
			// codificar abaixo a instrução de cin.getline do nome
			cin.getline(stRaia.cNome, EXTENSAO_NOME, '\n');
			cout << "Informe o sobrenome do aluno: ";
			// codificar abaixo a instrução de cin.getline do sobrenome
			cin.getline(stRaia.cSobreNome, EXTENSAO_SOBRENOME, '\n');

			// vai calcular o valor da mensalidade em função da quantidade de parentes da
			//	mesma família
			nQtdeParentes = VerificaParentes(stRaia.cSobreNome, fdRaia, stQtRaias.nQtdeRaias);

			// calcular o valor da mensalidade sabendo que o valor básico está em 
			//		VALOR_MENSALIDADE e a cada parente (nQtdeParentes) é dado um
			// desconto de 10% até no máximo de 40% se tiver 4 parentes com o mesmo
			//	sobrenome). Copiar o valor calculado em stRaia.dVlrMensalidade

			if (nQtdeParentes == 0)
				stRaia.dVlrMensalidade = VALOR_MENSALIDADE;
			else if (nQtdeParentes == 1)
				stRaia.dVlrMensalidade = (VALOR_MENSALIDADE - ((VALOR_MENSALIDADE * VALOR_DESCONTO_POR_PARENTE) / 100));
			else if (nQtdeParentes == 2)
				stRaia.dVlrMensalidade = (VALOR_MENSALIDADE - ((VALOR_MENSALIDADE * (2 * VALOR_DESCONTO_POR_PARENTE)) / 100));
			else if (nQtdeParentes == 3)
				stRaia.dVlrMensalidade = (VALOR_MENSALIDADE - ((VALOR_MENSALIDADE * (3 * VALOR_DESCONTO_POR_PARENTE)) / 100));
			else if (nQtdeParentes > 3)
				stRaia.dVlrMensalidade = (VALOR_MENSALIDADE - ((VALOR_MENSALIDADE * (4 * VALOR_DESCONTO_POR_PARENTE)) / 100));

			//
			// calcular o indice desta raia para saber o posicional da raia dentro do arquivo de
			//	raias - é função do periodo, quantidade de raias da piscina e a raia da piscina
			//	que retornou da função BuscarRaiaLivreNoPeriodo

			nPosicionalRaia = ((nPeriodo - 1) * stQtRaias.nQtdeRaias) + (nRaia-1);

			// armazenar este cálculo em nPosicionalRaia para a chamada da função
			//		GravaPosicional codificada logo abaixo

			stRaia.flgRaiaOcupada = RAIA_OCUPADA;					// indica que a raia está ocupada
			if (!GravaPosicional(nPosicionalRaia, &stRaia, fdRaia)) // erro de gravação?
			{
				cout << "Erro de gravação!" << endl;
				PAUSA;
				break;										// volta ao menu
			}

			// Indicar em que raia do período o aluno foi matriculado
			cout << "Aluno: " << stRaia.cNome << " " << stRaia.cSobreNome << endl
				<< "Foi matriculado no período: " << vetNomesPeriodos[nPeriodo - 1] << " raia: "
				<< stRaia.nRaia << endl;
			PAUSA;
			break;								// cai fora do switch e volta ao menu
		case CANCELAR_MATRICULA:
			// <<<9>>>  Chamar a função que pede o periodo e a raia indicando que a ação é
			//			Cancelamento de Matrícula - função PedirPeriodoRaia
			//		
			if (!PedirPeriodoRaia(&nPeriodo, &nRaia, QTDE_PERIODOS, stQtRaias.nQtdeRaias, "Cancelar Matricula"))
			{
				cout << "Periodo ou raia inválido" << endl;
				PAUSA;
				break;
			}

			//			Calcular o posicional para está raia.
			nPosicionalRaia = ((nPeriodo - 1) * stQtRaias.nQtdeRaias) + (nRaia - 1);

			//			Chamar a função que lê posicional

			if(!LerPosicional(nPosicionalRaia, &stRaia, fdRaia))
			{
				cout << "\nErro de Leitura!" << endl;
				PAUSA;
				break;														// volta ao menu
			}

			//			Verificar se a raia está ocupada
			//			Se não estiver ocupada avisar ao operador e voltar ao menu
			if (stRaia.flgRaiaOcupada == false)
			{
				cout << "Essa raia não está ocupada!" << endl;
				PAUSA;
				break;
			}

			//			Se estiver ocupada, exibir todos os dados da raia e
			//				pedir a confirmação do cancelamento com S ou N.
			//			Se o operador confirmar com S ou s, gravar a raia com a função
			//				gravar posicional.
			//			voltar ao menu principal

			cout << "Aluno: " << stRaia.cNome << " " << stRaia.cSobreNome << endl
				<< "Matriculado no período: " << vetNomesPeriodos[nPeriodo - 1] << " raia: "
				<< stRaia.nRaia << endl << "Tem certeza que deseja cancelar a matricula?" << endl
				<< "Digite S(Sim) para cancelar ou qualquer outra tecla para continuar: ";
			cin >> cOpcao;

			if (cOpcao == 's' || cOpcao == 'S')
			{
				stRaia.flgRaiaOcupada = RAIA_LIVRE;
				if (!GravaPosicional(nPosicionalRaia, &stRaia, fdRaia)) // erro de gravação?
				{
					cout << "Erro de gravação!" << endl;
					PAUSA;
					break;										// volta ao menu
				}
				cout << "Matricula Cancelada com sucesso!" << endl;
				PAUSA;
				break;

			}
			
			break;								// cai fora do switch e volta ao menu
		case EXIBIR_DADOS_ALUNO:
			// <<<10>>>  Chamar a função que pede o periodo e a raia indicando que a ação é
			//			Mostrar dados do aluno - função PedirPeriodoRaia

			if (!PedirPeriodoRaia(&nPeriodo, &nRaia, QTDE_PERIODOS, stQtRaias.nQtdeRaias, "Cancelar Matricula"))
			{
				cout << "Periodo ou raia inválido" << endl;
				PAUSA;
				break;
			}

			//			Calcular o posicional para está raia.

			nPosicionalRaia = ((nPeriodo - 1) * stQtRaias.nQtdeRaias) + (nRaia - 1);

			//			Chamar a função que lê posicional

			if (!LerPosicional(nPosicionalRaia, &stRaia, fdRaia))
			{
				cout << "\nErro de Leitura!" << endl;
				PAUSA;
				break;														// volta ao menu
			}

			//			Verificar se a raia está ocupada
			//			Se não estiver ocupada avisar ao operador e voltar ao menu

			if (stRaia.flgRaiaOcupada == false)
			{
				cout << "Essa raia não está ocupada!" << endl;
				PAUSA;
				break;
			}

			//			Se estiver ocupada, exibir todos os dados da raia e dar uma pausa

			sprintf_s(cWork, sizeof cWork, "Raia Nome        Sobrenome  Vlr. Mensalidade");
			cout << cWork << endl;

			sprintf_s(cWork, sizeof cWork, "%-5d %-12s %-11s %8.2f", stRaia.nRaia,
						stRaia.cNome, stRaia.cSobreNome, stRaia.dVlrMensalidade);
			cout << cWork << endl;
			PAUSA;

			break;								// voltar ao menu
		case LISTAR_PERIODO:
			// <<<15>>> Pedir um período válido ou zero para cancelar a ação de listar
			//				função PedirPeriodo

			nPeriodo = PedirPeriodo(QTDE_PERIODOS, "Matricular Aluno");
			if (nPeriodo == 0)					// cancelou a ação?
				break;							// cai fora do switch

			//			Se foi informado um período válido listar todos as raias ocupadas
			//			no seguinte formato:
			//				Listagem das raias do periodo: ppppppp
			//			Raia Nome        Sobrenome  Vlr. Mensalidade 
			//			 RR  NNNNNNNNNN  SSSSSSSSS  MMMMMM,MM	
			//			.....
			//			.....
			//					       Total das Mensalidades: TTTTTT,TT
			//			Onde: PPPPPPP - periodo: "Manhã", "Tarde" ou "Noite" por extenso
			//				  RR - raia ocupada ( 1 a Qtde de Raias da Piscina)
			//				  NNNNNNNNN - nome do aluno matriculado 
			//				  SSSSSSSSS - sobrenome do aluno matriculado
			//				  MMMMM - valor da mensalidade
			//				  TTTTTTT = somatória das mensalidades dos alunos matriculados
			//		Para essa listagem considerar o seguinte:
			//		Calcular o posicional para a primeira raia do periodo.
			//		Fazer um looping lendo posicional de cada raia do periodo e
			//			listar no formato acima pedido se a raia estiver ocupada.
			//		Fazer a somatória de mensalidades deste período.
			
			nPosicionalRaia = ((nPeriodo - 1) * stQtRaias.nQtdeRaias);
			cout << endl;
			if (nPeriodo == 1)
				cout << "\tListagem das raias do periodo: " << "Manhã" << endl;
			else if (nPeriodo == 2)
				cout << "\tListagem das raias do periodo: " << "Tarde" << endl;
			else if (nPeriodo == 3)
				cout << "\tListagem das raias do periodo: " << "Noite" << endl;
			sprintf_s(cWork, sizeof cWork, "Raia  Nome       Sobrenome  Vlr. Mensalidade");
			cout << cWork << endl;

			dValorMensalidade = 0;
			for (i = 0; i < stQtRaias.nQtdeRaias; i++, nPosicionalRaia++)
			{
				if (!LerPosicional(nPosicionalRaia, &stRaia, fdRaia))
				{
					cout << "\nErro de Leitura!" << endl;
					PAUSA;
					break;														// volta ao menu
				}

				if (stRaia.flgRaiaOcupada == true)
				{
					sprintf_s(cWork, sizeof cWork, "%-5d %-10s %-9s %8.2f", stRaia.nRaia,
						stRaia.cNome, stRaia.cSobreNome, stRaia.dVlrMensalidade);
					cout << cWork << endl;

					dValorMensalidade += stRaia.dVlrMensalidade;
				}
			}

			sprintf_s(cWork, sizeof cWork, "               Total das Mensalidades: ");
			cout << cWork;

			sprintf_s(cWork, sizeof cWork, "%8.2f", dValorMensalidade);
			cout << cWork << endl;

			PAUSA;

			break;								// cai fora do switch
		case SAIR_DO_PROGRAMA:
			cout << "\n\tVai sair realmente? (S ou N): ";
			cin >> cOpcao;
			if (cOpcao == 's' || cOpcao == 'S')	// sair realmente?
			{
				fclose(fdRaia);					// ativar quando o programa estiver em 
				// condição de testes.
				return;
			}
			break;								// cai fora do switch
		default:
			cout << "Opção inválida!" << endl;
			PAUSA;
		} // switch
	} // while
} // main
// 
// Funções do Programa
//
// Função que pede um período válido e uma raia da piscina válida
// Parâmetros:
//	Entrada: int *ptrPeriodo - ponteiro para receber o período desejado
//			 int *ptrRaia - ponteiro para receber a raia da piscina desejada
//			 int nQtdePeriodos - quantidade de períodos da Escola de Natação
//			 int nQtRaiasPiscina - quantidade de raias que tem a piscina da Escola de Natação
//			 char *ptrAcao - ponteiro de um string que contém a ação que está sendo executada
//	Retorno: bool - true - indica que foi informado um período e uma raia válidos
//					false - indica que o operador desistiu da ação que iria executar:
bool PedirPeriodoRaia(int *ptrPeriodo, int *ptrRaia,
	int nQtdePeriodos, int nQtRaiasPiscina, char *ptrAcao)
{
	do
	{
		cout << "\n\t" << ptrAcao << endl;
		cout << "Informe o período desejado " << endl <<
			"\t1 - Manhã" << endl << "\t2 - Tarde" << endl << "\t3 - Noite" << endl
			<< "Ou zero para cancelar está ação: ";
		cin >> *(ptrPeriodo);
		if (*(ptrPeriodo) == 0)				// cancelou a ação
			return false;					// indica que cancelou
	} while (*(ptrPeriodo) < PERIODO_MANHA ||
		*(ptrPeriodo) > nQtdePeriodos);
	do
	{
		cout << "Informe a raia entre 1 e " << nQtRaiasPiscina << endl
			<< "Ou zero para cancelar a execução desta ação: ";
		cin >> *(ptrRaia);
		if (*(ptrRaia) == 0)					// cancelou a ação?
			return false;
	} while (*(ptrRaia) < 1 ||
		*(ptrRaia) > nQtRaiasPiscina);
	return true;							// indica que foi digitado um período e uma raia
}
//
// Função que verifica se tem uma raia livre no período desejado
//	Parâmetros:
//		Entrada: int nPeriodo - período desejado
//				 int nQtRaiasPiscina - quantidade de raia que a piscina tem
//				 RAIA *ptrStRaia - ponteiro para uma struct a conter os dados da raia 
//									livre.
//				 FILE *fdRaia - file descriptor do arquivo de raias
//		Retorno: int - Número da raia que está livre ou zero se não existir nenhuma
//						raia livre no período desejado
int BuscarRaiaLivreNoPeriodo(int nPeriodo, int nQtRaiasPiscina, RAIA *ptrStRaia, FILE *fdRaia)
{
	RAIA stRaia;						// buffer de leitura de cada raia
	int i;								// indice genérico
	int nPosicao = (nPeriodo - 1) * nQtRaiasPiscina; // posição inicial do período


	// em função do período desejado e a quantidade de raias da piscina
	//	calcular o posicional da primeira raia do periodo desejado.
	// posicionar com o fseek na primeira raia do período ( se der erro - devolve zero)
	// ficar em looping limitado a qtde de raias da piscina
	// lendo sequencialmente até encontrar uma raia livre
	// Se encontrou uma raia livre devolve o seu número e copie os dados desta raia em
	//		uma struct apontada por ptrStRaia
	// ou devolve zero se não encontrou nenhuma livre.
	if (fseek(fdRaia, nPosicao * sizeof(RAIA), SEEK_SET) != 0)		// erro de seek?
		return 0;													// indica sem raia livre
	for (i = 0; i < nQtRaiasPiscina; i++)
	{	// loop de leitura sequencial
		if (fread_s(ptrStRaia, sizeof(RAIA), sizeof(RAIA), 1, fdRaia) == 0) // erro de leitura?
			return 0;
		if (ptrStRaia->flgRaiaOcupada == RAIA_LIVRE)					// raia livre?
			return ptrStRaia->nRaia;								// indica qual é a raia livre
	} // for i
	return 0;														// não tem raia livre
}

// Função que pede um período válido ou zero para cancelar a ação
//	Parâmetros:
//		Entrada: int nQtdePeriodos - quantidade de períodos da escola de natação
//				 char *ptrAcao - ponteiro para uma string que contem a ação sendo executada
//		Retorno: int - o período desejado ou zero para cancelar a ação
int PedirPeriodo(int nQtdePeriodos, char *ptrAcao)
{
	int nPeriodo;									// para receber o periodo
	do
	{
		cout << "\n\t" << ptrAcao << endl;
		cout << "Informe o período desejado " << endl <<
			"\t1 - Manhã" << endl << "\t2 - Tarde" << endl << "\t3 - Noite" << endl
			<< "Ou zero para cancelar está ação: ";
		cin >> nPeriodo;
	} while (nPeriodo < 0 || nPeriodo > nQtdePeriodos);
	// devolver o que foi válido digitado
	return nPeriodo;								// devolve o digitado
}
// Função que verifica se tem parentes com o mesmo sobrenome
//	Parâmetros:
//		Entrada: char *ptrSobrenome - ponteiro para um string que contém o sobrenome
//				 FILE *fdRaia - ponteiro para o file descriptor do arquivo de raias
//		Retorno: int - contendo a quantidade de parentes com o mesmo sobrenome (máximo de 4).
int VerificaParentes(char *ptrSobrenome, FILE *fdRaia, int QtdRaias)
{
	RAIA stRaia;							// buffer de leitura para cada raia do arquivo
	int nContador = 0,						// contador de parentes com mesmo sobrenome
		i;									// contador para o for e para ser utilizado na função LerPosicional
	// posicionar o arquivo de raias na primeira raia do primeiro período (posicional zero).
	// fazer um loop de leitura sequencial até o fim do arquivo ou até encontrar 4 parentes
	// com o mesmo sobrenome (o máximo de desconto será de 40%)
	// a cada raia lida verificar se está ocupada e se tem o mesmo sobrenome
	// se tiver o mesmo sobrenome somar um no nContador e verificar se chegou a 4.
	// se chegou a 4 retornar este valor.
	// se chegou ao fim do arquivo retornar o nContador.

	for (i = 0; i < (QtdRaias - 1); i++)
	{
		if (!LerPosicional(i, &stRaia, fdRaia))
		{
			cout << "\nErro de Leitura!" << endl;
			PAUSA;
			break;														// volta ao menu
		}
		if (strcmp(ptrSobrenome, stRaia.cSobreNome) == 0)				// iguais?
		{
			nContador++;

			if (nContador == 4)
				return nContador;
		}

	}

	return nContador;					// retornar o que foi encontrado
}

// Função que grava uma raia posicional no arquivo de raias
//	Parâmetros:
//		Entrada: int nPosicional - posicional para gravação da raia
//				 RAIA *ptrStRaia - ponteiro para a struct que contem os dados a serem gravados
//				 FILE *fdRaia - file descriptor do arquivo de raias.
//		Retorno: bool - true a gravação foi realizada OK
//						false - se houve erro de fseek ou fwrite
bool GravaPosicional(int nPosicional, RAIA *ptrStRaia, FILE *fdRaia)
{

	// posicionar na raia através do fseek
	// gravar os dados que foram passados com o fwrite.

	if (fseek(fdRaia, nPosicional * sizeof(RAIA), SEEK_SET))
		return false;

	if (fwrite(ptrStRaia, sizeof(RAIA), 1, fdRaia) == 0)
		return false;

	return true;								// para não dar erro de compilação ????????????
}

// Função que lê uma raia posicional do arquivo de raias
//	Parâmetros:
//		Entrada: int nPosicional - posicional para leitura da raia
//				 RAIA *ptrStRaia - ponteiro para a struct que receberá os dados a serem lidos
//				 FILE *fdRaia - file descriptor do arquivo de raias.
//		Retorno: bool - true a leitura foi realizada OK e os dados estão na struct informada
//						false - se houve erro de fseek ou fread_s
bool LerPosicional(int nPosicional, RAIA *ptrStRaia, FILE *fdRaia)
{

	// posicionar na raia através do fseek
	// ler os dados para a struct que foi passada com fread_s

	if (fseek(fdRaia, nPosicional * sizeof(RAIA), SEEK_SET) != 0)
		return false;									// Indica erro

	if (fread_s(ptrStRaia, sizeof(RAIA), sizeof(RAIA), 1, fdRaia) == 0)
		return false;									// Indica erro

	return true;								// para não dar erro de compilação ????????????
}
