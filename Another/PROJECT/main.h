//=============================================================================
//
// ���C������ [main.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION (0x0800)
#define _CRT_SECURE_NO_WARNINGS
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "d3dx9.h"   //�`��ɕK�v
#include "dinput.h"  //���͏����ɕK�v
#include "xaudio2.h"   //�T�E���h�֘A

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")   //�`��ɕK�v
#pragma comment(lib,"d3dx9.lib")   //[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")  //DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib") //���͏����ɕK�v

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH (1280)                                          //�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)                                          //�E�B���h�E�̍����@16:9�̃T�C�Y
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1) //���_�t�H�[�}�b�g
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1) //���_�t�H�[�}�b�g

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
//�O���錾
//class CScene2D;

//�v���g�^�C�v�錾
int GetFPS();	//FPS�`��
//CScene2D **GetScene();
#endif