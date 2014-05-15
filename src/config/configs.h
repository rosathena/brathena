/****************************************************************************!
*                _           _   _   _                                       *    
*               | |__  _ __ / \ | |_| |__   ___ _ __   __ _                  *  
*               | '_ \| '__/ _ \| __| '_ \ / _ \ '_ \ / _` |                 *   
*               | |_) | | / ___ \ |_| | | |  __/ | | | (_| |                 *    
*               |_.__/|_|/_/   \_\__|_| |_|\___|_| |_|\__,_|                 *    
*                                                                            *
*                                                                            *
* \file src/config/configs.h                                                 *
* Descri��o Prim�ria.                                                        *
* Descri��o mais elaborada sobre o arquivo.                                  *
* \author brAthena, rAthena                                                  *
* \date ?                                                                    *
* \todo ?                                                                    *  
*****************************************************************************/

#ifndef _VERSION
#define _VERSION
#ifndef _CONFIG_CONFIGS_H_
#define _CONFIG_CONFIGS_H_

/**
 * @INFO: Este arquivo tem o proposito de definir configura��es apenas da renova��o.
 * Para desabilitar uma configura��o, comente a linha que cont�m o #define com //
 **/

/* Define o modo do Emulador [brAthena] *
 *  1 - Renova��o                       *
 *  0 - Pr�-Renova��o                   *
 * -1 - Old-Times                       */
#define VERSION 1

/*		F�rmula de Ataque Base		 *
 *	Valor da constante [ Renova��o ] */
#define RENEWAL_ATK

/// Tempo de conjura��o de habilidades, da renova��o
/// Dentro dos padr�es da renova��o, a conjura��o:
///  - Tem sua f�rmula reduzida por DEX * 2 + INT
///  - O tempo de conjura��o se divide em f�rmula e fixo, cujo o fixo ser� adicionado por habilidades e itens.
#define RENEWAL_CAST

/// Taxa de drop da renova��o
/// A tabela de drops pode ser analisada em: 
#define RENEWAL_DROP

/// Taxa de experi�ncia da renova��o
/// A tabela de experi�ncia pode ser analisada em: 
#define RENEWAL_EXP

/// Taxa de modifica��o do dano conforme o n�vel
#define RENEWAL_LVDMG

/// Habilidade "encantar com veneno mortal" da renova��o
/// Fora dos padr�es da renova��o a habilidade:
///  - N�o ter� o dano reduzido por 400%
///  - N�o ter� efeito de amplifica��o com a habilidade grimtooth
///  - Ataque com armas e status STR (for�a) ser�o aumentados.
#define RENEWAL_EDP

/// Velocidade de ataque da renova��o
/// Dentro dos par�metros da renova��o a velocidade de ataque:
/// - Ter� penalidade e redu��o de velocidade de ataque conforme escudos utilizados.
/// - O status de AGI (agilidade) ter�o grande influ�ncia no c�lculo da f�rmula.
/// - Algumas habilidades e itens mudam a f�rmula de bonificar velocidade de ataque, para valores fixos.
#define RENEWAL_ASPD

#endif // _CONFIG_CONFIGS_H_
#endif // _VERSION
