#pragma once

#define         _WIN32_WINNT 0x0A00
#define         _CRT_SECURE_NO_WARNINGS
#define         _ARFNETO_ CH2019

#include <windows.h>
#include <tlhelp32.h>

#include "stdio.h"
#include "stdlib.h"
#include "tchar.h"
#include "time.h"
#include "wchar.h"

// define para as cores para simplificar
#define		_preto_            0
#define		_azul_             1
#define		_verde_            2
#define		_ciano_            3
#define		_vermelho_         4
#define		_magenta_          5
#define		_marron_           6
#define		_cinza_claro_      7
#define		_cinza_escuro_     8
#define		_azul_claro_       9
#define		_verde_claro_     10
#define		_ciano_claro_     11
#define		_vermelho_claro_  12
#define		_magenta_claro_   13
#define		_amarelo_         14
#define		_branco_          15


// funces para a console
char		choice();
int			cls();
WORD		cor_atual_fundo();
WORD		cor_atual_letras();
void        flush();
void		gotoYX(int, int);
void		mensagem_em_video_reverso(char* mensagem);
void		mensagem_em_cores(char*, const char, const char);
void        mostra_grade_256_cores();
void		pause();
void		restaura_cores(int);
void		text_color(int, int);

